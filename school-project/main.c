#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "school.h"

int main() {
  SubjectList *subject_head = NULL;
  StudentList *student_head = NULL;
  
  printf("========================================\n");
  printf("   SCHOOL MANAGEMENT SYSTEM - STARTUP   \n");
  printf("========================================\n");
  printf("\n");
  
  // Try to load data from files first
  load_all_data(&student_head, &subject_head);
  
  // If no data loaded, initialize with at least one subject and student
  if (subject_head == NULL) {
    printf("No existing data found. Setting up initial data...\n");
    printf("Please add at least one subject to start.\n\n");
    
    char subject_name[64];
    char teacher_name[64];
    bool valid_input = false;
    
    // Get first subject
    while (!valid_input) {
      printf("Enter first subject name: ");
      fgets(subject_name, 64, stdin);
      strip_newline(subject_name);
      
      if (subject_name[0] == '\0') {
        printf("Error: Subject name cannot be empty. Try again.\n");
        continue;
      }
      
      printf("Enter teacher name: ");
      fgets(teacher_name, 64, stdin);
      strip_newline(teacher_name);
      
      if (teacher_name[0] == '\0') {
        printf("Error: Teacher name cannot be empty. Try again.\n");
        continue;
      }
      
      valid_input = true;
    }
    
    // Create first subject
    subject_head = create_subject(subject_name, teacher_name);
    if (!subject_head) {
      printf("Error: Failed to create subject. Exiting.\n");
      return 1;
    }
    printf("✓ Subject '%s' added successfully\n\n", subject_name);
  }
  
  if (student_head == NULL) {
    // Get first student
    char student_name[64];
    bool valid_input = false;
    
    while (!valid_input) {
      printf("Enter first student name: ");
      fgets(student_name, 64, stdin);
      strip_newline(student_name);
      
      if (student_name[0] == '\0') {
        printf("Error: Student name cannot be empty. Try again.\n");
        continue;
      }
      
      valid_input = true;
    }
    
    // Create first student
    student_head = create_student(student_name);
    if (!student_head) {
      printf("Error: Failed to create student. Exiting.\n");
      return 1;
    }
    printf("✓ Student '%s' added successfully\n\n", student_name);
  }
  
  printf("Initial setup complete!\n");
  printf("Starting main menu...\n");
  
  // Run the interactive menu
  run_menu(&student_head, &subject_head);
  
  // Save data before exiting
  save_all_data(student_head, subject_head);
  
  printf("\nProgram terminated.\n");
  
  return 0;
}