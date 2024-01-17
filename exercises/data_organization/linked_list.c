// Write a library with linked list operations. Write a program to test the library
#include<stdio.h>
#include <stdlib.h>
#include"linked_list_operations.h"

int main() {
  Node *head;
  Node *temp;

  temp = create_node(100);
  head = temp;

  // Inserting at the head
  Node *new_node1 = create_node(34);
  head = insert_at_head(head, new_node1);
  print_linked_list(head);

  // Inserting at the head using loop
  for (int i = 1; i <10; i++) {
      temp = create_node(i);
      head = insert_at_head(head, temp);
  };
  printf("Creating a linked list \n");
  print_linked_list(head);

  // Inserting a NULL node, should generate an error message
  Node *new_node2 = create_node(55);
  head = insert_at_head(head, new_node2);
  printf("%d \n", head->data );
  print_linked_list(head);

  // Inserting at the back of a linked list
  Node *new_node3 = create_node(23);
  insert_at_back(head, new_node3);
  printf("Inserting at the back of a linked list \n");
  print_linked_list(head);

  // Finding a node with node.data 4
  temp = find_node(head, 4);
  printf("Found node with the data %d\n", temp->data);

  // Inserting a node  aftera node with node.dat = 1
  Node *node_to_insert = create_node(389);
  Node *insert_after = find_node(head, 1);
  insert_after_node(head, insert_after, node_to_insert);
  printf("Inserting a new node after a given node \n");
  print_linked_list(head);

  // Deleting a head
  printf("Deleting a head \n");
  print_linked_list(head);

  // Deleting the last node
  delete_last_node(head);
  printf("Deleting the last node of a linked list \n");
  print_linked_list(head);


  // Deleting the node with node.dat = 5
  Node *delete_after = find_node(head, 5);
  delete_node_after(delete_after);
  printf("Deleting a node after a node with the value 5 \n");
  print_linked_list(head);

  // Length of a linked list 
  printf("Length of a linked list with the head is %d\n", size(head));

  // Testing the edge cases (when head is NULL, or nodes to insert/delete are NULL)
  Node *head1 = NULL;
  Node *new_node4 = create_node(278);
  
  // Inserting at the head when head is NULL
  head1 = insert_at_head(head1, new_node4);
  printf("head1 data %d \n", head1->data);
  printf("Length of a linked list with the head1 is %d \n", size(head1));
  print_linked_list(head1);

  // Inserting at the head when head is NULL and node to insert is NULL
  // Generates an error message
  Node *head2 = NULL;
  Node *new_node5 = NULL;
  head2 = insert_at_head(head2, new_node5);


  // Deleting head if head is NULL
  // Generates an error message
  delete_head(head2);


  free(head);
  free(head1);
  free(head2);
  
  return 0;
}
