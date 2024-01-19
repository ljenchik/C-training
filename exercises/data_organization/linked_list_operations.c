#include<stdio.h>
#include <stdlib.h>
#include"linked_list_operations.h"

// Printing a linked list
void print_linked_list(Node *head){
  if (head == NULL)
  {
    printf("Error: invalid pointer \n");
  }
  else {
    // Creating a temp link to a head
    Node *temp = head;
    while (temp != NULL) {
    printf("%d ", temp->data);
    temp = temp->next;
  }
  printf("\n");
  }
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
  if (node_to_insert == NULL && head == NULL)
  {
    printf("Error: invalid pointer, no node to insert \n");
    return NULL;
  }
  if (head == NULL && node_to_insert != NULL) {
    head = node_to_insert;
    return head;
  }
  node_to_insert->next = head;
  head = node_to_insert;
  return head;
}

// Inserting a new node at the back of a linked list
void insert_at_back(Node *head, Node *node_to_insert) {
  if (node_to_insert == NULL)
  {
    printf("Error: invalid pointer, no node to insert \n");
  }
  if (head == NULL)
  {
    head = node_to_insert;
  }
  else {
    Node *temp = head;
    while (temp->next != NULL) {
      temp = temp->next;
    }
    temp->next = node_to_insert;
    node_to_insert->next=NULL;
  }
}

// Finding a node in with a given data
Node *find_node(Node *head, int data) {
  if (head == NULL)
  {
    printf("Error: invalid pointer \n");
    return NULL;
  }
    Node *temp = head;
    while (temp != NULL) {
      if (temp->data == data) {
        return temp;        
      }
      temp = temp->next;
  }
  printf("Node with data %d is not in a list", data);
  return NULL;
}

// Inserting a new node after a given node in a linked list
void insert_after_node(Node *head, Node *node_to_insert_after, Node *node_to_insert) {
  if (node_to_insert_after == NULL || find_node(head, node_to_insert_after->data) == NULL)
  {
    printf("Error: invalid pointer");
  }
  if (node_to_insert == NULL)
  {
    printf("Error: invalid pointer, no node to insert \n");
  }
  node_to_insert->next = node_to_insert_after->next;
  node_to_insert_after->next = node_to_insert;
}


// Deleting a head of a linked list, returns a new head
Node *delete_head(Node *head) {
  if (head == NULL) {
    printf("Error: invalid pointer, no node to delete \n");
    return NULL;
  }
  if (head != NULL && head->next == NULL) {
      return NULL;
      free(head);
  }
  if (head->next != NULL) {
    Node *temp = head;
    head = head->next;
    free(temp);
    
  }
  return head;
}

// Deleting last element of a linked list
void delete_last_node(Node *head) {
   if (head == NULL) {
    printf("Error: invalid pointer, no node to delete \n");
  }
  if (head->next == NULL) {
    free(head);
    head = NULL;
  }
  Node *temp = head;
  while (temp != NULL) {
    if (temp->next->next == NULL) {
      free(temp->next);
      temp->next = NULL;
    }
    temp = temp->next;
  } 
}

// Deleting node after a given node
void delete_node_after(Node *node_to_delete_after) {
  if (node_to_delete_after == NULL) {
    printf("Error: invalid pointe \n");
  }
  Node *temp = node_to_delete_after->next;
  node_to_delete_after->next = node_to_delete_after->next->next;
  free(temp);
}

// Determine the length of a linked list
int size(Node *head) {
  int count = 0;
  Node *temp = head;
  while (temp != NULL) {
    ++count;
    temp = temp->next;
  }
  return count;
}

// Delete list
void delete_list(Node *head) {
   if (head == NULL) {
    printf("Error: invalid pointer, no node to delete \n");
  }
  else {
    Node *temp = head;
    while (temp != NULL) {
        delete_last_node(temp);
    }
  }
}
