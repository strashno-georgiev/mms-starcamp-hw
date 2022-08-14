#include "list.h"
#include <stdlib.h>
#include <stdio.h>


void push_back(struct list_t* list, struct Book value) {
	struct node_t* new_node = malloc(sizeof(struct node_t));
	if(new_node == NULL) {
		perror("malloc failed");
	}
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
int list_size(struct list_t list) {
	struct node_t* curr = list.head;
	int s = 0;
	while(curr != NULL) {
		s++;
		curr = curr->next;
	}
	return s;
}
void sort_list(struct list_t* list, int (*comp)(const struct node_t*, const struct node_t*)) {
	struct node_t* current;
	//printf("Sorting\n");
	for(int i=0; i < list_size(*list); i++) {
		current = list->head;
		while(current->next != NULL) {
			if(comp(current, current->next) > 0) {
				//printf("Swapping %s and %s \n", current->value.title, current->next->value.title);
				struct Book tmp = current->value;
				current->value = current->next->value;
				current->next->value = tmp;
			}
			current = current->next;
		}
	}
}


void push_front(struct list_t* list, struct Book value) {
	struct node_t* new_node = malloc(sizeof(struct node_t));
	new_node->value = value;
	new_node->next = list->head;
	list->head = new_node;
}

struct Book get_index(const struct list_t * const list, int index) {
	struct node_t* current = list->head;
	int i = 0;
	while(current != NULL && i != index) {
		current = current->next;
		i++;
	};
	if(current != NULL) {
		return current->value;
	}
	else {
		struct Book empty = {0};
		printf("index out of range\n");
		return empty;
	}
	
}

struct Book detach(struct list_t* list, struct node_t* node) {
	if(node == list->head) {
		list->head = list->head->next;
		struct Book val = node->value;
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
			struct Book val = current->value;
			free(current);
			return val;
		}
		else {
			struct Book empty = {0};	
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
