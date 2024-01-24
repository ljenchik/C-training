#include<stdio.h>
#include <stdlib.h>
#include<string.h>

static int subject_id = 0;
static int student_id = 0;

typedef struct subject {
  int subject_id;
	char *subject_name;	
	char *teacher;
	int grade;
} Subject;

typedef struct subject_list {
	Subject subject;
	struct subject_list *next;
} SubjectList;


typedef struct student {
	int student_id;
	char *student_name;
  SubjectList *student_subjects;
} Student;


typedef struct student_list {
	Student student;
  struct student_list *next;
} StudentList;

// =================Subjects functions================

// Creating a new subject
SubjectList *create_subject(char *subject_name, char *teacher) {
  SubjectList *new_subject=malloc(sizeof(SubjectList));
  new_subject->subject.subject_id = ++subject_id;

  new_subject->subject.subject_name = malloc(strlen(subject_name));
  strcpy(new_subject->subject.subject_name, subject_name); 

  new_subject->subject.teacher = malloc(strlen(teacher));
  strcpy(new_subject->subject.teacher, teacher);

  new_subject->next=NULL;
  return new_subject;
}

// Printing a  given subject with all info
void print_subject(SubjectList *subject) {
  printf("\t%d\t%s\t%s\n", subject->subject.subject_id, subject->subject.subject_name, subject->subject.teacher);
}

// Printing a specified subject found by id
void find_and_print_subject(SubjectList *head, int subject_id){
  if (head == NULL) {
    printf("Error: invalid pointer \n");
  } else {
      SubjectList *current = head;
      while (current != NULL) {
        if (current->subject.subject_id == subject_id) {
            print_subject(current);
            return;
        }
        current = current->next;
      }
  }
  printf("Subject with id %d was not found \n", subject_id);
}

// Printing all subjects with teachers
void print_subjects(SubjectList *head){
  if (head == NULL)
  {
    printf("Error: invalid pointer \n");
  }
  else {
    SubjectList *current = head;
    printf("Subject id \t Subject \t Teacher \n");
    while (current != NULL) {
      print_subject(current);
      current = current->next;
    }
  }
}

// Inserting a new subject at the back of a list
void add_subject(SubjectList *head, SubjectList *new_subject) {
  if (new_subject == NULL)
  {
    printf("Error: invalid pointer, no subject to insert \n");
    return;
  }
  if (head == NULL)
  {
    printf("Error: invalid pointer, no subject head \n");
    return;
  }
  SubjectList *current = head;
  while (current->next != NULL) {
    current = current->next;
  }
  current->next = new_subject;
  new_subject->next=NULL;
}

// Getting a specified subject found by id
SubjectList *get_subject_by_id(SubjectList *head, int subject_id){
  // if (head == NULL)
  // {
  //   printf("Error: invalid pointer \n");
  //   return NULL;
  // }
  // else {
    SubjectList *current = head;
    while (current != NULL) {
      if (current->subject.subject_id == subject_id) {
          return current;
        }
        current = current->next;
    }
  // }
  // printf("Subject with id %d was not found \n", subject_id);
  return NULL;
}

// Getting a specified subject found by name
Subject *get_subject_by_name(SubjectList *head, char * subject_name){
  if (head == NULL)
  {
    printf("Error: invalid pointer \n");
    return NULL;
  }
  else {
    SubjectList *current = head;
    while (current != NULL) {
      if (strcmp(current->subject.subject_name, subject_name) == 0) {
          print_subject(current);
          return &(current->subject);
        }
        current = current->next;
    }
    printf("Subject with name %s was not found \n", subject_name);
  }
  return NULL;
}


//================Students functions====================
// Creating a student
StudentList *create_student(char *student_name) {
  StudentList *new_student=malloc(sizeof(StudentList));
  new_student->student.student_id = ++student_id;

  new_student->student.student_name = malloc(strlen(student_name));
  strcpy(new_student->student.student_name, student_name);

  new_student->student.student_subjects=NULL;
  new_student->next=NULL;

  return new_student;
}

// Printing a given student with all info
void print_student(Student *student) {
  printf("Student id\tStudent name\tSubjects\n");
  printf("\t%d\t%s\t\t", student->student_id, student->student_name);
  SubjectList *current = student->student_subjects;
  while (current != NULL) {
    printf("%s  ", current->subject.subject_name);
    current = current->next;
  }
  printf("\n");
}

// Printing a student found by id
void find_and_print_student(StudentList *head, int student_id){
  if (head == NULL) {
    printf("Error: invalid pointer \n");
  } else {
      StudentList *current = head;
      while (current != NULL) {
        if (current->student.student_id == student_id) {
            print_student(&current->student);
            return;
        }
        current = current->next;
      }
  }
  printf("Student with id %d was not found \n", student_id);
}

// Adding a new student 
void add_student(StudentList *head, StudentList *new_student) {
  if (new_student == NULL)
  {
    printf("Error: invalid pointer, no student to add \n");
  }
  if (head == NULL)
  {
    head = new_student;
  }
  else {
    StudentList *current = head;
    while (current->next != NULL) {
      current = current->next;
    }
    current->next = new_student;
    new_student->next=NULL;
  }
}

// Printing all students with their subjects, needs some work on printing subjects
void print_students(StudentList *head){
  if (head == NULL)
  {
    printf("Error: invalid pointer \n");
  }
  else {
    StudentList *current = head;
    printf("Student id\tName\t\tSubjects\n");
    while (current != NULL) {
      if (current->student.student_subjects == NULL) {
        print_student(&(current->student));
      }
      else {
        printf("\t%d\t%s\t\t", current->student.student_id, current->student.student_name);
        while (current->student.student_subjects != NULL) {
          printf("%s ",  current->student.student_subjects->subject.subject_name);
          current->student.student_subjects = current->student.student_subjects->next;
        }
        printf("\n");
      }
        
      current = current->next;
  }
  printf("\n");
  }
}

// Getting a student by id
StudentList *get_student_by_id(StudentList *head, int student_id){
  if (head == NULL)
  {
    printf("Error: invalid pointer \n");
  }
  else {
    StudentList *current = head;
    while (current != NULL) {
      if (current->student.student_id == student_id) {
          // print_student(current);
          return current;
        }
        current = current->next;
    }
    printf("Student with id %d was not found \n", student_id);
  }
  return NULL;
}

// Getting a student by name
Student *get_student_by_name(StudentList *head, char *student_name){
  if (head == NULL)
  {
    printf("Error: invalid pointer \n");
    return NULL;
  }
  else {
    StudentList *current = head;
    while (current != NULL) {
       if (strcmp(current->student.student_name, student_name) == 0) {
          print_student(&current->student);
          return &(current->student);
        }
        current = current->next;
    }
    printf("Student with name %s was not found \n", student_name);
  }
  return NULL;
}

// Adds a subject and a corresponding teacher to the subjects of a student with a given id
void add_subject_to_student(StudentList *student_head, SubjectList *subject_head) {
    SubjectList *existing_subjects = student_head->student.student_subjects;
    SubjectList *new_head = malloc(sizeof(SubjectList));
    new_head->subject = subject_head->subject;
    new_head->next = existing_subjects;
    student_head->student.student_subjects = new_head;
}

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

// Add a grade to a given student to a given subject
void add_grade(Student *student, int subject_id, int grade) {
  SubjectList *existing_subjects = student->student_subjects;
  SubjectList *found_subject = get_subject_by_id(existing_subjects, subject_id);
  if (found_subject != NULL) {
    found_subject->subject.grade = grade;
  }
}

// Prints all subjects with the corresponding grades for a given student
void print_subjects_with_grades(Student *student) {
   SubjectList *existing_subjects = student->student_subjects;
   if (existing_subjects == NULL) {
    printf("Subjects and grades were no assigned to %s \n", student->student_name);
   }
   else {
    printf("%s\'s subjects and grades \n", student->student_name);
    while (existing_subjects != NULL) {
    printf("%d\t\t%s\t\t%d \n", existing_subjects->subject.subject_id, existing_subjects->subject.subject_name, existing_subjects->subject.grade);
    existing_subjects=existing_subjects->next;
   }
  }
}

// Finds a grade for a specified student for a given subject
void print_grade_per_subject(Student *student, int subject_id) {
  SubjectList *existing_subjects = student->student_subjects;
  SubjectList *found_subject = get_subject_by_id(existing_subjects, subject_id);
  if (found_subject != NULL) {
      printf("%d \n", found_subject->subject.grade);
    }
  }
  
int main () {
  SubjectList *subject_head = NULL;
  // Creating a head for SubjectList
  subject_head = create_subject("Mathematics", "Mr Black");
  // Creating a new subject and adding it to the SubjectList
  SubjectList *new_subject = create_subject("English", "Mrs Brown");
  add_subject(subject_head, new_subject);
  // Creating a new subject and adding it to the SubjectList
  SubjectList *new_subject1 = create_subject("History", "Mrs White");
  add_subject(subject_head, new_subject1);
  // Printing all subjevts with subject ids and teachers
  print_subjects(subject_head);
  printf("=================================================== \n");
  // Getting a subject by subject id
  // get_subject_by_id(subject_head, 2);
  // Generates an error message, wrong subject id
  // get_subject_by_id(subject_head, 5);
  // Getting a subject by subject name
  // get_subject_by_name(subject_head, "History");
  // Generates an error message, wrong subject name
  // get_subject_by_name(subject_head, "Science");
  printf("=================================================== \n");
  StudentList *student_head = NULL;
  student_head = create_student("Jack");
  StudentList *new_student = create_student("Lisa");
  add_student(student_head, new_student);
  StudentList *new_student1 = create_student("Misha");
  add_student(student_head, new_student1);
  print_students(student_head);
  printf("=================================================== \n");
  get_student_by_id(student_head, 2);
  // Generates an error message, wrong student id
  get_student_by_id(student_head, 5);
  get_student_by_name(student_head, "Misha");
  // Generates an error message, wrong student name
  get_student_by_name(student_head, "Olena");
  printf("=================================================== \n");
  
  SubjectList *subjects_with_id_2 = get_subject_by_id(subject_head, 2);
  SubjectList *subjects_with_id_3 = get_subject_by_id(subject_head, 3);

  StudentList* student_with_id_1 = get_student_by_id(student_head, 1);

  add_subject_to_student(student_with_id_1, subjects_with_id_2);
  add_subject_to_student(student_with_id_1, subjects_with_id_3);

  StudentList* student_with_id_3 = get_student_by_id(student_head, 3);
  add_subject_to_student(student_with_id_3, subjects_with_id_3);

  StudentList* student_with_id_2 = get_student_by_id(student_head, 2);

  // print_student with their subjects
  print_student(&student_with_id_3->student);
  print_student(&student_with_id_1->student);
  print_student(&student_with_id_2->student);
  printf("=================================================== \n");
  // prints a teacher by subject id
  //find_teacher_by_subject(subject_head, 2);
  printf("=================================================== \n");

  print_students_by_subject(student_head, 3);

  print_students_by_subject(student_head, 2);

  print_students_by_subject(student_head, 1);

  print_students_by_subject(student_head, 5);
  printf("=================================================== \n");
  add_grade(&student_with_id_1->student, 3, 98);
  print_subjects_with_grades(&student_with_id_1->student);

  printf("=================================================== \n");
  print_grade_per_subject(&student_with_id_1->student, 3);

  return 0;
}

