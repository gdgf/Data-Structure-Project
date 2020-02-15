/*
C 库函数 char *ctime(const time_t *timer) 返回一个表示
当地时间的字符串，当地时间是基于参数 timer。
返回的字符串格式如下： Www Mmm dd hh:mm:ss yyyy
其中，Www 表示星期几，
      Mmm 是以字母表示的月份，
      dd 表示一月中的第几天，
      hh:mm:ss 表示时间，
      yyyy 表示年份。
*/
#include <stdio.h>
#include <time.h>

int main ()
{
   time_t curtime;

   time(&curtime);

   printf("当前时间 = %s", ctime(&curtime));

   return(0);
}
