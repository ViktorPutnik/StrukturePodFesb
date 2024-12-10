#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct _element* position;

typedef struct _element
{
	int koef,exp;
	position next;

} element;

int InsertSortedToList(position head, position NextEl);
int InsertAfter(position head, position NextEl);
int DeleteAfter(position Element);
position InsertNew(int koef,int exp);
int GetFromFile(position head,FILE* fp);
int print_list(position first);
int ZbrajanjePolinoma(position head1, position head2,position zbroj);
int UmnozakPolinoma(position head1, position head2, position headMultiply);
int lenghtOfList(position ptr);
int main()
{
	element head = {
		.koef=0,
		.exp=0,
		.next = NULL
	};
	element head1 =
	{
		.koef = 0,
		.exp = 0,
		.next = NULL
	};
	element Zbroj =
	{
		.koef = 0,
		.exp = 0,
		.next = NULL
	};
	element Produkt =
	{
		.koef = 0,
		.exp = 0,
		.next = NULL
	};
	FILE* fp = fopen("zdtk4.txt", "r");
	FILE* fp1 = fopen("drugipol.txt", "r");


	GetFromFile(&head,fp);
	GetFromFile(&head1, fp1);
	print_list(&head);
	printf("\n");
	print_list(&head1);
	ZbrajanjePolinoma(&head, &head1, &Zbroj);
	printf("\n");
	print_list(&Zbroj);
	UmnozakPolinoma(&head, &head1, &Produkt);
	printf("\n");
	print_list(&Produkt);
	//mnozenje i zbrajanje se sprema obrnuto nemam volje fixovat sad al da radi
	return 0;
}



position InsertNew(int koef,int exp)
{
	position NewEl=(position)malloc(sizeof(element));
	if (!NewEl)
	{
		printf("failed to find memory for new person\n");
	}
	NewEl->koef = koef;
	NewEl->exp = exp;
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
	while (temp->next!=NULL && (temp->next->exp < NextEl->exp))
	{
		temp = temp->next;
	}
	
	if (temp->next == NULL || temp->next->exp > NextEl->exp)
	{
		InsertAfter(temp, NextEl);
	}
	else if(temp->next->exp==NextEl->exp)
	{
		int Sumexp = 0;
		Sumexp = temp->next->exp + NextEl->exp;
		if (Sumexp == 0)
		{
			DeleteAfter(temp);
		}free(NextEl);
		
	}
	else
	{
		InsertAfter(temp, NextEl);
	}

	return EXIT_SUCCESS;
}

int InsertAfter(position temp ,position NextEl)
{
	NextEl->next = temp->next;
	temp->next = NextEl;
}


int GetFromFile(position head,FILE* fp)
{
	if (!fp)
	{
		printf("mistake loading the document\n");
		return 1;
	}
	char line[256];
	while (fgets(line, sizeof(line), fp))
	{
		int koef;
		int exp;
		int movingbyte;
		int buf_number = 0;
		
	
		while (sscanf(line+buf_number, "%d %d%n", &koef, &exp, &movingbyte) == 2)
		{
			InsertSortedToList(head, InsertNew(koef, exp));
			buf_number += movingbyte;
		}
	
		fclose(fp);
		return EXIT_SUCCESS;
	}
	
}
int print_list(position first)
{
	position temp = first->next;

	while (temp)
	{
		printf("number:koef %d exp %d \n", temp->koef,temp->exp);
		temp = temp->next;
	}

	return 0;
}

int DeleteAfter(position Element)
{
	position temp = Element->next;
	Element->next = Element->next->next;
	free(temp);
}
//funk za zbrajanja
int ZbrajanjePolinoma(position head1, position head2,position zbroj)
{
	while (head1 != NULL && head2 != NULL) {
		if (head1->exp == head2->exp) {
			int sum = head1->koef + head2->koef;
			if (sum != 0) {
				InsertSortedToList(zbroj, InsertNew(sum, head1->exp));
				head1 = head1->next;
				head2 = head2->next;
				break;
			}
		}
		else if (head1->exp > head2->exp) {
			InsertSortedToList(zbroj, InsertNew(head2->koef, head2->exp));
			head2 = head2->next;
		}
		else if (head1->exp < head2->exp) {
			InsertSortedToList(zbroj, InsertNew(head1->koef, head1->exp));
			head1 = head1->next;
		}



		while (head1 != NULL) {
			InsertSortedToList(zbroj, InsertNew(head1->koef, head1->exp));
			head1 = head1->next;
		}
		while (head2 != NULL)
		{
			InsertSortedToList(zbroj, InsertNew(head2->koef, head2->exp));
			head2 = head2->next;
		}
	}
	return 0;
	
}

int lenghtOfList(position ptr) {
	int len = 0;
	while (ptr != NULL) {
		len++;
		ptr = ptr->next;
	}
	return len;
}
int UmnozakPolinoma(position head1, position head2, position headMultiply) {

	int maxLen = 0;
	if (lenghtOfList(head1) >= lenghtOfList(head2)) {
		maxLen = lenghtOfList(head1);
	}
	else {
		maxLen = lenghtOfList(head2);
	}

	while (maxLen != 0) {
		if (head1 == NULL) {
			InsertSortedToList(headMultiply, InsertNew(head2->koef, head2->exp));
			head2 = head2->next;
			maxLen--;
		}
		else if (head2 == NULL) {
			InsertSortedToList(headMultiply, InsertNew(head1->koef, head1->exp));
			head1 = head1->next;
			maxLen--;
		}
		else {
			headMultiply->koef = head1->koef * head2->koef;
			headMultiply->exp = head1->exp + head2->exp;
			InsertSortedToList(headMultiply, InsertNew(headMultiply->koef, headMultiply->exp));
			head1 = head1->next;
			head2 = head2->next;
			maxLen--;
		}

	}


	return 0;
}
