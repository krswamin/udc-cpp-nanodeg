/*
Exercise 2: Using std::shared_ptr for Shared Ownership
This exercise demonstrates how to use std::shared_ptr to manage an object that needs to be accessed and owned by multiple parts of a program. The objective is to understand how std::shared_ptr automates memory deallocation when the last owner of an object is destroyed.

Task
The Sensor class below is currently managed with a raw pointer, which can lead to memory management issues. Your task is to refactor the main function to use std::shared_ptr so that the Sensor object is safely managed and automatically deallocated when no longer in use.

Replace the raw pointer sensor1 with a std::shared_ptr.
Use std::make_shared to create the Sensor object.
Assign the std::shared_ptr to a second std::shared_ptr (sensor2) to demonstrate shared ownership.
Print the use_count() to observe the number of owners.

Code to Complete:
*/

#include <iostream>
#include <string>

class Sensor {
public:
    std::string name;
    Sensor(const std::string& n) : name(n) {
        std::cout << "Sensor '" << name << "' created." << std::endl;
    }
    ~Sensor() {
        std::cout << "Sensor '" << name << "' destroyed." << std::endl;
    }
};

void process_data(std::shared_ptr<Sensor> s) {
    std::cout << "Processing data from " << s->name << ". Use count: " << s.use_count() << std::endl;
}

int main() {
    // TODO: Replace the raw pointer with std::shared_ptr and use std::make_shared
    // Sensor* sensor1 = new Sensor("Main_Sensor");

    // TODO: Create a second shared_ptr to the same object
    // std::shared_ptr<Sensor> sensor2;

    // TODO: Call process_data with the shared_ptr

    // The program should demonstrate that the Sensor is not destroyed until the last shared_ptr goes out of scope.

    return 0;
}