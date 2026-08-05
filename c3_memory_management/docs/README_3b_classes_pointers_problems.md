# CODE PROBLEMS : WITH CLASSES, POINTERS & IMPLEMENTING MANUAL RAII IN CLASSES


## 1) CAN A CLASS HAVE THE FOLLOWING ?

- have a pointer to its own type: YES
- have a member that is its own type: ABSOLUTELY NO
- one construtor call another constructor: maybe if there are no cyclical dependencies
  KSW TODO: DRAW Diagram for this (like a memory diagram)

## 2) SHALLOW COPY Vs DEEP COPY
- **PRIMITIVE DATA TYPES:** primitive data types like int, float etc. copying is simple. it copies the value as is. 
- **NON PRIMITIVE DATA TYPES:** Shallow copy vs Deep Copy Applies to non primitive data types such as pointers, structs, classes etc.
- Shallow copy vs Deep copy can happen anywhere stack, heap, global-static data etc. But as usual one of the most signficant sources of bugs and errors is when unintended shallow copy occurs on the heap ! Hence rule of 5 (move and copy semantics are important to follow. also use smart pointers)
- **POINTERS: shallow copy vs deep copy:** When you copy one pointer to the other it copies the memory address over. It does not create a copy of the data that the pointer points to. 
    - when a pointer points to a primitive such as an int, you dont expect a copy of the int as well
    - But for some reason when a pointer points to a class object , especially a class object on the heap , you expect a deep copy (The mind playing tricks ??)
    - In this diagram the following examples are demonstrated
    - shallow copy of pointer to primitive data type(Ex1-memory in stack, Ex2-memory in heap)
    - shallow copy of pointer to class data type    (Ex3-memory in stack, Ex4-memory in heap)
    ![alt text](readme_imgs/cpp_pointers_classes/shallow_copy.jpg)
- **OBJECTS: shallow copy vs deep copy:**  
    - objects are by default a shallow copy (unless you have defined the copy assignment operator)
    - this means the primitive data


## 3) RETURNING OBJECTS 
-  Never Return a Local Pointer in a function
-  Never Return a Local Reference
-  Can you Return a Class, By Value: Yes of course you can return them by value ! but there are clauses
- What about returning a class object from a function that has a pointer inside it. are you returning the class by by value ? what about the pointer inside it. So when copying the class by value, is that a shallow copy or deep copy ?
    - returning a object by value is totally fine as long as the object had primitive data types only as the class members)
    - if the object has non primitive data types such as a pointer, other classes(that possible have pointers), things get more complicated. you would have to follow the rule of 5 and obey the copy and move semantics. 
    - This because when you return this class by value, for member pointers and member classes , that would be a shallow copy by default. The pointer inside the class is copied i.e the pointer's value is the the memory address that it points to. This memory address/value is copied. But the entire variable or object at that memory address is not duplicated ( this memory address could be in heap or stack. But it is not duplicated)

## 4) COPYING A OBJECT
This is a shallow copy by default. You would have to take care of rule of 5. Take care of copy semantics


## CODE DISCUSSION

See : [L5_smart_memory_management/ksw_demo1a_wrapper_around_raw_pointers.cpp](../L5_smart_memory_management/ksw_demo1a_wrapper_around_raw_pointers.cpp)

- demo1 :  
  key concepts: raw pointers
- demo2: raii like abstraction.
    - acquire and initialize in constructor
    - destroy in destructor
    - does not obey rule of 3/5 though
    - demo2a vs demo2b: 
        - which of these 2 is better. KSW TODO: Draw memory Diagram for below piece of code
    ``` 
        # Demo 2a
        StudentWrapper stuwrap1 = StudentWrapper();
        StudentWrapper stuwrap2 = StudentWrapper(51);
        
        # Demo 2b
        StudentWrapper stuwrap1;
        StudentWrapper stuwrap2(51);
    ```
- demo3a:
    - causes memory leak despite raii type implementation. 
    - also causes dangling pointer, & double deletion
    - This because rule of 3/5 not obeyed, it also exposes a raw pointer
    - KSW TODO: Draw memory Diagram for below piece of code
    ``` 
        # Demo 3a
        StudentWrapper stuwrap1 = StudentWrapper();
        stuwrap2 = StudentWrapper(51);
    ```
- demo3b: 
    - fixes the memory leak very unelegantly
    - overall but the point of demos is taken care of though. 
        - you can implement raii principles manually and abstract away the raw pointers from the user
        - but if you dont implement properly, like raw pointers within classes are exposed. Rule of 3/5 are violated. Then it will lead to all sorts of dangerous bugs
  

```