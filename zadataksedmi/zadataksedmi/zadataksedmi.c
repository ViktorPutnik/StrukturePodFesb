#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#define MAX_DIR_LENGHT 256
#define MAX_COMMAND_LENGHT 256


typedef struct dir* Pos;

typedef struct dir {

	char name[MAX_DIR_LENGHT];

	Pos next;
	Pos Child;
	Pos Parent;
}Dir;

Dir Root =
{
	.name = ":C",
	.next = NULL,
	.Child = NULL,
	.Parent = NULL

};
Pos current = &Root;


Pos CreateDirectory(char* name);
int Command();
int ConnectDirectory(char* name, Pos Parent);
int ChangeDirectory(char* name);
int PrintDirectory(Pos current,int layer);
int PrintDirectoryElement(char* name);
int ReturnToPrev();

int main()
{
	Command();
	

	
	return 0;
}

Pos CreateDirectory(char* name)
{
	Pos NewDirectory = malloc(sizeof(Dir));
	if (!NewDirectory)
	{
		printf("ne moze se alocirati memorija\n");
		return EXIT_FAILURE;
	}
	strncpy(NewDirectory->name, name, sizeof(name));
	NewDirectory->Parent = NULL;
	NewDirectory->Child = NULL;
	NewDirectory->next = NULL;
	return NewDirectory;
}
int ConnectDirectory(char* name, Pos Parent)
{
	Pos New = CreateDirectory(name);
	if (!New)
	{
		printf("nije moguce kreirati novi direktorij\n");
		return EXIT_FAILURE;
	}
	Pos CurChild = current->Child;
	if (CurChild == NULL)
	{
		New->Parent = current;
		current->Child = New;
		return EXIT_SUCCESS;
	}
	while (CurChild->next)
	{
		CurChild = CurChild->next;
	}
	New->Parent = current;
	CurChild->next = New;
	return EXIT_SUCCESS;
}


int PrintDirectory(Pos current,int layer)
{
	Pos temp = current->Child;
	if (temp == NULL)
	{
		return EXIT_FAILURE;
	}
	while (temp)
	{
		for (int i = 0;i < layer;i++)
			printf("\t");
		PrintDirectoryElement(temp->name);
		PrintDirectory(temp,layer+1);
		temp = temp->next;
	}
	return EXIT_SUCCESS;
}
int PrintDirectoryElement(char* name)
{
	printf("[%s]\n", name);
}

int ChangeDirectory(char* name)
{
	Pos temp = current->Child;
	if (temp == NULL)
	{
		return EXIT_SUCCESS;
	}
	while (temp)
	{
		if (strcmp(name, temp->name) == 0)
		{
			current = temp;
			return EXIT_SUCCESS;
		}
		temp = temp->next;
	}
	printf("Taj Direktorij ne postoji\n");
	return EXIT_FAILURE;
}

int ReturnToPrev()
{
	current = current->Parent;
	
	return EXIT_SUCCESS;
}
int Command()
{
	//: 1- "md", 2 - "cd dir", 3 - "cd..", 4 - "dir" i 5 – izlaz.
	int end = 0;
	int Wrongchoice = 0;
	char name[MAX_DIR_LENGHT], choice[MAX_COMMAND_LENGHT];
	memset(name, -1, sizeof(name));
	memset(choice, -1, sizeof(choice));
	while (end == 0)
	{
		if (Wrongchoice == 1)
		{
			printf("that command not exist try again:\n");
			Wrongchoice = 0;
		}
		printf("choose command:\n");
		printf("1-md\n2-cd\n3-cd..\n4-dir\n5-izlaz\n");
		scanf("%s", choice);

		if (strcmp("md", choice) == 0)
		{
			printf("enter name of new Directory: ");
			scanf("%s", name);
			system("cls");
			ConnectDirectory(name, current);
		}
		else if (strcmp("cd", choice) == 0)
		{
			printf("enter name of Directory to change to: ");
			printf("\n");
			PrintDirectory(current,1);
			scanf("%s", name);
			
			ChangeDirectory(name);
		}
		else if (strcmp("cd..", choice) == 0)
		{
			ReturnToPrev();
			}
		else if (strcmp("dir", choice) == 0)
		{
			PrintDirectory(current,1);
		}
		else if (strcmp("izlaz", choice) == 0)
		{
			end = 1;
		}
		else
		{
			Wrongchoice = 1;
		}

	}
	return EXIT_SUCCESS; 
}
