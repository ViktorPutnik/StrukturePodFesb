#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>


struct article;
typedef struct article* articlePos;
typedef struct article {
	char name[20];
	double quantity;
	double price;
	articlePos next;
}Article;

Article NULL_ART = {
	.name = {0},
	.price = 0.0,
	.quantity = 0,
	.next = NULL
};

struct receipt;
typedef struct receipt* receiptPos;
typedef struct receipt {
	char dateTime[11];
	Article article;
	receiptPos nextRe;
}Receipt;



void ReadReceiptFromFile(receiptPos);
void ReadArticleFromFile(articlePos, FILE*);
void SortReceiptByDate(receiptPos, receiptPos);
void SortArticleAlphabeticaly(articlePos, articlePos);
articlePos CreateArticle(char[], double, double);
receiptPos CreateReceipt(char[]);
void InsertArticleAfter(articlePos, articlePos);
void InsertReceiptAfter(receiptPos, receiptPos);
int DateTimeComparison(char[], char[]);
void PrintReceipt(receiptPos);
void PrintArticle(articlePos);
void SpendOnItem(receiptPos);



int main(void) {
	Receipt headRec = {
		.dateTime = " ",
		.nextRe = NULL,
		.article = {
			.name = " ",
			.price = 0.0,
			.quantity = 0.0}
	};

	ReadReceiptFromFile(&headRec);
	SpendOnItem(&headRec);


}

void ReadReceiptFromFile(receiptPos headRec) {
	FILE* fp = fopen("racuni.txt", "r");
	if (fp == NULL) {
		printf("Greska pri otvaranju datoteke1.");
		return;
	}
	char fileName[100];
	char receiptDate[11];

	while (fscanf(fp, "%s", fileName) == 1) {
		FILE* fp1 = fopen(fileName, "r");
		if (fp1 == NULL) {
			printf("Greska pri otvaranju datoteke 2.");
			continue;
		}
		fgets(receiptDate, 11, fp1);
		receiptDate[strcspn(receiptDate, "\n")] = '\0';
		receiptPos newReceipt = CreateReceipt(receiptDate);
		ReadArticleFromFile(&newReceipt->article, fp1);
		SortReceiptByDate(headRec, newReceipt);
	}


	fclose(fp);
	PrintReceipt(headRec);

}

void ReadArticleFromFile(articlePos headArt, FILE* fp) {
	if (fp == NULL) {
		printf("Greska pri otvaranju filea");
		return;
	}
	char articleName[15];
	double articlePrice;
	double articleQuantity;


	while (!feof(fp)) {
		if (fscanf(fp, "%s %lf %lf", articleName, &articleQuantity, &articlePrice) == 3) {
			articlePos newArticle = CreateArticle(articleName, articleQuantity, articlePrice);
			SortArticleAlphabeticaly(headArt, newArticle);
		}
	}

	fclose(fp);

}

articlePos CreateArticle(char name[], double quantity, double price) {
	articlePos newArticle = (articlePos)malloc(sizeof(Article));
	if (newArticle == NULL) {
		printf("Nema mjesta u memoriji");
		return NULL;
	}
	strcpy(newArticle->name, name);
	newArticle->quantity = quantity;
	newArticle->price = price;
	newArticle->next = NULL;
	return newArticle;
}

receiptPos CreateReceipt(char receiptDate[]) {
	receiptPos newReceipt = (receiptPos)malloc(sizeof(Receipt));
	if (newReceipt == NULL) {
		printf("Nema mjesta u memoriji");
		return NULL;
	}

	strcpy(newReceipt->dateTime, receiptDate);
	newReceipt->article.next = NULL;
	newReceipt->nextRe = NULL;

	return newReceipt;

}

void SortArticleAlphabeticaly(articlePos headRec, articlePos newArticle) {
	articlePos temp = headRec;
	while (temp->next != NULL && strcmp((temp->next)->name, newArticle->name) < 0)
		temp = temp->next;

	if (temp->next != NULL && strcmp((temp->next)->name, newArticle->name) == 0) {
		temp->next->quantity += newArticle->quantity;
		temp->next->price += newArticle->price;
		free(newArticle);
	}
	else
		InsertArticleAfter(temp, newArticle);

}

void SortReceiptByDate(receiptPos head, receiptPos newReceipt) {
	receiptPos temp = head;
	int check = 1;
	while (temp->nextRe != NULL && DateTimeComparison(newReceipt->dateTime, temp->nextRe->dateTime) == 1)
		temp = temp->nextRe;

	if (temp->nextRe != NULL && DateTimeComparison(newReceipt->dateTime, temp->nextRe->dateTime) == 2) {
		articlePos existingArticle = temp->nextRe->article.next;
		articlePos newArticle = newReceipt->article.next;

		while (newArticle != NULL) {
			articlePos nextNewArticle = newArticle->next;
			articlePos prev = &temp->nextRe->article;
			articlePos current = prev->next;
			while (current != NULL && strcmp(current->name, newArticle->name) < 0) {
				prev = current;
				current = current->next;
			}
			if (current != NULL && strcmp(current->name, newArticle->name) == 0) {
				current->quantity += newArticle->quantity;
				current->price += newArticle->price;
				free(newArticle);
			}
			else
				InsertArticleAfter(prev, newArticle);
			newArticle = nextNewArticle;
		}
		free(newReceipt);
	}
	else
		InsertReceiptAfter(temp, newReceipt);

}

void InsertArticleAfter(articlePos ptr, articlePos newArticle) {
	articlePos temp = ptr->next;
	ptr->next = newArticle;
	newArticle->next = temp;

}

void InsertReceiptAfter(receiptPos ptr, receiptPos newReceipt) {
	receiptPos temp = ptr->nextRe;
	ptr->nextRe = newReceipt;
	newReceipt->nextRe = temp;
}

int DateTimeComparison(char datetime1[], char datetime2[]) {
	int day1, month1, year1;
	int day2, month2, year2;

	sscanf(datetime1, "%d %d %d", &year1, &month1, &day1);
	sscanf(datetime2, "%d %d %d", &year2, &month2, &day2);

	if (year1 > year2)
		return 1;
	if (year1 < year2)
		return 0;

	if (month1 > month2)
		return 1;
	if (month1 < month2)
		return 0;

	if (day1 > day2)
		return 1;
	if (day1 < day2)
		return 0;

	return 2;



}

void PrintReceipt(receiptPos headRec) {
	receiptPos temp = headRec->nextRe;
	while (temp != NULL) {
		printf("Datum: %s\n", temp->dateTime);
		PrintArticle(temp->article.next);
		temp = temp->nextRe;
	}
}

void PrintArticle(articlePos headArt) {
	articlePos temp = headArt;
	while (temp != NULL) {
		printf("Artikl: %s Kolicina: %.2lf Cijena: %.2lf\n", temp->name, temp->quantity, temp->price);
		temp = temp->next;
	}
}

void SpendOnItem(receiptPos headRec) {
	printf("\n\n");
	receiptPos temp = headRec;
	char itemName[20];
	printf("Upisite ime artikla:");
	fgets(itemName, 20, stdin);
	itemName[strcspn(itemName, "\n")] = '\0';
	printf("Upisite razdoblje datumsko za prozivod:(YYYY-MM-DD) \n");
	char date1[12];
	char date2[12];
	double sum = 0;
	fgets(date1, 12, stdin);
	date1[strcspn(date1, "\n")] = '\0';
	fgets(date2, 12, stdin);
	date2[strcspn(date2, "\n")] = '\0';
	while (temp->nextRe != NULL) {
		if (DateTimeComparison(date1, temp->nextRe->dateTime) == 0 && DateTimeComparison(date2, temp->nextRe->dateTime) == 1) {
			articlePos tempArt = temp->nextRe->article.next;
			while (tempArt != NULL) {
				if (strcmp(tempArt->name, itemName) == 0) {
					sum += tempArt->price;
				}
				tempArt = tempArt->next;
			}
		}
		temp = temp->nextRe;
	}

	printf("Ukupno potroseno je: %.2lf", sum);
}