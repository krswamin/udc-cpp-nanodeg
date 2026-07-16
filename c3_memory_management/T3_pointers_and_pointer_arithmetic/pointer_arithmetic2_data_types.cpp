/* Goal is 
Increment pointers. Notice that all the pointers do not increase by the same value. 
They increase by the number of bytes that the data type that they point to consumes .
HENCE PROVING POINTERS ARE TYPED
*/


# include<iostream>
using namespace std;

int main(){
  short n_short = 5;
  int n_int = 10;;
  float n_float = 10.1;
  double n_double = 10.23;
  
  short* p_short   = &n_short;
  int*   p_int     = &n_int;
  float* p_float   = &n_float;
  double* p_double = &n_double;
  
  cout<<"Note : incrementing pointers , pointing to single data types is WRONG AND DANGEROUS !!!! "<<endl;
  cout<<"It is accessing the pointer outside its memory bounds. You can only access incremented pointers within arrays !"<<endl;
  cout<<"DEREFERENCING THESE INCREMENTED POINTERS WILL LEAD TO UNDEFINED BEHAVIOUR  !!! "<<endl;
  cout<<"p_short  : "<<p_short  <<", ++p_short  : "<< ++p_short  <<  " .On this compiler short is 2 bytes"<<endl;
  cout<<"p_int    : "<<p_int    <<", ++p_int    : "<< ++p_int    <<  " .On this compiler int is 4 bytes"<<endl;
  cout<<"p_float  : "<<p_float  <<", ++p_float  : "<< ++p_float  <<  " .On this compiler float 4 bytes"<<endl;
  cout<<"p_double : "<<p_double <<", ++p_double : "<< ++p_double <<  " .On this compiler double is 8 bytes"<<endl;

  short a_short[5]   ;
  int   a_int[5]     ;
  float a_float[5]   ;
  double a_double[5] ;
  

  // The name of the array decays to a pointer to the first element in c++
  p_short  = a_short;
  p_int    = a_int;
  p_float  = a_float;
  p_double = a_double;
  cout<<"\n\n";
  cout<<"Now the pointers point to arrays. So incrementing them within bounds is fine"<< endl;
  cout<<"GOAL OF THIS EXERCISE: Increment pointers. Notice that all the pointers do not increase by the same value. "<<endl;
  cout<<"They increase by the number of bytes that the data type that they point to consumes ."<<endl;
  cout<<"HENCE PROVING POINTERS ARE TYPED ."<<endl;

  cout<<"p_short  : "<<p_short  <<", ++p_short  : "<< ++p_short  <<  " .On this compiler short is 2 bytes"<<endl;
  cout<<"p_int    : "<<p_int    <<", ++p_int    : "<< ++p_int    <<  " .On this compiler int is 4 bytes"<<endl;
  cout<<"p_float  : "<<p_float  <<", ++p_float  : "<< ++p_float  <<  " .On this compiler float 4 bytes"<<endl;
  cout<<"p_double : "<<p_double <<", ++p_double : "<< ++p_double <<  " .On this compiler double is 8 bytes"<<endl;

}