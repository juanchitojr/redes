#include<stdio.h>

void quicksort(int*, int, int);
int partition(int*, int, int);
void swap(int*, int*);


int main() {
  int nums[10] = {10,9,8,7,6,5,4,3,1,2};
  quicksort(nums, 1, 10);
  int i;
  for(i=0; i<10; i++)
    printf("i:%d ", nums[i]);
  return 0; 
}

void quicksort(int *numeros, int p, int r) {
  int q;
  if (p < r) {
    q = partition(numeros, p, r);
    quicksort(numeros, p, q-1);
    quicksort(numeros, q+1, r);
  }
}

int partition(int *numeros, int p, int r) {
  int x, i, j;
  x = numeros[r];
  i = p-1;
  for(j=p; j<r; j++) {
    if (numeros[j]<=x) {
      i = i+1;
      swap(&numeros[i], &numeros[j]);
    }
  }
  swap(&numeros[i+1], &numeros[r]);
  return i+1;
}

void swap (int* a, int* b){
  int temp;
  temp = *a;
  *a = *b;
  *b = temp;
}
