#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

int row1,row2;
int col1,col2;
int array1[100][100];
int array2[100][100];
int output[100][100];
int outputr[100][100];



void *eachElement(int  x)
{

int sum = 0;
int r = x / col2;
int c = x % col2;
int i;

//printf("r = %d , c = %d , x = %d \n",r,c,x);

for(i=0 ; i < col1 ; i++)
sum = sum + array1[r][i]*array2[i][c];

output[r][c] =sum;

}

void *eachRow(int  r)
{

int sum = 0;
int i,j;
for(i=0 ; i < col2 ; i++)
{
for(j=0 ; j < col1 ; j++)
sum = sum + array1[r][j]*array2[j][i];

//printf("r = %d , c = %d \n",r,i);
outputr[r][i] = sum;
sum = 0;
}

}



int main()
{

FILE *fp;

int i,j;

/////////////////
fp = fopen("input.txt", "r"); // read mode
if (fp == NULL)
    {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }
////////////////

/// 1st matrix
fscanf(fp, "%d%d", &row1, &col1);
for(i=0; i < row1 ; i++)
{
    for(j=0; j < col1 ; j++)
        fscanf(fp, "%d", &array1[i][j]);
}

/// 2nd matrix
fscanf(fp, "%d%d", &row2, &col2);
for(i=0; i < row2 ; i++)
{
    for(j=0; j < col2 ; j++)
        fscanf(fp, "%d", &array2[i][j]);
}
////////////////

/*
///print
for(i=0; i < row1 ; i++)
{
    for(j=0; j < col1 ; j++)
        printf("%d ",array1[i][j]);
    printf("\n");
}
printf("--------------------\n");
for(i=0; i < row2 ; i++)
{
    for(j=0; j < col2 ; j++)
        printf("%d ",array2[i][j]);
    printf("\n");
}///end of print
*/

fclose(fp);


fp = fopen("output.txt","w");


//printf("row1 = %d , col2 = %d \n",row1,col2);

int x;
clock_t t1;
clock_t t2;


/// eachElement
pthread_t tid[row1*col2];

t1 = clock();

for (x=0 ; x < row1*col2 ; x++)
pthread_create(&tid[x], NULL, eachElement, x);

for (x=0 ; x < row1*col2 ; x++)
pthread_join(tid[x], NULL);

t1 = clock() - t1;
double time_taken1 = ((double)t1)/CLOCKS_PER_SEC; // calculate the elapsed time

//printf("elemnt print \n");
for(i=0; i < row1 ; i++)
{
    for(j=0; j < col2 ; j++)
        fprintf(fp,"%d ",output[i][j]);
    fprintf(fp,"\n");
}

fprintf(fp,"END1 \t %f\n", time_taken1);

////////////////////////////////////////

///eachRow
pthread_t tidr[row1];

t2 = clock();

for (x=0 ; x < row1 ; x++)
pthread_create(&tidr[x], NULL, eachRow, x);

for (x=0 ; x < row1 ; x++)
pthread_join(tidr[x], NULL);

t2 = clock() - t2;
double time_taken2 = ((double)t2)/CLOCKS_PER_SEC; // calculate the elapsed time

//printf("row print \n");
for(i=0; i < row1 ; i++)
{
    for(j=0; j < col2 ; j++)
        fprintf(fp,"%d ",outputr[i][j]);
    fprintf(fp,"\n");
}


fprintf(fp,"END2 \t %f\n", time_taken2);








return 0;

}
