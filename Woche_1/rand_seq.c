#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#define MAXNUM 1000

int * randSeq(int amount);
void setData(int data[], char filename[], int size);

int main(int argc, char *argv[]) {
    int * squence;
    if(argc == 3) {
        int amount = atoi(argv[1]);
        squence = randSeq(amount);
        setData(squence, argv[2], amount);
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
        squence = randSeq(_amount);
        setData(squence, _filename, _amount);
    }
    return 42;
}

int * randSeq(int amount) {
    int random, i;
    time_t timer;
    srand(time(&timer));
    int * squence = malloc(sizeof(random));

    for(i = 0; i < amount; i++) {
        random = rand() % MAXNUM;
        squence[i] = random;
        printf("random: %d\n", squence[i]);
    }

    return squence;
}

void setData(int * data, char filename[], int size) {
    FILE *datei;
    datei = fopen(filename, "w");
    int i = 0;
    while (i < size) {
        fprintf(datei, "%d\n", data[i]);
        i++;
    }
    fclose(datei);
}
