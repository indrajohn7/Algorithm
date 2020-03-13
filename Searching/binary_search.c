#include<stdio.h>
#include<stdlib.h>


int search(int arr[], int start, int end, int ch)
{
	int middle = (start + end)/2 ;
	int size = (end - start + 1);
	if (arr[middle] == ch)
		return middle;
	else if (size <= 1)
		return -1;
	else if (arr[middle] > ch)
		search(arr, start, middle-1, ch);
	else 
		search(arr, middle+1, end, ch);
}


int main()
{
	int i, size, ch;
	int arr[] = {1,12,23,34,45,56,67,78,89,90,91};
	size = sizeof(arr)/sizeof(int);
	for(i = 0; i < size; i++)
		printf("%d\t",arr[i]);
	printf("\nEnetr the number to be found: ");
	scanf("%d", &ch);
	int res = search(arr, 0, size, ch);
	if(res == -1)
		printf("Not Found:\n");
	else
		printf("Found at index: %d\n", res);
	return 0;
}
