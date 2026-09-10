/*
Solution:
Exercise 1: Using Smart Pointers for Automatic Ownership

Objective: Introduce std::unique_ptr and demonstrate how it simplifies memory management and prevents leaks.

Task: The program below has a memory leak because the raw pointer my_array is never deleted. Refactor the code to use a std::unique_ptr to manage the dynamic array. Your solution should:
Replace the raw pointer with a std::unique_ptr.
Use std::make_unique to allocate the memory.
Remove the explicit delete call, allowing the smart pointer to handle deallocation automatically.

*/


#include <iostream>
#include<memory>
// this should be avoided, but i couldnt be bothered with typing std:: every single time for a demo !
using namespace std; 

void do_something() {
  const size_t array_size = 5;
  // Memory leak due to the use of new has been fixed by using unique_ptr
  auto my_array = make_unique<int[]>(array_size);

  for (int i = 0; i < array_size ; ++i) {
      my_array[i] = i * 10;
  }

  std::cout << "Array elements: ";
  for (int i = 0; i < array_size ; ++i) {
      std::cout << my_array[i] << " ";
  }
  std::cout << std::endl;
  
  // The 'my_array' pointer goes out of scope here, 
  // the memory it pointed to is also freed due to the unique_ptr
}

int main() {
  do_something();
  return 0;
}