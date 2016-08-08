#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int* set;
    int size;
} T_DATA_SET;
              
//               curSits  pElem     slist
//                 ---     ---      --- ---
//                | 0 |   | --|->  | 1 | 2 |
//                 ---     ---      -^- --- ---
// curLevel -->   | 1 |   | --|->  | 4 | 5 | 6 |
//                 ---     ---      --- -^- ---
//                | 0 |   | --|->  | 7 | 8 |
//                 ---     ---      -^- --- 

// Output the Cartesian product of specialed sets.
// slist [in], defines the list of all the data sets
// list_len [in], defines the length of the list
// Idea: multiple tree traversal algorithm
void Product(T_DATA_SET* slist, int list_len)
{
	int** pElem;	// Array of pointers which point to current position of each list.
	int* curSits;	// Array of index which hold the current position of each list.
	int curLevel;	// Index of current list.
	int i;
	
	if (NULL == slist || 0 == list_len)
	{
		return;
	}
	
	pElem = (int**)malloc(sizeof(int*) * list_len);
	curSits = (int*)malloc(sizeof(int) * list_len);
	// Initialize elements in pElem, point to set of each list.
	for (i = 0; i < list_len; i++)
	{
		pElem[i] = slist[i].set;
		curSits[i] = 0;
	}

	while (1 == 1)
	{
		// Move down untile the last level.
		curLevel = list_len - 1;

		// Output result of current position.
		printf("(");
		for(i=0;i<list_len;i++)
		{
			printf("%d, ", *(pElem[i]));
		}
		printf("\b\b)\n");

		// Can current level walk right?
		while (curSits[curLevel] == slist[curLevel].size-1)
		{
			// If have arrived the top level.
			if (0 == curLevel)
			{
				free(pElem);
				free(curSits);
				return;
			}
			// Reset pointer in current level to origin.
			curSits[curLevel] = 0;
			pElem[curLevel] = slist[curLevel].set;
			curLevel--;
		}

		// Walk one step right in current level.
		curSits[curLevel]++;
		pElem[curLevel]++;
	}
}

void Combine(int* list, int list_len, int cmb);

void main()
{
	T_DATA_SET slist[3];
	int set0[2] = {1, 2};
	int set1[5] = {4, 5, 6, 7, 8};	
	int set2[2] = {7, 8};
	slist[0].set = set0;
	slist[0].size = 2;
	slist[1].set = set1;
	slist[1].size = 5;
	slist[2].set = set2;
	slist[2].size = 2;
	
	Product(slist, 3);

	printf("******\n");

	Combine(set1, 5, 3);
}

