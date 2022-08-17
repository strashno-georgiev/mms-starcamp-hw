#ifndef LIST_HH
#define LIST_HH

typedef enum products {
	vegetable, appliance, clothing, shoes, bread, fruit, accessory, meat, herb 
} product_type;

typedef struct product_t {
	unsigned int barcode;
	product_type description;
	double price;
} product_t;

struct node_t {
	product_t value;
	struct node_t* next;
};

struct list_t {
	struct node_t* head;
};

void push_front(struct list_t* list, product_t value);
void push_back(struct list_t* list, product_t value);
struct node_t* list_index(const struct list_t * const list, int index);
void destroy_list(struct list_t* list);
product_t detach(struct list_t* list, struct node_t* node);

#endif


