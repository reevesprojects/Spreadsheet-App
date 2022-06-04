#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define SIZE 90

void cleanUp(char *, int *);
void getCommand(char *, int *, float **);
void syntaxAnalyzerA(char *, int *, int *, int *, int *, int *);
void syntaxAnalyzerB(char *, int *, int *, int *, int *, int *);
void syntaxAnalyzerC(char *, int *, int *, int *, int *, double *, int *);
void add(int, int, int, int, int *, float **);
void mul(int, int, int, int, int *, float **);
void del(int, int, int, int, int *, float **);
void ins(int, int, int, int, double, int *, float **);
void rangeCalculator(int, int, int, int, int *);
void printArray(float **);

int main()
{
    int i, j, *error;
    float **ar;
    char inBuf[SIZE];
    char *input;

    error = (int *)calloc(sizeof(int), 1);
    input = (char *)calloc(sizeof(char), SIZE);
    ar = (float **)calloc(sizeof(float *), 5);
    for (i = 0; i < 5; i++)
    {
        ar[i] = (float *)calloc(sizeof(float), 1);
    }

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            ar[i][j] = (float) 0;
        }
    }

    while (1 == 1)
    {
        *error = 0;
        printf("\n>>");
        fflush(stdin);
        fgets(inBuf, SIZE, stdin);
        sscanf(inBuf, "%[^\n]", input);
        cleanUp(input, error);
        getCommand(input, error, ar);
    }

    free(ar);
    free(input);
    free(error);
    return 0;
}

void cleanUp(char *input, int *error){
    if (*error != 1)
    {
        char *holder;
        char current[2];
        int i;

        /*removing spaces and uppercase*/
        holder = (char *)calloc(sizeof(char), SIZE);
        strcpy(holder, "");
        current[1] = '\0';
        for (i = 0; i < strlen(input); i++)
        {
            if (input[i] != ' ')
            {
                current[0] = toupper(input[i]);
                strcat(holder, current);
            }
        }
        strcpy(input, holder);
        free(holder);

        /*quit command*/
        if (strcmp(input, "QUIT") == 0)
        {
            exit(-1);
        }

        if (strlen(input) < 6)
        {
            printf("\nError! Invalid Operation");
            *error = 1;
        }
    }
}

void getCommand(char *input, int *error, float **ar)
{
    int firstPla, secPla, thirdPla, fourPla;
    double value;
    if (*error != 1)
    {
        char *code = "";
        code = (char *) calloc(3, sizeof(char));
        strncat(code, input, 3);

        if (strcmp(code, "ADD") == 0 || strcmp(code, "MUL") == 0)
        {
            strcpy(input, &input[2]);
            syntaxAnalyzerB(input, &firstPla, &secPla, &thirdPla, &fourPla, error);
            if (strcmp(code, "ADD") == 0){
                add(firstPla, secPla, thirdPla, fourPla, error, ar);
            } else {
                mul(firstPla, secPla, thirdPla, fourPla, error, ar);
            }
        } else if (strcmp(code, "DEL") == 0){
            strcpy(input, &input[2]);
            syntaxAnalyzerA(input, &firstPla, &secPla, &thirdPla, &fourPla, error);
            del(firstPla, secPla, thirdPla, fourPla, error, ar);
        } else if (strcmp(code, "INS") == 0){
            strcpy(input, &input[2]);
            syntaxAnalyzerC(input, &firstPla, &secPla, &thirdPla, &fourPla, &value, error);
            ins(firstPla, secPla, thirdPla, fourPla, value, error, ar);
        } else {
            printf("\nError! Invalid Operation");
            *error = 1;
        }
        free(code);
    }
}


void syntaxAnalyzerC(char *input, int *firstPla, int *secPla, int *thirdPla, int *fourPla, double *value, int *error){
    char colon, semi, firstLoc, secLoc, thirdLoc, fourLoc;
    char *thing, *holder;

    if ('(' == input[1] && ')' == input[2]){
        thing = (char *) calloc(sizeof(char), strlen(input-3));
        strcpy(thing, input+3);
        semi = thing[strlen(thing)-1];
        thing[strlen(thing) - 1] = '\0';
        *value = atof(thing);
        free(thing);

        if (semi == ';'){
            *firstPla = -1;
        } else{
            printf("\nError! Invalid Operation");
            *error = 1;
        }
    } else if ('(' == input[1] && ')' == input[4]){
        firstLoc = input[2];
        secLoc = input[3];
        thing = (char *) calloc(sizeof(char), strlen(input-4));
        strcpy(thing, input+5);
        semi = thing[strlen(thing)-1];
        thing[strlen(thing) - 1] = '\0';
        *value = atof(thing);
        free(thing);

        if (semi == ';'){
            if ((firstLoc == 'A' || firstLoc == 'B' || firstLoc == 'C' || firstLoc == 'D' || firstLoc == 'E') && (secLoc == '1' || secLoc == '2' || secLoc == '3' || secLoc == '4' || secLoc == '5')){
                switch (firstLoc){
                case 'A':
                    *firstPla = 0;
                    break;
                case 'B':
                    *firstPla = 1;
                    break;
                case 'C':
                    *firstPla = 2;
                    break;
                case 'D':
                    *firstPla = 3;
                    break;
                case 'E':
                    *firstPla = 4;
                    break;
                }
                *secPla = atoi(&secLoc) - 1;
                *thirdPla = -1;
            } else {
                printf("\nError! Invalid Cell");
                *error = 1;
            }
        } else {
            printf("\nError! Invalid Operation");
            *error = 1;
        }
    }
    else if ('(' == input[1] && ')' == input[7]){
        firstLoc = input[2];
        secLoc = input[3];
        colon = input[4];
        thirdLoc = input[5];
        fourLoc = input[6];

        thing = (char *) calloc(sizeof(char), strlen(input-7));
        strcpy(thing, input+8);
        semi = thing[strlen(thing)-1];
        thing[strlen(thing) - 1] = '\0';
        *value = atof(thing);
        free(thing);

        if (semi == ';' && colon == ':') {
            if ((firstLoc == 'A' || firstLoc == 'B' || firstLoc == 'C' || firstLoc == 'D' || firstLoc == 'E') && (secLoc == '1' || secLoc == '2' || secLoc == '3' || secLoc == '4' || secLoc == '5') && (thirdLoc == 'A' || thirdLoc == 'B' || thirdLoc == 'C' || thirdLoc == 'D' || thirdLoc == 'E') && (fourLoc == '1' || fourLoc == '2' || fourLoc == '3' || fourLoc == '4' || fourLoc == '5')){
                switch (firstLoc){
                case 'A':
                    *firstPla = 0;
                    break;
                case 'B':
                    *firstPla = 1;
                    break;
                case 'C':
                    *firstPla = 2;
                    break;
                case 'D':
                    *firstPla = 3;
                    break;
                case 'E':
                    *firstPla = 4;
                    break;
                }
                switch (thirdLoc){
                case 'A':
                    *thirdPla = 0;
                    break;
                case 'B':
                    *thirdPla = 1;
                    break;
                case 'C':
                    *thirdPla = 2;
                    break;
                case 'D':
                    *thirdPla = 3;
                    break;
                case 'E':
                    *thirdPla = 4;
                    break;
                }
                *secPla = atoi(&secLoc) - 1;
                holder = (char *) calloc(sizeof(char), 1);
                strncat(holder, &fourLoc, 1);
                *fourPla = atoi(holder) - 1;
                free(holder);
                rangeCalculator(*firstPla,*secPla, *thirdPla, *fourPla, error);
            } else {
                printf("\nError! Invalid Cell");
                *error = 1;
            }
        } else {
            printf("\nError! Invalid Operation");
            *error = 1;
        }
    } else {
        printf("\nError! Invalid Operation");
        *error = 1;
    }
}

void syntaxAnalyzerA(char *input, int *firstPla, int *secPla, int *thirdPla, int *fourPla, int *error){
    char opBrack, cloBrack, colon, semi, firstLoc, secLoc, thirdLoc, fourLoc;
    char *holder;
    if (strlen(input) == 4){
        opBrack = input[1];
        cloBrack = input[2];
        semi = input[3];
        if (opBrack == ';' && cloBrack == ')' && semi == ';'){
            *firstPla = -1;
        } else{
            printf("\nError! Invalid Operation");
            *error = 1;
        }
    } else if (strlen(input) == 6){
        opBrack = input[1];
        firstLoc = input[2];
        secLoc = input[3];
        cloBrack = input[4];
        semi = input[5];
        if (opBrack == '(' && cloBrack == ')' && semi == ';'){
            if ((firstLoc == 'A' || firstLoc == 'B' || firstLoc == 'C' || firstLoc == 'D' || firstLoc == 'E') && (secLoc == '1' || secLoc == '2' || secLoc == '3' || secLoc == '4' || secLoc == '5')){
                switch (firstLoc){
                case 'A':
                    *firstPla = 0;
                    break;
                case 'B':
                    *firstPla = 1;
                    break;
                case 'C':
                    *firstPla = 2;
                    break;
                case 'D':
                    *firstPla = 3;
                    break;
                case 'E':
                    *firstPla = 4;
                    break;
                }
                *secPla = atoi(&secLoc) - 1;
                *thirdPla = -1;
            } else {
                printf("\nError! Invalid Cell");
                *error = 1;
            }
        } else {
            printf("\nError! Invalid Operation");
            *error = 1;
        }
    }
    else if (strlen(input) == 9){
        opBrack = input[1];
        firstLoc = input[2];
        secLoc = input[3];
        colon = input[4];
        thirdLoc = input[5];
        fourLoc = input[6];
        cloBrack = input[7];
        semi = input[8];
        if (opBrack == '(' && cloBrack == ')' && semi == ';' && colon == ':') {
            if ((firstLoc == 'A' || firstLoc == 'B' || firstLoc == 'C' || firstLoc == 'D' || firstLoc == 'E') && (secLoc == '1' || secLoc == '2' || secLoc == '3' || secLoc == '4' || secLoc == '5') && (thirdLoc == 'A' || thirdLoc == 'B' || thirdLoc == 'C' || thirdLoc == 'D' || thirdLoc == 'E') && (fourLoc == '1' || fourLoc == '2' || fourLoc == '3' || fourLoc == '4' || fourLoc == '5')){
                switch (firstLoc){
                case 'A':
                    *firstPla = 0;
                    break;
                case 'B':
                    *firstPla = 1;
                    break;
                case 'C':
                    *firstPla = 2;
                    break;
                case 'D':
                    *firstPla = 3;
                    break;
                case 'E':
                    *firstPla = 4;
                    break;
                }
                switch (thirdLoc){
                case 'A':
                    *thirdPla = 0;
                    break;
                case 'B':
                    *thirdPla = 1;
                    break;
                case 'C':
                    *thirdPla = 2;
                    break;
                case 'D':
                    *thirdPla = 3;
                    break;
                case 'E':
                    *thirdPla = 4;
                    break;
                }
                *secPla = atoi(&secLoc) - 1;
                holder = (char *) calloc(sizeof(char), 1);
                strncat(holder, &fourLoc, 1);
                *fourPla = atoi(holder) - 1;
                free(holder);
                rangeCalculator(*firstPla,*secPla, *thirdPla, *fourPla, error);
            } else {
                printf("\nError! Invalid Cell");
                *error = 1;
            }
        } else {
            printf("\nError! Invalid Operation");
            *error = 1;
        }
    } else {
        printf("\nError! Invalid Operation");
        *error = 1;
    }
}

void syntaxAnalyzerB(char *input, int *firstPla, int *secPla, int *thirdPla, int *fourPla, int *error){
    char opBrack, cloBrack, colon, semi, firstLoc, secLoc, thirdLoc, fourLoc;
    char *holder;
    if (strlen(input) == 4){
        opBrack = input[1];
        cloBrack = input[2];
        semi = input[3];
        if (opBrack == ';' && cloBrack == ')' && semi == ';'){
            *firstPla = -1;
        } else{
            printf("\nError! Invalid Operation");
            *error = 1;
        }
    } else if (strlen(input) == 9){
        opBrack = input[1];
        firstLoc = input[2];
        secLoc = input[3];
        colon = input[4];
        thirdLoc = input[5];
        fourLoc = input[6];
        cloBrack = input[7];
        semi = input[8];
        if (opBrack == '(' && cloBrack == ')' && semi == ';' && colon == ':') {
            if ((firstLoc == 'A' || firstLoc == 'B' || firstLoc == 'C' || firstLoc == 'D' || firstLoc == 'E') && (secLoc == '1' || secLoc == '2' || secLoc == '3' || secLoc == '4' || secLoc == '5') && (thirdLoc == 'A' || thirdLoc == 'B' || thirdLoc == 'C' || thirdLoc == 'D' || thirdLoc == 'E') && (fourLoc == '1' || fourLoc == '2' || fourLoc == '3' || fourLoc == '4' || fourLoc == '5')){
                switch (firstLoc){
                case 'A':
                    *firstPla = 0;
                    break;
                case 'B':
                    *firstPla = 1;
                    break;
                case 'C':
                    *firstPla = 2;
                    break;
                case 'D':
                    *firstPla = 3;
                    break;
                case 'E':
                    *firstPla = 4;
                    break;
                }
                switch (thirdLoc){
                case 'A':
                    *thirdPla = 0;
                    break;
                case 'B':
                    *thirdPla = 1;
                    break;
                case 'C':
                    *thirdPla = 2;
                    break;
                case 'D':
                    *thirdPla = 3;
                    break;
                case 'E':
                    *thirdPla = 4;
                    break;
                }
                *secPla = atoi(&secLoc) - 1;
                holder = (char *) calloc(sizeof(char), 1);
                strncat(holder, &fourLoc, 1);
                *fourPla = atoi(holder) - 1;
                free(holder);
                rangeCalculator(*firstPla,*secPla, *thirdPla, *fourPla, error);
            } else {
                printf("\nError! Invalid Cell");
                *error = 1;
            }
        } else {
            printf("\nError! Invalid Operation");
            *error = 1;
        }
    } else {
        printf("\nError! Invalid Operation");
        *error = 1;
    }
}

void rangeCalculator(int firstPla, int secPla, int thirdPla, int fourPla, int *error){
    if (firstPla == thirdPla && secPla >= fourPla){
        printf("\nError! Wrong Range");
        *error = 1;
    } else if (secPla == fourPla && firstPla >= thirdPla){
        printf("\nError! Wrong Range");
        *error = 1;
    }
}

void add(int firCol, int firRow, int secCol, int secRow, int *error, float **ar){
    if (*error != 1){
        if (firCol == -1){
            int i, j;
            double total = 0;
            for (i = 0; i < 5; i++){
                for (j = 0; j <5; j++){
                    total += ar[i][j];
                }
            }
            printf("\n%.2f", total);
        } else {
            int i;
            double total = 0;
            if (firCol == secCol){
                for (i = firRow; i <= secRow; i++){
                    total += ar[i][firCol];
                }
            } else {
                for (i = firCol; i <= secCol; i++){
                    total += ar[firRow][i];
                }
            }
            printf("\n%.2f", total);
        }
    }
}

void mul(int firCol, int firRow, int secCol, int secRow, int *error, float **ar){
    if (*error != 1){
        if (firCol == -1){
            int i, j;
            double total = 0;
            for (i = 0; i < 5; i++){
                for (j = 0; j <5; j++){
                    total *= ar[i][j];
                }
            }
            printf("\n%.2f", total);
        } else {
            int i;
            double total = 0;
            if (firCol == secCol){
                for (i = firRow; i <= secRow; i++){
                    total *= ar[i][firCol];
                }
            } else {
                for (i = firCol; i <= secCol; i++){
                    total *= ar[firRow][i];
                }
            }
            printf("\n%.2f", total);
        }
    }
}

void del(int firCol, int firRow, int secCol, int secRow, int *error, float **ar)
{
    if (*error != 1){
        int i, j;
        if (firCol == -1){
            for (i = 0; i < 5; i++){
                for (j = 0; j < 5; j++){
                    ar[i][j] = 0;
                }
            }
        } else if (secCol == -1){
            ar[firRow][firCol] = 0;
        } else{
            if (firCol == secCol){
                for (i = firRow; i <= secRow; i++){
                    ar[i][firCol] = 0;
                }
            } else {
                for (i = firCol; i <= secCol; i++){
                    ar[firRow][i] = 0;
                }
            }
        }
        printArray(ar);
    }
}

void ins(int firCol, int firRow, int secCol, int secRow, double value, int *error, float **ar)
{
    if (*error != 1){
        int i, j;
        if (firCol == -1){
            for (i = 0; i < 5; i++){
                for (j = 0; j < 5; j++){
                    ar[i][j] = value;
                }
            }
        } else if (secCol == -1){
            ar[firRow][firCol] = value;
        } else{
            if (firCol == secCol){
                for (i = firRow; i <= secRow; i++){
                    ar[i][firCol] = value;
                }
            } else {
                for (i = firCol; i <= secCol; i++){
                    ar[firRow][i] = value;
                }
            }
        }
        printArray(ar);
    }
}

void printArray(float **ar){
    int i, j;
    printf("\n\tA\tB\tC\tD\tE");
    for (i = 0; i < 5; i++){
        printf("\n%i", i+1);
        for (j = 0; j < 5; j++){
            printf("\t%.2f", ar[i][j]);
        }
    }
}