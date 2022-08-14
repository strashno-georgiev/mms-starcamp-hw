#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "list.h"
#define COUNT 10

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



void fprintBook(struct Book book, FILE* stream) {
	fprintf(stream, "\t%s\n", book.title);
	fprintf(stream, "\t%s\n\t%d pages\n", book.author, book.page_count);
	fprintf(stream, "\t$%.2lf\n\n", book.price);
}

int alphabetic_compare(const char* str1, const char* str2) {
	int i=0;
	for(; str1[i+1] != 0 && str2[i+1] != 0; i++) {
		if(str1[i] != str2[i]) {
			return str1[i] - str2[i];
		}
	}
	return (str1[i] - str2[i]);
}

int title_comp(const struct node_t* el1, const struct node_t*el2) {
	return alphabetic_compare(el1->value.title, el2->value.title);
}

int main(int argc, char* argv[]) {
	if(argc < 3) {
		fprintf(stderr, "Usage: %s [-c [output file]] / [-s [input file] [output file]]\n", argv[0]);	
		return -1;	
	}
	if(strcmp(argv[1], "-c") == 0) {
		FILE* output = fopen(argv[2], "wb");
		if(!output) {
			fprintf(stderr, "%s: invalid file\n", argv[0]);
			return -1;
		}
		srand(time(NULL));
		struct Book books[COUNT];
		
		for(int i=0; i < COUNT; i++) {
			books[i] = randBook();
			fwrite(books+i, sizeof(struct Book), 1, output);
		}
		fclose(output);
	}
	else if(strcmp(argv[1], "-s") == 0) {
		if(argc < 3) {
			fprintf(stderr, "Usage: %s [input file] [output file]\n", argv[0]);
			return -1;
		}
		struct Book *books;
		FILE *input, *output;
		struct list_t list;
		list.head = NULL;
		int res, initial_cap = 20, cap = initial_cap, count=0;
		
		input = fopen(argv[2], "rb");
		output = fopen(argv[3], "wb");
		
		if(!input || !output) {
			fprintf(stderr, "%s: invalid file\n", argv[0]);
			return -1;
		}
		
		books = malloc(sizeof(struct Book) * cap);
		//int i=0;
		while(1) {
			res = fread(books+count, sizeof(struct Book), 1, input);
			count += res;
			//printf("Read %d books\n", res);
			//i++;
			//fprintBook(books[count-1], stdout);
			if(res == 0) {
				break;
			}
			if(count == cap - 1) {
				books = realloc(books, cap += initial_cap);
			}
		
		}
		
		//qsort(books, count, sizeof(struct Book), title_comp);
		//printf("Sorted books\n");
		
		
		for(int i=0; i < count ; i++) {
			//printf("i : %d\n", i);
			push_back(&list, books[i]);
		}
		sort_list(&list, title_comp);
		//printf("Books are in list\n");
		free(books);
		//printf("a\n");
		
		for(struct node_t* curr = list.head; curr != NULL; curr = curr->next) {
			//printf("c\n");
			fwrite(&(curr->value), sizeof(struct Book), 1, output);
			//fprintBook(curr->value, stdout);
		}
		
		//printf("b\n");
		destroy_list(&list);
		fclose(input);
		fclose(output);
	}
	return 0;
	
}	
