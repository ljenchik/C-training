// Write a program which prints all the values stored in a struct.
#include<stdio.h>
#include<string.h>
struct person {
  char name[20];
  int age;
  char address[30];
  float height;
};

struct item {
  char name[20];
  int quantity;
  float price;
};

struct student {
  char name[20];
  char gender[10];
  int age;
  float average_grade;
};

struct number {
  float num;
};

struct child {
  char name[20];
  int age;
};

struct parent {
  char name[20];
  int number_of_children;
  struct child child; 
};

int main(void) {
  // Initialization using Initializer List
  struct person new_person = {"John", 23, "London", 1.78};
  printf("Name: %s\n", new_person.name);
  printf("Age: %d\n", new_person.age);
  printf("Address: %s\n", new_person.address);
  printf("Height: %.2f\n", new_person.height);

  //Initialization using Assignment Operator
  struct item new_item;
  // Use the strcpy() function to assign the value array:
  strcpy(new_item.name, "Pen");
  new_item.quantity = 20;
  new_item.price = 2.50;
  printf("Name: %s\n", new_item.name);
  printf("Quantity: %d\n", new_item.quantity);
  printf("Price: %.2f\n", new_item.price);

  //Initialization using Initializer List
  struct student new_student = {.average_grade = 84.5, .name = "Chris", .age = 34, .gender = "Female"};
  printf("Name: %s\n", new_student.name);
  printf("Gender %s\n", new_student.gender);
  printf("Age %d\n", new_student.age);
  printf("Average grade %.2f\n", new_student.average_grade);

  // Use of typedef
  typedef struct number number;
  number new_number = {35.12};
  printf("Number: %.f\n", new_number.num);

  // Nested structures (parent and child)
  struct child child1 = {"Helen", 12};
  struct parent parent1 = {"David", 2, child1};
  printf("Parent name: %s\n", parent1.name);
  printf("Number of children: %d\n", parent1.number_of_children);
  printf("Child's name: %s\n", parent1.child.name);
  printf("Child's age: %d\n", parent1.child.age);



  return 0;
}