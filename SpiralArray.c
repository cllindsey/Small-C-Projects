/*
Christopher Lndsey
02/10/2016
*/

// Include and definitions
#include <stdio.h>
#define ROW 20
#define COL 20

// Function Protypes
void PopulateArray2DUnique (int A[][COL], unsigned int rowsize, unsigned int colsize, int min, int max);
void DisplayArray2D(int A[][COL], unsigned int rowsize, unsigned int colsize);
int FindLargest(int A[][COL], unsigned int rowsize, unsigned int colsize);
int FindColSum(int A[][COL], unsigned int rowsize, unsigned int colsize, unsigned int col_to_sum);
int Sort2DArray(int A[][COL], unsigned int rowsize, unsigned int colsize);
int CopyArray2D(int A[][COL], int B[][COL], unsigned int rowsize, unsigned int colsize);
int CopyArray2DSpiral(int A[][COL], int B[][COL], unsigned int rowsize, unsigned int colsize);

// Main Program
int main (void)
{ 
	unsigned int rowsize = 0, colsize = 0;
	int min, max, A[ROW][COL], B[ROW][COL], largestNum, colSum, col;

	// FInding the number of rows
	printf("PLease type in the number of rows you wish to have in your array from 1 to 20: \n");
	scanf("%d", &rowsize);
	while (rowsize < 1 || rowsize > 20)
	{
		printf("Invalid Input! Please enter a value between 1 and 20: \n");
		scanf("%d", &rowsize);
	}

	// Fnding the number of columns
	printf("PLease type in the number of columns you wish to have in your array from 1 to 20: \n");
	scanf("%d", &colsize);
	while (colsize < 1 || colsize > 20)
	{
		printf("Invalid Input! Please enter a value between 1 and 20: \n");
		scanf("%d", &colsize);
	}

	//FInding the min value
	printf("What is the minimum number you wish to have in your array from 1 to 99?: \n");
	scanf("%d", &min);
	while (min < 1 || min > 99)
	{
		printf("Invalid Input! Please enter a value between 1 and 99: \n");
		scanf("%d", &min);
	}

	// Finding the max value
	printf("What is the maximum number you wish to have in your array from 1 to 99?: \n");
	scanf("%d", &max);
	while (max < 1 || max > 99)
	{
		printf("Invalid Input! Please enter a value between 1 and 99: \n");
		scanf("%d", &max);
	}

	// Populates the array
	PopulateArray2DUnique (A, rowsize, colsize, min, max);

	// Displays the array
	DisplayArray2D (A, rowsize, colsize);

	// Sorts the array in ascending order
	Sort2DArray (A, rowsize, colsize);

	// Displays array A
	printf("\nArray A: \n");
	DisplayArray2D (A, rowsize, colsize);
	
	// Copies array A to array B
	CopyArray2D (A, B, rowsize, colsize);

	// Copies array A to array B but in a spiral formation
	CopyArray2DSpiral (A, B, rowsize, colsize);
	printf("\nSpiral Array: \n");
	DisplayArray2D (B, rowsize, colsize);
	
} 

// Function to populate the array with values up to 20 x 20
void PopulateArray2DUnique (int A[ROW][COL], unsigned int rowsize, unsigned int colsize, int min, int max)
{
	int a, b;

	// Ensures numbers are always random
	srand (time(NULL));

	// Populating the array with the random numbers
	for (a = 0; a < rowsize; a++)
	{
		for (b = 0; b < colsize; b++)
		{
			A[a][b] = (rand () % (max-min)+min+1);
		}
	}

	return;
}

// Function to display the array to the screen
void DisplayArray2D(int A[][COL], unsigned int rowsize, unsigned int colsize)
{
	int a, b;

	// Printing the array to the screen
	for (a = 0; a < rowsize; a++)
	{
		for (b = 0; b < colsize; b++)
		{
			// Makes values under 10 to be displayed with a zero in front
			if (A[a][b] < 10)
				printf("0%d ", A[a][b]); 
			else
				printf("%d ", A[a][b]);
		}
		printf("\n");
	}

	return;
}

// Function to find the largest number in the array
int FindLargest(int A[][COL], unsigned int rowsize, unsigned int colsize)
{
	int a, b, largest = 0;

	// Finding what the largest number in the array is
	for (a = 0; a < rowsize; a++)
	{
		for (b = 0; b < colsize; b++)
		{	
			// If the current value is larger then the previous largest they switch
			if (A[a][b] > largest)
				largest = A[a][b];
		}
	}
	
	// Returns the largest value
	return largest;
}

// Function for finding the sum of a given column
int FindColSum(int A[][COL], unsigned int rowsize, unsigned int colsize, unsigned int col_to_sum)
{
	int a, sum = 0; 

	// FInding the sum of the selected column
	for (a = 0; a < colsize; a++)
	{	
		sum += A[a][col_to_sum];
	}
	
	// Returns the sum of the column
	return sum;
}

// Sorts the array into ascending order
int Sort2DArray(int A[][COL], unsigned int rowsize, unsigned int colsize)
{
	int a, b, k = 0, temp1, temp2, C[rowsize * colsize];

	// Bubble Sort method
	for (a = 0; a < (int)rowsize; a++)
	{
		for (b = 0; b < (int)colsize; b++)
		{
			C[k] = A[a][b];
			k++;
		}
	}
	k = 0;
	for (temp1 = 0; temp1 < (int)(rowsize*colsize); temp1++)
	{
		for (k = 0; k < (int)(rowsize*colsize-1); k++)
		{
			if (C[k] > C[k+1])
			{
				temp2 = C[k];
				C[k] = C[k+1];
				C[k+1] = temp2;
			}		
		}
	}
	k = 0;
	for (a = 0; a < (int)rowsize; a++)
	{
		for (b = 0; b < (int)colsize; b++)
		{
			A[a][b] = C[k];
			k++;
		}
	}

	return 0;
}

// Function to copy array A into array B
int CopyArray2D(int A[][COL], int B[][COL], unsigned int rowsize, unsigned int colsize)
{
	int a, b;

	// Copying the array to the new array
	for (a = 0; a < rowsize; a++)
	{
		for (b = 0; b < colsize; b++)
		{
			B[a][b] = A[a][b];
		}
	}

	return 0;
}

// Function to make array B appear in a spiral pattern
int CopyArray2DSpiral(int A[][COL], int B[][COL], unsigned int rowsize, unsigned int colsize)
{
	int a, b, c, d, e, x = 0, y = 0, k = 0;

	// Four loops tp create the spiraling pattern
	for (a = 0; a < (rowsize / 2) + rowsize % 2; a++)
	{
		if (k < rowsize * colsize)
		{
			for (b = a; b < colsize - a; b++)
			{
				B[a][b] = A[x][y];
\
				if (y == colsize - 1)
				{
					y = 0;
					x++;
				}
				else
				{
					y++;
				}

				k++;
			}
		}
		if (k < rowsize * colsize)
		{
			for (c = 1 + a; c <= rowsize - 1 - a; c++)
			{
				B[c][colsize - 1 - a] = A[x][y];
\
				if (y == colsize - 1)
				{
					y = 0;
					x++;
				}
				else
				{
					y++;
				}

				k++;
			}
		}
		if (k < rowsize * colsize)
		{
			for (d = colsize - 2 - a; d >= a; d--)
			{
				B[rowsize - 1 - a][d] = A[x][y];
\
				if (y == colsize - 1)
				{
					y = 0;
					x++;
				}
				else
				{
					y++;
				}

				k++;
			}
		}
		if (k < rowsize * colsize)
		{
			for (e = rowsize - 2 - a; e >= 1 + a; e--)
			{
				B[e][a] = A[x][y];
\
				if (y == colsize - 1)
				{
					y = 0;
					x++;
				}
				else
				{
					y++;
				}

				k++;
			}
		}
	}
	return 0;
}










