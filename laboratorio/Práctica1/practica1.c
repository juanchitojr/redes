#include<stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]){
  
  char opc = argv[1][0];
  int a;
  int *numeros;

  switch(opc){
  int i;
  case 'f':
    a = arreglo_aleatorio(5);
    printf("aleatorio: %d", a);
    break;
  // Se le pasan los valores 
  case 'v':
    numeros = (int*)malloc(sizeof(int) * (argc-2));
    for(i=0; i<argc-2; i++) {
      numeros[i] = atoi(argv[i+2]);
    }

    for(i=0; i<argc-2; i++){
      printf("i: %d\n", numeros[i]);
    }
  }
  return 0;
}


int arreglo_aleatorio(int n) {
  return rand();
}
