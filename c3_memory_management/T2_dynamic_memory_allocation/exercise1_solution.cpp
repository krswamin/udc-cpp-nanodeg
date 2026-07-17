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
using namespace std;

int main() {
      // Seed the random number generator
      srand(time(0));

      int size;
      std::cout << "Enter the size of the array: ";
      std::cin >> size;
      if (size <= 0) {
            cout << "Invalid array size.\n";
            return 1;
      }
      
      // TODO: Dynamically allocate an array of integers of 'size'
      int* dynamic_array = new int[size];

      // TODO: Fill the array with random numbers and print them
      // (Hint: Use a for loop)    
      cout<<endl;
      for(int i =0;i <size; i++){
            // fill with random numbers between 1 and 100
            dynamic_array[i] =rand() % 100 + 1;
            cout<<dynamic_array[i]<<", ";
      }
      cout<<endl;

      // TODO: Deallocate the memory for the dynamic array
      delete[] dynamic_array;
      dynamic_array = nullptr;

      return 0;
}