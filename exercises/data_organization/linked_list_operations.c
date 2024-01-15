#include<stdio.h>
#include <stdlib.h>
#include"linked_list_operations.h"

// typedef struct node {
//   int data;
//   struct node *next;
// } Node;

// Printing a linked list
void print_linked_list(Node *head){
  // Creating a temp link to a head
  Node *temp = head;
  while (temp != NULL) {
    printf("%d ", temp->data);
    temp = temp->next;
  }
  printf("\n");
}

// Creating a new node
Node *create_node(int data) {
  Node *new_node=malloc(sizeof(Node));
  new_node->data = data;
  new_node->next=NULL;
  return new_node;
}


// Inserting a new node at the beginning of a linked list
Node *insert_at_head(Node *head, Node *node_to_insert) {
  node_to_insert->next = head;
  return node_to_insert;
}

// Inserting a new node at the back of a linked list
Node *insert_at_back(Node *head, Node *node_to_insert) {
    Node *temp = head;
    while (temp->next != NULL) {
      temp = temp->next;
  }
  temp->next = node_to_insert;
  node_to_insert->next=NULL;
  return node_to_insert;
}

// Finding a node in with a given data
Node *find_node(Node *head, int data) {
    Node *temp = head;
    while (temp != NULL) {
      if (temp->data == data) {
        return temp;        
      }
      temp = temp->next;
  }
  return NULL;
}

// Inserting a new node after a given node in a linked list
void insert_after_node(Node *node_to_insert_after, Node *node_to_insert) {
  node_to_insert->next = node_to_insert_after->next;
  node_to_insert_after->next = node_to_insert;
}


// Deleting a head of a linked list, returns a new head
Node *delete_head(Node *head) {
  if (head->next != NULL) {
    head = head->next;
    return head;
  }
  return NULL;
}

// Deleting last element of a linked list
void delete_last_node(Node *head) {
  Node *temp = head;
  while (temp != NULL) {
    if (temp->next->next == NULL) {
      temp->next = NULL;
    }
    temp = temp->next;
  } 
}

// Deleting node after a given node
void delete_node_after(Node *node_to_delete_after) {
  node_to_delete_after->next = node_to_delete_after->next->next;
}