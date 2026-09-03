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
#include <memory>
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
    if(s) {
    std::cout << "Processing data from " << s->name << ". Use count: " << s.use_count() << std::endl;
    std::cout<<"Notice that the use.count, withing process_data is one more than expected because shared_ptr has been passed by value, which has created a temporary copy"<<std::endl;
    } else {
         std::cout << ". Use count: " << s.use_count() << std::endl;
    }
}

void ksw_solution1(){
    std::cout<<"\n\n\n ---------------- ksw_solution1: START -----------------------------------------------\n"<<std::endl;
    // TODO: Replace the raw pointer with std::shared_ptr and use std::make_shared
    std::shared_ptr<Sensor> sensor1 = std::make_shared<Sensor>("number001");
    std::cout<<"\n At start sensor1 only use_count() ="<<sensor1.use_count()<<std::endl;

    process_data(sensor1);
    std::cout<<"\n Right after process data, sensor1 only use_count() ="<<sensor1.use_count()<<std::endl;
  
    // TODO: Create a second shared_ptr to the same object
    std::shared_ptr<Sensor> sensor2 = sensor1;

    // TODO: Call process_data with the shared_ptr
    std::cout<<"\n At start, sensor 1 and sensor 2"<<std::endl;
    process_data(sensor1);
    process_data(sensor2);

    // The program should demonstrate that the Sensor is not destroyed until the last shared_ptr goes out of scope.
   
    std::cout<<"\n ---------------- ksw_solution1: BODY END (not scope end) -----------------------------------------------\n"<<std::endl;
}


void ksw_solution2(){
    std::cout<<"\n\n\n ---------------- ksw_solution2: START -----------------------------------------------\n"<<std::endl;  
    
    // TODO: Replace the raw pointer with std::shared_ptr and use std::make_shared
    std::shared_ptr<Sensor> sensor1 = std::make_shared<Sensor>("number002");
    std::cout<<"\n At start sensor1 only use_count() ="<<sensor1.use_count()<<std::endl;

    process_data(sensor1);
    std::cout<<"\n Right after process data, sensor1 only use_count() ="<<sensor1.use_count()<<std::endl;
  
    // TODO: Create a second shared_ptr to the same object
    std::shared_ptr<Sensor> sensor2 = sensor1;

    // TODO: Call process_data with the shared_ptr
    std::cout<<"\n At start, sensor 1 and sensor 2"<<std::endl;
    process_data(sensor1);
    process_data(sensor2);

    sensor1.reset();
    std::cout<<"\n After sensor1.reset()"<<std::endl;
    process_data(sensor1);
    process_data(sensor2);
    std::cout<<"sensor2->name ="<<sensor2->name<<std::endl;
    
    std::cout<<"\nGoing to reset sensor2.reset()/ last of the shared_ptrs to number_23"<<std::endl;
    sensor2.reset();
    std::cout<<"\nAfter sensor2.reset()"<<std::endl;
    process_data(sensor1);
    process_data(sensor2);

    // The program should demonstrate that the Sensor is not destroyed until the last shared_ptr goes out of scope.

    std::cout<<"\n ---------------- ksw_solution2: BODY END (not scope end) -----------------------------------------------\n"<<std::endl;
}


/*
Udacity explanation of changes

Explanation of Changes
1) Header Inclusion: The <memory> header is now included to access std::shared_ptr and std::make_shared.

2) std::shared_ptr Declaration: std::shared_ptr<Sensor> sensor1; replaces the raw pointer declaration. 
The template argument <Sensor> specifies the type of object the smart pointer will manage.

3) std::make_shared: The line std::shared_ptr<Sensor> sensor1 = std::make_shared<Sensor>("Main_Sensor"); 
is a safe and efficient way to create a shared_ptr. 
It allocates the Sensor object and the shared_ptr's control block in a single memory allocation, 
improving performance and exception safety compared to separate new calls.

4) Shared Ownership: The line std::shared_ptr<Sensor> sensor2 = sensor1; 
correctly creates a new shared_ptr that points to the same Sensor object. 
This increments the reference count to 2.

5) use_count(): The use_count() member function is used to demonstrate how many shared_ptr objects are currently owning the resource. 
This is a key feature for understanding shared ownership.

6) Automatic Deallocation: The Sensor's destructor is called only after both sensor1 and sensor2 go out of scope at the end of main,
 demonstrating that the memory is freed only when the last shared_ptr owner is gone.

*/
void udc_solution() {
  std::cout<<"\n\n\n ---------------- udc_solution: START -----------------------------------------------\n"<<std::endl;  
  
  std::shared_ptr<Sensor> sensor1 = std::make_shared<Sensor>("Main_Sensor");
  std::cout << "Initial use count: " << sensor1.use_count() << std::endl;

  std::shared_ptr<Sensor> sensor2 = sensor1;
  std::cout << "After creating a second shared_ptr, use count: " << sensor1.use_count() << std::endl;

  process_data(sensor1);
  std::cout << "After function call, use count: " << sensor1.use_count() << std::endl;
  std::cout<<"\n ---------------- udc_solution2: BODY END (not scope end) -----------------------------------------------\n"<<std::endl;  

}

int main() {
      ksw_solution1();
      ksw_solution2();
      udc_solution();

      return 0;
}