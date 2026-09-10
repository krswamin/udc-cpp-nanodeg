/*
This corrected code DOES NOT CAUSE A MEMORY 

The exception flow is below: i.e from the inner most function doWork() all the way to main(),
the exception keeeps getting rethrown until the user can handle it in main

doWork()
throws
      ↓
processDataRaw()
   deletes res
   rethrows
      ↓
main()
   handles and prints the error

BUT THIS EXCEPTION SAFETY IS FRAGILE. Any other function could throw an exception
void processDataRaw(){
    MyResource* res = new MyResource(6,5); // Acquire

    try {
        res->doWork(); //This might throw an exception. Memory Leak has been handled though !
        someOtherFunctionThrowsException(); // this can throw an exception that could  lead to a memory leak
        } 

---------------- TESTING THE MEMORY LEAK

Step 1) Run WITHOUT Address Sanitizer

Run the following in a terminal(from the folder where the cpp file is). There are 2 commands. Run one after the other
g++ ksw_demo6c_exception_safety_solution_with_new_delete.cpp -o ksw_demo6c_exception_safety_solution_with_new_delete.out
./ksw_demo6c_exception_safety_solution_with_new_delete.out

Notice that there is no seg fault, or no indication of a leak. This is not an indicator of the absence of a leak (There is no leak though)

Step 2) Run WITH Address Sanitizer

Run the following in a terminal(from the folde
Notice that there is a leak

Run the following in a terminal(from the folder where the cpp file is). There are 2 commands. Run one after the other
g++ -std=c++17 -g -O1 -fsanitize=address -fno-omit-frame-pointer ksw_demo6c_exception_safety_solution_with_new_delete.cpp -o ksw_demo6c_exception_safety_solution_with_new_delete.out
./ksw_demo6c_exception_safety_solution_with_new_delete.out 


Notice that there is NO LEAK

*/


# include<iostream>
# include<memory>
using namespace std;

class MyResource{
    public: 
      int dividend;
      int divisor;    
      
      MyResource(int dividendValue, int divisorValue)
        : dividend(dividendValue), divisor(divisorValue) {}

      void doWork() {
        cout<<"My resource: dividend = "<<dividend<< ", divisor ="<< divisor<<endl;    
        if ( divisor == 0) {
                throw runtime_error("Cannot divide by zero");
        }
        cout<<"My resource: Quotient = "<<dividend/divisor<<endl;
     }
};

void processDataRaw(){
    unique_ptr<MyResource> res = make_unique<MyResource>(6,0); // Acquire

    try {
        res->doWork(); //This might throw an exception. Memory Leak has been handled though !
    } 
    catch(...) {        
        // Rethrow the exception.  Pass the original error to the caller
        // Without throw;, the catch block would silently swallow the exception, and the caller 
        // incorrectly assumes that processing succeeded.
        throw;
    }
    cout << "processDataRaw: body end without exception \n";
}

int main() {
    try {
        processDataRaw();
    }
    catch (const std::exception& error) {
        std::cout << "main: Error: " << error.what() << '\n';
    }
}
