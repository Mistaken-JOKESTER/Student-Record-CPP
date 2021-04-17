#ifndef STUDENT
#define STUDENT

class student{
    private:
        int standard;
        int rollNo;
        char name[40];
        int p_marks, c_marks, m_marks, e_marks;
        float percentage;
        char grade;
    public:
        void addStudent(bool);
        void addToDatabase();
        void getStudent();
        bool exsistStudent(int, int);

};

void showStudents();
void update();
void search();
void deleteStudent();

#endif // STUDENT
