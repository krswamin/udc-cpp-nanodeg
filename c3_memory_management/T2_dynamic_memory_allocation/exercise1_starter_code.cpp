/* 
INSTRUCTIONS

Exercise 1: Dynamic Array Allocation and Cleanup
Objective: Practice allocating and deallocating an array of integers on the heap.

Task: Write a C++ program that:

1) Asks the user for a number n.
2) Dynamically allocates an array of n integers.
3) Fills the array with n random numbers.
4) Prints the elements of the array.
5) Crucially, frees the dynamically allocated memory before the program ends.

*/

#include <iostream>
#include <ctime>

int main() {
      // Seed the random number generator
      srand(time(0));

      int size;
      std::cout << "Enter the size of the array: ";
      std::cin >> size;

      // TODO: Dynamically allocate an array of integers of 'size'
      int* dynamic_array;

      // TODO: Fill the array with random numbers and print them
      // (Hint: Use a for loop)

      // TODO: Deallocate the memory for the dynamic array
      
      return 0;
}