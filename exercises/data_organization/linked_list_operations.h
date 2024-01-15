typedef struct node {
  int data;
  struct node *next;
} Node;

// Printing a linked list
void print_linked_list(Node *head);

// Creating a new node
Node *create_node(int data);

// Inserting a new node at the beginning of a linked list
Node *insert_at_head(Node *head, Node *node_to_insert);

// Inserting a new node at the back of a linked list
Node *insert_at_back(Node *head, Node *node_to_insert);

// Finding a node in with a given data
Node *find_node(Node *head, int data) ;

// Inserting a new node after a given node in a linked list
void insert_after_node(Node *node_to_insert_after, Node *node_to_insert);

// Deleting a head of a linked list, returns a new head
Node *delete_head(Node *head);

// Deleting last element of a linked list
void delete_last_node(Node *head) ;

// Deleting node after a given node
void delete_node_after(Node *node_to_delete_after);