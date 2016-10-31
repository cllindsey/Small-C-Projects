/* 
Christopher Lindsey

Date: 3/9/2016

===================================
INCLUDING LIBRARIES AND DEFINITIONS
===================================
*/

#include <stdio.h>
#include <string.h>

// Defining MAX
#define MAX 20


/*
==================================================================
STRUCTURE DEFINITION
Purpose: Creating a structure to hold information for the schedule
==================================================================
*/

struct event
{
	int hour;		// Integer for the hour of the event
	int minute;		// Integer for the minutes of the event
	char description[41];	// Character String for the descrtiption of the event (maximum 40 characters)
};

typedef struct event Event;

// End of structure definition of Event

/*
=================
FUNCTION PROTYPES
=================
*/

int InputRange(int min, int max);				// Input Range protype
Event* InputEvent(Event *newEvent);				// Input Event protype (from the structure event)
int AddEventAtIndex(Event list[], Event e, int i);		// Add Event at Index protype
int InsertionSortEvent(Event list[], int *p_size, Event e);	// Insertion Sort protype
void DisplayEvent(Event e);					// Display Event protype
void DisplayEventList(Event list[], int size);			// Display Event List protype
int DeleteEvent(Event list[], int i, int *p_size);		// Delete Event protype

/*
=======================
BONUS FUNCTION PROTYPES
=======================
*/

int SaveEventList(char *filename,Event list[],int size);	// Save Event List protype
int LoadEventList(char *filename,Event list[],int *p_size);	// Load Event List protype
char* encode(char*s);						// Encode protype
char* decode(char*s);						// Decode protype

/*
=============
MAIN FUNCTION
=============
*/

int main ()
{
	// Defining variables
	Event eventList[MAX];
	int eventListSize = 0, menuSelection = 0;
	int exit = 0, delete, i;
	Event newEvent = {0,0," "};
	
	
	// Interactive Menu
	do
	{
		// Asking the user for menu selection
		printf("__= Scheduler v1.0 =__\n 1. Schedule an event.\n 2. Delete an event.\n 3. Display schedule.\n 4. Save schedule.\n 5. Load schedule.\n 6. Exit\n\n");
		menuSelection = InputRange(1,6);

		// Switch case for interactive menue
		switch (menuSelection)
		{
			// Case 1 for adding and sorting events
			case 1: if (eventListSize < MAX)
					InsertionSortEvent(eventList, &eventListSize, *InputEvent(&newEvent));
				else
				{
					// Informing user of a full schedule (5 events)
 					printf("The maximum number of events you can add to the schedule has been reached!\nWe apologize for any inconvenience this may cause.\n\n");
				}
				break;

			// Case 2 for deleting an event
			case 2: printf("What event index do you wish to delete? or type -1 to cancel.\n");
				
				// Displaying the users schedule for reference before deleting
				DisplayEventList(eventList, eventListSize);
				printf("\n:");
				scanf("%d", &delete);
				
				DeleteEvent(eventList, delete, &eventListSize);
			
				break;
			
			// Case 3 for displaying the event list
			case 3: DisplayEventList(eventList, eventListSize);
				break;
			
			// Case 4 for saving the event list BONUS
			case 4: SaveEventList("myschedule.txt", eventList, eventListSize);
				break;
			
			// Case 5 for deleting the current list before loading the saved list BONUS
			case 5: for (i = 0; i < eventListSize; i++)
				{
					DeleteEvent(eventList, i, &eventListSize);
				}		
				LoadEventList("myschedule.txt", eventList, &eventListSize);
				
				break;
			
			// Case 6 for ending the program
			case 6: exit = 1;
				break;
			
			// Default case for an invalid input
			default: printf("Invalid Input\n\n");
				 break;
		}

	} while (exit != 1);
	
	// Returnig 0 to end program
	return 0;
}

/*
=========================
MAIN ASSIGNMENT FUNCTIONS
=========================
*/

/*
===============================================
INPUT RANGE FUNCTION
Purpose: To take in input values based of range
Input: A minimum and a maximum integer value
Output: Returns the value the user inputted
===============================================
*/

int InputRange(int min, int max)
{
	int value = 0;
			
	do
	{
		// Takes in an integer in the range
		printf("Please enter an integer between %d and %d: ", min, max);
		scanf("%d", &value);
		printf("\n");
		
		// Checks invalid input
		if (value < min || value > max)
			printf("Invalid Input\n\n");
			
	} while (value < min || value > max);
	
	return value;
}

/*
=================================================================================
INPUT EVENT FUNCTION
Purpose: To create an event to be scheduled with an hour, minute, and description
Input: A blank event structured {0,0," "}
Output: Returns the new event structured {hour,minute,description}
=================================================================================
*/

Event* InputEvent(Event *newEvent)
{	
	if (newEvent != NULL) // make sure the pointer is valid
 	{

		// Gets user input for hour, minute, description
 		printf("Enter the event time:\n");
		newEvent->hour = InputRange(0, 23);
		newEvent->minute = InputRange(0, 59);
		printf("Enter the event description: ");
		scanf("%*c%[^\n]s",newEvent->description);
		
	}
 	
 	return newEvent;
}

/*
===========================================================================
ADD EVENT AT INDEX FUNCTION
Purpose: to add an event at the next available index in the schedule
Input: The event list, the event to be added, and the current index number
Output: Returns the index the event was inserted at
==========================================================================
*/

int AddEventAtIndex(Event list[], Event e, int i)
{
	// Adds the event
	list[i] = e;
	return i;
	
}

/*
=========================================================================
INSERTON SORT FUNCTION
Purpose: To perform an insertion sort on the curent schedule 
Input: The event list, the pointer to the list size , the new event added
Output: Returns a to end the function
=========================================================================
*/

int InsertionSortEvent(Event list[], int *p_size, Event e)
{
	// Adds event at index
	AddEventAtIndex(list, e, *p_size);
	(*p_size)++;
	
	int a, b;
	Event temp;
	
	// Sorts based on hours
	for (a = 1; a < *p_size; a++)
	{
		temp = list[a];
		b = a - 1;
		
		while (b >= 0 && list[b].hour > temp.hour)
		{
			list[b+1] = list[b];
			b = b - 1;
		}
		
		list[b+1] = temp;
	}
	
	// If hours are the same, sorts based on minutes
	for (a = 1; a < *p_size; a++)
	{
		temp = list[a];
		b = a - 1;
		if (list[b].hour == temp.hour)
		{
			while (b >= 0 && list[b].minute > temp.minute)
			{
				list[b+1] = list[b];
				b = b - 1;
			}
		
			list[b+1] = temp;
		}
	}
	return a;
} 	
 
/*
====================================================
DISPLAY EVENT FUNCTION
Purpose: To display an event 
Input: The event to be displayed
Output: Returns nothing due to being a void function
====================================================
*/	

void DisplayEvent(Event e)
{

	// Displays the event 
	printf("%02d:%02d %s\n",e.hour, e.minute, e.description);
	return;
}

/*
====================================================
DISPLAY EVENT LIST FUNCTION
Purpose: To display all currently scheduled events 
Input: The event list, and current event list size
Output: Returns nothing due to being a void function
====================================================
*/	
	
void DisplayEventList(Event list[], int size)
{
	int i = 0;
	
	// For loop to display the events
	for (i = 0; i < size; i++)
	{
		printf("[%d] ",i);
		DisplayEvent(list[i]);
	}
	printf("\n");
	return;
}

/*
====================================================================================
DELETE EVENT FUNCTION
Purpose: To delete an event 
Input: The event list, the index the event is at, the pointer to the event list size
Output: Returns 0 to end the function
====================================================================================
*/	

int DeleteEvent(Event list[], int i, int *p_size)
{
	int a = 0;
	
	// Checks if -1 to end delete without deleting
	if (i == -1)
	{
		return 0;
	}
	
	// Removes event at index then shifts other events down to the proper index position
	else
	{
		for (a = i; a < *p_size; a++)
		{
			list[a] = list[a+1];
		}
		(*p_size)--;
	}
	
	return 0;
}

/*
===============
BONUS FUNCTIONS
===============
*/

/*
===================================================================
SAVE EVENT LIST FUNCTION
Purpose: To save the schedule
Input: The pointer to the file, the event list, the event list size
Output: Returns 0 to end the function
===================================================================
*/	

int SaveEventList(char *fptr, Event list[], int size)
{	
	int i = 0;
	
	// Opens writable file
	FILE *fp;
	fp = fopen(fptr,"w");
	
	// Saves events to the file
	for (i = 0; i < size; i++)
	{
		fprintf(fp, "%d %d %s\n", list[i].hour, list[i].minute, list[i].description);
		// Encodes the list descriptions
		encode(list[i].description);
	}
	
	// Closes file
	fclose(fp);
	printf("File successfully saved!\n\n");
	return 0;
}

/*
============================================================================
LOAD EVENT LIST FUNCTION
Purpose: To load the saved event list
Input: The pointer to the file, the event list, the pointer to the list size
Output: Returns i to end the function
============================================================================
*/	
	
int LoadEventList(char *fptr, Event list[], int *p_size)
{
	// To open a readable file
	FILE *fp;
	int i = 0;
	fp = fopen(fptr, "r");
	
	// Checks if file exists
	if (fp == NULL)
	{
		printf("Error: File was not found. \n");
		return -1;
	}
	
	// Scans in the informaon from the file
	while (fscanf(fp, "%d %d %s\n", &list[i].hour, &list[i].minute, list[i].description) > 0)
	{
		// Decodes the file
		decode(list[i].description);
		i++;
		(*p_size)++;
	}
	
	// CLoses the file
	fclose(fp);
	
	printf("Successfully loaded %d events from %s! \n", i, fptr);
	return i;
}

/*
=============================================
ENCODE FUNCTION
Purpose: To encode the description when saved
Input: The string to be encoded
Output: Returns s to end the function
=============================================
*/	

char * encode(char * s)	
{
	char rep = '_';
	
	// Encodes the spaces with underscores
	while (*s != '\0')
	{
		if (*s == ' ')
		{
			*s = rep;
		}
		s++;
	}
	return s;
}

/*
==============================================
DECODE FUNCTION
Purpose: To decode the description when loaded
Input: The string to be decoded
Output: Returns s to end the function
==============================================
*/

char * decode(char * s)
{
	char rep = ' ';
	
	while (*s != '\0')
	{
		if (*s == ' ')
		{
			*s = rep;
		}
		s++;
	}
	return s;
}
	
	
