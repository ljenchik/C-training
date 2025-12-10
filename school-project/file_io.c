#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "school.h"

#define SUBJECTS_FILE "subjects.txt"
#define STUDENTS_FILE "students.txt"

// Save subjects to file
// Format: subject_id|subject_name|teacher
int save_subjects_to_file(SubjectList *head, const char *filename) {
  FILE *file = fopen(filename, "w");
  if (!file) {
    printf("Error: Could not open file '%s' for writing\n", filename);
    return 0;
  }
  
  SubjectList *current = head;
  while (current != NULL) {
    fprintf(file, "%d|%s|%s\n",
            current->subject.subject_id,
            current->subject.subject_name,
            current->subject.teacher);
    current = current->next;
  }
  
  fclose(file);
  return 1;
}

// Save students to file
// Format: student_id|student_name|subject_id1,subject_id2,subject_id3|grade1,grade2,grade3
int save_students_to_file(StudentList *head, const char *filename) {
  FILE *file = fopen(filename, "w");
  if (!file) {
    printf("Error: Could not open file '%s' for writing\n", filename);
    return 0;
  }
  
  StudentList *current = head;
  while (current != NULL) {
    fprintf(file, "%d|%s|",
            current->student.student_id,
            current->student.student_name);
    
    // Write subject IDs
    SubjectList *subject = current->student.student_subjects;
    while (subject != NULL) {
      fprintf(file, "%d", subject->subject.subject_id);
      if (subject->next != NULL) {
        fprintf(file, ",");
      }
      subject = subject->next;
    }
    fprintf(file, "|");
    
    // Write grades
    subject = current->student.student_subjects;
    while (subject != NULL) {
      fprintf(file, "%d", subject->subject.grade);
      if (subject->next != NULL) {
        fprintf(file, ",");
      }
      subject = subject->next;
    }
    fprintf(file, "\n");
    
    current = current->next;
  }
  
  fclose(file);
  return 1;
}

// Load subjects from file
SubjectList *load_subjects_from_file(const char *filename, int *max_id) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    printf("Info: File '%s' not found. Starting with empty subject list.\n", filename);
    return NULL;
  }
  
  SubjectList *head = NULL;
  SubjectList *tail = NULL;
  char line[512];
  
  while (fgets(line, sizeof(line), file)) {
    // Remove newline
    char *newline = strchr(line, '\n');
    if (newline) *newline = '\0';
    
    // Parse: subject_id|subject_name|teacher
    char *token;
    int id;
    char name[256];
    char teacher[256];
    
    token = strtok(line, "|");
    if (!token) continue;
    id = atoi(token);
    
    token = strtok(NULL, "|");
    if (!token) continue;
    strncpy(name, token, 255);
    name[255] = '\0';
    
    token = strtok(NULL, "|");
    if (!token) continue;
    strncpy(teacher, token, 255);
    teacher[255] = '\0';
    
    // Create subject node
    SubjectList *new_subject = malloc(sizeof(SubjectList));
    if (!new_subject) continue;
    
    new_subject->subject.subject_id = id;
    new_subject->subject.subject_name = malloc(strlen(name) + 1);
    if (!new_subject->subject.subject_name) {
      free(new_subject);
      continue;
    }
    strcpy(new_subject->subject.subject_name, name);
    
    new_subject->subject.teacher = malloc(strlen(teacher) + 1);
    if (!new_subject->subject.teacher) {
      free(new_subject->subject.subject_name);
      free(new_subject);
      continue;
    }
    strcpy(new_subject->subject.teacher, teacher);
    
    new_subject->subject.grade = 0;  // Initialize grade to 0
    new_subject->next = NULL;
    
    // Track max ID
    if (id > *max_id) {
      *max_id = id;
    }
    
    // Add to list
    if (head == NULL) {
      head = new_subject;
      tail = new_subject;
    } else {
      tail->next = new_subject;
      tail = new_subject;
    }
  }
  
  fclose(file);
  return head;
}

// Load students from file
StudentList *load_students_from_file(const char *filename, SubjectList *subject_head, int *max_id) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    printf("Info: File '%s' not found. Starting with empty student list.\n", filename);
    return NULL;
  }
  
  StudentList *head = NULL;
  StudentList *tail = NULL;
  char line[512];
  
  while (fgets(line, sizeof(line), file)) {
    // Remove newline
    char *newline = strchr(line, '\n');
    if (newline) *newline = '\0';
    
    // Parse: student_id|student_name|subject_ids|grades
    char *token;
    int id;
    char name[256];
    
    token = strtok(line, "|");
    if (!token) continue;
    id = atoi(token);
    
    token = strtok(NULL, "|");
    if (!token) continue;
    strncpy(name, token, 255);
    name[255] = '\0';
    
    // Create student node
    StudentList *new_student = malloc(sizeof(StudentList));
    if (!new_student) continue;
    
    new_student->student.student_id = id;
    new_student->student.student_name = malloc(strlen(name) + 1);
    if (!new_student->student.student_name) {
      free(new_student);
      continue;
    }
    strcpy(new_student->student.student_name, name);
    new_student->student.student_subjects = NULL;
    new_student->next = NULL;
    
    // Track max ID
    if (id > *max_id) {
      *max_id = id;
    }
    
    // Parse subject IDs
    token = strtok(NULL, "|");
    if (token && token[0] != '\0') {
      char subject_ids_str[256];
      strncpy(subject_ids_str, token, 255);
      subject_ids_str[255] = '\0';
      
      // Parse grades
      token = strtok(NULL, "|");
      char grades_str[256] = "";
      if (token) {
        strncpy(grades_str, token, 255);
        grades_str[255] = '\0';
      }
      
      // Process subject IDs and grades
      char *subject_token = strtok(subject_ids_str, ",");
      char *grade_token = strtok(grades_str, ",");
      
      while (subject_token != NULL) {
        int subject_id = atoi(subject_token);
        int grade = 0;
        if (grade_token != NULL) {
          grade = atoi(grade_token);
          grade_token = strtok(NULL, ",");
        }
        
        // Find subject in master list
        SubjectList *found_subject = get_subject_by_id(subject_head, subject_id);
        if (found_subject != NULL) {
          // Add subject to student
          SubjectList *student_subject = malloc(sizeof(SubjectList));
          if (student_subject) {
            student_subject->subject = found_subject->subject;
            student_subject->subject.grade = grade; // Set the grade
            student_subject->next = new_student->student.student_subjects;
            new_student->student.student_subjects = student_subject;
          }
        }
        
        subject_token = strtok(NULL, ",");
      }
    }
    
    // Add to list
    if (head == NULL) {
      head = new_student;
      tail = new_student;
    } else {
      tail->next = new_student;
      tail = new_student;
    }
  }
  
  fclose(file);
  return head;
}

// Save all data to files
void save_all_data(StudentList *student_head, SubjectList *subject_head) {
  printf("\nSaving data to files...\n");
  
  if (save_subjects_to_file(subject_head, SUBJECTS_FILE)) {
    printf("✓ Subjects saved to %s\n", SUBJECTS_FILE);
  } else {
    printf("✗ Failed to save subjects\n");
  }
  
  if (save_students_to_file(student_head, STUDENTS_FILE)) {
    printf("✓ Students saved to %s\n", STUDENTS_FILE);
  } else {
    printf("✗ Failed to save students\n");
  }
}

// Load all data from files
void load_all_data(StudentList **student_head, SubjectList **subject_head) {
  printf("Loading data from files...\n");
  
  // Reset static IDs
  extern int subject_id;
  extern int student_id;
  int max_subject_id = 0;
  int max_student_id = 0;
  
  // Load subjects first
  *subject_head = load_subjects_from_file(SUBJECTS_FILE, &max_subject_id);
  subject_id = max_subject_id;
  
  if (*subject_head != NULL) {
    printf("✓ Loaded subjects from %s\n", SUBJECTS_FILE);
  }
  
  // Load students (needs subject_head to resolve subject references)
  *student_head = load_students_from_file(STUDENTS_FILE, *subject_head, &max_student_id);
  student_id = max_student_id;
  
  if (*student_head != NULL) {
    printf("✓ Loaded students from %s\n", STUDENTS_FILE);
  }
  
  printf("\n");
}