#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <assert.h>

#define MAXCOLS  256
#define MAXROWS  256
#define BORDER '#'
#define START 'X'
#define END 'S'

/* Data type: Labyrinth - ASCII map, costs, direction */

typedef struct labyrinth
{
   char lab[MAXCOLS+2][MAXROWS];
   long costs[MAXCOLS][MAXROWS];
   long bestx[MAXCOLS][MAXROWS];
   long besty[MAXCOLS][MAXROWS];
   int maxrow;
   int startx;
   int starty;
   int treasurex;
   int treasurey;
}LabCell, *Lab_p;

void file_read(Lab_p lab, char* filename);
void print_lab(Lab_p lab);

int main(int argc, char *argv[]) {
    Lab_p lab = malloc(sizeof(LabCell));
    if (argc == 2) {
        file_read(lab, argv[1]);
    }
}

void file_read(Lab_p lab, char* filename)
{
    char c;
    int i, j;
    FILE *file;

    file = fopen(filename, "r");
    if (!file) printf("File is empty\n");
    else {
        i = 0;
        j = 0;
        while (!feof(file)) {
            
            c = fgetc(file);
            lab -> lab[i][j] = c;
            printf("%c", lab -> lab[i][j]);
            if (c == START) {
                lab -> startx = i;
                lab -> starty = j;
            }
            if (c == '\n') {
                j++;
                i = 0;
            }
            i++;
        }
    }
    fclose(file);
}

void print_lab(Lab_p lab) {
    int i = 0, j = 0;
    while (lab -> lab[i][j]) {
        printf("%c", lab -> lab[i][j]);
        if (lab -> lab[i][j] == '\n') {
            j++;
            i = 0;
        }
        i++;
    }
}

void solve_lab(Lab_p lab) {

}