/**
 * MATTHEW RINNE
 * p420.c
 * CS300
 **/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>


#define MIN_PID 300 /* minimum pid */
#define MAX_PID 5000 /* maximum pid */


/********* functions *********/
int allocate_map(); /* allocates map of pids */
int allocate_pid(); /* allocates a pid, returns pid or -1 if unable */
void release_pid(int pid); /* reallocates a pid */
void *runner(); /* function to be run in threads */
/*****************************/

/****** global variable ******/
int *pid_map;
/*****************************/

int
allocate_map()
{
  pid_map = malloc(MAX_PID+1 * sizeof(int));

  for (int i=0; i<MAX_PID+1; i++) pid_map[i] = 0;

  if (pid_map)
  {
    printf("map successfully allocated\n");
    return 1;
  }
  else
  {
    printf("map unsuccessfully allocated\n");
    return 0;
  }
}

int
allocate_pid()
{
  for (int i=MIN_PID; i<MAX_PID+1; i++)
  {
    if (pid_map[i] == 0)
    {
      pid_map[i] = 1;
      printf("allocated a pid: %d\n", i);
      return i;
    }
  }
  return -1;
}

void
release_pid(int pid)
{
  pid_map[pid] = 0;
  printf("released a pid: %d\n", pid);
  return;
}

void *
runner()
{
  int pid = allocate_pid();
  sleep(rand() % 3);
  release_pid(pid);
  pthread_exit(0);
}

int
main(void)
{
  int NUM_THREADS;
  printf("Enter the number of threads you would like: \n");
  scanf("%d", &NUM_THREADS);

  pthread_t tid[NUM_THREADS];
  pthread_attr_t attr;

  allocate_map();
  srand(time(0));

  pthread_attr_init(&attr);

  for (int i=0; i<NUM_THREADS; i++) pthread_create(&tid[i],&attr,runner,NULL);
  for (int i=0; i<NUM_THREADS; i++) pthread_join(tid[i], NULL);
  return 0;
}
