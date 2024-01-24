#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#include <stdbool.h>

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

// Creating a new subject (it's a node in a SubjectList)
SubjectList *create_subject(char *subject_name, char *teacher) {
  if (strlen(subject_name) <= 1 || strlen(teacher) <= 0) {
    printf("Subject name and/or teacher name must not be empty");
    return NULL;
  }
  else {
    SubjectList *new_subject=malloc(sizeof(SubjectList));
  // Creating subject_id using a static variable
  new_subject->subject.subject_id = ++subject_id;

  new_subject->subject.subject_name = malloc(strlen(subject_name));
  strcpy(new_subject->subject.subject_name, subject_name); 

  new_subject->subject.teacher = malloc(strlen(teacher));
  strcpy(new_subject->subject.teacher, teacher);

  new_subject->next=NULL;
  return new_subject;
  }
}

// Printing a  given subject with all info
void print_subject(SubjectList *subject) {
  // Breaks a string by delimiter "/n"
  strtok(subject->subject.subject_name, "\n");
  strtok(subject->subject.teacher, "\n");
  printf("\t%d\t\%s\t\t%s\n", subject->subject.subject_id, subject->subject.subject_name, subject->subject.teacher);
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
    printf("Subject id\tSubject\t\tTeacher\n");
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
  if (head == NULL)
  {
    printf("Error: invalid pointer \n");
    return NULL;
  }
  else {
    SubjectList *current = head;
    while (current != NULL) {
      if (current->subject.subject_id == subject_id) {
          return current;
        }
        current = current->next;
    }
  }
  printf("Subject with id %d was not found \n", subject_id);
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
        printf("%s \n" ,current->student.student_name);
      }
      current_subjects = current_subjects->next;
    }
    current = current->next;
  }
}

int main () {
  // ==================Subject functions=====================
  SubjectList *subject_head = NULL;
  char subject_name[64];
  char subject_teacher[64];
  bool empty_head_subject = true;
  bool empty_head_teacher = true;

  // Getting user's data (subject name and subject teacher)
  printf("Add the first subject\n");

  while (empty_head_subject == true) {
        printf("Enter a subject name \n");
        fgets(subject_name, 64, stdin);
        if (subject_name[0] == '\0' || subject_name[0] == '\n') {
          printf("Subject name must not be empty\n");
        }
        else {
          empty_head_subject= false;
        }
    }
    empty_head_subject = true;

   while (empty_head_teacher == true) {
        printf("Enter a teacher name \n");
        fgets(subject_teacher, 64, stdin);
        if (subject_teacher[0] == '\0' || subject_teacher[0] == '\n') {
          printf("Teacher name must not be empty\n");
        }
        else {
          empty_head_teacher= false;
        }
    }
    empty_head_teacher = true;

  // Creating a head of SubjectList
  subject_head = create_subject(subject_name, subject_teacher);

  bool add_more_subjects = true;
  bool empty_subject = true;
  bool empty_teacher = true;
  char user_response[5];

  printf("Add another subject? (y/n) \n");
  fgets(user_response, 5, stdin);
  if (strcmp(user_response, "n\n") == 0) {
    add_more_subjects = false;
  }
  else {
    while (add_more_subjects == true) {
      // Adding a new subject to the SubjectList
      char subject_name[64];
      char subject_teacher[64];

      // Getting user's data (subject name and subject teacher)
      // Checking for empty inputs
      while (empty_subject == true) {
        printf("Enter a subject name \n");
        fgets(subject_name, 64, stdin);
        if (subject_name[0] == '\0' || subject_name[0] == '\n') {
          printf("Subject name must not be empty\n");
        }
        else {
          empty_subject= false;
        }
      }
      empty_subject = true;
      
      // Checking for empty inputs
      while (empty_teacher == true) {
        printf("Enter a teacher name \n");
        fgets(subject_teacher, 64, stdin);
        if (subject_teacher[0] == '\0' || subject_teacher[0] == '\n') {
          printf("Teacher name must not be empty\n");
        }
        else {
          empty_teacher= false;
        }
      }
      empty_teacher = true;

      SubjectList *new_subject = create_subject(subject_name, subject_teacher);
      add_subject(subject_head, new_subject);

      printf("Do you want to add another subject? (y/n) \n");
      fgets(user_response, 5, stdin);
      if (strcmp(user_response, "n\n") == 0) {
        add_more_subjects = false;
      }
    }
  }

  // To do: check empty inputs and if subject is already in the list
  print_subjects(subject_head);

  printf("=================================================== \n");

  // // Testing functions get_subject_by_id() and get_subject_by_name()
  // // Getting a subject by subject id
  // get_subject_by_id(subject_head, 2);
  // // Generates an error message, wrong subject id
  // get_subject_by_id(subject_head, 5);
  // // Getting a subject by subject name
  // get_subject_by_name(subject_head, "History");
  // // Generates an error message, wrong subject name
  // get_subject_by_name(subject_head, "Science");

  printf("=================================================== \n");

  // StudentList *student_head = NULL;
  // student_head = create_student("Jack");
  // StudentList *new_student = create_student("Lisa");
  // add_student(student_head, new_student);
  // StudentList *new_student1 = create_student("Misha");
  // add_student(student_head, new_student1);
  // print_students(student_head);
  // printf("=================================================== \n");
  // get_student_by_id(student_head, 2);
  // // Generates an error message, wrong student id
  // get_student_by_id(student_head, 5);
  // get_student_by_name(student_head, "Misha");
  // // Generates an error message, wrong student name
  // get_student_by_name(student_head, "Olena");
  // printf("=================================================== \n");
  
  // SubjectList *subjects_with_id_2 = get_subject_by_id(subject_head, 2);
  // SubjectList *subjects_with_id_3 = get_subject_by_id(subject_head, 3);

  // StudentList* student_with_id_1 = get_student_by_id(student_head, 1);

  // add_subject_to_student(student_with_id_1, subjects_with_id_2);
  // add_subject_to_student(student_with_id_1, subjects_with_id_3);

  // StudentList* student_with_id_3 = get_student_by_id(student_head, 3);
  // add_subject_to_student(student_with_id_3, subjects_with_id_3);

  // StudentList* student_with_id_2 = get_student_by_id(student_head, 2);

  // // print_student with their subjects
  // print_student(&student_with_id_3->student);
  // print_student(&student_with_id_1->student);
  // print_student(&student_with_id_2->student);
  // printf("=================================================== \n");
  // // prints a teacher by subject id
  // //find_teacher_by_subject(subject_head, 2);
  // printf("=================================================== \n");

  // print_students_by_subject(student_head, 3);

  // print_students_by_subject(student_head, 2);

  // print_students_by_subject(student_head, 1);

  // print_students_by_subject(student_head, 5);
  // printf("=================================================== \n");
  // add_grade(&student_with_id_1->student, 3, 98);
  // print_subjects_with_grades(&student_with_id_1->student);

  // printf("=================================================== \n");
  // print_grade_per_subject(&student_with_id_1->student, 3);


  // printf("=================================================== \n");
  // print_students_by_teacher(student_head, "Mrs White");

  // print_students_by_teacher(student_head, "Mrs Brown");

  // print_students_by_teacher(student_head, "Mr Black");

  // printf("=================================================== \n");
  // print_teachers_by_student(student_head, 1);

  return 0;
}
