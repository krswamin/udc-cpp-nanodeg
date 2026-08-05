#include <iostream>


void demonstrateDoubleDelete() {
    std::cout << "--- Double Deletion Demo ---" << std::endl;
    int* myIntPtr = new int;
    *myIntPtr = 100;
    std::cout << "Allocated memory at address: " << myIntPtr << " with value: " << *myIntPtr << std::endl;


    // First, correct deletion.
    delete myIntPtr;
    std::cout << "Memory at " << myIntPtr << " successfully freed once." << std::endl;


    // This is the double delete. It's a critical error!
    // The program's behavior is now undefined. It might crash immediately,
    // or it might corrupt memory, leading to a crash much later.
    std::cout << "Attempting to delete the same pointer again..." << std::endl;
    delete myIntPtr; // ERROR: Double free!
    std::cout << "This line may or may not be reached depending on the system/compiler." << std::endl;
}


void demonstrateWildPointer() {
    std::cout << "\n--- Wild Pointer Demo ---" << std::endl;


    int* myWildPtr = new int;
    *myWildPtr = 200;
    std::cout << "Allocated memory at address: " << myWildPtr << " with value: " << *myWildPtr << std::endl;


    // The memory is freed, but the pointer still holds the old address.
    delete myWildPtr;
    std::cout << "Memory at " << myWildPtr << " freed, but pointer is not reset." << std::endl;


    // The pointer 'myWildPtr' is now a wild or "dangling" pointer.
    // It points to memory that is no longer guaranteed to be valid for use.
    // Attempting to access it is a critical error.
    std::cout << "Attempting to read from the wild pointer..." << std::endl;
    // The program may crash here, or print a garbage value, or something else entirely.
    // The behavior is unpredictable and dangerous.
    // std::cout << "Value read from wild pointer: " << *myWildPtr << std::endl; // DANGEROUS!


    // The correct way to handle this is to always set the pointer to nullptr after deletion.
    myWildPtr = nullptr;
}


// This function shows the correct way to handle deletion to avoid the above issues.
void demonstrateCorrectDeletion() {
    std::cout << "\n--- Correct Deletion Demo ---" << std::endl;


    int* safePtr = new int;
    *safePtr = 300;
    std::cout << "Allocated memory at " << safePtr << std::endl;


    delete safePtr;
    // After deletion, immediately set the pointer to nullptr.
    // This prevents it from becoming a wild pointer.
    safePtr = nullptr;
    std::cout << "Memory freed and pointer set to nullptr." << std::endl;


    // Now, a subsequent delete or access attempt is safe.
    // The `if` check prevents a double delete.
    if (safePtr != nullptr) {
        std::cout << "Attempting to delete again... (this code will not run)" << std::endl;
        delete safePtr;
    } else {
        std::cout << "The pointer is null, so no operation is performed. This is safe." << std::endl;
    }
}


int main() {
    // Note: It is likely this program will crash, as it's designed to show bad practices.
    // You may need to run each function individually to see the different effects.


    // Calling the function that demonstrates double deletion.
    // demonstrateDoubleDelete();


    // Calling the function that demonstrates a wild pointer.
    // demonstrateWildPointer();


    // Calling the function that demonstrates correct deletion.
    demonstrateCorrectDeletion();


    return 0;
}
