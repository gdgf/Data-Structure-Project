/*
����ֵ:
�ú�������һ�� C �ַ����������˿ɶ���ʽ�����ں�ʱ��
��Ϣ Www Mmm dd hh:mm:ss yyyy��
���У�  Www ��ʾ���ڼ���
        Mmm ������ĸ��ʾ���·ݣ�
        dd ��ʾһ���еĵڼ��죬
        hh:mm:ss ��ʾʱ�䣬
        yyyy ��ʾ��ݡ�
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
