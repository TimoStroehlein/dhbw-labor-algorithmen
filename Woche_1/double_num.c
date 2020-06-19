#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int * getData(char filename[], int amount);
void setData(int data[], char filename[], int amount);

int main(int argc, char *argv[]) {
  int * data;
  char * filename = malloc(sizeof(argv[2]));
  int amount = atoi(argv[1]);
  if(argc == 3) {
    filename = strdup(argv[2]);
    data = getData(filename, amount);
    setData(data, filename, amount);
  }
  else {
    char _filename[30];
    int _amount;
    printf("Filename: ");
    scanf("%s", _filename);
    fflush(stdin);
    printf("Amount: ");
    scanf("%d", &_amount);
    fflush(stdin);
    data = getData(_filename, _amount);
    setData(data, _filename, _amount);
  }
  return 42;
}

int * getData(char filename[], int amount) {
  char charnumber[5];
  int number;
  int * numbers = malloc(amount * sizeof(number));
  
  FILE *file;
  file = fopen(filename, "r");
  if (!file) printf("Datei ist leer oder existiert nicht\n");
  else {
    int i = 0;
    while (!feof(file) && i < amount) {
        fgets(charnumber, 10, file);
        sscanf(charnumber, "%d\n", &number);
        numbers[i] = number * 2;
        printf("double: %d\n", numbers[i]);
        i++;
    }
  }
  fclose(file);
  return numbers;
}

void setData(int * data, char filename[], int amount) {
  FILE *file;
  file = fopen(filename, "w");
  int i = 0;
  while(i < amount) {
    fprintf(file, "%d\n", data[i]);
    i++;
  }
  fclose(file);
}