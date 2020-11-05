
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>


//Main define
#define N_GEN 2
#define N_IND 10
#define N_EPOCH 10
#define POLYNOM 4

//Definition of GA
//P stands for percentage
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
    int upper = 1000;
    int lower = -1000;
    for(int i = 0;i < N_IND; i++){
        for(int j = 0; j < POLYNOM; j++){
            ind_array[i][j] = ((double) (rand() % (upper -  lower +1))+lower);
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
            geneticOperations(ind_array, new_array)
        //  printGeneration(ind_array);


            printf("____end of generation___\n");
        }

        ind_array[0][0] = 0;
        printf("____end of epoch____\n");
    }

}
