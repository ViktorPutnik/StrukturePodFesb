#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct _element* position;

typedef struct _element
{
	int koef;
	position next;

} element;

int InsertSortedToList(position head, position NextEl);
int InsertAfter(position head, position NextEl);
int DeleteAfter(position Element);
position InsertNew(int koef);
int GetFromFile(char* line,char*token,position head);
int print_list(position first);
int main()
{
	element head = {
		.koef = 0,
		.next = NULL
	};
	char line[256];
	char* token;
	GetFromFile(line,&token,&head);
	print_list(&head);
	return 0;
}



position InsertNew(int koef)
{
	position NewEl=(position)malloc(sizeof(element));
	if (!NewEl)
	{
		printf("failed to find memory for new person\n");
	}
	NewEl->koef = koef;
	NewEl->next = NULL;
	return NewEl;
}



int InsertSortedToList(position head, position NextEl)
{
	position temp = head;
	if (!NextEl)
	{
		printf("failed to allocate memory \n");
	}
	while (temp->next!=NULL && (temp->next->koef < NextEl->koef))
	{
		temp = temp->next;
	}
	
	if (temp->next == NULL || temp->next->koef > NextEl->koef)
	{
		InsertAfter(temp, NextEl);
	}
	else
	{
		int SumKoef = 0;
		SumKoef = temp->next->koef - NextEl->koef;
		if (SumKoef == 0)
		{
			DeleteAfter(temp);
		}free(NextEl);
		
	}

	return EXIT_SUCCESS;
}

int InsertAfter(position temp ,position NextEl)
{
	NextEl->next = temp->next;
	temp->next = NextEl;
}


int GetFromFile(char* line,char* token,position head)
{
	int koef;
	FILE* fp = fopen("zdtk4.txt", "r");
	while (fgets(line, sizeof(line), fp))
	{
		token = strtok(line, " ");
		while (token != NULL)
		{
			koef =  atoi(token);
			InsertSortedToList(head, InsertNew(koef));
			token = strtok(NULL, " ");
			
		}
	}
	fclose(fp);
}
int print_list(position first)
{
	position temp = first;

	while (temp)
	{
		printf("number: %d \n", temp->koef);
		temp = temp->next;
	}

	return 0;
}

int DeleteAfter(position Element)
{
	Element->next = NULL;
}
//funk za zbrajanja


//funk za mnozenja
