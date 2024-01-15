// Write a library with linked list operations. Write a program to test the library
#include<stdio.h>
#include <stdlib.h>

typedef struct node {
  int data;
  struct node *next;
} Node;


void print_linked_list(Node *head){
  // Creating a temp link to a head
  Node *temp = head;
  while (temp != NULL) {
    printf("%d ", temp->data);
    temp = temp->next;
  }
  printf("\n");
}

int main() {
  Node n1, n2, n3, n4;
  Node *head;

  n1.data = 5;
  n2.data = 90;
  n3.data = 12;
  n4.data = 56;

  // linking the nodes n1, n2, n3 in the list, inserting n4 in the middle of the list
  head = &n1;
  head->next=&n2;
  n2.next=&n4;
  n4.next=&n3;
  n3.next=NULL;

  // removing head
  head=head->next;

  print_linked_list(head);






  return 0;
}
