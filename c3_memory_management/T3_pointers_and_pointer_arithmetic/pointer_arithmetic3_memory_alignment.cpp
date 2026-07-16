/* Goal is 
Increment pointers. Notice that all the pointers do not increase by the same value. 
They increase by the number of bytes that the data type that they point to consumes .
HENCE PROVING POINTERS ARE TYPED
*/


# include<iostream>
using namespace std;

struct Student{
    // Student should nominally only occupy 2+8+4 = 14 bytes
    // But on this compiler it is shown to occupy  24 bytes
    // On this compiler the memory page seems to be 8 bytes long, 
    // so the compiler pads bytes accordingly to take care of memory alignment
    short id;          //2 bytes on this compiler
                       // Compiler adds 6 bytes for memory alignment after short id;
    double gpa;        //8 bytes on this compiler
    int    math_score; //4 bytes on this compiler
                       // Compiler adds 4 bytes for memory alignment after short id;
                       // Total = 2+(4)+ 8 + 4+(4) = 24 bytes !!!
                   
};

struct Teacher{
    // Teacher should nominally only occupy 2+8+4+4 = 18 bytes
    // But on this compiler it is shown to occupy  24 bytes
    // On this compiler the memory page seems to be 8 bytes long, 
    // so the compiler pads bytes accordingly to take care of memory alignment
    short id;          //2 bytes on this compiler
                       // Compiler adds 6 bytes for memory alignment after short id;
    double gpa;        //8 bytes on this compiler
    int    math_score; //4 bytes on this compiler
    float  phd_score;  //4 bytes on this compiler
                       // NOTE that compiler need not pad here since INT is 4 bytes, float is 4 bytes as well 
                       // Total = 2+(4)+ 8 + 4+4 = 24 bytes !!!
                   
};

int main(){
  short a_short[5]   ;
  int   a_int[5]     ;
  float a_float[5]   ;
  double a_double[5] ;
  

  // The name of the array decays to a pointer to the first element in c++
  short* p_short   = a_short;
  int*   p_int     = a_int;
  float* p_float   = a_float;
  double* p_double = a_double;
  

  cout<<"\n\n";
  cout<<"Now the pointers point to arrays. So incrementing them within bounds is fine"<< endl;
  cout<<"GOAL OF THIS EXERCISE: Increment pointers. Notice that all the pointers do not increase by the same value. "<<endl;
  cout<<"They increase by the number of bytes that the data type that they point to consumes ."<<endl;
  cout<<"HENCE PROVING POINTERS ARE TYPED ."<<endl;

  cout<<"p_short  : "<<p_short  <<", ++p_short  : "<< ++p_short  <<  " .On this compiler short is 2 bytes"<<endl;
  cout<<"p_int    : "<<p_int    <<", ++p_int    : "<< ++p_int    <<  " .On this compiler int is 4 bytes"<<endl;
  cout<<"p_float  : "<<p_float  <<", ++p_float  : "<< ++p_float  <<  " .On this compiler float 4 bytes"<<endl;
  cout<<"p_double : "<<p_double <<", ++p_double : "<< ++p_double <<  " .On this compiler double is 8 bytes"<<endl;

  Student students[5];
  Student* p_student = students;
  cout<<"\n\n";
  cout<<"MEMORY ALIGNMENT DEMONSTRATION: Using Struct"<<endl;
  cout<<"Student should nominally only occupy 2+8+4 = 14 bytes"<<endl;
  cout<<"But on this compiler it is shown to occupy  24 bytes"<<endl;
  cout<<"On this compiler the memory page seems to be 8 bytes long"<<endl; 
  cout<<"So the compiler pads bytes accordingly to take care of memory alignment"<<endl;
  cout<<"See the code comments for padding and memory alignment details"<<endl;
  cout<<endl;
  cout<<"p_student              : "<<p_student <<endl;
  cout<<"&p_student->id         : "<<&p_student->id  <<endl;
  cout<<"&p_student->gpa        : "<<&p_student->gpa <<endl;
  cout<<"&p_student->math_score : "<<&p_student->math_score<<endl;
  cout<<endl;
  cout<<"++p_student            : "<< ++p_student  <<  " .Notice that it has jumped 18hex = 24 decimal bytes(instead of 14 decimal bytes)"<<endl;
  
  Teacher teachers[5];
  Teacher* p_teacher = teachers;
  cout<<"\n\n";
  cout<<"MEMORY ALIGNMENT DEMONSTRATION: Using Struct"<<endl;
  cout<<"Teacher should nominally only occupy 2+8+4+4 = 18 bytes"<<endl;
  cout<<"But on this compiler it is shown to occupy  24 bytes"<<endl;
  cout<<"On this compiler the memory page seems to be 8 bytes long"<<endl; 
  cout<<"So the compiler pads bytes accordingly to take care of memory alignment"<<endl;
  cout<<"See the code comments for padding and memory alignment details"<<endl;
  cout<<endl;
  cout<<"p_teacher              : "<<p_teacher <<endl;
  cout<<"&p_teacher->id         : "<<&p_teacher->id  <<endl;
  cout<<"&p_teacher->gpa        : "<<&p_teacher->gpa <<endl;
  cout<<"&p_teacher->math_score : "<<&p_teacher->math_score<<endl;
  cout<<"&p_teacher->phd_score : "<<&p_teacher->math_score<<endl;
  cout<<endl;
  cout<<"++p_teacher            : "<< ++p_teacher  <<  " .Notice that it has jumped 18hex = 24 decimal bytes(instead of 18 decimal bytes)"<<endl;
  
}




