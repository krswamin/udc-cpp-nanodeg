// Case 1: Forgetting delete entirely: The most basic form.
void simpleLeak() {
    int *data1 = new int[100]; // Allocation
    // ... use data1 ...
    // No delete here! Leak!

    // data1 pointer variable itself will be deleted here i.e at the end of scope of simpleLeak()
    // But the heap memory that data1 pointed to WILL NOT BE RELEASED -> Hence Memory Leak
    // In face data1 will not be released even when main() exits .
    // It will be released when the process exits and the operating system reclaims all of the process's memory.
} 

// Case 2: Returning early without delete:
// You need to ensure that delete is called no matter how the function exits (return, throw exception, etc.).
bool processData(int* buffer) {
    int* temp = new int[100];
    if (buffer == nullptr) {
        // delete[] temp; // MISSING! Leak if buffer is null.
        return false;
    }
    // ... process ...
    delete[] temp; // This might be reached, but not always.
    return true;
}

//Case 3
// Reassigning Pointers: Losing the only pointer to dynamically allocated memory.
// Imagine having a key to a storage unit, but then you lose the key. The unit is still yours, but you can no longer access it or return it.
void reassingedPointers(){
    int* p = new int(10);
    int* q = new int(20);
    p = q; // 'new int(10)' is now leaked because 'p' no longer points to it, and no other pointer does.
        // 'q' points to 'new int(20)'.
    delete q; // Only 'new int(20)' is deleted.
}

int main(){
    bool processDataFlag;
    int* bufferPointer = nullptr;
    void simpleLeak();
    processDataFlag = processData(bufferPointer);
    void reassignedPointers();

    // Case 4: Memory Leak in main
    int *ptr  = new int(42);
    // There is not delete ptr, hence it is a leak


    // ptr variable itself will be deleted here i.e. at the end of scope of main.
    // But the heap memory that ptr pointed to WILL NOT BE RELEASED -> Hence Memory Leak

    // even the heap memory that data1 pointer from simpleLeak() pointed to, will not be released here i.e. at the end of scope of main.
}


// At some point the process itself that ran main will exit 
// All of the following will be reclaimed by the operating system, when the process exits.
// But YOU SHOLDN'T HAVE TO RELY ON THE OPERATING SYSTEM 
// simpleLeak(): heap memory pointed to by data1 pointer
// processData(): heap memor

