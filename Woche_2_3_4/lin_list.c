#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct lin_list {
    char *payload;
    struct lin_list *next;
}LinListCell, *LinList_p;

LinList_p LinListAllocCell(char* payload);
void LinListPrint(LinList_p *anchor);
void LinListFreeCell(LinList_p junk);
void LinListFree(LinList_p *junk);
LinList_p LinListInsertFirst(LinList_p *anchor, LinList_p newcell);
LinList_p LinListExtractFirst(LinList_p *anchor);
LinList_p LinListFind(LinList_p *anchor, char* payload);
LinList_p LinListSort(LinList_p *anchor);
void LinListChangeCell(LinList_p *current, LinList_p *compare);
LinList_p LinListStat(LinList_p *anchor);

int main(int argc, char *argv[]) {
    int i;
    char c[255];
    LinList_p linlist = NULL;
    do {
        printf("Zahl: ");
        scanf("%d", &i);
        fflush(stdin);
        switch (i) {
            case 0:
                break;
            case 1:
                LinListPrint(&linlist);
                break;
            case 2:
                printf("Wie viele Eingaben: ");
                scanf("%d", &i);
                for(int j = 0; j < i; j++) {
                    scanf("%s", c);
                    LinListInsertFirst(&linlist, LinListAllocCell(c));
                }
                break;
            case 3:
                LinListExtractFirst(&linlist);
                break;
            case 4:
                LinListFree(&linlist);
                break;
            case 5:
                printf("Suche: ");
                scanf("%s", c);
                printf("%s\n", LinListFind(&linlist, c) -> payload);
                break;
            case 6:
                LinListSort(&linlist);
                break;
            case 7:
                LinListSort(&linlist);
                LinListStat(&linlist);
                break;
            default:
                break;  
        }
    } while (i != 0);
    return 42;
}

LinList_p LinListAllocCell(char* payload) {
    LinList_p newCell = malloc(sizeof(LinListCell));
    newCell -> payload = strdup(payload);
    newCell -> next = NULL;
    return newCell;
}

void LinListPrint(LinList_p *anchor) {
    LinList_p current = *anchor;
    while (current != NULL) {
        printf("%s\n", current -> payload);
        current = current -> next;
    }
}

void LinListFreeCell(LinList_p junk) {
    free(junk -> payload);
    free(junk);
}

void LinListFree(LinList_p *junk) {
    LinList_p current;
    while(*junk) {
        current = (*junk) -> next;
        LinListFreeCell(*junk);
        *junk = current;
    }
}

LinList_p LinListInsertFirst(LinList_p *anchor, LinList_p newcell) {
    newcell -> next = *anchor;
    *anchor = newcell;
    return newcell;
}

LinList_p LinListExtractFirst(LinList_p *anchor) {
    LinList_p list = *anchor;
    *anchor = list -> next;
    list -> next = NULL;
    return *anchor;
}

LinList_p LinListFind(LinList_p *anchor, char* payload) {
    LinList_p current = *anchor;
    while(strcmp(current -> payload, payload) != 0 && current) {
        if(current -> next) current = current -> next;
        else return NULL;
    }
    return current;
}

LinList_p LinListSort(LinList_p *anchor) {
    LinList_p current = *anchor;
    LinList_p compare = *anchor;
    while(current) {
        while(compare)
        {
            if (strcmp(current -> payload, compare -> payload) < 0) LinListChangeCell(&current, &compare);
            compare = compare -> next;
        }
        compare = *anchor;
        current = current -> next;
    }
    return *anchor;
}

void LinListChangeCell(LinList_p *current, LinList_p *compare) {
    char* temp = malloc(sizeof(LinListCell));
    temp = strdup((*current) -> payload);
    (*current) -> payload = strdup((*compare) -> payload);
    (*compare) -> payload = strdup(temp);
}

LinList_p LinListStat(LinList_p *anchor) {
    LinList_p current = *anchor;
    char before[255];
    int i = 0;
    while(current) {
        if (strcmp(current -> payload, before) == 0 || i == 0) i++;
        else {
            printf("%d - %s\n", i, before);
            i = 1;
        }
        strcpy(before, current -> payload);
        current = current -> next;
    }
    printf("%d - %s\n", i, before);
    return *anchor;
}