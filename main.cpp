#include <iostream>
#include "student.h"
#include<limits>
using namespace std;

int menu(int*);

int main()
{
    int choice;
    while(menu(&choice)!= 6){
        system("clear");
        if(choice == 1){
            showStudents();
            cout << "\n\n Press any key to continue";
        } else if(choice == 2){
            student s;
            s.addStudent(false);
            s.addToDatabase();
            cout << "New record added successfully, Press enter to continue.\n";
        } else if(choice == 3){
            update();
        } else if(choice == 4){
            search();
        } else if(choice == 5){
            deleteStudent();
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        system("clear");
    }

    system("clear");
    cout << endl << "bye bye";
    return 0;
}

int menu(int* choice){
    system("clear");
    cout << "****\tStudents Record Menu\t****\n";
    cout <<"\n1 - Show all records.";
    cout <<"\n2 - Add new student.";
    cout <<"\n3 - Update student.";
    cout <<"\n4 - Search student.";
    cout <<"\n5 - Delete student.";
    cout <<"\n6 - Exit.";
    cout <<"\n\nEnter an option :";
    cin >> *choice;
    getchar();
    return *choice;
}
