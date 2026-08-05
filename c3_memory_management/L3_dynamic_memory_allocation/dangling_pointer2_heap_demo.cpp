#include <iostream>


// This function demonstrates how a dangling pointer is created.
void createDanglingPointer() {
    std::cout << "--- Demonstrating a Dangling Pointer ---" << std::endl;


    // 1. Allocate memory on the heap.
    int* ptr = new int;
    *ptr = 100;
    std::cout << "Allocated memory for an integer at address: " << ptr << std::endl;


    // 2. Free the memory. The pointer 'ptr' still holds the address.
    delete ptr;
    std::cout << "Memory at " << ptr << " has been freed." << std::endl;


    // 3. The pointer 'ptr' is now a "dangling pointer." It points to
    // a memory location that is no longer valid. Trying to access or
    // modify it will lead to undefined behavior.
    std::cout << "The pointer 'ptr' is now a dangling pointer." << std::endl;


    // DANGEROUS: Attempting to dereference a dangling pointer.
    // The program's behavior is unpredictable and could crash.
    std::cout << "Attempting to read from the dangling pointer: " << *ptr << std::endl; // DANGEROUS LINE!
    *ptr = 200; // DANGEROUS LINE!
    std::cout << "The dangerous dereferencing lines are commented out to prevent a crash." << std::endl;


    // The correct step, which is missing, would be: ptr = nullptr;
}


// This function demonstrates the correct way to handle pointers.
void demonstrateSafePointerUsage() {
    std::cout << "\n--- Demonstrating Safe Pointer Usage ---" << std::endl;


    int* safe_ptr = new int;
    *safe_ptr = 300;
    std::cout << "Allocated memory at address: " << safe_ptr << std::endl;


    // Free the memory and immediately reset the pointer to nullptr.
    delete safe_ptr;
    safe_ptr = nullptr;
    std::cout << "Memory freed and pointer set to nullptr." << std::endl;


    // Now, any attempt to use the pointer will be safe. The condition
    // below will prevent a crash because the pointer is null.
    if (safe_ptr != nullptr) {
        std::cout << "This line will not execute, as the pointer is null." << std::endl;
        *safe_ptr = 400;
    } else {
        std::cout << "The pointer is nullptr. This is the safe state." << std::endl;
    }
}


int main() {
    createDanglingPointer();
    demonstrateSafePointerUsage();


    return 0;
}
