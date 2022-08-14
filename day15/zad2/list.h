#ifndef LIST_HH
#define LIST_HH

struct Book {
	double price;
	int page_count;
	char title[150];
	char author[100];
};

struct node_t {
	struct Book value;
	struct node_t* next;
};

struct list_t {
	struct node_t* head;
};

void push_front(struct list_t* list, struct Book value);
void push_back(struct list_t* list, struct Book value);
struct Book get_index(const struct list_t * const list, int index);
void destroy_list(struct list_t* list);
int list_size(struct list_t list);
void sort_list(struct list_t* list, int (*comp)(const struct node_t*, const struct node_t*));
struct Book detach(struct list_t* list, struct node_t* node);

#endif


