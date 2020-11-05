
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>


//Main define
#define N_GEN 2
#define N_IND 10
#define N_EPOCH 1
#define POLYNOM 4

//range of random numbers
#define UPPER 1000
#define LOWER -1000

//Definition of GA
//P stands for percentage
//Sum can't be more than 100
#define P_CROSS 33
#define P_MUT 33

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

        char *ptr;
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
                int pol = POLYNOM;
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

void saveBestInd(double *array){

    for(int i = 0; i < 5; i ++){
        printf("%f, ", array[i]);
        //TODO: finish best to the created file;
        //name of file is Epochs_num_
        //first finish createFile function
    }
}

void createFile(int *i){

    char num[N_EPOCH];
    sprintf(num,"%d",(*i+1));

    char *filename = (char *) malloc(1 + strlen("Epochs_num_")+ strlen(num));
    strcpy(filename,"Epochs_num_");
    strcat(filename, num);

    //TODO: create file

    free(filename);
}

double randomRange(int lower, int upper){
    return ((double) (rand() % (upper -  lower +1))+lower);
}

//Selection by using elitism
void selection(double (*ind_array)[POLYNOM + 1], double *par1, double *par2){

}

void geneticOperations(double (*ind_array)[POLYNOM + 1], double (*new_array)[POLYNOM + 1]){
    //Mutation
    int n_best_m = round(((double)N_IND / 100) * P_MUT);
    int i;
    for(i = 0; i < n_best_m; i++){
        //random number between 0 - POLYNOM
        int rand = round(randomRange(0, POLYNOM));
        for(int j = 0; j < POLYNOM + 1 ; j++){
            new_array[i][j] = ind_array[i][j];
        }
        new_array[i][rand] = randomRange(LOWER, UPPER);
    }

    //Crossover
    int n_best_c = round(((double)N_IND / 100) * P_CROSS) + n_best_m;
    int j = 1;
    int x = 0;

    for(i; i < n_best_c; i++){
        getchar();
            if((x+1) == N_IND){
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
            x++;
    }



    //Copy 100 - P_CROSS - P_MUT percentyge to new_array;
    //int n_best = round(((double)N_IND / 100) * (100 - P_CROSS - P_MUT));
    /*for(int i = 0; i < n_best; i++){

    }
    printf("   %d, ",n_best);
*/
    //TODO:complete this function.
    //TODO:complete the copiing to new_array.
}

void main(){
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
        //  saveBestInd(ind_array[0]);
            geneticOperations(ind_array, new_array);
        //  printGeneration(ind_array);


            printf("____end of generation___\n");
        }

        ind_array[0][0] = 0;
        printf("____end of epoch____\n");
    }

}
