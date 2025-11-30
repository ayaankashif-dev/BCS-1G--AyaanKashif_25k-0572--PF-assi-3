#include<stdio.h>
#include<math.h>
#include<string.h>

struct Employee{
    int id;
    char name[50];
    char designation[50];
    float salary;
};

void show(){
    printf("1. Display all employees\n");
    printf("2. Find the employee with highest salary\n");
    printf("3. Search by ID\n");
    printf("4. Search by Name\n");
    printf("5. To give bonus to employees\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");

    return;
}

void displayEmployees(struct Employee employees[], int n){
    printf("Employee Details:\n");
    for(int i=0;i<n;i++){
        printf("ID: %d, Name: %s, Designation: %s, Salary: %.2f\n", employees[i].id, employees[i].name, employees[i].designation, employees[i].salary);
    }
    return;
}

void findhighestSalary(struct Employee employees[], int n){
    
    int maxIndex=0;
    char n1[50];
    float maxsalary=-1.0;
    for(int i=0;i<n;i++){
        if(employees[i].salary>maxsalary){
            maxsalary=employees[i].salary;
            strcpy(n1, employees[i].name);
        }
    }
    printf("Employee with highest salary is %s with salary %.2f\n", n1, maxsalary);
    return;
}

void searchByID(struct Employee employees[], int n){
    int id;
    printf("Enter ID to search: ");
    scanf("%d", &id);
    int found=0;
    for(int i=0;i<n;i++){
        if(employees[i].id==id){
            printf("Employee found: ID: %d, Name: %s, Designation: %s, Salary: %.2f\n", employees[i].id, employees[i].name, employees[i].designation, employees[i].salary);
            found=1;
            break;
        }
    }
    if(!found){
        printf("Employee with ID %d not found\n", id);
    }
    return;
}

void searchByName(struct Employee employees[], int n){
    char name[50];
    printf("Enter Name to search: ");
    scanf(" %[^\n]s", name);
    int found=0;
    for(int i=0;i<n;i++){
        if(strcmp(employees[i].name, name)==0){
            printf("Employee found: ID: %d, Name: %s, Designation: %s, Salary: %.2f\n", employees[i].id, employees[i].name, employees[i].designation, employees[i].salary);
            found=1;
            break;
        }
    }
    if(!found){
        printf("Employee with Name %s not found\n", name);
    }
    return;
}

void giveBonus(struct Employee employees[], int n){
    float temp;
    printf("Enter salaray below which you want to give 10% bonus: ");
    scanf("%f", &temp);
    for(int i=0;i<n;i++){
        if(employees[i].salary < temp){
            employees[i].salary += employees[i].salary * 0.10;
        }
    }
    printf("Bonus given to employees with salary below %.2f\n", temp);
    return;
}

int main(){
    int n;
    printf("Enter number of employees: ");
    scanf("%d", &n);
    struct Employee employees[n];
    for(int i=0;i<n;i++){
        printf("Enter details for employee %d\n", i+1);
        printf("ID: ");
        scanf("%d", &employees[i].id);
        printf("Name: ");
        scanf(" %[^\n]s", employees[i].name);
        printf("Designation: ");
        scanf(" %[^\n]s", employees[i].designation);
        printf("Salary: ");
        scanf("%f", &employees[i].salary);
    }

    int choice;
    do{
        show();
        scanf("%d", &choice);

        switch(choice){
            case 1:
            displayEmployees(employees,n);
                break;
            case 2:
            findhighestSalary(employees,n);
                break;
            case 3:
            searchByID(employees,n);
                break;
            case 4:
            searchByName(employees,n);
                break;
            case 5:
            giveBonus(employees,n);
                break;
            case 6:
            printf("Exiting...\n");
                break;
            default:
            printf("Invalid choice\n");
        }
    }while(choice!=6);


    return 0;
}