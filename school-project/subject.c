#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "school.h"

// One teacher per one subject, we are not adding subjects to the list if their name is on the list already

// Static variable definition
int subject_id = 0;

// Creating a new subject (it's a node in a SubjectList)
SubjectList *create_subject(char *subject_name, char *teacher) {
  SubjectList *new_subject = malloc(sizeof(SubjectList));
  if (!new_subject) return NULL;

  // Creating subject_id using a static variable
  new_subject->subject.subject_id = ++subject_id;

  new_subject->subject.subject_name = malloc(strlen(subject_name) + 1);
  if (!new_subject->subject.subject_name) {  
    free(new_subject);
    return NULL;
  }

  strcpy(new_subject->subject.subject_name, subject_name); 

  new_subject->subject.teacher = malloc(strlen(teacher) + 1);
  if (!new_subject->subject.teacher) { 
    free(new_subject->subject.subject_name);
    free(new_subject);
    return NULL;
  }

  strcpy(new_subject->subject.teacher, teacher);

  new_subject->subject.grade = 0;
  new_subject->next = NULL;
  return new_subject;
}

// Printing a given subject with all info
void print_subject(SubjectList *subject) {
  // Make copies to avoid corrupting original strings
  char name_copy[256];
  char teacher_copy[256];
  
  strncpy(name_copy, subject->subject.subject_name, 255);
  name_copy[255] = '\0';
  
  strncpy(teacher_copy, subject->subject.teacher, 255);
  teacher_copy[255] = '\0';
  
  // Remove newline from copies
  char *newline = strchr(name_copy, '\n');
  if (newline) *newline = '\0';
  
  newline = strchr(teacher_copy, '\n');
  if (newline) *newline = '\0';
  
  printf("\t%d\t%s\t\t%s\n", subject->subject.subject_id, name_copy, teacher_copy);
  printf("\n");
}

// Printing all subjects with teachers
void print_subjects(SubjectList *head) {
  if (head == NULL) {
    printf("Error: invalid pointer \n");
  }
  else {
    SubjectList *current = head;
    printf("Subject id\tSubject\t\tTeacher\n");
    printf("\n");
    while (current != NULL) {
      print_subject(current);
      current = current->next;
    }
  }
}

// Getting a specified subject found by id
SubjectList *get_subject_by_id(SubjectList *head, int subject_id) {
  SubjectList *current = head;
  while (current != NULL) {
    if (current->subject.subject_id == subject_id) {
      return current;
    }
    current = current->next;
  }
  return NULL;
}

// Getting a specified subject found by name
Subject *get_subject_by_name(SubjectList *head, char *subject_name) {
  SubjectList *current = head;
  while (current != NULL) {
    if (strcasecmp(current->subject.subject_name, subject_name) == 0) {
      return &(current->subject);
    }
    current = current->next;
  }
  return NULL;
}

// Getting a specified subject found by teacher
Subject *get_subject_by_teacher(SubjectList *head, char *teacher) {
  SubjectList *current = head;
  while (current != NULL) {
    if (strcmp(current->subject.teacher, teacher) == 0) {
      return &(current->subject);
    }
    current = current->next;
  }
  return NULL;
}

// Inserting a new subject at the back of a list
void add_subject(SubjectList *head, SubjectList *new_subject) {
  if (head == NULL) {
    printf("Error: invalid head pointer\n");
    return;
  }
  
  SubjectList *current = head;

  // Check if subject name already exists
  Subject *found_subject_by_name = get_subject_by_name(head, new_subject->subject.subject_name);
  
  if (found_subject_by_name != NULL) {
    // Make a copy to avoid strtok corruption
    char name_copy[256];
    strncpy(name_copy, new_subject->subject.subject_name, 255);
    name_copy[255] = '\0';
    char *newline = strchr(name_copy, '\n');
    if (newline) *newline = '\0';
    
    printf("%s is already in the list of subjects\n", name_copy);
    return;
  }
  
  // Add to end of list
  while (current->next != NULL) {
    current = current->next;
  }
  current->next = new_subject;
  new_subject->next = NULL;
}