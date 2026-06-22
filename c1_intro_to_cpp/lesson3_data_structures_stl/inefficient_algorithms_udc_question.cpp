/*
Below you are presented with some C++ code that mnaually implements an algorithm
to reverse a vector. Your task is to identify how to improve it by using
an STL algorithm or different container.

This code asks the users to keep entering numbers until they want to stop. 
It implements a custom function grow_array to increase the size of our array and
finally it reverses the order of the array and prints it
*/

#include <iostream>

// What can we do to avoid implementing a custom function like this?
int* grow_array(int* arr, int old_size, int new_size) {
	int* new_arr = new int[new_size];
	for (int i = 0; i < old_size; ++i) {
    	new_arr[i] = arr[i];
	}
	delete[] arr;
	return new_arr;
}

int main() {
	int* numbers = nullptr;
	int size = 0;

	std::cout << "Enter numbers (type -1 to stop): ";
	while (true) {
    	int input;
    	std::cin >> input;
    	if (input == -1) break;

        // Is there another container we can use to continue adding new input?
    	int* new_numbers = grow_array(numbers, size, size + 1);
    	new_numbers[size] = input;
    	numbers = new_numbers;
    	++size;
	}

    // Is there a beter way to loop through our array?
	std::cout << "Reversed order: ";
    /* HINT: does STL provide a built in algorithm for reversing a container?
    Before writing a custom solution, it is always good to search the web with a sample search as:
    "stl algorithm for <my_problem> in c++"
    
    AI Tools can be helpful here as well, but instead of just asking for the solution, learning is more productive
    if asking "What is a built-in STL algorithm that can help resolve reversing an array or vector in C++"
    */
	for (int i = size - 1; i >= 0; --i) {
    	std::cout << numbers[i] << " ";
	}
	std::cout << std::endl;

	delete[] numbers;
	return 0;
}
