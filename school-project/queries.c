#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "school.h"

// Prints a teacher name by a given subject id
void find_teacher_by_subject(SubjectList *head, int subject_id) {
  SubjectList *found_subject = get_subject_by_id(head, subject_id);
  print_subject(found_subject);
}

// Prints all students studying a given subject
void print_students_by_subject(StudentList *head, int subject_id) {
  StudentList *current = head;
  while (current != NULL) {
    SubjectList *found_subject = get_subject_by_id(current->student.student_subjects, subject_id);
    if (found_subject != NULL) {
      printf("%s \n", current->student.student_name);
    }
    current = current->next;
  }
}

// Find which teachers teach a specified student
void print_teachers_by_student(StudentList *head, int student_id) {
  StudentList *found_student = get_student_by_id(head, student_id);
  SubjectList *existing_subjects = found_student->student.student_subjects;
  if (existing_subjects != NULL) {
    printf("%s\'s teachers \n", found_student->student.student_name);
    SubjectList *current_subjects = existing_subjects;
    while (current_subjects != NULL) {
      printf("%s \n", current_subjects->subject.teacher);
      current_subjects = current_subjects->next;
    }
  }
  else {
    printf("No teachers were assigned to %s \n", found_student->student.student_name);
  }
}

// Find which students are taught by a specified teacher
void print_students_by_teacher(StudentList *head, char *teacher) {
  StudentList *current = head;
  while (current != NULL) {
    SubjectList *existing_subjects = current->student.student_subjects;
    SubjectList *current_subjects = existing_subjects;
    while (current_subjects != NULL) {
      if (strcmp(current_subjects->subject.teacher, teacher) == 0) {
        printf("%s \n", current->student.student_name);
      }
      current_subjects = current_subjects->next;
    }
    current = current->next;
  }
}