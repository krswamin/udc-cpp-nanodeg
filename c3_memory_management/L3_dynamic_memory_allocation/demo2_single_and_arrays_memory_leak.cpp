/*
This code demos 
- dynamic memory allocation for a single integer
- dynamic memory allocation for a integer array
- It specifically shows how memory leaks are created and how to fix them in both cases

i) Dynamic Memory Allocation for a Single Integer
- use new-delete-nullptr. setting to nullptr prevents dangling pointer
- before using a pointer check if it is not null

ii) Dynamic Memory Allocation for an array
- use new[]-delete[]-nullptr. setting to nullptr prevents dangling pointer
- key is new[] , should be accompanied by delete[]. Using a plain delete without brackets with new[] creates MEMORY LEAK
- before using a pointer check if it is not null

*/





#include <iostream>
#include <vector> // We'll use this for a more robust data structure


// A simple function that demonstrates a memory leak.
void createMemoryLeak() {
    // This memory is allocated on the heap.
    int* myLeakedInt = new int;
    *myLeakedInt = 100;


    // The function returns without deleting the memory.
    // The pointer 'myLeakedInt' goes out of scope and is destroyed,
    // but the memory it pointed to remains allocated, becoming "leaked."
    // It can no longer be accessed or freed.
    std::cout << "Intentionally creating a memory leak. The value was: " << *myLeakedInt << std::endl;
    // We should have a 'delete myLeakedInt;' here, but we've omitted it.
}


// A function that correctly allocates and deallocates memory.
void createAndFixMemory() {
    // Allocate a single integer.
    int* myInt = new int;
    *myInt = 200;


    std::cout << "Creating and fixing a memory allocation. The value is: " << *myInt << std::endl;


    // Correctly free the memory before the function returns.
    delete myInt;
    myInt = nullptr; // Good practice to prevent dangling pointers
}


// Another leak example, this time with an array.
void createArrayMemoryLeak() {
    const int size = 3;
    int* myLeakedArray = new int[size];
    // Fill the array
    for (int i = 0; i < size; ++i) {
        myLeakedArray[i] = (i + 1) * 10;
    }
    std::cout << "Intentionally creating an array memory leak. First element was: " << myLeakedArray[0] << std::endl;
    // 'delete[] myLeakedArray;' is missing here, leading to a leak.
}


// The corrected version for the array.
void createAndFixArray() {
    const int size = 3;
    int* myArray = new int[size];
    // Fill the array
    for (int i = 0; i < size; ++i) {
        myArray[i] = (i + 1) * 10;
    }
    std::cout << "Creating and fixing an array allocation. First element is: " << myArray[0] << std::endl;
   
    // Correctly free the array memory.
    delete[] myArray;
    myArray = nullptr;
}




int main() {
    std::cout << "--- Demoing a Memory Leak ---" << std::endl;
    createMemoryLeak();
    std::cout << "After createMemoryLeak(), the memory allocated is now leaked." << std::endl;
    std::cout << "-----------------------------" << std::endl;


    std::cout << "\n--- Demoing a Correct Allocation ---" << std::endl;
    createAndFixMemory();
    std::cout << "After createAndFixMemory(), the memory was correctly freed." << std::endl;
    std::cout << "-----------------------------" << std::endl;


    std::cout << "\n--- Demoing an Array Memory Leak ---" << std::endl;
    createArrayMemoryLeak();
    std::cout << "After createArrayMemoryLeak(), the array memory is now leaked." << std::endl;
    std::cout << "-----------------------------" << std::endl;


    std::cout << "\n--- Demoing a Correct Array Allocation ---" << std::endl;
    createAndFixArray();
    std::cout << "After createAndFixArray(), the array memory was correctly freed." << std::endl;
    std::cout << "-----------------------------" << std::endl;


    return 0;
}
