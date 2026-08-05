#include<iostream>
using namespace std;

/*---------------------------class Student--------------------------------------*/

class Student{
    public:     
        int roll_num;
        float math_score;
        float science_score;
        string  art_grade; 
    
    public:
        Student();
        Student(int roll_num);
        void print_scores();
};

Student::Student() : roll_num(0),
                     math_score(0.0f),
                     science_score(0.0f),
                     art_grade(""){
    cout<<"\n Constructor for Student()"<<endl;
}

Student::Student(int roll_num):roll_num(roll_num){ 
    cout<<"\n Constructor for Student(roll_num)"<<endl;
}

void Student::print_scores(){
    cout<<endl;
    cout<<" ------------- roll_num  :"<<roll_num<<" -------------------" <<endl;
    cout<<"math_score:"<<math_score<<endl;
    cout<<"science_score:"<<science_score<<endl;
    cout<<"art_grade:"<<art_grade<<endl;
    cout<<"----------------------------- "<<endl;
}




/*---------------------------class StudentWrapper--------------------------------------*/

/*
Note this StudentWrapper is just for a demo of RAII principles of abstracting the new and delete away from the user
Good: The constructor acquires the resource, and the destructor releases it.

Bad: - Why is a pointer public, that too a raw pointer
     - The class is incomplete because it owns a raw pointer but does not define copy or move operations. This violates the Rule of Three/Five.

Howevever : I am going to deliberattely avoid implementing the rule of 3/5 here , because
- I just wanted to show that it is possible to abstract away new and delete from the user: which has been shown already
- I want to show if you dont do this abstraction properly a tonne of problems occur: which has also been demoed

My job is done here, so i am not making the code any more bulky

*/
class StudentWrapper{
    public:
    Student* ptr;
    
    StudentWrapper();
    StudentWrapper(int roll_num);
    ~StudentWrapper();
};

StudentWrapper::StudentWrapper(){  
    cout<<"\n\n --------------"<<endl;
    cout<<"Constructor for StudentWrapper(): will call new Student()" <<endl;
    ptr = new Student();
    cout<<"Constructor for StudentWrapper(): allocated dynamic memory at ptr ="<<ptr<<endl;
    
}

StudentWrapper::StudentWrapper(int roll_num){
    cout<<"\n\n --------------"<<endl;
    cout<<"Constructor for StudentWrapper(roll_num): will call new Student(roll_num)"<<endl;
    ptr = new Student(roll_num);
    cout<<"Constructor for StudentWrapper(roll_num): allocated dynamic memory at ptr ="<<ptr<<endl; 
}

StudentWrapper::~StudentWrapper(){
    cout<<"Destructor StudentWrapper: dynamic memory pointed to by StudentWrapper.ptr is going out of scope. ptr = "<<ptr<<endl;
    delete ptr;
    ptr = nullptr;
    cout<<"-------------- \n\n"<<endl;
}



/*---------------------------demo functions --------------------------------------*/
/*demo1_ptr_to_student_raw_pointers()
- there is only one class Student.
- new and delete are not abstracted away from the user, hence user has to deal with raw pointers
- But this code is a correct implementation of raw pointers
*/
void demo1_ptr_to_student_raw_pointers(){
    cout<<"\n\n"<<endl;
    cout<<"============== demo1_ptr_to_student_raw_pointers() =============="<<endl;
    Student* ptr = new Student();
    cout<<"dynamic memory allocated at ptr: "<<ptr<<endl;
    if(ptr){
        ptr->math_score = 100 ;
        ptr->science_score = 98;
        ptr->art_grade = "A+";
        ptr->print_scores();
        cout<<"dynamic memory will be deleted at ptr: "<<ptr<<endl;
        delete ptr; 
        ptr = nullptr;
    }

    ptr = new Student(51);
    cout<<"dynamic memory allocated at ptr: "<<ptr<<endl;
    if(ptr){
        ptr->math_score = 84 ;
        ptr->science_score = 92;
        ptr->art_grade = "A-";
        ptr->print_scores();
        cout<<"dynamic memory will be deleted at ptr: "<<ptr<<endl;
        delete ptr; 
        ptr = nullptr;
    }
}

/* 
demo2a_ptr_to_student_manual_raii(): 
- this is an implementation of raii, where you abstract away the new and delete from the user
- i) There is a Student class, 
  ii) There is a StudentWrapper() which deals with the new and delete for Student, 
     - The user does not deal with Student, new or delete, but completely uses StudentWrapper 
     - The user only deals with StudentWrapper
     - StudentWrapper: constructor acquires the dynamic memory + initializes the pointer to the dynamic memory
     - StudentWrapper: destructor releases the dynamic memory and sets the pointer to null
- in this the pointer is reassigned before releasing memory from the previous

There is no bug in this, but this implementation is not bug proof, see demo3
*/
void demo2a_ptr_to_student_manual_raii(){
    cout<<"\n\n"<<endl;
    cout<<"============== demo2a_ptr_to_student_manual_raii() ============================"<<endl;
    // This is INITIALIZATION i.e stuwrap1 does not exist already, 
    // in modern c++ 17 and later, it does not create a temporary object StudentWrapper() 
    // that is later copied into stuwrap1.
    // Instead, because of guaranteed copy elision, the compiler constructs stuwrap1 directly.
    // Same as StudentWrapper stuwrap1; 
    StudentWrapper stuwrap1 = StudentWrapper();
    if(stuwrap1.ptr){
        stuwrap1.ptr->math_score = 100 ;
        stuwrap1.ptr->science_score = 98;
        stuwrap1.ptr->art_grade = "A+";
        stuwrap1.ptr->print_scores();
    }

    // This is INITIALIZATION i.e stuwrap2 does not exist already, 
    // in modern c++ 17 and later, it does not create a temporary object StudentWrapper() 
    // that is later copied into stuwrap2.
    // Instead, because of guaranteed copy elision, the compiler constructs stuwrap1 directly.
    // Same as StudentWrapper stuwrap1(51); 
    StudentWrapper stuwrap2 = StudentWrapper(51);
    if(stuwrap2.ptr){
        stuwrap2.ptr->math_score = 84 ;
        stuwrap2.ptr->science_score = 92;
        stuwrap2.ptr->art_grade = "A-";
        stuwrap2.ptr->print_scores();
    }
}

/* 
demo2b_ptr_to_student_manual_raii_improved(): 
this is same as demo2a_ptr_to_student_manual_raii(): except I've fixed how the class objects are created
StudentWrapper stuwrap1 = StudentWrapper();   ---> StudentWrapper stuwrap1;
StudentWrapper stuwrap2 = StudentWrapper(42); ---> StudentWrapper stuwrap1(42)
*/
void demo2b_ptr_to_student_manual_raii_improved(){
    cout<<"\n\n"<<endl;
    cout<<"============== demo2b_ptr_to_student_manual_raii_improved() ============================"<<endl;
    StudentWrapper stuwrap1;
    if(stuwrap1.ptr){
        stuwrap1.ptr->math_score = 100 ;
        stuwrap1.ptr->science_score = 98;
        stuwrap1.ptr->art_grade = "A+";
        stuwrap1.ptr->print_scores();
    }

    StudentWrapper stuwrap2(51);
    if(stuwrap2.ptr){
        stuwrap2.ptr->math_score = 84 ;
        stuwrap2.ptr->science_score = 92;
        stuwrap2.ptr->art_grade = "A-";
        stuwrap2.ptr->print_scores();
    }
}

/* 
demo3_ptr_to_student_manual_raii_memory_leak(): 
- this code is similar to demo2 but with a change.
- this shows that you could try to implement raii based wrappers around raw pointers,
     but if you havent taken care of the rule of 5, the code can become buggy
- in this the pointer is reassigned before releasing memory from the previous assignment leading to a memory leak
- demo3 is not just a memory leak. There are other issues such as shallow copy, dangling pointer , double deletion
- see c3_memory_management/docs/README_3b_classes_pointers_problems.md for a discussion of this
*/


void demo3a_ptr_to_student_manual_raii_memory_leak(){
    cout<<"\n\n"<<endl;
    cout<<"============== demo3a_ptr_to_student_manual_raii_memory_leak() ======="<<endl;
    cout<<"Demo3a creates a memory leak. Notice that 2 memory locations are acquired, but only 1 of them is released"<<endl;
    
    // This is INITIALIZATION i.e stuwrap1 does not exist already, 
    // in modern c++ 17 and later, it does not create a temporary object StudentWrapper() 
    // that is later copied into stuwrap1.
    // Instead, because of guaranteed copy elision, the compiler constructs stuwrap1 directly.
    // Same as StudentWrapper stuwrap1; 
    StudentWrapper stuwrap1 = StudentWrapper();
    if(stuwrap1.ptr){
        stuwrap1.ptr->math_score = 100 ;
        stuwrap1.ptr->science_score = 98;
        stuwrap1.ptr->art_grade = "A+";
        stuwrap1.ptr->print_scores();
    }
    
    // DANGEROUS 1: This is the step that will cause memory leak
    // stuwrap1 from the previous StudentWrapper() is never released

    // DANGEROUS 2: dangling pointer, DOUBLE DELETION
    // This is NOT INITIALIZATION. THIS IS ASSIGNMENT
    // i) StudentWrapper(51) is a temporatry with a ptr inside it
    // ii) the equal to sign = is a copy-assignment operator. since there is no custom definition of the operator, 
    //    the compiler interprets it as a shallow copy. there is a shallwo copy from StudentWrapper(51) to stuwrap1
    // iii) the destructor on temporary StudentWrapper(51) is called and it deletes the ptr inside it
    // iv)  DANGLING POINTER: But stuwrap1 is a shallow copy , so it points to the same ptr, the memory has been released though. so ptr is dangling
    //  v)  DOUBLE DELETIONG: the when stuwrap1 goes out of scope , stuwrap1 destructor is called, whiCH tries to delete ptr again, resulting in double deletion

    stuwrap1 = StudentWrapper(51);
    if(stuwrap1.ptr){ 
        stuwrap1.ptr->math_score = 84 ;
        stuwrap1.ptr->science_score = 92;
        stuwrap1.ptr->art_grade = "A-";
        stuwrap1.ptr->print_scores();
    }
}


/*
demo3b_ptr_to_student_manual_raii_memory_leak_fixed()
- this code is similar to demo2, demo3. But demo3 bug has been fixed (although very poorly. Its not a fix, its a temporary bandage)
Here is why it is a poor fix
- but the fact that this needs a fix means that the raw pointers are not completely abstracted away from the user
- Why are we able to access stuwrap1.ptr ? this should not be public in the first place, StudentWrapper needs to take care of everything
*/
void demo3b_ptr_to_student_manual_raii_memory_leak_fixed(){
    cout<<"\n\n"<<endl;
    cout<<"============== demo3b_ptr_to_student_manual_raii_memory_leak_fixed ======="<<endl;
    StudentWrapper stuwrap1 = StudentWrapper();
    if(stuwrap1.ptr){
        stuwrap1.ptr->math_score = 100 ;
        stuwrap1.ptr->science_score = 98;
        stuwrap1.ptr->art_grade = "A+";
        stuwrap1.ptr->print_scores();
    }
    
    // FIX: stuwrap1.ptr before reassigning. 
    // But if this check is skipped memory leak is very real
    // So hence this design approach is not very robust
    if(!stuwrap1.ptr) { // check if it is nullptr, it should be null before reassignment
        stuwrap1 = StudentWrapper(51);
        if(stuwrap1.ptr) {  // check if it is NOT nullptr, it should NOT BE null after reassignment
            stuwrap1.ptr->math_score = 84 ;
            stuwrap1.ptr->science_score = 92;
            stuwrap1.ptr->art_grade = "A-";
            stuwrap1.ptr->print_scores();
        }
    }
    else {
        cout<<"stuwrap1.ptr memory HAS NOT been released ! Cannot reassign student2 " <<endl;
    }
    
}




int main(){
    demo1_ptr_to_student_raw_pointers();
    demo2a_ptr_to_student_manual_raii();
    demo2b_ptr_to_student_manual_raii_improved();
    demo3a_ptr_to_student_manual_raii_memory_leak();
    demo3b_ptr_to_student_manual_raii_memory_leak_fixed();
}


