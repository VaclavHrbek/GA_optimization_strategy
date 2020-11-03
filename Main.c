
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
#define P_CROSS 33
#define P_MUT 33
#define




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
    //TODO: Add lower range in minus values to generate individual.
    for(int i = 0;i < N_IND; i++){
        for(int j = 0; j < POLYNOM; j++){
            ind_array[i][j] = ((double) (rand() % upper));
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
            //printf("out: %f", out_polyn),
            arr_polyn[j] = out_polyn;
            //printf("arr: %f", arr_polyn[j]);
        }
        long double fitness_function = 0;
        for(int j = 0; j < NUM_ROWS; j++){
            fitness_function += pow((data[j][1] + arr_polyn[j]), 2);
        }
        ind_array[i][POLYNOM] = fitness_function;
    }
}


void main(){
    //Initialize data array
    double data[NUM_ROWS][NUM_COLUMS];

    //Loading data from csv file
    loadData(data);

    //first loop for epochs
    for(int i = 0; i < N_EPOCH; i++){
        //Initialize array of individual plus fitness fuction
        double ind_array[N_IND][POLYNOM + 1];
        double new_array[N_IND][POLYNOM + 1];

        createInitialPop(ind_array);
        for(int j = 0; j< N_GEN; j++){
            calculateFitnessFunction(data, ind_array);
            for(int k = 0; k< POLYNOM + 1; k++){

                printf("%f , ",ind_array[0][k]);
            }


            printf("____end of generation___\n");
        }

        ind_array[0][0] = 0;
        printf("____end of epoch____\n");
    }

}
