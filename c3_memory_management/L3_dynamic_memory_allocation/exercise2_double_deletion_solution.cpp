/*

Double Deletion
Objective: This exercise focuses on a specific type of memory corruption error: double deletion. You will analyze a class that mismanages its dynamically allocated memory, leading to an attempt to free the same memory block twice.

Task: The program below defines a MyResource class that owns a dynamically allocated integer. The main function demonstrates a scenario where a MyResource object's pointer is duplicated and then both are deleted, causing a crash. Your task is to:

Identify why the provided code will cause a double deletion error.
Refactor the main function to correct the mistake and ensure the memory is only deleted once.

*/

#include <iostream>

class MyResource {
public:
    int* data;
    MyResource(int val) {
        data = new int(val);
        std::cout << "Resource created at address " << data << std::endl;
    }
    ~MyResource() {
        std::cout << "Resource destroyed, deleting data at " << data << std::endl;
        delete data;
    }
};

int main() {
    MyResource* ptr1 = new MyResource(10);
    MyResource* ptr2 = ptr1; // ptr2 now points to the same object as ptr1

    // IMPORTANT: Don't delete the same object twice.
    delete ptr1;
    ptr1 = nullptr ;
    ptr2 = nullptr ; 

    return 0;
}