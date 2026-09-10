#include <iostream>
#include <string>
#include <memory>

class Parent; // Forward declaration

class Child {
public:
    std::shared_ptr<Parent> parent; // This creates the circular dependency
    ~Child() {
        std::cout << "Child destroyed." << std::endl;
    }
};

class Parent {
public:
    std::shared_ptr<Child> child;
    ~Parent() {
        std::cout << "Parent destroyed." << std::endl;
    }
};

int main() {
    std::shared_ptr<Parent> parent_ptr = std::make_shared<Parent>();
    std::shared_ptr<Child> child_ptr = std::make_shared<Child>();
    
    // Create the circular dependency
    parent_ptr->child = child_ptr;
    child_ptr->parent = parent_ptr;

    // TODO: Observe the memory leak
    // Hint: No destructors will be called at the end of main.

    return 0;
}