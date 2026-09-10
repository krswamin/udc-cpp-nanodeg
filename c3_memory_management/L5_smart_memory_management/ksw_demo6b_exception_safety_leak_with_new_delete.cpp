/*
This code CAUSES A MEMORY LEAK

The exception flow is below: i.e from the inner most function doWork() all the way to main(),
the exception keeps getting rethrown until the user can handle it in main

doWork()
throws
      ↓
processDataRaw()
   throws before deleting res
   deletes res is never reached so memory leak !
      ↓
main()
   catches the exception and prints the error: 
   the memory leak persists nevertheless (even though there is no segfault)



---------------- TESTING THE MEMORY LEAK

Step 1) Run WITHOUT Address Sanitizer

Run the following in a terminal(from the folder where the cpp file is). There are 2 commands. Run one after the other
g++ ksw_demo6b_exception_safety_leak_with_new_delete.cpp -o ksw_demo6b_exception_safety_leak_with_new_delete.out
./ksw_demo6b_exception_safety_leak_with_new_delete.out

Notice that there is no seg fault, or no indication of a leak. But there is a leak nevertheless

Step 2) Run WITH Address Sanitizer

Run the following in a terminal(from the folde
Notice that there is a leak

Run the following in a terminal(from the folder where the cpp file is). There are 2 commands. Run one after the other
g++ -std=c++17 -g -O1 -fsanitize=address -fno-omit-frame-pointer ksw_demo6b_exception_safety_leak_with_new_delete.cpp -o ksw_demo6b_exception_safety_leak_with_new_delete_address_sanitized.out
./ksw_demo6b_exception_safety_leak_with_new_delete_address_sanitized.out

Notice that there is a leak
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


void processDataRaw() {
    MyResource* res = new MyResource(6, 0); // divisor = 0

    res->doWork(); // Throws here

    delete res; // Never reached, causing a memory leak
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
