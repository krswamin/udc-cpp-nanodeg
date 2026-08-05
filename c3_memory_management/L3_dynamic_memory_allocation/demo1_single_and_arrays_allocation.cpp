/*
This code demos 
- dynamic memory allocation for a single integer
- dynamic memory allocation for a integer array

i) Dynamic Memory Allocation for a Single Integer
- use new-delete-nullptr. setting to nullptr prevents dangling pointer
- before using a pointer check if it is not null

ii) Dynamic Memory Allocation for an array
- use new[]-delete[]-nullptr. setting to nullptr prevents dangling pointer
- key is new[] , should be accompanied by delete[]. Using a plain delete without brackets with new[] creates MEMORY LEAK
- before using a pointer check if it is not null

*/


#include <iostream>



int main() {
    // --------------------------------------------------------
    // Part 1: Dynamically allocating and deallocating a single integer
    // --------------------------------------------------------
    std::cout << "--- Single Variable Demo ---" << std::endl;


    // Declare a pointer to an integer.
    // This pointer will hold the memory address of the dynamically allocated integer.
    int* myIntPtr = nullptr;


    // Allocate memory on the heap for a single integer using 'new'.
    // The 'new' operator returns the memory address of the allocated block.
    myIntPtr = new int;


    // Check if the memory allocation was successful.
    // In modern C++, 'new' throws an exception on failure, but this check
    // is good practice, especially in older codebases or with 'new(std::nothrow)'.
    if (myIntPtr != nullptr) {
        // Assign a value to the allocated memory block using the dereference operator (*).
        *myIntPtr = 42;


        // Print the value stored at the memory address.
        std::cout << "Value stored in dynamically allocated memory: " << *myIntPtr << std::endl;


        // Free the memory allocated by 'new' using the 'delete' operator.
        // It's crucial to call 'delete' exactly once for each 'new' to prevent memory leaks.
        delete myIntPtr;


        // Set the pointer to nullptr to prevent it from being a "dangling pointer."
        // A dangling pointer points to deallocated memory, which can lead to
        // unpredictable behavior if you try to use it.
        myIntPtr = nullptr;
    } else {
        std::cerr << "Memory allocation for single integer failed!" << std::endl;
    }


    std::cout << "----------------------------" << std::endl;


    // --------------------------------------------------------
    // Part 2: Dynamically allocating and deallocating an array of integers
    // --------------------------------------------------------
    std::cout << "\n--- Array Demo ---" << std::endl;


    const int arraySize = 5;
    int* myArrayPtr = nullptr;


    // Allocate memory on the heap for an array of 5 integers using 'new[]'.
    // Note the brackets '[]' after 'new', which tells the compiler to allocate
    // a block of memory large enough for the entire array.
    myArrayPtr = new int[arraySize];


    if (myArrayPtr != nullptr) {
        // Initialize the array elements with values.
        for (int i = 0; i < arraySize; ++i) {
            myArrayPtr[i] = (i + 1) * 10;
        }


        // Print the elements of the dynamically allocated array.
        std::cout << "Values in the dynamically allocated array: ";
        for (int i = 0; i < arraySize; ++i) {
            std::cout << myArrayPtr[i] << " ";
        }
        std::cout << std::endl;


        // Free the memory allocated by 'new[]' using 'delete[]'.
        // It is absolutely critical to use 'delete[]' for arrays,
        // not 'delete'. Using the wrong one can lead to undefined behavior
        // and memory corruption.
        delete[] myArrayPtr;


        // Set the pointer to nullptr again.
        myArrayPtr = nullptr;
    } else {
        std::cerr << "Memory allocation for array failed!" << std::endl;
    }


    std::cout << "----------------------------" << std::endl;


    return 0;
}
