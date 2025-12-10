#ifndef SCHOOL_H
#define SCHOOL_H

// External variables for ID generation
extern int subject_id;
extern int student_id;

// Subject structure
typedef struct subject {
  int subject_id;
  char *subject_name;
  char *teacher;
  int grade;
} Subject;

// Subject list node
typedef struct subject_list {
  Subject subject;
  struct subject_list *next;
} SubjectList;

// Student structure
typedef struct student {
  int student_id;
  char *student_name;
  SubjectList *student_subjects;
} Student;

// Student list node
typedef struct student_list {
  Student student;
  struct student_list *next;
} StudentList;

// Subject function declarations
SubjectList *create_subject(char *subject_name, char *teacher);

void print_subject(SubjectList *subject);
void print_subjects(SubjectList *head);

SubjectList *get_subject_by_id(SubjectList *head, int subject_id);
Subject *get_subject_by_name(SubjectList *head, char *subject_name);
Subject *get_subject_by_teacher(SubjectList *head, char *teacher);
void add_subject(SubjectList *head, SubjectList *new_subject);

// Student function declarations
StudentList *create_student(char *student_name);

void print_student(Student *student);
void print_students(StudentList *head);
void add_student(StudentList *head, StudentList *new_student);
void print_subjects_with_grades(Student *student);
void print_grade_per_subject(Student *student, int subject_id);

StudentList *get_student_by_id(StudentList *head, int student_id);
Student *get_student_by_name(StudentList *head, char *student_name);
void add_subject_to_student(StudentList *student_node,
                            SubjectList *subject_node,
                            SubjectList *all_subjects_head);
void add_grade(Student *student, int subject_id, int grade);

// Query functions
void find_teacher_by_subject(SubjectList *head, int subject_id);
void print_students_by_subject(StudentList *head, int subject_id);
void print_teachers_by_student(StudentList *head, int student_id);
void print_students_by_teacher(StudentList *head, char *teacher);

// Menu functions void display_menu(void);
void run_menu(StudentList **student_head, SubjectList **subject_head);

// Helper functions for menu
void menu_add_subject(SubjectList **subject_head);
void menu_add_student(StudentList **student_head);
void menu_add_subject_to_student(StudentList *student_head,
                                 SubjectList *subject_head);
void menu_add_grade(StudentList *student_head);
void menu_find_students_by_subject(StudentList *student_head);
void menu_find_teacher_by_subject(SubjectList *subject_head);
void menu_find_grades(StudentList *student_head);
void menu_find_teachers_by_student(StudentList *student_head);
void menu_find_students_by_teacher(StudentList *student_head);

// Utility functions
void strip_newline(char *str);
int get_int_input(const char *prompt);

// File I/O functions
int save_subjects_to_file(SubjectList *head, const char *filename);
int save_students_to_file(StudentList *head, const char *filename);
SubjectList *load_subjects_from_file(const char *filename, int *max_id);
StudentList *load_students_from_file(const char *filename,
                                     SubjectList *subject_head, int *max_id);
void save_all_data(StudentList *student_head, SubjectList *subject_head);
void load_all_data(StudentList **student_head, SubjectList **subject_head);

#endif