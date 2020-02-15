/**
 * merge_sort: 非递归实现 --迭代
 * 非递归思想: 将数组中的相邻元素两两配对。用merge函数将他们排序，
 * 构成n/2组长度为2的排序好的子数组段，然后再将他们排序成长度为4的子数组段，
 * 如此继续下去，直至整个数组排好序。
**/

#include <stdio.h>
#include <stdlib.h>
#define LEN 8

// merge_sort(): 非递归实现-自底向上
// 将原数组划分为left[min...max] 和 right[min...max]两部分
void merge_sort(int *list, int length)
{
	int i, left_min, left_max, right_min, right_max, next;
	int *tmp = (int*)malloc(sizeof(int) * length);

	if (tmp == NULL)
	{
		fputs("Error: out of memory\n", stderr);
		abort();
	}

	for (i = 1; i < length; i *= 2) // i为步长，1,2,4,8……
	{
		for (left_min = 0; left_min < length - i; left_min = right_max)
		{
			right_min = left_max = left_min + i;
			right_max = left_max + i;

			if (right_max > length)
				right_max = length;

			next = 0;
			while (left_min < left_max && right_min < right_max)
				tmp[next++] = list[left_min] > list[right_min] ? list[right_min++] : list[left_min++];

			while (left_min < left_max)
				list[--right_min] = list[--left_max];

			while (next > 0)
				list[--right_min] = tmp[--next];
		}
	}

	free(tmp);

}


int main(void)
{
	int a[LEN] = { 5, 2, 4, 7, 1, 3, 2, 6 };
	merge_sort(a, LEN);

	// print array
	int i;
	for (i = 0; i < LEN; i++)
		printf("%d ", a[i]);

	return 0;
}