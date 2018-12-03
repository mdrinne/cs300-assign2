/**
 * MATTHEW RINNE
 * p320.c
 * CS300
 **/

#include <stdio.h>
#include <stdlib.h>

#define MIN_PID 300 /* minimum pid */
#define MAX_PID 5000 /* maximum pid */


/********* functions *********/
int allocate_map(); /* allocates map of pids */
int allocate_pid(); /* allocates a pid, returns pid or -1 if unable */
void release_pid(int pid); /* reallocates a pid */
/*****************************/

/***** global variables *****/
int *pid_map;

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

int
main(void)
{
  int temp = allocate_map();
  return 0;
}
