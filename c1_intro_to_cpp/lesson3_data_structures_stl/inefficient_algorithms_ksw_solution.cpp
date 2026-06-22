/*
Below you are presented with some C++ code that mnaually implements an algorithm
to reverse a vector. Your task is to identify how to improve it by using
an STL algorithm or different container.

This code asks the users to keep entering numbers until they want to stop. 
It implements a custom function grow_array to increase the size of our array and
finally it reverses the order of the array and prints it
*/

#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> numbers;
	int size = 0;

	std::cout << "Enter numbers (type -1 to stop): ";
	while (true) {
    	int input;
    	std::cin >> input;
    	if (input == -1) break;

        numbers.push_back(input);
    }

    // Is there a beter way to loop through our array?
    reverse(numbers.begin(), numbers.end());
	for (auto x: numbers) {
    	std::cout << x << " ";
	}
	std::cout << std::endl;

	return 0;
}
