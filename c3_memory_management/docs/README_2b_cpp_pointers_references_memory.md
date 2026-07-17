
# 🎯 CPP : POINTERS, REFERENCES, MEMORY
This entire readme deals with pointers, references, heap memory in c++ only

# 🎯 1) POINTERS : MEMORY LEAK 
## ----------------------------------------------------------------------------------------
## ----------------------------------------------------------------------------------------
## ----------------------------------------------------------------------------------------
## ----------------------------------------------------------------------------------------

## 🎯 1.1) POINTERS : MEMORY LEAK ON STACK
## ----------------------------------------------------------------------------------------
## ----------------------------------------------------------------------------------------

## 🎯 1.2) POINTERS : MEMORY LEAK ON HEAP
## ----------------------------------------------------------------------------------------
## ----------------------------------------------------------------------------------------


# 🎯 2) DANGLING POINTERS 
Dangling Pointers:
- When the memory that a pointer points to has been released , but the pointer is still alive that is a dangling pointer . **The pointer and the memory that it points to have independent lifetimes and scope.** This is the root issue
- Its like telling that there is a house number, but no house there though
- dangling pointers can be on the stack, heap, global/static data. basically anywhere


## 🎯 2.1) POINTERS : DANGLING POINTERS ON STACK
- see  T3_pointers_and_pointer_arithmetic/dangling_pointer1_stack_demo.cpp

## 🎯 2.2) POINTERS : DANGLING POINTERS ON HEAP
- see  T3_pointers_and_pointer_arithmetic/dangling_pointer2_heap_demo.cpp

| Pointer stored in | Pointing to | Object destroyed?      | Dangling?  |
| ----------------- | ----------- | ---------------------- | ---------  |
| Stack             | Heap        | Yes (`delete`)         | ✅         |
| Stack             | Stack       | Yes (function returns) | ✅         |
| Heap              | Heap        | Yes (`delete`)         | ✅         |
| Global            | Stack       | Yes (function returns) | ✅         |
| Global            | Heap        | Yes (`delete`)         | ✅         |


# 🎯 4) COMMON POINTER PROBLEMS

1) accessing invalid pointers
    - accessing wild pointers/ uninitalized pointers
    - accessing null pointers
    - accessing dangling pointers
2) double deletion
3) returning local pointers 
4) accessing pointers out of their index



# 🎯 5) CARDINAL RULE WITH POINTERS

1) for dynamic memory: new-delete-nullptr, new[]-delete[]-nullptr: 
2) for static memory: create pointer-assign address-then dereference (otherwise you are accessing a wild pointer)
2) instead of raw pointers try the following alternatives
  - use smart pointers wherever possible
  - use c++ stl containers like <vector>
  - use references whereever possible
4) within functions never return a local pointer??? or a pointer to a local variable. Never return a local reference  either
5) when using a reference, the reference lifetime, scope should end before the memory on heap/ stack ends. Because a DANGLING REFERENCE CANNOT BE REASSIGNED


# 🎯 6) Pointers vs References . When to use what ?

