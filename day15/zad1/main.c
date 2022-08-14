#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define COUNT 10

struct Book {
	double price;
	int page_count;
	char title[150];
	char author[100];
};

int randint(int min, int max) {
	return (rand() % (max-min)) + min;
}

double randreal(int min, int max) {
	return ((double)rand() / (double)RAND_MAX) * (max - min) + min;
}

struct Book randBook() {
	struct Book book;
	int authlen = randint(10, 20);
	int titlen = randint(10, 20);
	book.page_count = randint(5, 2000);
	book.price = randreal(1.0, 1000.0);
	
	for(int i=0; i < authlen; i++) {
		char up = randint('A', 'Z'), low = randint('a', 'z');
		book.author[i] = randint(0, 2) ? up : low;
	}
	book.author[authlen] = 0;
	
	for(int i=0; i < titlen; i++) {
		char up = randint('A', 'Z'), low = randint('a', 'z');
		book.title[i] = randint(0, 2) ? up : low;
	}
	book.title[titlen] = 0;
	
	return book;
	
}

void printBook(struct Book book) {
	printf("\t%s\n", book.title);
	printf("\t%s\n\t%d pages\n", book.author, book.page_count);
	printf("\t$%.2lf\n\n", book.price);
}

int main() {
	srand(time(NULL));
	struct Book books[COUNT];
	
	for(int i=0; i < COUNT; i++) {
		books[i] = randBook();
		printBook(books[i]);
	}
}	
