#include <stdio.h>
#include <stdlib.h>

typedef int bool;
#define true 1
#define false 0

int FindFirstAvailableIdxFrom(bool* list, int start, int list_len)
{
	int i;
	for(i = start+1; i < list_len; i++)
	{
		if(false == list[i])
		{
			return i;
		}
	}
	return -1;
}

// list [in], defines the list of data.
// list_len [in], defines the length of the list.
void Permutation(int* list, int list_len)
{
	int** pointers;
	int** curLevel;
	bool* isOccupied;
	int i;
	int idx;

	pointers = (int**)malloc(sizeof(int*) * list_len);
	isOccupied = (bool*)malloc(sizeof(bool) * list_len);
	for(i=0; i<list_len; i++)
	{
		pointers[i] = NULL;
		isOccupied[i] = false;
	}

	while(true)
	{
		curLevel = pointers;
		while(list_len > curLevel - pointers)
		{
			idx = FindFirstAvailableIdxFrom(isOccupied, 0, list_len);
			if(NULL != *curLevel)
			{
				isOccupied[*curLevel - list] = false;
			}
			*curLevel = list + idx;
			isOccupied[idx] = true;
			curLevel++;
		}

		printf("{");
		for(i=0; i<list_len; i++)
		{
			printf("%d, ", *(*(pointers+i)));
		}
		printf("\b}\n");

		while(-1 == (idx=FindFirstAvailableIdxFrom(isOccupied, *curLevel - list, list_len)))
		{
			if (curLevel == pointers)
			{
				return;
			}
			isOccupied[*curLevel - list] = false;
			curLevel--;
		}
		isOccupied[idx] = true;
		curLevel++;
	}


}




void main()
{
	int a[2] = {1,2};
	Permutation(a, 2);
}