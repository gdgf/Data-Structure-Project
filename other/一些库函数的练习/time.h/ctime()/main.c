/*
C �⺯�� char *ctime(const time_t *timer) ����һ����ʾ
����ʱ����ַ���������ʱ���ǻ��ڲ��� timer��
���ص��ַ�����ʽ���£� Www Mmm dd hh:mm:ss yyyy
���У�Www ��ʾ���ڼ���
      Mmm ������ĸ��ʾ���·ݣ�
      dd ��ʾһ���еĵڼ��죬
      hh:mm:ss ��ʾʱ�䣬
      yyyy ��ʾ��ݡ�
*/
#include <stdio.h>
#include <time.h>

int main ()
{
   time_t curtime;

   time(&curtime);

   printf("��ǰʱ�� = %s", ctime(&curtime));

   return(0);
}
