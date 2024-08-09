#include <stdio.h>

struct student
{
    int ID ;
    float LAB ;
    float MID ;
    float FINAL ;
    float TOTAL ;
    char GRADE ;
} ;

int main() {
 struct student student1 = {111,58.00,56.00,57.00,56.90,"D"};
 struct student student2 = {222,63.00,65.00,69.00,66.60,"C"};
 struct student student3 = {333,86.00,85.00,84.00,84.70,"A"};
 struct student student4 = {444,68.00,76.00,86.00,79.40,"A"};


printf("Student 1:\n");
    printf("ID: %d\n", student1.ID);
    printf("LAB: %.2f\n", student1.LAB);
    printf("MID: %.2f\n", student1.MID);
    printf("FINAL: %.2f\n", student1.FINAL);
    printf("TOTAL: %.2f\n", student1.TOTAL);
    printf("GRADE: %c\n", student1.GRADE);

}
