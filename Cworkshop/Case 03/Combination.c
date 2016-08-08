#include <stdio.h>
#include <stdlib.h>

//          --- --- ---
// pAssign | . | . | . |
//          -*- -#- -$-
// 
//          -*- -#- --- -$- ---
// list    | 2 | 6 | 7 | 9 |
//          --- --- --- --- ---
// Idea: multiple tree traversal algorithm.

void Combine(int* list, int list_len, int cmb)
{
	int** pAssign;
	int curAssign = 0;
	int i;

	if (NULL == list || 0 == list_len || 0 == cmb)
	{
		return;
	}

	pAssign = (int**)malloc(sizeof(int*) * cmb);
	pAssign[0] = list;
	curAssign = 1;
	
	while (1)
	{
		// (Still need to assign)
		// and (amount need to assign <= amount available for assignment)
		while ((curAssign < cmb) &&
			(cmb-curAssign) <= (list_len - (pAssign[curAssign-1]-list) - 1))
		{
			pAssign[curAssign] = pAssign[curAssign-1] + 1;
			curAssign++;
		}

		// If all cmb have assigned then output.
		if (curAssign>=cmb)
		{
			printf("(");
			for(i = 0; i < cmb; i++)
			{
				printf("%d, ", *pAssign[i]);
			}
			printf("\b\b)\n");
			curAssign--;
		}

		// Find the position to walk right.
		while (pAssign[curAssign]-list >= list_len-1)
		{
			curAssign--;
		}

		// If no cmb can walk right then return.
		if (-1 == curAssign)
		{
			free(pAssign);
			return;
		}

		// walk right.
		pAssign[curAssign]++;
		curAssign++;
	}
}
