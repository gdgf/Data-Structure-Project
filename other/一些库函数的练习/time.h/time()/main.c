#include <stdio.h>
#include <time.h>

int main ()
{
  time_t seconds;

  seconds = time(NULL);
  printf("�� 1970-01-01 ���Сʱ�� = %ld\n", seconds/3600);

  return(0);
}
