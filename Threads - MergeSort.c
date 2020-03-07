#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


int array[100]; /// shared
int temp[100];

struct index
{
int l;
int r;
};

void * mergesort (struct index * ind)
{
int l = ind->l; int r = ind->r ; int m ;
if (l < r)
{
m = (l+r) / 2;

struct index indl = {l,m};
struct index indr = {m+1,r};

pthread_t tid[2];
pthread_create(&tid[0], NULL, mergesort, &indl);
pthread_create(&tid[1], NULL, mergesort, &indr);

pthread_join(tid[0], NULL);
pthread_join(tid[1], NULL);

merge (l,m,r);

}

}

void merge(int low, int mid, int high) {
   int l1, l2, i;

   for(l1 = low, l2 = mid + 1, i = low; l1 <= mid && l2 <= high; i++) {
      if(array[l1] <= array[l2])
         temp[i] = array[l1++];
      else
         temp[i] = array[l2++];
   }

   while(l1 <= mid)
      temp[i++] = array[l1++];

   while(l2 <= high)
      temp[i++] = array[l2++];

   for(i = low; i <= high; i++)
      array[i] = temp[i];
}



int main()
{

int n,i;

struct index ind;

FILE *fp;
fp = fopen("input.txt", "r"); // read mode
if (fp == NULL)
    {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }
/// shil array1 mlhash lazma i think
fscanf(fp, "%d", &n );
for(i=0; i < n ; i++)
fscanf(fp, "%d", &array[i]);

ind.l = 0;
ind.r = n-1;

pthread_t tid;
pthread_create(&tid, NULL, mergesort, &ind);
pthread_join(tid, NULL);

fp = fopen("output.txt","w");

for(i=0; i < n ; i++)
fprintf(fp,"%d ", array[i]);

return 0;
}
