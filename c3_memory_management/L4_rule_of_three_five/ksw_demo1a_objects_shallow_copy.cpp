/* 
This code demonstrates shallow copy 
See relevant README for details c3_memory_management/docs/README_3b_classes_pointers_problems.md
*/

# include<iostream>
using namespace std;

class Teacher {
    private:
        string name;
        int grade;  //grade the teacher will handle

    public:
        Teacher();
        Teacher(string name, int grade);
        void print_details();
};

Teacher::Teacher() : name(""), grade(0){}
Teacher::Teacher(string name, int grade) : name(name), grade(grade){}
void Teacher::print_details(){
    cout<<"\n Teacher Details:"<<endl;
    cout<<"Name          : "<< name <<endl;
    cout<<"Teaching Grade: "<< grade<<endl;
}

class Student {
    private:
        int roll_num;
        float math_score;
        float science_score;
        string art_grade;

        int *ptr1;
        int *ptr2;
        Teacher *main_tptr1;
        Teacher *assistant_tptr2;

    public:
        Student();
        Student( int roll_num,
                 float math_score,
                 float science_score,
                 string art_grade,

                 Teacher* main_teacher_ptr,
                 string assistant_teacher_name, 
                 int assistant_teacher_grade) ;
        ~Student();
        void print_details();
        
};

Student::Student(){
    roll_num = 0;
    math_score = 0.1;
    science_score = 0.2;
    art_grade = "A";

    ptr1 = &roll_num;
    ptr2 = new int(roll_num+1000);
    
    main_tptr1 = nullptr;
    // this should also be nullptr , but want to set it to new to see how copying goes
    assistant_tptr2 = new Teacher(); 
}

Student::Student(int roll_num,
                 float math_score,
                 float science_score,
                 string art_grade,

                 Teacher* main_teacher_ptr,
                 string assistant_teacher_name, 
                 int assistant_teacher_grade) {
    this->roll_num = roll_num;
    this->math_score = math_score;
    this->science_score = science_score;
    this->art_grade = art_grade;

    this->ptr1 = &this->roll_num;
    this->ptr2 = new int(roll_num+1000);
    
    this->main_tptr1 = main_teacher_ptr;
    this->assistant_tptr2 = new Teacher(assistant_teacher_name,assistant_teacher_grade);
}


Student::~Student(){

    delete ptr2;
    delete assistant_tptr2;
    ptr2 = nullptr;
    assistant_tptr2 = nullptr;
}


void Student::print_details(){
    cout<<"\n Student Details:"<<endl;
    cout<<"roll_num      : "<< roll_num <<endl;
    cout<<"math_score    : "<< math_score <<endl;
    cout<<"science_score : "<< science_score <<endl;
    cout<<"art_grade     : "<< art_grade <<endl;

    cout<<"\n Pointer1 details: "<<endl;
    cout<<" ptr1 ="<< ptr1<<endl;
    cout<<"*ptr1 ="<<*ptr1<<endl;

    cout<<"\n Pointer2 details(int pointer to a heap location): "<<endl;
    if (ptr2) {
        cout<<" ptr2 ="<< ptr2<<endl;
        cout<<"*ptr2 ="<<*ptr2<<endl;
    } else {
        cout<<"ptr2 is Null"<<endl;
    }  

    cout<<"\n Main Teacher Details:"<<endl;
    if(main_tptr1) {
        cout<<"Main teacher pointer address it points to :"<<main_tptr1<<endl;
        main_tptr1->print_details();
    } else {
        cout<<"Main Teacher Pointer is Null"<<endl;
    }

    cout<<"\n Assistant Teacher Details:"<<endl;
    if (assistant_tptr2) {
        cout<<"Assistant teacher pointer address it points to  :"<<assistant_tptr2<<endl;
        assistant_tptr2->print_details();
    } else {
        cout<<"Assistant Teacher Pointer is Null"<<endl;
    }


  
}

int main(){
    //Question: main_teacher has been declared in main and hence cannot be accessed in the constructor
    //But passing the address to the constructor , &main_teacher 
    // i) how are we able to access main_teacher in the constructor just because we pass the adddress
    // ii) we can even print main_teacher details from student.print_details method ?
    // How is this possible if main_teacher scope is limited to main() ?

    /* Answer : AHA MOMENT !
    Scope determines where a variable’s name can be used.
    Lifetime determines whether the object still exists.
    - It is definitely possible to access a variable outside its scope as long as it is alive
    - A pointer allows code outside the name’s scope to access the object, provided the object is still alive.
    */
    Teacher main_teacher("Ms. Renee",2);
    Student s1;
    Student s2(15, //roll_num
               76.0, //math_score
               100.0, //science_score
               "A+", //art grade
              &main_teacher, // main teacher object
              "Ms. Chloe" , // assistant teacher name
              1)  ;         // assistant teacher grade

    cout<<"\n\n------------- Main Teacher-----------------"<<endl;
    cout<<"&main_teacher :"<<&main_teacher <<endl;
    main_teacher.print_details();
    
    cout<<"\n\n ---------------Student S1-------------------"<<endl;
    s1.print_details();

    cout<<"\n\n ---------------- Student S2------------------"<<endl;
    s2.print_details();

    cout<<"----------- Eveyrything until above this line is fine, since there is no copying involved--------"<<endl;

    cout<<"\n\n --------- Below there are attempts to copy objects without implementing the rule of 5. it will lead to undefined behaviour------"<<endl;
    s1 = s2;
    cout<<"\n\n ---------------Student S1:after copying -------------------"<<endl;
    s1.print_details();

    cout<<"\n\n ---------------- Student S2: after copying (should be no change)------------------"<<endl;
    s2.print_details();

    cout<<"\n\n ---------------- S2 and S1 will be deleted due to end of scope.----------------" <<endl;
    cout<<"S2 will be deleted first. S1 will be deleted next. "<<endl;
    cout<<"But their pointers point to the same underlying memory leading to a double deletion \n\n"<<endl;
    
    // s2 will be deleted when it goes out of scope first
    // then s1 will be deleted when it goes out of scope. but s1 and s2 point to the same underlying memory causing a double deletion
}