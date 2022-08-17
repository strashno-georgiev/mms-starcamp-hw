#include "list.h"
#include <stdlib.h>
#include <stdio.h>


void push_back(struct list_t* list, product_t value) {
	struct node_t* new_node = malloc(sizeof(struct node_t));
	new_node->value = value;
	new_node->next = NULL;
	if(list->head == NULL) {
		list->head = new_node;
	} 
	else {
		struct node_t* current = list->head;
		while(current->next != NULL) {
			current = current->next;
		}
		current->next = new_node;
	}
}


void push_front(struct list_t* list, product_t value) {
	struct node_t* new_node = malloc(sizeof(struct node_t));
	new_node->value = value;
	new_node->next = list->head;
	list->head = new_node;
}

struct node_t* list_index(const struct list_t * const list, int index) {
	struct node_t* current = list->head;
	int i = 0;
	while(current != NULL && i != index) {
		current = current->next;
		i++;
	};
	if(current != NULL) {
		return current;
	}
	else {
		printf("index out of range\n");
		return NULL;
	}
	
}

product_t detach(struct list_t* list, struct node_t* node) {
	if(node == list->head) {
		list->head = list->head->next;
		product_t val = node->value;
		free(node);
		return val;
	}
	else {
		struct node_t* current = list->head;
		struct node_t* last = NULL;
		while(current != NULL && current != node) {
			last = current;
			current = current->next;
		}
		if(current == node) {
			if(last != NULL) {
				last->next = current->next;
			}
			product_t val = current->value;
			free(current);
			return val;
		}
		else {
			product_t empty = {0};
			printf("detach: Node isn't in list\n");
			return empty;
		}
	}
}


void destroy_list(struct list_t* list) {
	struct node_t* current = list->head;
	struct node_t* last = NULL;
	while(current != NULL) {
		last = current;
		current = current->next;
		free(last);
	}
}
