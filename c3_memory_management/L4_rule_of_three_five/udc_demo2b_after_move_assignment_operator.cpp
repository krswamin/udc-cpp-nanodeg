/*
udacity demo: move constructors, move assignment operator

demonstrates class copying . 
In the presence of move constructors and move assignment operators,
copy constructors and copy assignment operators are NOT called

also demos std::move
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
          this->size = other.size;
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
      
      // Move Assignment Operator
      // TODO: Implement the move assignment operator
      DynamicArray& operator=(DynamicArray&& other) noexcept {
          // Your code goes here

          // Protect against: s1 = s1;
          if (this == &other) {
                return *this;
          }

          delete[] this->data;
          this->data = other.data;
          this->size = other.size;
          other.data = nullptr;   
          other.size =0;
          std::cout << "Move Assignment Operator: Transferred ownership." << std::endl;   
          
          return *this;
      }
};

DynamicArray create_array(size_t s) {
      return DynamicArray(s);
}

int main() {
      
      cout<<"\n Task 1"<<endl;
      // 1. This is ASSIGNMENT: will call MOVE ASSIGNMENT OEPRATOR
      DynamicArray arr1(10);
      // Since rule of 5 has been implemented,it will use the move assignment operator. 
      // It will NOT use the slow copy assignment
      arr1 = create_array(15); 
      
      cout<<"\n Task 2"<<endl;
      // 2. This is INITIALIZATION: will call MOVE CONSTRUCTOR
      // Since rule of 5 has been implemented,it will use the move constructor. 
      // It will NOT use the slow move constructor
      DynamicArray arr2 = create_array(20); 

      cout<<"\n Task 3"<<endl;
      // 3. Assigning one lvalue to another will call the COPY ASSIGNMENT OPERATOR by default
      // This is true even when a MOVE ASSIGNMENT OPERATOR has been defined
      arr1 = arr2;

      cout<<"\n Task 4"<<endl;
      // 4. Assigning one lvalue to another will call the COPY ASSIGNMENT OPERATOR by default
      // This is true even when a MOVE ASSIGNMENT OPERATOR has been defined
      // You have to call explicitly std::move
      DynamicArray arr3 = create_array(25); 
      arr1 = move(arr3);

      cout<<"\n End all Tasks"<<endl;

      return 0;
}