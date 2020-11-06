
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>


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
  for(int j = 0; j < NUM_ROWS; j++){
      //printf(" %f\n", data[j][0]);
      //printf(" %f", ind_array[0][i]);
  }
}

int main(){
    srand(time(NULL));
    double data[NUM_ROWS][NUM_COLUMS];
    double ind_array[0][5];
    ind_array[0][0] = 2;
    ind_array[0][1] = 5;
    ind_array[0][2] = 0;
    ind_array[0][3] = 3;
    ind_array[0][4] = 0;
    loadData(data);




    for(int j = 0; j < NUM_ROWS; j++){
        printf(" %f\n", data[j][0]);
        //printf(" %f", ind_array[0][i]);
    }
    return 0;
}
