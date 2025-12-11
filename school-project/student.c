#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "school.h"

int student_id = 0;

// Creating a student
StudentList *create_student(char *student_name) {

  StudentList *new_student = malloc(sizeof(StudentList));

  if (!new_student) return NULL; 
  
  new_student->student.student_id = ++student_id;

  new_student->student.student_name = malloc(strlen(student_name) + 1);
  if (!new_student->student.student_name) { 
    free(new_student);
    return NULL;
  }

  strcpy(new_student->student.student_name, student_name);
  
  new_student->student.student_subjects = NULL;
  new_student->next = NULL;

  return new_student;
}

// Printing a given student with all info
void print_student(Student *student) {
  char name_copy[256];
  strncpy(name_copy, student->student_name, 255);
  name_copy[255] = '\0';
  
  char *newline = strchr(name_copy, '\n');
  if (newline) *newline = '\0';
  
  printf("\t%d\t%s\t\t", student->student_id, name_copy);
  
  SubjectList *current = student->student_subjects;
  while (current != NULL) {
    printf("%s  ", current->subject.subject_name);
    current = current->next;
  }
  printf("\n");
}

// Printing a given student with grades for all subjects
void print_student_with_subjects_grades(Student *student) {
  if (student == NULL) {
    return;
  }
  
  char name_copy[256];
  strncpy(name_copy, student->student_name, 255);
  name_copy[255] = '\0';
  
  char *newline = strchr(name_copy, '\n');
  if (newline) *newline = '\0';
  
  printf("\t%d\t%s\t\t", student->student_id, name_copy);
  
  SubjectList *current = student->student_subjects;
  if (current == NULL) {
    printf("(no subjects)");
  } else {
    while (current != NULL) {
      // Show grade if assigned, otherwise show "-"
      if (current->subject.grade > 0) {
        printf("%s(%d)  ", current->subject.subject_name, current->subject.grade);
      } else {
        printf("%s(-)  ", current->subject.subject_name);
      }
      current = current->next;
    }
  }
  printf("\n");
}

// Printing all students with their subjects
void print_students(StudentList *head) {
  if (head == NULL) {
    printf("Error: invalid pointer\n");
    return;
  }
  
  StudentList *current = head;
  printf("Student id\tName\t\tSubjects\n");
  printf("\n");
  while (current != NULL) {
    print_student(&(current->student));
    current = current->next;
  }
  printf("\n");
}



// Getting a student by id
StudentList *get_student_by_id(StudentList *head, int student_id) {
  StudentList *current = head;
  while (current != NULL) {
    if (current->student.student_id == student_id) {
      return current;
    }
    current = current->next;
  }
  return NULL;
}

// Getting a specified subject found by name
Student *get_student_by_name(StudentList *head, char *student_name) {
  StudentList *current = head;
  while (current != NULL) {
    if (strcmp(current->student.student_name, student_name) == 0) {
      return &(current->student);
    }
    current = current->next;
  }
  return NULL;
}

// Adding a new student 
void add_student(StudentList *head, StudentList *new_student) {
  if (head == NULL) {
    printf("Error: invalid head pointer\n");
    return;
  }
  if (new_student == NULL) {
    printf("Error: invalid pointer, no student to add\n");
    return;
  }
  
  Student *found_student_by_name = get_student_by_name(head, new_student->student.student_name);

  if (found_student_by_name != NULL) {
    char name_copy[256];
    strncpy(name_copy, new_student->student.student_name, 255);
    name_copy[255] = '\0';
    char *newline = strchr(name_copy, '\n');
    if (newline) *newline = '\0';
    
    printf("%s is already in the list of students\n", name_copy);
    free(new_student->student.student_name);
    free(new_student);
    return;
  }
 
  StudentList *current = head;
  while (current->next != NULL) {
    current = current->next;
  }
  current->next = new_student;
  new_student->next = NULL;
}

// Check if student already has this subject
int student_has_subject(Student *student, int subject_id) {
  SubjectList *current = student->student_subjects;
  while (current != NULL) {
    if (current->subject.subject_id == subject_id) {
      return 1;  
    }
    current = current->next;
  }
  return 0;  
}

// Add subject to student (with validation)
void add_subject_to_student(StudentList *student_node, SubjectList *subject_node, SubjectList *all_subjects_head) {
  if (student_node == NULL) {
    printf("Error: Student not found\n");
    return;
  }
  
  if (subject_node == NULL) {
    printf("Error: Subject not found\n");
    return;
  }
  
  // Check if subject exists in the master subject list
  SubjectList *found_in_master = get_subject_by_id(all_subjects_head, subject_node->subject.subject_id);
  if (found_in_master == NULL) {
    printf("Error: Subject with id %d does not exist in the subject list\n", subject_node->subject.subject_id);
    return;
  }
  
  // Check if student already has this subject
  if (student_has_subject(&student_node->student, subject_node->subject.subject_id)) {
    printf("Student already has subject: %s\n", subject_node->subject.subject_name);
    return;
  }
  
  // Create a new node for student's subject list
  SubjectList *new_node = malloc(sizeof(SubjectList));
  if (!new_node) {
    printf("Error: Memory allocation failed\n");
    return;
  }
  
  // Copy subject data (not pointer, to avoid shared memory issues)
  new_node->subject = subject_node->subject;
  new_node->next = student_node->student.student_subjects;
  student_node->student.student_subjects = new_node;
  
  printf("Added subject %s to student %s\n", 
         subject_node->subject.subject_name, 
         student_node->student.student_name);
}

// Add a grade to a given student for a given subject
void add_grade(Student *student, int subject_id, int grade) {
  if (student == NULL) {
    printf("Error: Invalid student\n");
    return;
  }
  
  SubjectList *existing_subjects = student->student_subjects;
  SubjectList *found_subject = get_subject_by_id(existing_subjects, subject_id);
  
  if (found_subject != NULL) {
    found_subject->subject.grade = grade;
    printf("Grade %d added for subject id %d\n", grade, subject_id);
  }
  else {
    printf("Error: Student does not have subject with id %d\n", subject_id);
  }
}

// Prints all subjects with the corresponding grades for a given student
void print_subjects_with_grades(Student *student) {
  if (student == NULL) {
    printf("Error: Invalid student\n");
    return;
  }
  
  SubjectList *existing_subjects = student->student_subjects;
  if (existing_subjects == NULL) {
    printf("Subjects and grades were not assigned to %s\n", student->student_name);
  }
  else {
    printf("%s's subjects and grades\n", student->student_name);
    printf("Subject ID\tSubject\t\tGrade\n");
    while (existing_subjects != NULL) {
      printf("%d\t\t%s\t\t%d\n", 
             existing_subjects->subject.subject_id, 
             existing_subjects->subject.subject_name, 
             existing_subjects->subject.grade);
      existing_subjects = existing_subjects->next;
    }
  }
}

// Finds a grade for a specified student for a given subject
void print_grade_per_subject(Student *student, int subject_id) {
  if (student == NULL) {
    printf("Error: Invalid student\n");
    return;
  }
  
  SubjectList *existing_subjects = student->student_subjects;
  SubjectList *found_subject = get_subject_by_id(existing_subjects, subject_id);
  
  if (found_subject != NULL) {
    printf("Grade: %d\n", found_subject->subject.grade);
  }
  else {
    printf("Error: Student does not have subject with id %d\n", subject_id);
  }
}