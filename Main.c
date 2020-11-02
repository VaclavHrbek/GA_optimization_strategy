
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define FILE_NAME "DataValues.csv"
#define NUM_ROWS 40
#define NUM_COLUMS 2
#define COMA " ,"

double * loadData(){

  double data[NUM_ROWS][NUM_COLUMS];
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
    return data;
  }
}


void main(){

    double* data;
    data = loadData();

}
