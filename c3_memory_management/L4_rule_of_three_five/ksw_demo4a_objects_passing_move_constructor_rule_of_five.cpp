/* 

This code demonstrates the RULE OF FIVE
It builds on top of : L4_rule_of_three_five/ksw_demo2b_objects_passing_rule_of_three.cpp
See relevant README for details c3_memory_management/docs/README_3b_classes_pointers_problems.md

The Rule of FIVE/ What value does Rule of 5 bring
- Rule of 3 is sufficient to make correct deep copies. 
  Rule of 3 is sufficient for the correct passing of objects by value & returning of objects by value
- But Copying is expensive. Wherever appropriate moving might be more efficient/ less expensive than copying
  Rule of 5 implements the move constructor , & move-assignment operator for better move semantics. 
  This is the value add of rule of 5

When passing the object
- pay attention to when move constructor is called (instead of copy constructor)
        Student s3 = pass_and_return_student(s2);
- when the move assignment operator is called  (instead of move assignment operator)
      Student s4;
      s4 = pass_and_return_student(s2);


*/

#include <iostream>
#include <string>
using namespace std;

class Teacher {
    private:
        string name;
        int grade;  //grade the teacher will handle

    public:
        Teacher();
        Teacher(string name, int grade);
        string get_name();
        int get_grade();
        void print_details();
};

Teacher::Teacher() : name(""), grade(0){}

Teacher::Teacher(string name, int grade) : name(name), grade(grade){}

string Teacher::get_name(){
    return name;
}

int Teacher::get_grade(){
    return grade;
}

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
        // Custom Default Constructor
        Student();
        // Custom Parameterized Constructor
        Student( int roll_num,
                 float math_score,
                 float science_score,
                 string art_grade,

                 Teacher* main_teacher_ptr,
                 string assistant_teacher_name, 
                 int assistant_teacher_grade) ;

        // Custom Copy Constructor
        Student(const Student& other);
        // Custom Copy Assignment Operator
        Student& operator=(const Student& other);

        // Custom Move Constructor
        Student(Student&& other) noexcept;
        // Custom Move Assignment Operator
        Student& operator=(Student&& other) noexcept;


        // Custom Destructor
        ~Student();

        void print_details(); 
};

// Constructor: Custom Default Constructor
Student::Student(){
    cout<<"\n ----- Student: Custom Default Constructor : this = "<< this<<"-----------"<<endl;
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

// Constructor: Custom Parameterized constructor
Student::Student(int roll_num,
                 float math_score,
                 float science_score,
                 string art_grade,

                 Teacher* main_teacher_ptr,
                 string assistant_teacher_name, 
                 int assistant_teacher_grade) {
    
    cout<<"\n ----- Student: Custom Parameterized Constructor : this = "<< this<<"-----------"<<endl;
    this->roll_num = roll_num;
    this->math_score = math_score;
    this->science_score = science_score;
    this->art_grade = art_grade;

    this->ptr1 = &this->roll_num;
    this->ptr2 = new int(roll_num+1000);
    
    this->main_tptr1 = main_teacher_ptr;
    this->assistant_tptr2 = new Teacher(assistant_teacher_name,assistant_teacher_grade);
}


// Custom Copy Constructor
Student::Student(const Student& other){
    cout<<"\n ----- Student: Custom Copy Constructor : this = "<< this<<"-----------"<<endl;
    this->roll_num = other.roll_num;
    this->math_score = other.math_score;
    this->science_score = other.science_score;
    this->art_grade = other.art_grade;

    this->ptr1 = &this->roll_num;

    this->ptr2 = nullptr ;
    if (other.ptr2) {
      this->ptr2 = new int(*other.ptr2);
    } 
    
    this->main_tptr1 = nullptr ;
    if (other.main_tptr1) {
      this->main_tptr1 = other.main_tptr1;
    } 
    
     this->assistant_tptr2 = nullptr ;
    if (other.assistant_tptr2) {
      this->assistant_tptr2 = new Teacher(other.assistant_tptr2->get_name(),
                                          other.assistant_tptr2->get_grade());
    } 
}

// Custom Copy assignment operator
/* Notice that the return type is a reference to student. 
Q: What does that mean ?
A: Take another Student as input, assign its contents to the current Student, and return a reference to the current Student object.
*/
Student& Student::operator=(const Student& other){
    cout<<"\n ----- Student: Custom Copy Assignment Operator  : this = "<< this<<"-----------"<<endl;
    // Protect against: s1 = s1;
    if (this == &other) {
        return *this;
    }

  
    // -------- Begin Copying -----------------
    // Copy the normal data
    this->roll_num = other.roll_num;
    this->math_score = other.math_score;
    this->science_score = other.science_score;
    this->art_grade = other.art_grade;
    
    // pointer 1: points to stack int memory
    this->ptr1 = &this->roll_num;
    
    // Pointer 2: points to dynamic int memory
    // Release the memory pointed to by this->ptr2, we dont want a memory leak
    // since they will get the other pointers deep copies anyway. 
    delete this->ptr2;
    this->ptr2 =nullptr; //prevents dangling pointer
    if (other.ptr2) {
      this->ptr2 = new int(*other.ptr2);
    }
    
    // Main teacher Pointer : points to stack memory of type Teacher, from external scope
    this->main_tptr1 = nullptr;
    if (other.main_tptr1) {
      this->main_tptr1 = other.main_tptr1;
    } 
    
    // Assistant teacher Pointer : points to heap memory of type Teacher, 
    // Release the memory pointed to by this->assistant_tptr2, we dont want a memory leak
    // since they will get the other pointers deep copies anyway. 
    delete this->assistant_tptr2 ;
    this->assistant_tptr2 = nullptr ;
    if (other.assistant_tptr2) {
      this->assistant_tptr2 = new Teacher(other.assistant_tptr2->get_name(),
                                          other.assistant_tptr2->get_grade());
    }

    // Required because the return type is Student&.
    return *this;

}


// Custom Move Constructor
Student::Student(Student&& other) noexcept{
    cout<<"\n ----- Student: Custom Move Constructor : this = "<< this<<"-----------"<<endl;
    this->roll_num = other.roll_num;
    this->math_score = other.math_score;
    this->science_score = other.science_score;
    this->art_grade = other.art_grade;

    this->ptr1 = &this->roll_num;

    this->ptr2 = other.ptr2; 
    other.ptr2 = nullptr;

    this->main_tptr1 = other.main_tptr1;
    
    
    this->assistant_tptr2 = other.assistant_tptr2;
    other.assistant_tptr2 = nullptr; 

}

// Custom Move Assignment Operator
/* Notice that the return type is a reference to student. 
Q: What does that mean ?
A: Take another Student as input, assign its contents to the current Student, and return a reference to the current Student object.
*/
Student& Student::operator=(Student&& other) noexcept{
    cout<<"\n ----- Student: Custom Move Assignment Operator  : this = "<< this<<"-----------"<<endl;
    // Protect against: s1 = s1;
    if (this == &other) {
        return *this;
    }

  
    // -------- Begin Copying -----------------
    // Copy the normal data
    this->roll_num = other.roll_num;
    this->math_score = other.math_score;
    this->science_score = other.science_score;
    this->art_grade = other.art_grade;
    
    // pointer 1: points to stack int memory
    this->ptr1 = &this->roll_num;
    
    // Pointer 2: points to dynamic int memory
    // Release the memory pointed to by this->ptr2, we dont want a memory leak
    // since they will get the other pointers deep copies anyway. 
    delete this->ptr2;
    this->ptr2 = other.ptr2; //prevents dangling pointer
    other.ptr2 = nullptr;
    
    // Main teacher Pointer : points to stack memory of type Teacher, from external scope
    this->main_tptr1 = other.main_tptr1;
    other.main_tptr1 = nullptr;

    // Assistant teacher Pointer : points to heap memory of type Teacher, 
    // Release the memory pointed to by this->assistant_tptr2, we dont want a memory leak
    // since they will get the other pointers deep copies anyway. 
    delete this->assistant_tptr2 ;
    this->assistant_tptr2 = other.assistant_tptr2;
    other.assistant_tptr2 = nullptr ;
 
    // Required because the return type is Student&.
    return *this;

}

//  Custom Destructor
Student::~Student(){
    cout<<"\n ----- Student: Custom Destructor : this = "<< this<<"-----------"<<endl;
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

    cout<<"\n Pointer1 details(int pointer, points to this->roll num): "<<endl;
    cout<<" &this->roll_num ="<<&this->roll_num<<endl;
    cout<<" ptr1 ="<< ptr1<<endl;
    cout<<"*ptr1 ="<<*ptr1<<endl;

    cout<<"\n Pointer2 details(int pointer to a heap location): "<<endl;
    if (ptr2) {
        cout<<" ptr2 ="<< ptr2<<endl;
        cout<<"*ptr2 ="<<*ptr2<<endl;
    } else {
        cout<<"ptr2 is Null"<<endl;
    }  

    cout<<"\n Main Teacher Pointer Details: Pointer to external Teacher"<<endl;
    if(main_tptr1) {
        cout<<"Main teacher pointer address it points to :"<<main_tptr1<<endl;
        main_tptr1->print_details();
    } else {
        cout<<"Main Teacher Pointer is Null"<<endl;
    }

    cout<<"\n Assistant Teacher Details:Pointer to a Teacher on the Heap"<<endl;
    if (assistant_tptr2) {
        cout<<"Assistant teacher pointer address it points to  :"<<assistant_tptr2<<endl;
        assistant_tptr2->print_details();
    } else {
        cout<<"Assistant Teacher Pointer is Null"<<endl;
    }
  
}

Student pass_and_return_student(Student stu){
    cout<<"\n\n ------------pass_and_return_student: student argument passed by value: stu address = " << &stu << "-----------"<<endl;
    stu.print_details();
    return stu;
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
    cout<<"\n\n------------- Main Teacher-----------------"<<endl;
    cout<<"&main_teacher :"<<&main_teacher <<endl;
    main_teacher.print_details();

    cout<<" \n======== Going to create s2======================="<<endl;
    Student s2(15, //roll_num
               76.0, //math_score
               100.0, //science_score
               "A+", //art grade
              &main_teacher, // main teacher object
              "Ms. Chloe" , // assistant teacher name
              1)  ;         // assistant teacher grade
    cout <<"\n &s2 = "<<&s2<<endl;  

    cout<<"\n----------------S2 details------------------"<<endl;
    s2.print_details();
    cout<<" \n======== s2 complete ======================="<<endl;

    cout<<" \n\n======== Going to create s3======================="<<endl;
    // Move Constructor: This is initialization. So the move constructor should be called 
    Student s3 = pass_and_return_student(s2);
    cout <<"\n &s3 = "<<&s3<<endl;

    cout<<"\n\n --------------S3 details------------------"<<endl;
    s3.print_details();
    cout<<" \n======== s3 complete ======================="<<endl;



}