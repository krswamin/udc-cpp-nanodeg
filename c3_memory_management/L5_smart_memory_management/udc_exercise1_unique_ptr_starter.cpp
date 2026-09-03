/*
Starter Code to Complete:
Exercise 1: Using Smart Pointers for Automatic Ownership

Objective: Introduce std::unique_ptr and demonstrate how it simplifies memory management and prevents leaks.

Task: The program below has a memory leak because the raw pointer my_array is never deleted. Refactor the code to use a std::unique_ptr to manage the dynamic array. Your solution should:
Replace the raw pointer with a std::unique_ptr.
Use std::make_unique to allocate the memory.
Remove the explicit delete call, allowing the smart pointer to handle deallocation automatically.

*/


#include <iostream>

void do_something() {
  // This is a memory leak!
  int* my_array = new int[5];

  for (int i = 0; i < 5; ++i) {
      my_array[i] = i * 10;
  }

  std::cout << "Array elements: ";
  for (int i = 0; i < 5; ++i) {
      std::cout << my_array[i] << " ";
  }
  std::cout << std::endl;
  
  // The 'my_array' pointer goes out of scope here, but the memory
  // it pointed to is never freed.
}

int main() {
  do_something();
  return 0;
}