#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>
#include "school.h"

// Utility: Remove trailing newline from fgets input
void strip_newline(char *str) {
  char *newline = strchr(str, '\n');
  if (newline) {
    *newline = '\0';
  }
}

// Utility: Get integer input with validation
int get_int_input(const char *prompt) {
  char buffer[64];
  printf("%s", prompt);
  fgets(buffer, 64, stdin);
  return atoi(buffer);
}

// Display main menu
void display_menu(void) {
  printf("\n");
  printf("========================================\n");
  printf("       SCHOOL MANAGEMENT SYSTEM         \n");
  printf("========================================\n");
  printf("1) Add subject with teacher\n");
  printf("2) Add student\n");
  printf("3) Add subject to student\n");
  printf("4) Add grade to student per subject\n");
  printf("5) Find students studying a subject\n");
  printf("6) Find teacher teaching a subject\n");
  printf("7) Find grades for a student in a subject\n");
  printf("8) Find teachers teaching a student\n");
  printf("9) Find students taught by a teacher\n");
  printf("10) Print all subjects\n");
  printf("11) Print all students\n");
  printf("0) Exit\n");
  printf("========================================\n");
  printf("Enter your choice: ");
}

// Menu option 1: Add subject with teacher
void menu_add_subject(SubjectList **subject_head) {
  char subject_name[64];
  char teacher_name[64];
  
  printf("\n--- Add New Subject ---\n");
  
  printf("Enter subject name: ");
  fgets(subject_name, 64, stdin);
  strip_newline(subject_name);
  
  if (subject_name[0] == '\0') {
    printf("Error: Subject name cannot be empty\n");
    return;
  }

  if (*subject_head != NULL) {
    Subject *existing = get_subject_by_name(*subject_head, subject_name);
    if (existing != NULL) {
      printf("Error: Subject '%s' already exists in the system, enter another subject \n", subject_name);
      return;  
    }
  }
  
  printf("Enter teacher name: ");
  fgets(teacher_name, 64, stdin);
  strip_newline(teacher_name);
  
  if (teacher_name[0] == '\0') {
    printf("Error: Teacher name cannot be empty\n");
    return;
  }
  
  // Only create if not duplicate
  SubjectList *new_subject = create_subject(subject_name, teacher_name);
  if (!new_subject) {
    printf("Error: Failed to create subject\n");
    return;
  }
  
  if (*subject_head == NULL) {
    *subject_head = new_subject;
    printf("Subject '%s' added as first subject\n", subject_name);
  } else {
    add_subject(*subject_head, new_subject);
  }
}

// Menu option 2: Add student
void menu_add_student(StudentList **student_head) {
  char student_name[64];
  
  printf("\n--- Add New Student ---\n");
  
  printf("Enter student name: ");
  fgets(student_name, 64, stdin);
  strip_newline(student_name);
  
  if (student_name[0] == '\0') {
    printf("Error: Student name cannot be empty\n");
    return;
  }
  
  if (*student_head != NULL) {
    Student *existing = get_student_by_name(*student_head, student_name);
    if (existing != NULL) {
      printf("Error: Student '%s' already exists in the system\n", student_name);
      return;
    }
  }
  
  // Only create if not duplicate
  StudentList *new_student = create_student(student_name);
  if (!new_student) {
    printf("Error: Failed to create student\n");
    return;
  }
  
  if (*student_head == NULL) {
    *student_head = new_student;
    printf("Student '%s' added as first student\n", student_name);
  } else {
    add_student(*student_head, new_student);
    printf("Student '%s' added successfully\n", student_name);
  }
}

// Menu option 3: Add subject to student
void menu_add_subject_to_student(StudentList *student_head, SubjectList *subject_head) {
  if (student_head == NULL) {
    printf("Error: No students in the system. Add students first.\n");
    return;
  }
  
  if (subject_head == NULL) {
    printf("Error: No subjects in the system. Add subjects first.\n");
    return;
  }
  
  printf("\n--- Add Subject to Student ---\n");
  
  // Show available students
  printf("\nAvailable students:\n");
  print_students(student_head);
  
  int student_id = get_int_input("Enter student ID: ");
  
  // Validate student immediately
  StudentList *found_student = get_student_by_id(student_head, student_id);
  if (found_student == NULL) {
    printf("Error: Student with ID %d not found\n", student_id);
    return;
  }
  
  // Show available subjects
  printf("\nAvailable subjects:\n");
  print_subjects(subject_head);
  
  int subject_id = get_int_input("Enter subject ID: ");
  
  // Validate subject immediately
  SubjectList *found_subject = get_subject_by_id(subject_head, subject_id);
  if (found_subject == NULL) {
    printf("Error: Subject with ID %d not found\n", subject_id);
    return;
  }
  
  add_subject_to_student(found_student, found_subject, subject_head);
}

// Menu option 4: Add grade to student per subject
void menu_add_grade(StudentList *student_head) {
  if (student_head == NULL) {
    printf("Error: No students in the system\n");
    return;
  }
  
  printf("\n--- Add Grade to Student ---\n");
  
  // Show available students
  printf("\nAvailable students:\n");
  print_students(student_head);
  
  int student_id = get_int_input("Enter student ID: ");
  
  StudentList *found_student = get_student_by_id(student_head, student_id);
  
  if (found_student == NULL) {
    printf("Error: Student with ID %d not found\n", student_id);
    return;
  }
  
  // Show student's subjects
  if (found_student->student.student_subjects == NULL) {
    printf("Error: Student has no subjects assigned\n");
    return;
  }
  
  printf("\nStudent's subjects:\n");
  printf("Subject ID\tSubject Name\n");
  SubjectList *current = found_student->student.student_subjects;
  while (current != NULL) {
    printf("%d\t\t%s\n", current->subject.subject_id, current->subject.subject_name);
    current = current->next;
  }
  
  int subject_id = get_int_input("Enter subject ID: ");
  int grade = get_int_input("Enter grade (0-100): ");
  
  if (grade < 0 || grade > 100) {
    printf("Warning: Grade should be between 0 and 100\n");
  }
  
  add_grade(&found_student->student, subject_id, grade);
}

// Menu option 5: Find students studying a subject
void menu_find_students_by_subject(StudentList *student_head) {
  if (student_head == NULL) {
    printf("Error: No students in the system\n");
    return;
  }
  
  printf("\n--- Find Students by Subject ---\n");
  
  int subject_id = get_int_input("Enter subject ID: ");
  
  printf("\nStudents studying subject ID %d:\n", subject_id);
  print_students_by_subject(student_head, subject_id);
}

// Menu option 6: Find teacher teaching a subject
void menu_find_teacher_by_subject(SubjectList *subject_head) {
  if (subject_head == NULL) {
    printf("Error: No subjects in the system\n");
    return;
  }
  
  printf("\n--- Find Teacher by Subject ---\n");
  
  printf("\nAvailable subjects:\n");
  print_subjects(subject_head);
  
  int subject_id = get_int_input("Enter subject ID: ");
  
  printf("\nTeacher for subject ID %d:\n", subject_id);
  find_teacher_by_subject(subject_head, subject_id);
}

// Menu option 7: Find grades for a student in a subject
void menu_find_grades(StudentList *student_head) {
  if (student_head == NULL) {
    printf("Error: No students in the system\n");
    return;
  }
  
  printf("\n--- Find Student Grades ---\n");
  
  printf("\nAvailable students:\n");
  print_students(student_head);
  
  int student_id = get_int_input("Enter student ID: ");
  
  StudentList *found_student = get_student_by_id(student_head, student_id);
  
  if (found_student == NULL) {
    printf("Error: Student with ID %d not found\n", student_id);
    return;
  }
  
  printf("\nOptions:\n");
  printf("1) View all grades for this student\n");
  printf("2) View grade for specific subject\n");
  
  int choice = get_int_input("Enter choice: ");
  
  if (choice == 1) {
    print_subjects_with_grades(&found_student->student);
  } else if (choice == 2) {
    int subject_id = get_int_input("Enter subject ID: ");
    print_grade_per_subject(&found_student->student, subject_id);
  } else {
    printf("Invalid choice\n");
  }
}

// Menu option 8: Find teachers teaching a student
void menu_find_teachers_by_student(StudentList *student_head) {
  if (student_head == NULL) {
    printf("Error: No students in the system\n");
    return;
  }
  
  printf("\n--- Find Teachers by Student ---\n");
  
  printf("\nAvailable students:\n");
  print_students(student_head);
  
  int student_id = get_int_input("Enter student ID: ");
  
  printf("\nTeachers teaching student ID %d:\n", student_id);
  print_teachers_by_student(student_head, student_id);
}

// Menu option 9: Find students taught by a teacher
void menu_find_students_by_teacher(StudentList *student_head) {
  if (student_head == NULL) {
    printf("Error: No students in the system\n");
    return;
  }
  
  printf("\n--- Find Students by Teacher ---\n");
  
  char teacher_name[64];
  printf("Enter teacher name: ");
  fgets(teacher_name, 64, stdin);
  strip_newline(teacher_name);
  
  if (teacher_name[0] == '\0') {
    printf("Error: Teacher name cannot be empty\n");
    return;
  }
  
  printf("\nStudents taught by %s:\n", teacher_name);
  print_students_by_teacher(student_head, teacher_name);
}

// Main menu loop
void run_menu(StudentList **student_head, SubjectList **subject_head) {
  int choice;
  bool running = true;
  
  while (running) {
    display_menu();
    choice = get_int_input("");
    
    switch (choice) {
      case 1:
        menu_add_subject(subject_head);
        break;
      case 2:
        menu_add_student(student_head);
        break;
      case 3:
        menu_add_subject_to_student(*student_head, *subject_head);
        break;
      case 4:
        menu_add_grade(*student_head);
        break;
      case 5:
        menu_find_students_by_subject(*student_head);
        break;
      case 6:
        menu_find_teacher_by_subject(*subject_head);
        break;
      case 7:
        menu_find_grades(*student_head);
        break;
      case 8:
        menu_find_teachers_by_student(*student_head);
        break;
      case 9:
        menu_find_students_by_teacher(*student_head);
        break;
      case 10:
        printf("\n--- All Subjects ---\n");
        if (*subject_head) {
          print_subjects(*subject_head);
        } else {
          printf("No subjects in the system\n");
        }
        break;
      case 11:
        printf("\n--- All Students ---\n");
        if (*student_head) {
          print_students(*student_head);
        } else {
          printf("No students in the system\n");
        }
        break;
      case 0:
        printf("\nExiting program. Goodbye!\n");
        running = false;
        break;
      default:
        printf("\nInvalid choice. Please try again.\n");
    }
    
    if (running) {
      printf("\nPress Enter to continue...");
      getchar();
    }
  }
}