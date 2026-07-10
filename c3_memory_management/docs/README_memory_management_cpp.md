# 🎯 CITATIONS, REFERENCES
- Course material and images are based on the Udacity C++ Nanodegree.
- The README content consists of my personal notes and explanations developed while studying the course material, in conjunction with deep conversations with chatgpt 😅


# 🎯 1) C++ : VIRTUAL ADDRESS SPACE
 C++ 's Organization of Virtual Address Space

```

 High Memory Addresses
+-----------------------------+
|         Stack               |  <-- Local variables, function calls
|      (grows downward)       |  <-- Mainly function call frames  
|                             |      - return address
|                             |      - function parameters
|                             |      - local variables
|                             |      - saved registers
|                             |
|                             |
+-----------------------------+
|                             |
|     Unused / Free Space     |
|                             |
+-----------------------------+
|          Heap               |  <-- Dynamic memory (new, malloc)
|      (grows upward)         |
|                             |
|                             |
+-----------------------------+
|  BSS Segment                |  <-- Uninitialized global/static variables
+-----------------------------+
|  Data Segment               |  <-- Initialized global/static variables
+-----------------------------+
|  Read-only Data (.rodata)   |  <-- String literals, const globals
+-----------------------------+
|  Text (Code) Segment        |  <-- Executable machine instructions
+-----------------------------+
 Low Memory Addresses

 ```

![alt text](readme_imgs/cpp_memory/cpp1_virtual_address_space.png)


 | Memory Region                | Stores                                                          | Lifetime                |
| ---------------------------- | --------------------------------------------------------------- | ----------------------- |
| **Text (Code)**              | Compiled machine instructions (functions)                       | Entire program          |
| **Read-only Data (.rodata)** | String literals, `const` global variables                       | Entire program          |
| **Data Segment**             | Initialized global and `static` variables                       | Entire program          |
| **BSS Segment**              | Uninitialized or zero-initialized global and `static` variables | Entire program          |
| **Heap**                     | Objects allocated using `new`, `new[]`, `malloc()`              | Until `delete`/`free()` |
| **Stack**                    | Function parameters, local variables, return addresses          | Until function returns  |



## 🎯 1.1) Sample Code
```
#include <iostream>

int globalVar = 10;           // Data segment
int globalUninit;             // BSS segment

const int MAX = 100;          // Read-only data (often)

void foo()
{
    static int counter = 0;   // Data segment

    int x = 5;                // Stack
    int arr[100];             // Stack

    int *p = new int(20);     // p on stack, object on heap

    delete p;
}

int main()
{
    foo();
}
```

## 🎯1.2 Important Note: Pointers & New:  Where are they stored ?
Notice something important:
```
int *p = new int(20);
```
There are actually two things here:
- p (the pointer variable) lives on the stack because it is a local variable.
- *p (the integer allocated by new) lives on the heap.

```
Stack                     Heap
------+                   +------+
| p | ------------------> | 20 |
------+                   +------+
```

**In Greater Detail**
```
                STACK                              HEAP
+-------------------------------+      +-------------------------------+
| Variable | Address | Value    |      | Variable | Address | Value    |
+----------+---------+----------+      +----------+---------+----------+
| p        |7FFE1000 |10002000  |----->| *p       |10002000 |20        |
+----------+---------+----------+      +----------+---------+----------+

```


# 🎯 2) STATIC  MEMORY AREAS

![alt text](readme_imgs/cpp_memory/cpp2_static_memory_areas.png)

- By static memory , we dont mean the area for statically allocated stuff such as int, float etc
- We mean the area in the virtual address space that does not change size. **💡 ONCE SPACE HAS BEEN ALLOCATED FOR THIS . IT DOES NOT CHANGE IN SIZE OR PURPOSE** . Global variables, static variables remain alive through the lifetime of the programme. Code of course will remain alive throughout
- The static memory areas from top to bottom are. 
    - uninitialized data (.bss):       
      - this is for global variables , static variables that are **UNINITIALIZED OR ZERO (or zero equivalent like NULL POINTER)**. 
      - BSS MEANS Block Started by Symbol, old assembly language directive.  
    - initialized data (.data): 
      - global variables, static variables that are explicitly initialized to **NON-ZERO VALUES**
    - code(.text): read only area
- Together the .text, .bss, .data provide the stable foundation for the code and long lived data needed for the programme. 


# 🎯 2) DYNAMIC MEMORY AREAS

![alt text](readme_imgs/cpp_memory/cpp3_dynamic_memory_areas.png)

- By dynamic memory , we *DON'T ONLY ** mean the area for PROGRAMMATICALLY dynamically allocated stuff such as new/delete malloc/free. 
- We mean the area in the virtual address space that keeps changing in size & purpose. This includes both 
  - STACK: for statically allocated ints, floats, class objects and function call stacj


## 🎯 2.1) STACK ALLOCATIONS
  - the progammatically static memory allocations such as ints, floats, class objects, etc. These are on the STACK. 
  - actually the stack is mainly for the **FUNCTION CALL STACK** : The stack holds ints, floats, class objects, etc local to the function. If you think about it main is also a function
  - The stack keeps growing and shrinking bassed on the ints, floats, or even class objects are getting created and deleted (depending on the scope & lifetime of the variable.). 
  - If the stack has to grow, it grows downwards towards lower memory addresses
  - The stack is optimized for speed for short lived data
  
    
## 🎯 2.2) HEAP ALLOCATIONS 
  - the progammatically dynamic memory allocations such as new. could be new int, new floats , or even new class objects. These are on the HEAP. 
  - The **LIFETIME IS CONTROLLED BY THE PROGRAMMER**: If the lifetime of the variable is done and you - the programmer forgets to release it, it causes a **MEMORY LEAK**
  - The heap keeps growing and shrinking based on the new / delete (or smart pointer controls it). 
  - If the heap has to grow, it grows upwards towards higher memory addresses
  - **MEMORY ALLOCATOR:**  
      ```
      PROGRAMME <-----> MEMORY ALLOCATOR (manages heap)  <--------> OPERATING SYSTEM
      ```
      - The C++ programme requests memory from the system during runtime for heap variables. (You do not know at compile time how much memory is needed). 
      - but everytime you call 'new' the programme doesnt grab memory directly from the operating system. Instead the programme talks to a component of the c++ runtime library called **memory allocator**. 
      - The memory allocator sits in between the programme and the operating system and manages the heap, releases heap memory, asks the os for more heap memory, . It manages using free lists

## 🎯 2.3) STACK : PROBLEMS
### 🎯 2.3.1) STACK : FAMOUS PROBLEMS
- **😈 1. STACK OVERFLOW** : The most common stack problem is  . The stack runs out of space/ stack grows beyond its allocated region. It can occur
    - if you allocate a very large array (RARE)
    - very deep recursion (MOST COMMON CAUSE)
      ```
          void recurse()
          {
              recurse();
          }
      ```

- **STACK OVERFLOW - DIAGNOSIS: GDB** : 
  - When a stack overflow occurs the code just ends abruptly
  - Can be diagnosed using GDB, you can traceback at what point the code exited and keep stepping backwards

### 🎯 2.3.2) STACK : LESS FAMOUS PROBLEMS
- **😈 2. STACK BUFFER OVERFLOW**: writing beyond a stack-allocated array.
   ```
    void foo()
    {
        int arr[10];
        arr[100] = 5;
    }
  ```

- **😈 3. INVALID STACK POINTER** : 
 That address doesn't belong to your program.
  ```
  int* p = (int*)0x12345678;
  *p = 5;
  ```



## 🎯 2.4) HEAP : PROBLEMS
### 🎯 2.4.1) HEAP: FAMOUS PROBLEMS
- **e 👹 1) MEMORY LEAK** : the most common problem is Memory Leak. The programmer forgot to delete a variable that is no longer needed
- **MEMORY LEAK: DIAGNOSIS: VALGRIND** : valgrind to diagnose memory leaks


### 🎯 2.4.2) HEAP: LESS FAMOUS PROBLEMS
- **e 👹 2) HEAP OVERFLOW / OUT OF MEMORY**: Heap overflow can occur. But this is called out of memory error
- **e 👹 3) HEAP BUFFER OVERFLOW** : Writing beyond the allocated heap block.
    ```
    int* arr = new int[10];
    arr[100] = 5;
    ```
- **e 👹 4) DANGLING HEAP POINTER/ USING A FREED HEAP POINTER** : 
  ```
  int* p = new int(42);
  delete p;
  *p = 10;      // Invalid
  ```


## 🎯 2.5) SEGMENTATION FAULT: HEAP & STACK
- Segmentation fault just means invalid/ illegal memory access. 
- It could occur due to any of the following reasons. But Memory Leak is not one of them
- can occur on the heap or stack

| Problem               | Segmentation Fault? |
| --------------------- | ------------------- |
| Null pointer          | ✅ Yes               |
| Stack overflow        | ✅ Usually           |
| Heap buffer overflow  | ✅ Often             |
| Stack buffer overflow | ✅ Often             |
| Use-after-free        | ✅ Often             |
| Invalid pointer       | ✅ Yes               |
| Memory leak           | ❌ No                |



# 🎯 3) POINTERS : ARE THEY ON THE HEAP OR STACK
Answer:
- Pointers can live anywhere: Stack, Heap, Global-Static Data (.bss, .data sections)
- The memory that they point to can live anywhere as well. Stack, Heap, Global-Static Data (.bss, .data sections)
- stack-stack, stack-heap, heap-heap . global-data region-stack, globaldata-heap. Any combination is possible

NOTE: 💡
- The following examples use new , for the purpose of demonstration and for the sake of demonstrating pointers in various locations,  memory leaks,  and dangling pointers. 
- But modern C++ never uses new. Modern C++ relies on the principle of Resource Acquisition Is Initialization (RAII) and smart pointers to handle memory automatically.

#### 💡 Example 1: pointer on stack, object on stack
- pointer on stack
- object pointer points to is also on stack
  ```
  int main()
  { 
    int a =10 ;  // a is on stack
    int* p1 ;    // pointer itself is on the stack
    p1 = &a  ;   // pointer to a stack variable

    Student s1;  // s1 is on stack
    Student* p2; // pointer itself is on the stack
    p2 = &s1;    // pointer to a stack object

  }
  ```

**Memory Layout:**
  ```
  Stack

  +----------------------+
  | a = 10               |
  +----------------------+
  | p ------------------+|
  +----------------------+
                        |
                        |
                        +-------> a
  ```


#### 💡 Example 2: pointer on stack, object on heap
- pointer on stack
- object pointer points is on heap
one of the most important concepts in c++ is
- delete does not delete the pointer itself
- it deletes the memory that the pointer points to
- once the memory is freed p1 still points to that freed memory. This would create a **DANGLING POINTER**
- hence p1 = nullptr **AVOIDS THE DANGLING POINTER**
  ```
  int main()
  { 
    int* p1 ;           // pointer itself is on the stack
    p1 = new int  ;     // *p1 is on heap
    *p1 = 10    
    delete p1 ;         // important to free heap memory. this does not delete p1 though
    p1 = nullptr        // good practise, so that p1 doesnt become a dangling pointer

    Student* p2;        // pointer itself is on the stack
    p2 = new Student(); // *p2 on heap
    delete p2 ;         // important to free heap memory. this does not delete p2 though
    p2 = nullptr        // good practise, so that p2 doesnt become a dangling pointer


  // p1 and p2  the pointers would get deleted right here. right before the end of main
  }
  ```

**Memory Layout:**

```
Stack                            Heap

+-----------------+           +---------+
| p1 = 0x1000 ----|  ------>  |   10    |
+-----------------+           +---------+

```

##### 💡 Example 2: MEMORY LEAK DISCUSSION
Question : Now in the same example above what if we dont release heap memory pointed by p1 and p2. 
- Would that memory never be released even after the program terminates ?
- Would this could be a code with memory leak  ?

  ```
  int main()
  { 
    int* p1 ;           // pointer itself is on the stack
    p1 = new int  ;     // *p1 is on heap
    *p1 = 10 
  
    Student* p2;        // pointer itself is on the stack
    p2 = new Student(); // *p2 on heap

  }
  ```

Answer:
- The memory would be released after the program termninates by the **OPERATING SYSTEM. IT IS NOT RELEASED BY THE PROGRAM ITSELF**. Hence this is bad code, and hence it is a memory leak as well. This distinction is the key reason why C++ requires you to manually delete memory allocated with new (unless you use smart pointers like std::unique_ptr or std::shared_ptr, which automate this).
- Yes this would be a memory leak. Because during the lifetime of this program there were sections in the heap memory that was once allocated and pointed to by a pointer and remained inaccessible . **THE C++ PROGAM LEAKED MEMORY DURING EXECUTION**
- Imagine this piece of code was inside a function or it ran on a server. Then the heap memory would not be released at the end of the function. The memory that was reserved but remained inaccesible (MEMORY LEAK) would continue to grow until you are out of memory

```
void demo_function(){
      int* p1 ;           // pointer itself is on the stack
    p1 = new int  ;     // *p1 is on heap
    *p1 = 10 
  
    Student* p2;        // pointer itself is on the stack
    p2 = new Student(); // *p2 on heap
}

// no the heap memory pointed to p1 and p2 would not be released at the end of the demo_function() , no not even here
```


#### 💡 Example 3: pointer on heap, object on heap 
This is essentially a pointer to a pointer for the purpose of demonstration
- pp on stack. pp is a pointer to a pointer
- pp points to new int*.  new int* is the second pointer here and it is on heap
- *(new int*) points to an integer on the heap

```
int main() {
  int **pp;        // pp is a pointer to a pointer. pp is on the stack
  
  pp = new int*;  // pp points to a pointer on the heap. new int* is the second pointer here and it is on heap
  *pp = new int;  // *(new int*) points to an integer on the heap
  **pp = 10;

  delete *pp;
  *pp = nullptr;

  delete pp;
  pp = nullptr;
}
```    

**Memory Layout:**
```
Stack                                   Heap

+--------------------+                  +----------------------+
| pp --------------+ |----------------->| int* -------------+  |
+--------------------+                  +-------------------|--+
                                                            |
                                                            |
                                         +------------------v---+
                                         | int = 10            |
                                         +----------------------+
```

#### 💡 Example 4:
In practice, you rarely allocate a standalone pointer on the heap. A much more common case is a pointer inside a heap-allocated object:
- pointer on stack
- Node Object on the heap
- the next pointer within the node object is also on the heap
```
Class Node {
  public:
  int number;
  Node *next ;
}

int main(){
   
   Node *node_p = new Node();
   delete node_p; 
}
```


**Memory Layout:**

```
        Stack                                                   Heap

+------------------------------+       +--------------------------------------+
| node_p                       | ----> | Node object                          |
| (pointer on the stack)       |       |                                      |
+------------------------------+       | number : int                         |
                                       | next   : Node* (pointer on the heap) |
                                       +--------------------------------------+
```


#### 💡 Example 5: Examples like this are commonly encountered

In practice, you rarely allocate a standalone pointer on the heap. A much more common case is a pointer inside a heap-allocated object:
- s1 and s2 are pointer variables on the stack.
- Both Student objects are on the heap.
- friendPtr is also on the heap because it is a member of a heap-allocated Student.
This is the pattern you'll encounter most often in linked lists, trees, graphs, and other dynamic data structures.


```
struct Student
{
    int age;
    Student* friendPtr = nullptr;
};

int main()
{
    Student* s1 = new Student;
    Student* s2 = new Student;

    s1->friendPtr = s2;

    delete s2;
    s2 = nullptr;
    s1->friendPtr = nullptr;

    delete s1;
    s1 = nullptr;
}
```

**Memory Layout:**

```
Stack                                 Heap

+----------------+            +----------------------+
| s1 -----------+|----------->| Student              |
+----------------+            | friendPtr --------+  |
                              +-------------------|--+
                                                  |
+----------------+                                |
| s2 -----------+|--------------------------------+
+----------------+            +----------------------+
                              | Student              |
                              +----------------------+

```


#### 💡 Example 6: Example 5 reimagined as Global Data
NOTE: There is no longer a stack


```
struct Student
{
    int age;
    Student* friendPtr = nullptr;
};

Student* s1 ;
Student* s2 ;

int main()
{
    s1 = new Student;
    s2 = new Student;

    s1->friendPtr = s2;

    delete s2;
    s2 = nullptr;
    s1->friendPtr = nullptr;

    delete s1;
    s1 = nullptr;
}
```

**Memory Layout:**

```
Global/Static Data(.bss)                        Heap

+--------------------------+            +----------------------+
| s1 ---------------------+|----------->| Student              |
+--------------------------+            | friendPtr --------+  |
                                        +-------------------|--+
                                                            |
+--------------------------+                                |
| s2 ---------------------+|--------------------------------+
+--------------------------+            +----------------------+
                                        | Student              |
                                        +----------------------+

```


#### 💡 Example 7: Static pointer → Static data

Again, the pointer is not on the stack.

```
void foo()
{
    static int* p = new int(10);
}
```

**Memory Layout:**

```
Static Data                 Heap

+----------------+       +---------+
| p ----------+  |------>|   10    |
+----------------+       +---------+
```


# 🎯 4. MEMORY AS ADDRESSABLE UNITS

- **1. THE SMALLEST UNIT OF MEMORY IS A BYTE = 8bits** 
  - virtually all modern computers, the smallest addressable unit of memory is one byte (8 bits).
  - This byte-addressable memory model is what C and C++ assume on mainstream architectures such as x86, x86-64, and ARM

- **2. ADDRESS REPRESENTATION: 64 BITS = 8 bytes**
  - The address itself is 64 bits long = 8 BYTES (on a 64 bit system)** 
  - Each address is 64 bits long (on a 64 bit system)
  - 64binary bits is too long. easier to represent as hexadecimal for every 4 bits. (This is middle school math, you know this !)
  - every 4 binary digits/bits is one hexadecimal character
    ```
    64bit hexadecimal :  A7F3-C91E-5D42-1230
    64bit binary value : 10100111-11110011-11001001-00011110   01011101-01000010-00010010-00110000
    ```

- **3. Each address location gets incremented by 1 (not 8)**
  - because it is the address / house number of the byte. Its like house numbers get incremeted by 1
  - it does not get incremeted by 8 bits .
  - I found this part confusing and hard to believe/ convince myself. You can have deep conversations with chatgpt/ claude/ gemini and sort this out  😂🤣
      ```
      Imagine apartment numbers
      Apartment 1230
      Apartment 1231
      Apartment 1232
      Apartment 1233

      Now the same thing in byte addresses increasing by 1 byte
      0xA7F3-C91E-5D42-1230
      0xA7F3-C91E-5D42-1231
      0xA7F3-C91E-5D42-1232
      0xA7F3-C91E-5D42-1233
      ```

**⚠️ RE-READ PTS 1, 2,3 above. It is a very common point of confusion . The the size of the location(8bits), the number of bits in an address(64bits),  and the value to increase the address byte (1) are three different concepts.**


![alt text](readme_imgs/cpp_memory/memory_bytes.png)

### 💡 How many bytes in various datatypes ?
- int32 : 32 bits = 4 bytes
- int16 : 16 bits = 2 bytes
- int8  :  8 bits = 1 byte
- int4  :  4 bits = 0.5 byte. This would need half a byte. But the smallest memory unit is a byte. So how does int4 work ?
- float : 32 bits = 4 bytes
- double: 64 bits = 8 bytes

### 💡 HOW DOES INT4 (half a byte) WORK if 1 BYTE is THE SMALLEST UNIT OF MEMORY ?
A short summary is:

**Memory is byte-addressable, not type-addressable. INT4 works by packing two 4-bit values into a single byte.**

- Memory addresses still point to 1 byte (8 bits).
- An INT4 value occupies only half of a byte, so it cannot have its own address.
- Instead, two INT4 values are packed into one byte.
- During inference, the CPU/GPU/NPU reads the byte and unpacks the two INT4 values before performing computations.
- Specialized AI hardware can unpack and process many INT4 values in parallel, making INT4 both memory-efficient and fast.**




## --------------------------------------THE END -----------------------------------------