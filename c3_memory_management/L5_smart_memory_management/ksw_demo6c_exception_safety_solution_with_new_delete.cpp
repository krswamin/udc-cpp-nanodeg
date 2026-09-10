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

----------------------BUT THIS EXCEPTION SAFETY IS FRAGILE. ----------------------
IT IS FRAGILE BECAUSE SAFETY IS DEPENDENT ON THE PROGRAMMER CALLING delete res ON EVERY POSSIBLE EXIT PATH

1) Any other function could throw an exception
void processDataRaw() {
    MyResource* res = new MyResource(6, 03  );
    anotherFunction(); // If this throws, delete is skipped

    try {
        res->doWork();
    }
    catch (...) {
        delete res;
        throw;
    }    

    delete res;
}

void processDataRaw() {
    MyResource* res = new MyResource(6, 0);

    try {
        res->doWork();
    }
    catch (...) {
        delete res;
        throw;
    }

    anotherFunction(); // If this throws, delete is skipped

    delete res;
}

2) More resources make cleanup complicated
MyResource* first = new MyResource(6, 5);
MyResource* second = new MyResource(10, 0);

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
    MyResource* res = new MyResource(6,0); // Acquire

    try {
        res->doWork(); //This might throw an exception. Memory Leak has been handled though !
    } 
    catch(...) {
        delete res; // Need to clean up on 
        
        // Rethrow the exception.  Pass the original error to the caller
        // Without throw;, the catch block would silently swallow the exception, and the caller 
        // incorrectly assumes that processing succeeded.
        throw;
    }

    delete res; // Release (if no exception)
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
