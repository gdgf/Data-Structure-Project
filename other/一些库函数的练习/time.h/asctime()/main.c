/*
返回值:
该函数返回一个 C 字符串，包含了可读格式的日期和时间
信息 Www Mmm dd hh:mm:ss yyyy，
其中，  Www 表示星期几，
        Mmm 是以字母表示的月份，
        dd 表示一月中的第几天，
        hh:mm:ss 表示时间，
        yyyy 表示年份。
*/
#include <stdio.h>
#include <string.h>
#include <time.h>

int main()
{
   struct tm t;

   t.tm_sec    = 10;
   t.tm_min    = 10;
   t.tm_hour   = 6;
   t.tm_mday   = 25;
   t.tm_mon    = 2;
   t.tm_year   = 89;
   t.tm_wday   = 6;

   puts(asctime(&t));

   return(0);
}
