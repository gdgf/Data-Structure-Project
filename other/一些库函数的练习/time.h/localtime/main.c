#include <stdio.h>
#include <time.h>

int main ()
{
   time_t rawtime;
   struct tm *info;
   char buffer[80];

   time( &rawtime );

   info = localtime( &rawtime );
   printf("��ǰ�ı���ʱ������ڣ�%s", asctime(info));

   return(0);
}
