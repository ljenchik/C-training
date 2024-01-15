// Write a library with linked list operations. Write a program to test the library
#include<stdio.h>
#include <stdlib.h>
#include"linked_list_operations.h"

int main() {
  Node *head;
  Node *temp;

  temp = create_node(0);
  head = temp;

  for (int i = 1; i <10; i++) {
      temp = create_node(i);
      head = insert_at_head(head, temp);
  };
  printf("Creating a linked list \n");
  print_linked_list(head);


  Node *new_node = create_node(23);
  insert_at_back(head, new_node);
  printf("Inserting at the back of a linked list \n");
  print_linked_list(head);

  temp = find_node(head, 4);
  printf("Found node with the data %d\n", temp->data);

  Node *node_to_insert = create_node(389);
  Node *insert_after = find_node(head, 1);
  insert_after_node(insert_after, node_to_insert);
  printf("Inserting a new node after a given node \n");
  print_linked_list(head);

  head = delete_head(head);
  printf("Deleting a head \n");
  print_linked_list(head);

  delete_last_node(head);
  printf("Deleting the last node of a linked list \n");
  print_linked_list(head);

  Node *delete_after = find_node(head, 5);
  delete_node_after(delete_after);
  printf("Deleting a node after a node with the value 5 \n");
  print_linked_list(head);

  return 0;
}
