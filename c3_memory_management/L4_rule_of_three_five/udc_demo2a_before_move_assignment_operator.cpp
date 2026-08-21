/*
udacity demo: copy constructors, copy assignment operator

demonstrates class copying . In the absence of move constructors and move assignment operators,
copy constructors and copy assignment operators are called
*/

#include <iostream>
#include <cstring> // For memcpy
using namespace std;

class DynamicArray {
public:
      int* data;
      size_t size;

      // Constructor
      DynamicArray(size_t s) : size(s) {
          data = new int[size];
          std::cout << "Constructor: Allocated " << size << " integers." << std::endl;
      }

      // Destructor
      ~DynamicArray() {
          if (data) {
              delete[] data;
              std::cout << "Destructor: Deallocated " << size << " integers." << std::endl;
          }
      }

      // Copy Constructor (already implemented)
      DynamicArray(const DynamicArray& other) : size(other.size) {
          data = new int[size];
          std::memcpy(data, other.data, size * sizeof(int));
          std::cout << "Copy Constructor: Performed a deep copy." << std::endl;
      }

      // Move Constructor (already implemented)
      DynamicArray(DynamicArray&& other) noexcept : data(other.data), size(other.size) {
          other.data = nullptr; // Take ownership
          other.size = 0;
          std::cout << "Move Constructor: Transferred ownership." << std::endl;
      }

      // Copy Assignment Operator
      // TODO: Implement the copy assignment operator
      DynamicArray& operator=(const DynamicArray& other) {
          // Your code goes here

          // Protect against: s1 = s1;
          if (this == &other) {
                return *this;
          }

          delete[] this->data;
          this->data = nullptr;
          this->size =0;
          if (other.data) {
            data = new int[other.size];
            std::memcpy(data, other.data, other.size * sizeof(int));
            this->size = other.size;
          }

          std::cout << "Copy Assignment Operator: Transferred ownership." << std::endl;   
          
          return *this;
      }

      /*
      // TODO: Implement the move assignment operator
      DynamicArray& operator=(DynamicArray&& other) noexcept {
          // Your code goes here     
      }
     */
      
};

DynamicArray create_array(size_t s) {
      return DynamicArray(s);
}

int main() {

      cout<<"\n Task 1"<<endl;
      //1. This is ASSIGNMENT: will call COPY ASSIGNMENT OEPRATOR
      DynamicArray arr1(10);
      // This will currently perform a slow copy assignment.
      // After your fix, it should use the move assignment operator.
      arr1 = create_array(15); 
      
      cout<<"\n Task 2"<<endl;
      // 2. This is INITIALIZATION: will call COPY CONSTRUCTOR
      // This will currently perform a slow copy constructor.
      // After your fix, it should use the move constructor.
      DynamicArray arr2 = create_array(20); 
      
      cout<<"\n Task 3"<<endl;
      // 3. Assigning one lvalue to another will call the COPY ASSIGNMENT OEPRATOR by default
      // This is true even when a MOVE ASSIGNMENT OPERATOR has been defined
      arr1 = arr2;

      cout<<"\n End all Tasks"<<endl;

      return 0;
}