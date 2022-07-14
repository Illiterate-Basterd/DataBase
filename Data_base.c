#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct library
{
	char* title;
	enum { Comedy, Detective, Novel, Poem, History, Fantasy } genre;
	unsigned short release_year;
	char* Author;
	union { unsigned short age; unsigned short year_death; } isAlive;
	char* publisher;
	bool IsFinished;
	float score;
	struct library* next;
}Library;

void AddElement(Library* book)
{
	Library* temp;
	temp = (Library*)malloc(sizeof(Library));
	book->next = temp;
	temp->next = NULL;
}

void DelElemet(Library** book, Library** First)
{
	if (*book == NULL)
	{
		printf("No Books left :(\n");
		return;
	}
	Library* temp = *First, *p;
	if (*book == *First)
	{
		temp = *First;
		*book = (*First)->next;
		*First = (*First)->next;
		free(temp);
		return;
	}
	while (temp->next != *book && temp != NULL)
	{
		temp = temp->next;
		if (temp == NULL)
			break;
	}
	p = *book;
	temp->next = (*book)->next;
	*book = temp;
	free(p);
}

void ReadFile(Library* book, FILE* file)
{
	if (feof(file))
		fseek(file, 0, SEEK_SET);
	char str[256];
	if (!feof(file))
	{
		fgets(str, 255, file);
		while (str[0] == '\n')
		{
			fgets(str, 255, file);
			if (feof(file))
				return;
		}
		book->title = (char*)calloc(strlen(str), sizeof(char));
		strcpy(book->title, str);
		fgets(str, 255, file);
		char c = str[0];
		switch (c)
		{
		case 'C':
			book->genre = Comedy;
			break;
		case 'D':
			book->genre = Detective;
			break;
		case 'N':
			book->genre = Novel;
			break;
		case 'P':
			book->genre = Poem;
			break;
		case 'H':
			book->genre = History;
			break;
		case 'F':
			book->genre = Fantasy;
			break;
		default:
			break;
		}
		fgets(str, 255, file);
		book->release_year = atoi(str);
		fgets(str, 255, file);
		book->Author = (char*)calloc(strlen(str), sizeof(char));
		strcpy(book->Author, str);
		fgets(str, 255, file);
		if (atoi(str) > 200)
			book->isAlive.year_death = atoi(str);
		else
			book->isAlive.age = atoi(str);
		fgets(str, 255, file);
		book->publisher = (char*)calloc(strlen(str), sizeof(char));
		strcpy(book->publisher, str);
		fgets(str, 255, file);
		c = str[0];
		if (c == 'F' || c =='f')
			book->IsFinished = true;
		else
			book->IsFinished = false;
		fgets(str, 255, file);
		book->score = atof(str);
	}
}

void print(Library* book)
{
	if (book == NULL)
	{
		printf("No Books left :(\n");
		return;
	}
	printf("Name - %s", book->title);
	switch (book->genre)
	{
	case Comedy:
		printf("Genre - Comedy\n");
		break;
	case Detective:
		printf("Genre - Detective\n");
		break;
	case Novel:
		printf("Genre - Novel\n");
		break;
	case Poem:
		printf("Genre - Poem\n");
		break;
	case History:
		printf("Genre - History\n");
		break;
	case Fantasy:
		printf("Genre - Fantasy\n");
		break;
	default:
		break;
	}
	printf("Release year - %hu\n", book->release_year);
	printf("Author - %s", book->Author);
	if (book->isAlive.age < 128)
		printf("Author's age - %hu\n", book->isAlive.age);
	else
		printf("Author's death year - %hu\n", book->isAlive.year_death);
	printf("Publisher - %s", book->publisher);
	if (book->IsFinished)
		printf("Book is finished\n");
	else
		printf("Book is not finished\n");
	printf("Score of the book - %.1f\n\n", book->score);
}

void WriteToFile(FILE* file)
{
	unsigned short q;
	fseek(file, 0, SEEK_END);
	fputc('\n', file);
	int pos = ftell(file);
	fputc('\n', file);
	char str[256];
	printf("Name: ");
	fseek(stdin, 0, SEEK_END);
	gets_s(str, 255);
	fputs(str, file);
	fputc('\n', file);
	printf("Genre: Comedy, Detective, Novel, Poem, History or Fantasy\n");
	gets_s(str, 255);
	fputs(str, file);
	fputc('\n', file);
	printf("Release year of the book: ");
	gets_s(str, 255);
	fputs(str, file);
	fputc('\n', file);
	printf("Author: ");
	gets_s(str, 255);
	fputs(str, file);
	fputc('\n', file);
	printf("Is Author alive?:\n1 - Yes\n2 - No\n");
	scanf("%hu", &q);
	if (q == 1)
	{
		printf("Author's age:\n");
		fseek(stdin, 0, SEEK_END);
		gets_s(str, 255);
		fputs(str, file);
		fputc('\n', file);
	}
	else if (q == 2)
	{
		printf("Author's death year:\n");
		fseek(stdin, 0, SEEK_END);
		gets_s(str, 255);
		fputs(str, file);
		fputc('\n', file);
	}
	printf("Publisher: ");
	gets_s(str, 255);
	fputs(str, file);
	fputc('\n', file);
	printf("Is the book finished?: ");
	gets_s(str, 255);
	fputs(str, file);
	fputc('\n', file);
	printf("The score of the book: ");
	gets_s(str, 255);
	fputs(str, file);
	fseek(file, pos, SEEK_SET);
}

void Search(Library* book)
{
	unsigned short choice;
	char str[256];
	unsigned short num;
	float score;
	printf("Which parameter?:\n1 - Name\n2 - Genre\n3 - Release year\n4 - Author\n5 - Author's age or death year\n6 - Publisher\n7 - Finished or not\n8 - Score\n");
	scanf("%hu", &choice);
	switch (choice)
	{
	case 1:
		printf("Enter name:\n");
		fseek(stdin, 0, SEEK_END);
		gets_s(str, 255);
		for (int i = 0; book != NULL; i++)
		{
			if (strncmp(book->title, str, strlen(str)) == 0)
				print(book);
			book = book->next;
		}
		break;
	case 2:
		printf("Enter genre:\n0 - Comedy\n1 - Detective\n2 - Novel\n3 - Poem\n4 - History\n5 - Fantasy\n");
		fseek(stdin, 0, SEEK_END);
		scanf("%hu", &num);
		for (int i = 0; book != NULL; i++)
		{
			if (book->genre == num)
				print(book);
			book = book->next;
		}
		break;
	case 3:
		printf("Enter release year:\n");
		fseek(stdin, 0, SEEK_END);
		scanf("%hu", &num);
		for (int i = 0; book != NULL; i++)
		{
			if (book->release_year == num)
				print(book);
			book = book->next;
		}
		break;
	case 4:
		printf("Enter Author:\n");
		fseek(stdin, 0, SEEK_END);
		gets_s(str, 255);
		for (int i = 0; book != NULL; i++)
		{
			if (strncmp(book->Author, str, strlen(str)) == 0)
				print(book);
			book = book->next;
		}
		break;
	case 5:
		printf("Is Author alive?:\n1 - Yes\n2 - No\n");
		scanf("%hu", &num);
		if (num == 1)
		{
			printf("Enter age:\n");
			fseek(stdin, 0, SEEK_END);
			scanf("%hu", &num);
			while (book != NULL)
			{
				if (book->isAlive.age == num)
					print(book);
				book = book->next;
			}
		}
		else if (num == 2)
		{
			printf("Enter death year:\n");
			fseek(stdin, 0, SEEK_END);
			scanf("%hu", &num);
			while (book != NULL)
			{
				if (book->isAlive.year_death == num)
					print(book);
				book = book->next;
			}
		}
		break;
	case 6:
		printf("Enter publisher:\n");
		fseek(stdin, 0, SEEK_END);
		gets_s(str, 255);
		for (int i = 0; book != NULL; i++)
		{
			if (strncmp(book->publisher, str, strlen(str)) == 0)
				print(book);
			book = book->next;
		}
		break;
	case 7:
		printf("Finished or Not finished?:\n");
		fseek(stdin, 0, SEEK_END);
		gets_s(str, 255);
		if (str[0] == 'F' || str[0] == 'f')
		{
			for (int i = 0; book != NULL; i++)
			{
				if (book->IsFinished)
					print(book);
				book = book->next;
			}
		}
		else
		{
			for (int i = 0; book != NULL; i++)
			{
				if (!book->IsFinished)
					print(book);
				book = book->next;
			}
		}
		break;
	case 8:
		printf("Enter score:\n");
		fseek(stdin, 0, SEEK_END);
		scanf("%f", &score);
		for (int i = 0; book != NULL; i++)
		{
			if (book->score == score)
				print(book);
			book = book->next;
		}
		break;
	default:
		printf("Wrong number!\n");
		break;
	}
}

int main()
{
	Library* Book;
	Book = (Library*)malloc(sizeof(Library));
	Book->next = NULL;
	Library* first = Book;
	FILE* books = fopen("Books.txt", "r+");
	ReadFile(Book, books);
	while (!feof(books))
	{
		AddElement(Book);
		Book = Book->next;
		ReadFile(Book, books);
	}
	Library* last = Book;
	unsigned short choice = 1;
	Book = first;
	printf("Choose option:\n1 - Write to file\n2 - Read file\n3 - Next book\n4 - Print book info\n5 - Go to beginning\n6 - Go to end\n7 - Search\n8 - Print this text again\n9 - Delete current element\n0 - Exit\n");
	while (choice)
	{
		scanf("%hu", &choice);
		switch (choice)
		{
		case 1:
			WriteToFile(books);
			break;
		case 2:
			Book = last;
			AddElement(Book);
			Book = Book->next;
			ReadFile(Book, books);
			last = Book;
			if (first == NULL)
				first = Book;
			break;
		case 3:
			if (Book != NULL && Book->next != NULL)
			{
				Book = Book->next;
				printf("Success!\n");
			}
			else
				printf("Can not move forward\n");
			break;
		case 4:
			print(Book);
			break;
		case 5:
			Book = first;
			break;
		case 6:
			Book = last;
			break;
		case 7:
			Book = first;
			Search(Book);
			Book = first;
			break;
		case 8:
			printf("Choose option:\n1 - Write to file\n2 - Read file\n3 - Next book\n4 - Print book info\n5 - Go to beginning\n6 - Go to end\n7 - Search\n8 - Print this text again\n9 - Delete current element\n0 - Exit\n");
			break;
		case 9:
			if (Book == last && last != first)
			{
				Book = first;
				while (Book->next != last)
					Book = Book->next;
				last = Book;
				Book = Book->next;
			}
			DelElemet(&Book, &first);
			break;
		case 0:
			break;
		default:
			printf("Wrong command!\n");
			break;
		}
	}
	return 0;
}