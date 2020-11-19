
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>


//Main define
#define N_GEN 1000
#define N_IND 5000
#define N_EPOCH 5
#define POLYNOM 4

//range of random numbers
#define UPPER 1000
#define LOWER -1000

//Definition of GA
//P stands for percentage
//Sum can't be more than 100
#define P_CROSS 48
#define P_MUT 48

//Load data define thing function
#define FILE_NAME "DataValues.csv"
#define NUM_ROWS 40
#define NUM_COLUMS 2
#define COMA " ,"

void loadData(double (*data)[2]){

  //double data[NUM_ROWS][NUM_COLUMS];
  FILE* data_file = fopen(FILE_NAME, "r");
  char line[NUM_ROWS];
  int i = 0;

  while(fgets(line, sizeof(line), data_file)){
    char* tok = strtok(line, COMA);
    int j = 0;
    while(tok != NULL){

        data[i][j] = atof(tok);   //const char to double
        tok = strtok(NULL, COMA);

        j++;
      }
      i++;
  }
}

void createInitialPop(double (*ind_array)[POLYNOM + 1]){
    for(int i = 0;i < N_IND; i++){
        for(int j = 0; j < POLYNOM; j++){
            ind_array[i][j] = ((double) (rand() % (UPPER -  LOWER +1))+LOWER);
        }
    }
}

void calculateFitnessFunction(double (*data)[2], double (*ind_array)[POLYNOM + 1]){
    for (int i = 0; i < N_IND; i++){
        double arr_polyn[NUM_ROWS];

        for (int j = 0; j < NUM_ROWS; j++){
            double out_polyn = 0;
            for (int k = 0; k < POLYNOM; k++){

                out_polyn += (ind_array[i][k]*(pow(data[j][0], ((double)(POLYNOM-(k+1))))));
            }

            arr_polyn[j] = out_polyn;

        }
        long double fitness_function = 0;
        for(int j = 0; j < NUM_ROWS; j++){
            fitness_function += pow((data[j][1] - arr_polyn[j]), 2);
        }
        ind_array[i][POLYNOM] = fitness_function;
    }
}

void printGeneration(double (*array)[POLYNOM + 1]){
    for(int i = 0; i < N_IND; i++){
        for(int k = 0; k< POLYNOM + 1; k++){

            printf("%f , ",array[i][k]);

        }
        printf("\n");

    }
    printf("---------------------------------\n");
}

//Insertion sort algorithm
void insertionSort(double (*array)[POLYNOM + 1]){
    int arr_lenght = N_IND;
    for(int k = 0; k < arr_lenght - 1; k++){
        for(int i = k + 1; i < arr_lenght; i++){
            if(array[i][4] < array[k][4]){
                //Insert individuals
                double hlp[POLYNOM + 1] = {0};
                //Copy array[i] to pom[]
                for(int j = 0; j < POLYNOM + 1; j++){
                    hlp[j] = array[i][j];
                }
                //Shift elements in array up
                for(int j = i - 1; j > k; j--){
                        for(int g = 0; g < POLYNOM + 1 ;g++){
                            array[j + 1][g] = array[j][g];
                        }
                    }

                for(int g = 0; g < POLYNOM + 1 ;g++){
                            array[k + 1][g] = array[k][g];
                            array[k][g] = hlp[g];
                    }
            }

        }

    }
}

void saveBestInd(double *array, int *i){
    FILE * fp;

    char num[N_EPOCH];
    sprintf(num,"%d",(*i+1));

    char *filename = (char *) malloc(1 + strlen("Epochs_num_")+ strlen(num) + strlen(".csv"));
    strcpy(filename,"Epochs_num_");
    strcat(filename, num);
    strcat(filename, ".csv");

    fp = fopen(filename, "a");

    if(fp == NULL){
        printf("Unable to open file!!!!!\n");
        exit(EXIT_FAILURE);
    }


    fprintf(fp,"\n%f, %f, %f, %f, %f", array[0], array[1],array[2],array[3],array[4]);
    fclose(fp);
    free(filename);


}

void createFile(int *i){

    char num[N_EPOCH];
    sprintf(num,"%d",(*i+1));

    char *filename = (char *) malloc(1 + strlen("Epochs_num_")+ strlen(num)+ strlen(".csv"));
    strcpy(filename,"Epochs_num_");
    strcat(filename, num);
    strcat(filename, ".csv");


    FILE *fp;
    fp = fopen(filename, "w");
    if(fp == NULL){
        printf("Unable to create file!!!!!\n");
        exit(EXIT_FAILURE);
    }

    fprintf(fp,"%s, %s, %s, %s, %s","x^3", "x^2", "x","  ", "fitness");

    fclose(fp);
    free(filename);
}

double randomRange(int lower, int upper){
    return ((double) (rand() % (upper -  lower +1))+lower);
}

void geneticOperations(double (*ind_array)[POLYNOM + 1], double (*new_array)[POLYNOM + 1]){
    //Mutation
    int n_best_m = round(((double)N_IND / 100) * P_MUT);
    int i;
    for(i = 0; i < n_best_m; i++){
        //random number between 0 - POLYNOM
        int rand = round(randomRange(0, POLYNOM));
        for(int j = 0; j < POLYNOM; j++){
            new_array[i][j] = ind_array[i][j];
        }
        new_array[i][rand] = randomRange(LOWER, UPPER);
    }

    //Crossover
    int n_best_c = round(((double)N_IND / 100) * P_CROSS) + n_best_m;
    int x = 0;

    for(i; i < n_best_c; i++){
            if((x+1) >= N_IND){
                x = 0;
            }
            int rand = round(randomRange(0, POLYNOM - 1));
            for(int k = 0; k < POLYNOM; k++){
                if(k < rand){
                    new_array[i][k] = ind_array[x][k];
                }
                else{
                    new_array[i][k] = ind_array[x+1][k];
                }
            }
            x = x + 2;
    }

    //fill in the rest of the population
    int j = 0;
    for(i; i < N_IND; i++){
        for(int k = 0; k < POLYNOM; k++){
                    new_array[i][k] = ind_array[j][k];
        }
        j++;
    }

}

void copyArrayToArray(double (*array_1)[POLYNOM + 1], double (*array_2)[POLYNOM + 1]){
    for(int i = 0; i < N_IND; i++){
        for(int j = 0; j < POLYNOM; j++){
            array_2[i][j] = array_1[i][j];
        }
    }
}

int main(){
/*    double data[NUM_ROWS][NUM_COLUMS];
    double ind_array[5][5];
    loadData(data);

    ind_array[0][0] = 2;
    ind_array[0][1] =  5;
    ind_array[0][2] =  0;
    ind_array[0][3] =  3;
    ind_array[0][4] =  0;
    for(int j = 0; j < NUM_ROWS; j++){
        printf(" %f\n", data[j][0]);

    }
    for(int j = 0; j < 5; j++){
        printf(" %f ", ind_array[0][j]);

    }
    printf("\n");
    calculateFitnessFunction(data, ind_array);
    for(int j = 0; j < 5; j++){
        printf(" %f ", ind_array[0][j]);

    }


return 0;*/
    time_t start, end;
    time(&start);
   srand(time(NULL));
    //Initialize data array
    double data[NUM_ROWS][NUM_COLUMS];

    //Loading data from csv file
    loadData(data);

    //first loop for epochs
    for(int i = 0; i < N_EPOCH; i++){

        createFile(&i);
        //Initialize array of individual plus fitness fuction
        double ind_array[N_IND][POLYNOM + 1];
        double new_array[N_IND][POLYNOM + 1];

        //Create initial population
        createInitialPop(ind_array);

        //Do GA.
        for(int j = 0; j< N_GEN; j++){
            calculateFitnessFunction(data, ind_array);
            insertionSort(ind_array);
            saveBestInd(ind_array[0], &i);

        //    printGeneration(ind_array);
            geneticOperations(ind_array, new_array);
        //    printGeneration(new_array);
            copyArrayToArray(new_array, ind_array);

            printf("____end of generation___%d\n", j);
        }

        ind_array[0][0] = 0;
        printf("----#####-----#####-----#####------\n");
        printf("____end of epoch____%d\n", i);
        printf("----#####-----#####-----#####------\n");
    }
    time(&end);
    printf("\nExecution time was %jd s", (end - start));
return 0;
}
