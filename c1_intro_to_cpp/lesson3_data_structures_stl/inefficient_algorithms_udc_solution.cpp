#include <iostream>
#include <vector>
#include <algorithm>

int main() {
	std::vector<int> numbers;
	int input;

	std::cout << "Enter numbers (type -1 to stop): ";
	while (std::cin >> input && input != -1) {
    	numbers.push_back(input);
	}

	std::reverse(numbers.begin(), numbers.end());

	std::cout << "Reversed order: ";
	for (int num : numbers) {
    	std::cout << num << " ";
	}
	std::cout << std::endl;

	return 0;
}

