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
int GetFromFile(char* line,char*token,position head,int file);
int print_list(position first);
int ZbrajanjePolinoma(position head1, position head2,position zbroj);
int MnozenjePolinoma(position head1, position head2,position produkt);
int DuljinaPolinoma(position head);
int main()
{
	element head = {
		.koef=0,
		.next = NULL
	};
	element head1 =
	{
		.koef = 0,
		.next = NULL
	};
	element Zbroj =
	{
		.koef = 0,
		.next = NULL
	};
	element Produkt =
	{
		.koef = 0,
		.next = NULL
	};
	char line[256];
	char* token;
	GetFromFile(line,&token,&head,1);
	print_list(&head);
	GetFromFile(line, &token, &head1,2);
	printf("\n");
	print_list(&head1);
	ZbrajanjePolinoma(&head, &head1, &Zbroj);
	printf("\n");
	print_list(&Zbroj);
	MnozenjePolinoma(&head, &head1, &Produkt);
	printf("\n");
	print_list(&Produkt);

	//mnozenje i zbrajanje se sprema obrnuto nemam volje fixovat sad al da radi
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


int GetFromFile(char* line,char* token,position head,int file)
{
	int koef;
	FILE* fp = fopen("zdtk4.txt", "r");
	FILE* fp1 = fopen("drugipol.txt", "r");
	switch (file)
	{
	case 1:
		while (fgets(line, sizeof(line), fp))
		{
			token = strtok(line, " ");
			while (token != NULL)
			{
				koef = atoi(token);
				InsertSortedToList(head, InsertNew(koef));
				token = strtok(NULL, " ");

			}
		}
		koef = 0;
		fclose(fp);
		break;
	case 2:
		while (fgets(line, sizeof(line), fp1))
		{
			token = strtok(line, " ");
			while (token != NULL)
			{
				koef = atoi(token);
				InsertSortedToList(head, InsertNew(koef));
				token = strtok(NULL, " ");

			}
		}
		fclose(fp1);
		break;
	}
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
int ZbrajanjePolinoma(position head1, position head2,position zbroj)
{
	position temp1 = head1;
	position temp2 = head2;
	
	int lenght;
	
	lenght = DuljinaPolinoma(head1) > DuljinaPolinoma(head2) ? DuljinaPolinoma(head1) : DuljinaPolinoma(head2);
	while (lenght != 0)
	{
		if (temp1->next || temp2->next)
		{
			position New = (position)malloc(sizeof(element));
			New->koef = temp1->next->koef + temp2->next->koef;
			New->next = zbroj->next;
			zbroj->next = New;
			temp1 = temp1->next;
			temp2 = temp2->next;
		}
		lenght--;
	}
}

int DuljinaPolinoma(position head)
{
	int count = 0;
	position temp = head;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	return count;
}
//funk za mnozenja
int MnozenjePolinoma(position head1, position head2, position produkt)
{
	position temp1 = head1;
	position temp2 = head2;

	int lenght;

	lenght = DuljinaPolinoma(head1) > DuljinaPolinoma(head2) ? DuljinaPolinoma(head1) : DuljinaPolinoma(head2);
	while (lenght != 0)
	{
		if (temp1->next || temp2->next)
		{
			position New = (position)malloc(sizeof(element));
			New->koef = temp1->next->koef * temp2->next->koef;
			New->next = produkt->next;
			produkt->next = New;
			temp1 = temp1->next;
			temp2 = temp2->next;
		}
		lenght--;
	}

}