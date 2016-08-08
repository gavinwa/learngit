#include <stdio.h>
#include <stdlib.h>

/*   
display the content of a piece of memory. waht are you doing now?
*/
void memViewer(void *p, int length, int width)
{
	int i = 0;
	int j = 0;
	unsigned char c;
	unsigned char* plocal = (unsigned char*)p;

	for(i=0; i<length; i+=width)
	{
		// 1) In section 1, the address should be displayed in hexadecimal 
		// taking 8 characters.
		printf("0X%08X:  ", plocal);

		// 2) In section 2, the hexadecimal value of each byte occupies 2 
		// characters, if less than 16, a leading '0' is needed. 
		// e.g., "0C", "3A".
		for(j=0; j<width; j++)
		{
			//Leave blanks if there is nothing remaining to fill. 
			if ( (i+j)>=length )
			{
				printf("   ");
			}
			else
			{
				printf("%02x ", *(plocal+j));
			}
		}

		// 3) In section 3, display the character whose ASCII code is the 
		// byte's value if its range is from 32 to 126(including 32 and 126). 
		// Otherwise, display only a '.'
		for(j=0; j<width && (i+j)<length; j++)
		{
			c = *(plocal+j);
			if ((c >= 32) && (c <= 126))
			{
				printf("%c", c);
			}
			else
			{
				printf(".");
			}
		}
		plocal+=width;
		printf("\n");
	}
}

void main()
{
	int i = 0;
	unsigned char array[256] = {0};
	for(i = 0; i < 256; i++)
	{
		array[i] = i;
	}
	memViewer(array, 256, 15);
}