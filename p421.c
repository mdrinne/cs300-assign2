/**
 * MATTHEW RINNE
 * p421.c
 * CS300
 **/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>


/********* functions ********/
void *runner0(); /* thread function for computing average */
void *runner1(); /* thread function for computing minimum */
void *runner2(); /* thread funciton for computing maximum */
/****************************/

/***** global variable *****/
int count;
char *numbers[500];
int avg;
int max;
int min;
/***************************/

void *
runner0()
{
  if (count == 0)
  {
    avg = 0;
    pthread_exit(0);
  }
  float sum = 0;

  for (int i=0; i<count; i++) sum = sum + atoi(numbers[i]);
  avg = sum / count;

  pthread_exit(0);
}

void *
runner1()
{

  min = atoi(numbers[0]);

  for (int i=1; i<count-1; i++)
  {
    if (min > atoi(numbers[i])) min = atoi(numbers[i]);
  }

  pthread_exit(0);
}

void *
runner2()
{
  max = atoi(numbers[0]);

  for (int i=1; i<count; i++)
  {
    if (max < atoi(numbers[i])) max = atoi(numbers[i]);
  }

  pthread_exit(0);
}

void
clean(char buffer[], char *numbers[])
{
  count = 0;
  int flag;
  int len;
  char *token = strtok(buffer, " ");
  while (token)
  {
    flag = 0;
    numbers[count] = token;
    len = strlen(token);
    for (int i=0; i<len; i++) if (isalpha(token[i])) flag = 1;
    if (!flag) count++;
    token = strtok(NULL, " ");
  }
  return;
}

int
main(void)
{
  char input_buffer[1000];

  fgets(input_buffer, 500, stdin);
  clean(input_buffer, numbers);

  pthread_t tid[3];
  pthread_attr_t attr;

  pthread_attr_init(&attr);

  pthread_create(&tid[0],&attr,runner0,NULL);
  pthread_create(&tid[1],&attr,runner1,NULL);
  pthread_create(&tid[2],&attr,runner2,NULL);

  for(int i=0; i<3; i++) pthread_join(tid[i],NULL);

  printf("The average value is %d\n", avg);
  printf("The minimum value is %d\n", min);
  printf("The maximum value is %d\n", max);

  return 0;
}
