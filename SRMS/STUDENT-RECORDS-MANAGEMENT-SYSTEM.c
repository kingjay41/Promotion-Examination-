#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STUDENTS 100

typedef struct {
    char name[50];
    int studentNo;
    float math, english, computer;
    float total, average;
    char grade;
} Student;

void addStudent(Student s[], int *count);
void viewStudents(Student s[], int count);
void searchStudent(Student s[], int count);
void calculateResults(Student s[], int count);
void saveToFile(Student s[], int count);
char determineGrade(float avg);

int main() {
    Student students[MAX_STUDENTS];
    int count = 0;
    int choice;

    while (1) {
        printf(" STUDENT MANAGEMENT SYSTEM\n");
        printf("1. Add Student\n");
        printf("2. View Students\n");
        printf("3. Search Student\n");
        printf("4. Calculate Results\n");
        printf("5. Save Results to File\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent(students, &count);
                break;
            case 2:
                viewStudents(students, count);
                break;
            case 3:
                searchStudent(students, count);
                break;
            case 4:
                calculateResults(students, count);
                break;
            case 5:
                calculateResults(students, count);
                saveToFile(students, count);
                break;
            case 6:
                exit(0);
            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}

void addStudent(Student s[], int *count) {
    if (*count >= MAX_STUDENTS) {
        printf("Nomore storage!\n");
        return;
    }

    printf("Enter Name: ");
    scanf(" %[^\n]", s[*count].name);

    printf("Enter Student Number: ");
    scanf("%d", &s[*count].studentNo);

    printf("Enter Math Marks: ");
    scanf("%f", &s[*count].math);

    printf("Enter English Marks: ");
    scanf("%f", &s[*count].english);

    printf("Enter Computer Marks: ");
    scanf("%f", &s[*count].computer);

    (*count)++;

    printf("Added successfully!\n");
}

void viewStudents(Student s[], int count) {
    if (count == 0) {
        printf("No records found.\n");
        return;
    }

    printf("\n%-20s %-12s %-6s %-8s %-8s\n", "\nName", "\nStudent No", "\nMath", "\nEnglish", "\nComputer");

    for (int i = 0; i < count; i++) {
        printf("%-20s %-12d %-6.1f %-8.1f %-8.1f\n",
               s[i].name,
               s[i].studentNo,
               s[i].math,
               s[i].english,
               s[i].computer);
    }
}

void searchStudent(Student s[], int count) {
    int id;
    int found = 0;

    printf("Enter Student Number to search: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (s[i].studentNo == id) {
            printf("\nStudent Found\n");
            printf("Name: %s\n", s[i].name);
            printf("Number: %d\n", s[i].studentNo);
            printf("Math: %.1f\n", s[i].math);
            printf("English: %.1f\n", s[i].english);
            printf("Computer: %.1f\n", s[i].computer);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Student not found.\n");
    }
}

char determineGrade(float avg) {
    if (avg >= 80)
        return 'A';
    else if (avg >= 70)
        return 'B';
    else if (avg >= 60)
        return 'C';
    else if (avg >= 50)
        return 'D';
    else
        return 'F';
}

void calculateResults(Student s[], int count) {
    if (count == 0) {
        printf("No students to calculate.\n");
        return;
    }

    printf("\n Records \n");

    for (int i = 0; i < count; i++) {
        s[i].total = s[i].math + s[i].english + s[i].computer;
        s[i].average = s[i].total / 3;
        s[i].grade = determineGrade(s[i].average);

        printf("Name: %s | Total: %.1f | Avg: %.2f | Grade: %c\n",
               s[i].name,
               s[i].total,
               s[i].average,
               s[i].grade);
    }
}

void saveToFile(Student s[], int count) {
    FILE *fp = fopen("students.txt", "w");

    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    fprintf(fp, "%-20s %-12s %-6s %-6s %-6s %-6s %-5s\n",
            "Name", "ID", "Mat", "Eng", "Com", "Avg", "Grd");

    for (int i = 0; i < count; i++) {
        fprintf(fp, "%-20s %-12d %-6.1f %-6.1f %-6.1f %-6.1f %-5c\n",
                s[i].name,
                s[i].studentNo,
                s[i].math,
                s[i].english,
                s[i].computer,
                s[i].average,
                s[i].grade);
    }

    fclose(fp);

    printf("Records saved to students.txt\n");
}
