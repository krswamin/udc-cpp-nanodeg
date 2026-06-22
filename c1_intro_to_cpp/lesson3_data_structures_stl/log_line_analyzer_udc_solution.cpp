#include <iostream>
#include <string>

int main() {
    std::string log = "[2025-07-14 10:15:32] ERROR: Camera stream failed to start";

    // Step 1: Extract timestamp
    size_t startBracket = log.find('[');
    size_t endBracket = log.find(']');
    std::string timestamp = log.substr(startBracket + 1, endBracket - startBracket - 1);

    // Step 2: Extract log level
    size_t levelStart = endBracket + 2; // skip "] "
    size_t colon = log.find(':', levelStart);
    std::string level = log.substr(levelStart, colon - levelStart);

    // Step 3: Extract message
    std::string message = log.substr(colon + 2); // skip ": "

    // Output
    std::cout << "Timestamp: " << timestamp << std::endl;
    std::cout << "Level: " << level << std::endl;
    std::cout << "Message: " << message << std::endl;

    // Highlight if it's an error
    if (level == "ERROR") {
        std::cout << "!!! This is an error message." << std::endl;
    }

    return 0;
}
