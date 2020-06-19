#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>

#define SIZE 100000

typedef struct arr
{
   int size;
   int* arr;
}ArrCell, *Arr_p;

Arr_p selectionSort(Arr_p arr);
Arr_p mergeSort(Arr_p arr);
void printArr(Arr_p arr);
Arr_p getData(char filename[], Arr_p arr);
void setData(int data[], char filename[], int amount);

int main(int argc, char *argv[]) {
  Arr_p arr = malloc(sizeof(ArrCell));
  LARGE_INTEGER start, end, freq;
  double interval;
  if (argc == 2) {
    arr = getData(argv[1], arr);

    Arr_p selection = malloc(sizeof(ArrCell) + SIZE * sizeof(int));
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);
    selection = selectionSort(arr);
    QueryPerformanceCounter(&end);
    interval = (double)(end.QuadPart-start.QuadPart)/freq.QuadPart;
    printf("Elapsed time (selection sort): %lf sec\n", interval);
    //printArr(selection);

    Arr_p merge = malloc(sizeof(ArrCell) + SIZE * sizeof(int));
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);
    merge = mergeSort(arr);
    QueryPerformanceCounter(&end);
    interval = (double)(end.QuadPart-start.QuadPart)/freq.QuadPart;
    printf("Elapsed time (merge sort): %lf sec\n", interval);
    //printArr(merge);
  }
}

Arr_p selectionSort(Arr_p arr) {
  int arrlen = arr -> size;
  int* sortedArr = malloc(arrlen * sizeof(int));
  sortedArr = arr -> arr; 
  for (int i = 0; i < arrlen-1; i++) {
    int min_i = i;
    for (int j = i+1; j < arrlen; j++) {
      if (sortedArr[j] < sortedArr[min_i]) min_i = j;
    }
    int temp = sortedArr[min_i];
    sortedArr[min_i] = sortedArr[i];
    sortedArr[i] = temp;
  }
  return arr;
}

Arr_p mergeSort(Arr_p arr) {
  if (arr -> size <= 1) {
    return arr;
  }
  int size1, size2;
  if (arr -> size % 2 == 1) {
    size1 = (arr -> size / 2) + 1;
  } else {
    size1 = arr -> size / 2;
  }
  size2 = arr -> size / 2;
  Arr_p arr1 = malloc(sizeof(ArrCell));
  arr1 -> arr = malloc(size1 * sizeof(int));
  memcpy(arr1 -> arr, arr -> arr, size1 * sizeof(int));
  arr1 -> size = size1;
  Arr_p arr2 = malloc(sizeof(ArrCell));
  arr2 -> arr = malloc(size2 * sizeof(int));
  memcpy(arr2 -> arr, arr -> arr + size2, size2 * sizeof(int));
  arr2 -> size = size2;
  arr1 = mergeSort(arr1);
  arr2 = mergeSort(arr2);
  int e1 = 0, e2 = 0;
  for (int i = 0; i < arr -> size; i++) {
    if (e1 >= arr1 -> size) {
      arr -> arr[i] = arr2 -> arr[e2];
      e2++;
    } else if (e2 >= arr2 -> size) {
      arr -> arr[i] = arr1 -> arr[e1];
      e1++;
    } else if (arr1 -> arr[e1] <= arr2 -> arr[e2]) {
      arr -> arr[i] = arr1 -> arr[e1];
      e1++;
    } else {
      arr -> arr[i] = arr2 -> arr[e2];
      e2++;
    }
  }
  return arr;
}

void printArr(Arr_p arr) {
  for (int i = 0; i < arr -> size; i++) {
      printf("%d\n", arr -> arr[i]);
  }
}

Arr_p getData(char filename[], Arr_p arr) {
  char charnumber[10];
  int number;
  arr -> arr = malloc(SIZE * sizeof(int));
  
  FILE *file;
  file = fopen(filename, "r");
  if (!file) printf("Datei ist leer oder existiert nicht\n");
  else {
    int i = 0;
    while (!feof(file) && i < SIZE) {
        fgets(charnumber, 10, file);
        sscanf(charnumber, "%d\n", &number);
        arr -> arr[i] = number;
        i++;
    }
    arr -> size = i;
  }
  fclose(file);
  return arr;
}

void setData(int data[], char filename[], int amount) {
  FILE *file;
  file = fopen(filename, "w");
  int i = 0;
  while(i < amount) {
    fprintf(file, "%d\n", data[i]);
    i++;
  }
  fclose(file);
}