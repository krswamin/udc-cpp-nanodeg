#include <iostream>
#include <string>

void reportError(std::string* message) {
    // error handling for null pointers
    if (message != nullptr) {
        std::cout << "ERROR: " << *message << std::endl;
    } else {
        std::cout << "No error message provided." << std::endl;
    }
}

int main() {
    std::string msg = "Camera stream failed.";
    reportError(&msg);         // Should print error
    reportError(nullptr);      // Should handle gracefully
    return 0;
}
