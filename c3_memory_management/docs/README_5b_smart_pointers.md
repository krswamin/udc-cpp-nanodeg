# 1) SMART POINTERS
- smart pointers are a raii wrapper around raw pointers
- corner stone of modern c++ memory management, helps avoid a lot of the major problems that arise from dealing with raw pointers. They save a lot of COGNITIVE OVERLOAD, & saves a lot of bugs
- smart pointes support both single memory ownership and shared memory ownership
    - std:: unique_ptr for exclusive ownership / single memory ownership
    - std:: shared_ptr for shared memory ownership

## 1.1) Unique Ptr
Unique pointer is used for accessing + managing dynamically allocated memory, with **exclusive ownership** i.e they maintain exclusive ownership to the allocated resources
![alt text](readme_imgs/smart_pointers/unique_ptr.png)

## 1.2) Shared Ptr
Shared Pointer: Definition
![alt text](readme_imgs/smart_pointers/shared_ptr_definition.png) 


### 1.2.1) Shared Ptr: Use Cases
- for shared ownership: multiple things own object
- for factory functions: factory function creates an object and multiple shared pointers to the object for those that need (like a factory that churns out shared pointers)
- data structures: graphs and nodes etc. where there might be multiple parents and multiple children
![alt text](readme_imgs/smart_pointers/shared_ptr_when_to_use.png)

### 1.2.2) Shared Ptr: Control Block
see section 3.2

## 1.2.3) Shared Ptr: Circular References
This is very common in graph structures, and parent child relationships
![alt text](readme_imgs/smart_pointers/shared_ptr_circular_references1.png) 

Instead of using two shared pointers referencing each other, it might be better to use on shared pointer and one weak pointer
![alt text](readme_imgs/smart_pointers/shared_ptr_circular_references2.png)

## 1.3) Weak Pointer
[L5_smart_memory_management/ksw_demo3_weak_ptr_simple_example.cpp](../L5_smart_memory_management/ksw_demo3_weak_ptr_simple_example.cpp)

- Weak pointer is for observing: without  owning
- weak pointers **CAN BE CREATED FROM SHARED POINTERS ONLY, OR FROM OTHER COMPATIBLE WEAK POINTERS** 

```
auto shared = std::make_shared<Student>();
std::weak_ptr<Student> weak1 = shared;
std::weak_ptr<Student> weak2 = weak1;
```
![alt text](readme_imgs/smart_pointers/weak_ptr.png)

## 1.3.1) Weak Ptr: Use Cases
![alt text](readme_imgs/smart_pointers/weak_ptr_use_cases.png)

## 1.3.2) Weak Ptr: lock() ( generates a shared pointer though)
- weak_ptr::lock() is not an exclusive lock like a mutex. The name can be misleading. lock(), infact, returns a shared pointer , 
    It means: “If the object still exists, create another shared_ptr that shares ownership of it.”\
    Therefore, locked2 succeeds precisely because the object is still alive. Multiple shared_ptrs are allowed to own the same object.\
    In your code, the ownership count changes like this:

    **test1: use count changes**

    | Point in execution              | Shared owners      |       `use_count()` |
    | ------------------------------- | ------------------ | ------------------: |
    | `shared` is created             | `shared`           |                   1 |
    | `print_shared_info(shared)`     | `shared`           |                   1 |
    | `weak1 = shared`                | `shared`           |                   1 |
    | `print_shared_info(shared)`     | `shared`           |                   1 |
    | Enter `print_weak_info(weak1)`  | `shared`           |                   1 |
    | `locked = weak.lock()`          | `shared`, `locked` |                   2 |
    | Return from `print_weak_info()` | `shared`           |                   1 |
    | `weak2 = shared`                | `shared`           |                   1 |
    | Enter `print_weak_info(weak2)`  | `shared`           |                   1 |
    | `locked = weak.lock()`          | `shared`, `locked` |                   2 |
    | Return from `print_weak_info()` | `shared`           |                   1 |
    | End of `test1()`                | no shared owners   | 0; object destroyed |

![alt text](readme_imgs/smart_pointers/weak_ptr_lock.png)

## 2) OWNERSHIP SEMANTICS
What should you define , with type of pointer \
**unique_ptr:**
  - There is no default copy constructor, copy-assignment-operator: you can leave at this, in which case no copying is possible(no shallow copy, no deep copy). **you can only move , this is called transferring ownership**
  - **custom deep copy :** you can define custom copy constructors, custom copy-assignment operators, that perform deep copying. it preserves unique_ptr semantics
**shared_ptr:**
  - The default copy constructor, copy-assignment-operator:  this does a *SHALLOW COPY** you can leave at this, in which case no copying is possible(no shallow copy, no deep copy)
  - custom deep copy : you can define custom copy constructors, custom copy-assignment operators. it preserves unique_ptr semantics

## 3) CONTROL BLOCKS

### 3.1) CONTROL BLOCKS: unique_ptr
unique_ptrs don't have a control block, since ownership is unique

### 3.2) CONTROL BLOCKS: shared_ptr
Only shared pointers have control blocks. \
Control Block consists of the following
- reference count: use_count()
- weak reference count: **THIS IS NOT ACCESSIBLE**
- deleter
Note: When you create a weak pointer from a shared pointer, and do 
weak_ptr.use_count, **it does not give the weak reference count i.e the number of weak pointers. it gives the use_count, i.e the number of shared pointers. There is no way to get the number of weak pointers (fact check this statement please on weak pointer count?? ). This is pretty confusing, but re-read it and see relevant code to wrap your head around it.**
![alt text](readme_imgs/smart_pointers/shared_ptr_control_block.png) 

```
shared_ptr object
┌──────────────────────────┐
│ Pointer to managed object│─────────────┐
│ Pointer to control block │──────┐      │
└──────────────────────────┘      │      │
                                  ▼      ▼
                     Control block       Managed object
                     ┌────────────────┐   ┌────────────┐
EXPOSED indirectly → │ Strong count   │   │ Object     │
NOT EXPOSED        → │ Weak count     │   │ data       │
EXPOSED conditionally│ Deleter        │   └────────────┘
NOT EXPOSED        → │ Allocator      │
NOT EXPOSED        → │ Other metadata │
                     └────────────────┘

```

### 3.3) CONTROL BLOCKS: weak_ptr
weak pointer does not have a separate control block. It shares a control block with shared pointers

```
shared_ptr                         weak_ptr
┌──────────────────────┐          ┌──────────────────────┐
│ object pointer       │───► Obj  │ observed pointer     │───► Obj*
│ control-block pointer│────┐     │ control-block pointer│────┐
└──────────────────────┘    │     └──────────────────────┘    │
                            └────────────┬─────────────────────┘
                                         ▼
                               Shared control block
                               ┌────────────────────────┐
EXPOSED indirectly ──────────► │ Strong count           │
NOT EXPOSED ─────────────────► │ Weak/internal count    │
EXPOSED conditionally ───────► │ Custom deleter         │
NOT EXPOSED ─────────────────► │ Allocator information  │
NOT EXPOSED ─────────────────► │ Internal metadata      │
                               │ Possibly object storage│
                               └────────────────────────┘

```



### 3.4) IMPORTANT INSIGHT: what happens when shared_ptr is destroyed


What happens when shared_ptr is destroyed, but the weak_ptrs still exist. What happens to the weak pointers and control blocks? \
When the strong count reaches zero, the object is destroyed. The control block remains alive as long as weak references still need it.
## CODE
- [L5_smart_memory_management/ksw_demo2a_raw_ptrs.cpp](../L5_smart_memory_management/ksw_demo2a_raw_ptrs.cpp)  
- [L5_smart_memory_management/ksw_demo2b_unique_ptr_with_custom_copy.cpp](../L5_smart_memory_management/ksw_demo2b_unique_ptr_with_custom_copy.cpp) 
- [L5_smart_memory_management/ksw_demo2c_unique_ptr_without_custom_copy.cpp](../L5_smart_memory_management/ksw_demo2c_unique_ptr_without_custom_copy.cpp) 
- [L5_smart_memory_management/ksw_demo2d_shared_ptr.cpp](../L5_smart_memory_management/ksw_demo2d_shared_ptr.cpp) 

**ksw_demo2a_raw_ptrs.cpp**
- uses raw pointers , **new, and delete**: hence it is not desirable
- obeys the rule of 5. so implements the following
    - custom destructor
    - custom copy constructor
    - custom copy assignment operator
    - custom move constructor
    - custom move assignment operator

**ksw_demo2b_unique_ptr_with_custom_copy.cpp**
- replaces the raw pointers ksw_demo2a_raw_ptrs.cpp with **unique_ptr**
- obeys the rule of 5. The following are default 
    - default destructor
    - default move constructor
    - default move assignment operator
- The following are custom implementations: unique_ptr cannot be copied, so no defaults exist for the following copy constructor & copy assignement operator. Custom ones are needed for deep copy
    - custom copy constructor: this implement deep copy, 
    - custom copy assignment operator: this implements


 **ksw_demo2c_unique_ptr_without_custom_copy.cpp**
- replaces the raw pointers ksw_demo2a_raw_ptrs.cpp with **unique_ptr**
- Only the following defaults exist
    - default destructor
    - default move constructor
    - default move assignment operator
- The following are custom implementations: unique_ptr cannot be copied, so no defaults exist for the following. Custom ones are needed for deep copy
    - custom copy constructor: this implement deep copy, 
    - custom copy assignment operator: this implements


 **ksw_demo2d_shared_ptr.cpp**
- replaces the raw pointers ksw_demo2a_raw_ptrs.cpp with **shared_ptr**
- obeys the Rule of zero: no need to define anything custom , defaults exist for everything
    - default destructor
    - default copy constructor
    - default copy assignment operator
    - default move constructor
    - default move assignment operator
- because of the shared_ptr, the default copy and copy assignment are not deep copies. This creates a shallow, shared-ownership copy:
        ```
        c1.engine_ptr1 ──┐
                        ├──> same Engine
        c2.engine_ptr1 ──┘

        ```
- you could possibly define deep copying custom-copy-constructors and custom-copy-assignment-operators, but that would completely mess up the shared pointer / shared owner semantics


  

**Testing: UNIQUE_PTR, SHARED_PTR**
 - i)  printing the address of the pointers
 - ii) use static_assert to see if copying, copy-assignment, moving, move-assignments are possible. 
       - unique ptrs: copying, copy-assignment are POSSIBLE IF AND ONLY IF custom deep copy methods have been defined. so it is possible in ksw_demo2b_unique_ptr_with_custom_copy.cpp. It is not possible for ksw_demo2c_unique_ptr_without_custom_copy.cpp
 - iii) use reference count: 
        - reference count only exists for shared_ptrs. 
        - reference_count **DOES NOT EXIST** for unique_ptrs