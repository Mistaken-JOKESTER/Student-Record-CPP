#include "student.h"
#include<iostream>
#include <iomanip>
#include<ios>
#include<limits>
#include<fstream>

using namespace std;

void student::getStudent(){
        cout << "Name" << setw(6) <<  ": "<< name <<  "\n";
        cout << "Roll No." << setw(3) <<  ": "<< rollNo <<  "\n";
        cout << "Standard" << setw(2) <<  ": "<< standard <<  "\n";
        cout << "Percentage" << setw(0) <<  ": "<< percentage <<  "\n";
        cout << "Grade" << setw(5) <<  ": "<< grade <<  "\n";
        cout << "Marks\n";
        cout << "\t> Physics" << setw(1) << ": " << p_marks <<  "\n";
        cout << "\t> Chemistry" << setw(0) << ": " << c_marks <<  "\n";
        cout << "\t> Maths" << setw(4) << ": " << m_marks <<  "\n";
        cout << "\t> English" << setw(2) << ": " << e_marks <<  "\n";
}

void student::addStudent(bool update){
    if(!update){
        do{
            cout << "Enter standard(1-12) :";
            cin >> standard;
        } while(standard < 0 || standard > 12);

        fstream file;
        file.open("student_record.dat", ios::binary|ios::in);

        if(!file.is_open()){
            cout << "Unable to open file, press any key to continue.";
            getchar();
            return;
        }

        bool flag;
        do{
            flag = false;
            cout << "Enter RollNo : ";
            cin >> rollNo;
            student st;
            while(file.read((char *)&st, sizeof(student))){
                if(st.exsistStudent(rollNo, standard)){
                    flag = true;
                    cout << "Student with give roll No. in given standard already exsists.\n";
                    break;
                }
            }
        }while(flag);
        file.close();
    }

    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter Name (Max 40 words) :";
    cin.getline(name, 40);

    do{
        cout << "Enter physics marks :";
        cin >> p_marks;
    } while(p_marks > 100 || p_marks < 0);

    do{
        cout << "Enter chemistry marks :";
        cin >> c_marks;
    } while(c_marks > 100 || c_marks < 0);

    do{
        cout << "Enter maths marks :";
        cin >> m_marks;
    } while(m_marks > 100 || m_marks < 0);

    do{
        cout << "Enter english marks :";
        cin >> e_marks;
    } while(e_marks > 100 || e_marks < 0);

    percentage = (p_marks + c_marks + m_marks + e_marks)/ 4.0;

    if(percentage < 33.0){
        grade = 'F';
    } else if(percentage < 50.0){
        grade = 'D';
    } else if(percentage < 70.0){
        grade = 'C';
    } else if(percentage < 80.0){
        grade = 'B';
    } else {
        grade = 'A';
    }
    getchar();
    return;
}

void student::addToDatabase(){
    fstream file;
    file.open("student_record.dat", ios::binary|ios::app);

    if(!file.is_open()){
        cout << "Unable to open file, press any key to continue.";
        getchar();
        return;
    }

    file.write((char*) this, sizeof(student));
    file.close();
};

bool student::exsistStudent(int r, int s){
    if(rollNo == r && s == standard){
        return true;
    }
    return false;
}

void showStudents(){
    fstream file;
    file.open("student_record.dat", ios::binary|ios::in);

    if(!file.is_open()){
        cout << "Unable to open file, press any key to continue.";
        getchar();
        return;
    }

    student st;
    int count = 0;
    while(file.read((char *)&st, sizeof(student))){
        count++;
        st.getStudent();
        cout << "-------------------------------\n";
    }

    if(count){
        cout << "No of records :" << count << "\n";
    } else {
        cout << "No record found, add some records.\n";
    }
    file.close();
}

void update(){
    int rollNo, standard;
    cout << "Enter the RollNo :";
    cin >> rollNo;
    cout << "Enter the standard :";
    cin >> standard;

    fstream file;
    file.open("student_record.dat", ios::binary|ios::in|ios::out);

    if(!file.is_open()){
        cout << "Unable to open file, press any key to continue.";
        getchar();
        return;
    }

    student st;
    int count = 0;
    streampos pos=file.tellg();
    while(file.read((char *)&st, sizeof(student))){
        if(st.exsistStudent(rollNo, standard)){
            count++;
            break;
        }
        pos=file.tellg();
    }

    file.seekp(pos);

    if(!count){
        cout << "No record found, add some records.\n";
    } else {
        cout << "**** Old Record ****\n";
        st.getStudent();
        cout << "\n**** Updating Record ****\n\n";
        st.addStudent(true);
        file.write((char*) &st, sizeof(student));
        cout << "Updating..............\n";
        cout << "Record updated successfully, Press enter to continue.\n";
    }
    file.close();
}

void search(){
    int rollNo, standard;
    cout << "Enter the RollNo :";
    cin >> rollNo;
    cout << "Enter the standard :";
    cin >> standard;
    getchar();

    fstream file;
    file.open("student_record.dat", ios::binary|ios::in);

    if(!file.is_open()){
        cout << "Unable to open file, press any key to continue.";
        getchar();
        return;
    }

    student st;
    int count = 0;
    while(file.read((char *)&st, sizeof(student))){
        if(st.exsistStudent(rollNo, standard)){
            count++;
            break;
        }
    }
    file.close();

    if(!count){
        cout << "No record found, add some records.\n";
    } else {
        cout << "********************\n";
        st.getStudent();
    }
    cout << "\n\n Press any Enter to continue.";

    return;
}

void deleteStudent(){
    int rollNo, standard;
    cout << "Enter the RollNo :";
    cin >> rollNo;
    cout << "Enter the standard :";
    cin >> standard;
    getchar();

    fstream file, temp;
    file.open("student_record.dat", ios::binary|ios::in);
    temp.open("temp.dat", ios::out|ios::binary);

    if(!file.is_open() || !temp.is_open()){
        cout << "Unable to open file, press any key to continue.";
        getchar();
        return;
    }

    student st;
    int count = 0;
    while(file.read((char *)&st, sizeof(student))){
        if(st.exsistStudent(rollNo, standard)){
            count++;
            cout << "***** Student Info *****\n";
            st.getStudent();
            cout << "\nPress Y to delete :";
            char c = getchar();
            getchar();
            if(c == 'Y' || c == 'y'){
                continue;
            }
        }
        temp.write((char*) &st, sizeof(student));
    }
    file.close();
    temp.close();

    remove("student_record.dat");
    rename("temp.dat", "student_record.dat");

    system("clear");
    if(!count){
        cout << "No record found, add some records.\n";
    } else {
        cout << "Record deleted successfully\n";
    }
    cout << "\n\n Press any Enter to continue.";

    return;
}


