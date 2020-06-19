#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXITEMS 10000

char ** getData(char filename[], int size);
char ** reverseStr(char * numbers[], int size);
void setData(char * data[], char filename[], int size);

int main(int argc, char *argv[]) {
  int size = atoi(argv[1]);
  if(argc == 3) {
    char ** numbers = getData(argv[2], size);
    char ** reversednumbers = reverseStr(numbers, size);
    setData(reversednumbers, argv[2], size);
  }
  else {
    char _filename[30];
    int _size;
    printf("Filename: ");
    scanf("%s", _filename);
    fflush(stdin);
    printf("Amount: ");
    scanf("%d", &_size);
    fflush(stdin);
    char ** numbers = getData(_filename, _size);
    char ** reversednumbers = reverseStr(numbers, _size);
    setData(reversednumbers, _filename, _size);
  }
  return 42;
}

char ** getData(char filename[], int size)
{
  char number[255+1];
  char ** numbers = malloc(size * 255+1);

  FILE *file;
  file = fopen(filename, "r");
  if (!file) printf("Datei ist leer oder existiert nicht\n");
  else {
    int i = 0;
    while (!feof(file) && i < MAXITEMS && i < size) {
        fgets(number, 255+1, file);
        numbers[i] = strdup(number);
        printf("before: %s", numbers[i]);
        i++;
    }
  }
  fclose(file); 
  return numbers;
}

void setData(char * data[], char filename[], int size) {
  FILE *file;
  file = fopen(filename, "w");
  int i = 0;
  while(i < size && i < MAXITEMS) {
    fprintf(file, "%s", data[i]);
    i++;
  }
  fclose(file);
}

char ** reverseStr(char * numbers[], int size) {
    int i;
    char ** reversed = malloc(size * 255+1);
    for(i = 0; i < size; i++) {
      reversed[i] = strdup(numbers[size - i - 1]);
      printf("reversed: %s", reversed[i]);
    }
    return reversed;
}