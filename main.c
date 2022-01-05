#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#include "readerwriter.h"
#define MAXLEN 12 // change this macro if the number of characters per line are changed in the scenarios.txt file

rwlock_t lock;
int x=0;

void *reading(){
  rwlock_acquire_readlock(&lock);
  printf("A reader started reading \n");
  int T;  
  T = rand()%10000; 
  for(int i = 0; i < T; i++)
    for(int j = 0; j < T; j++) 
      x=i*j;
  printf("A reader stopped reading\n");
  rwlock_release_readlock(&lock);
  return (void*) &x ;
}

void *writing(){
  rwlock_acquire_writelock(&lock);
  printf("A writer started writing \n");
  int T;  
  T = rand()%10000; 
  for(int i = 0; i < T; i++)
    for(int j = 0; j < T; j++) 
      x=i*j;
  printf("A writer stopped writing \n");
  rwlock_release_writelock(&lock);
  return (void*) &x;
}

int main() {
  FILE * inputFile;
  inputFile = fopen("scenarios.txt", "r");
  rwlock_init(&lock);
  if (inputFile != NULL){
    char c;
    int count = 1;
    while (1){
      pthread_t t[MAXLEN];
      for (int i =0; i < MAXLEN; i++){
        c = fgetc(inputFile);
        if ( c == '\n')
          {i--;continue;}
        else if (c == EOF) 
          {break;}
        else if (c == 'r')
          {
            if (i == 0){ printf("\nNew Scenario %d\n \n", count++); }
            pthread_create(&t[i], NULL, reading, NULL);
          } 
        else if (c == 'w')
          {
            if (i == 0){ printf("\nNew Scenario %d\n \n", count++); }
            pthread_create(&t[i], NULL, writing, NULL);
          }   
      }
      if (c == EOF) {break;}
      for (int i =0; i < MAXLEN; i++){
      pthread_join(t[i], NULL);
      }
    }
  }
    return 0;
}