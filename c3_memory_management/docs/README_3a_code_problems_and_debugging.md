# 👺 I) COMMON CPP PROBLEMS

Indvidual Problems
- 🚨 1) STACK           : Stack Overflow
- 😐 2) STACK           : Stack Buffer Overflow
- 😐 3) STACK           : Invalid Stack Pointer
- 😐 4) HEAP            : Heap Overflow/ Heap Buffer Overflow
- 🚨 5) HEAP            : Memory Leak
- 🚨 6) HEAP &/or STACK : Dangling Pointer 
- 🚨 7) HEAP &/or STACK : Other Pointer Problems

Compound Problems (can have any 1 of multiple root causes)
- 😐  8) HEAP                                 : Heap Exhaustion
- 🚨  9) ~~STACK~~, HEAP &/or OTHER LOCATIONS : OOM- Out of Memory OOM
- 🚨 10) HEAP &/or STACK                      : Segmentation Fault

Key
- 🚨 : Very famous and Very common Problem
- 😐 : Maybe/Maynot be common. But not Famous

A lot of these problems are inter-related 
Also See 
- 
- Discussion on stack and heap problems , see  [c3_memory_management/docs/README_4_code_debugging.md](README_4_code_debugging.md)



## INDIVIDUAL PROBLEMS/ STAND ALONE PROBLEMS
## 👺 1) STACK: STACK OVERFLOW 
When stack outgrows the stack area in the virtual address spaces. This can occur in one of the following ways
    - if you allocate a very large array (RARE)
    - very deep recursion (MOST COMMON CAUSE)
      ```
          void recurse()
          {
              recurse();
          }
      ```

**DIAGNOSIS**
-  Stack overflow **does not cause of Out Of Memory Error** (although it seems like it fits the bill). It does not cause - Out of Memory (std::bad_alloc) , (C++ cannot throw an excpetion see below why)
- A stack overflow could cause a seg fault, though not always. 
  - On Linux/macOS, a stack overflow usually appears as a segmentation fault (SIGSEGV).
  - On Windows, it typically appears as a stack overflow exception (STATUS_STACK_OVERFLOW, code 0xC00000FD)
- A stack overflow is a hardware/operating system exception, not a C++ exception.
  - Once the stack has overflowed, there usually isn't enough stack space left to safely execute more code, including exception handling.The operating system therefore terminates the process.
- **GDB** : 
  - When a stack overflow occurs the code just ends abruptly
  - Can be diagnosed using GDB, you can traceback at what point the code exited and keep stepping backwards (though ask chatgpt for more modern tools)


## 👺 2) STACK BUFFER OVERFLOW (less famous problem)
- writing beyond a stack-allocated array. 
- This probably occurs pretty often, but its just not as famous.
   ```
    void foo()
    {
        int arr[10];
        arr[100] = 5;
    }
  ```

## 👺 3) INVALID STACK POINTER (less famous problem)
- That address doesn't belong to your program.
- Not sure if this happens at all or its just sth that chatgpt contrived. Not very famous though
  ```
  int* p = (int*)0x12345678;
  *p = 5;
  ```
\
\
\
## 👺 4) HEAP: HEAP OVERFLOW = HEAP BUFFER OVERFLOW
This is a very common point of confusion between stack overflow and heap overflow
- ❌ HEAP OVERFLOW **does not** mean running out of heap space. (Running out of heap space is in fact calle HEAP EXHAUSTION , and is a different problem). See section on HEAP EXHAUSTION)
- ✅ Heap overflow means writing past the end of a heap-allocated object.
    ```
    int* arr = new int[10];
    arr[100] = 5;
    ```

**DIAGNOSIS**
There is no single guaranteed outcome. 
- The program may crash immediately . This crash might or might not be a seg fault. see error message to determine error

| Message                            | Meaning                                                           |
| ---------------------------------- | ----------------------------------------------------------------- |
| `Segmentation fault (core dumped)` | Invalid memory access (SIGSEGV)                                   |
| `Aborted (core dumped)`            | Program called `abort()` or runtime detected corruption (SIGABRT) |
| `malloc(): corrupted top size`     | Heap allocator detected heap corruption                           |
| `double free or corruption`        | Heap allocator detected an invalid free or corrupted metadata     |
| Windows: `0xC0000005`              | Access violation                                                  |


- appears to work , but silently silently corrupt data overtime, but no crash at all. Just corrupted data over time. THIS IS DANGEROUS ⚠️
- appears to work , but silently silently corrupt data overtime, crashes . THIS IS DANGEROUS ⚠️
  - The program appears to work. Five minutes later it crashes somewhere completely unrelated because the earlier overflow corrupted memory.

Yeah I am copy pasting the same errors agaIn. But the takeaway is this ivalid memory access could have occured way earlier, not just at the crashing point. So when you get errors, you'd have to be astute + experienced enough to know if the root cause is immediate/ runs far deeer
| Message                            | Meaning                                                           |
| ---------------------------------- | ----------------------------------------------------------------- |
| `Segmentation fault (core dumped)` | Invalid memory access (SIGSEGV)                                   |
| `Aborted (core dumped)`            | Program called `abort()` or runtime detected corruption (SIGABRT) |
| `malloc(): corrupted top size`     | Heap allocator detected heap corruption                           |
| `double free or corruption`        | Heap allocator detected an invalid free or corrupted metadata     |
| Windows: `0xC0000005`              | Access violation                                                  |


\
\
\



## 👺👺👺 5) HEAP: MEMORY LEAK (THE MOST FAMOUS PROBLEM )

- MEMORY LEAKS IN C++ OCCUR ON THE HEAP ONLY
- You allocated heap memory when you needed it, but failed to deallocate it properly when it was no longer needed it. THIS IS A MEMORY LEAK.
- PRACTICALLY: There was a pointer to a part of the heap/ dynamically allocated memory . That pointer was lost. Hence that memory becomes permanently inaccessible for the duration of the program.  
  - That LEAKED MEMORY IS NOT ACCESSIBLE EVEN WHEN THE FUNCTION EXITS, ITS NOT AVALIABLE EVEN WHEN MAIN EXITS i.e at the } closing bracket of main
  - The process that called main will exit at some point. Then the OPERATING SYSTEM RECALIMS ALL THE PROCESSES MEMORY WHEN THE PROCESS EXITS (i.e. its not a permanent memory leak on the hardware)
- **HOUSE & HOUSE NUMBER ANALOGY:** There was a house (heap memory location), and a house number (the pointer). The house lost the house number/address. The house still exists but no way to reach it 
```
Start        :  ✅🔢(pointer) -----------> ✅🏠(heap memory)
Memory Leak  :  ❌            -----❌----> ✅🏠(heap memory)
```

## 👺 5.1) POINTERS : MEMORY LEAK ON STACK
❌ MEMORY LEAK IN C++ DOES NOT OCCUR ON THE STACK

## 👺 5.2) POINTERS : MEMORY LEAK ON HEAP
MEMORY LEAK IN C++ OCCUR ON THE HEAP ONLY
- See T2_dynamic_memory_allocation/memory_leak_demo.cpp
- Pay attention to all 4 cases in the code in memory_leak_demo.cpp

## 👺 5.3) Is a Memory Leak in main() really a memory leak
Question: Is a Memory Leak in main() really a memory leak ?. At the end of main the memory is released anyway ? \
Answer: 
- Yes a memory leak is a leak no matter where. A memory leak in main is not released by the program . You have to rely on the operating system to release it when the process exits. This is not good. Imagine the leaky code ran in a loop on  a server ! It would cause the server to crash !
- See T2_dynamic_memory_allocation/memory_leak_demo.cpp- Case 4
- See  README_2a_cpp_pointers.md/ Example 1.2: MEMORY LEAK DISCUSSION

## 👺 5.4) MEMORY LEAK IS SLOW DEATH 😆 THAT CAN BE AVOIDED !
- Memory leak is like slow death, because small memory leaks dont cause immediate crashes, but it could crash later making diagnosis confusing. 
 - memory could have leaked in an older part of the code, and a genuine heap allocation could crash
 - if you find your code inconsistently crashing in random parts of the code, it could signal a memory leak in an earlier part of the code
-  Here some examples of how memory leaks could occur
    - you have badly written leaky code
    - if you have a small memory leak and the code runs on a server / in a loop. 
    - In autonomous vehicles if you acquire a very large frame of data such as lidar where the data volume is typically large (Note: lidar point clouds , though large are typically accounted for in the perception stack design. A point cloud that is larger than usual typically indicates a bug/error etc that needs investigation )

## 👺 5.5) MEMORY LEAK: DIAGNOSIS 
- you can use valgrind to diagnose memory leaks
- address sanitizer is great as well. 
- see below section on debugging tools

\
\
\

## 👺 6) HEAP &/or STACK: DANGLING POINTERS 
Dangling Pointers:
- unlike memory leaks in c++ which are always with the heap(dynamically allocated memory), dangling pointers in c++ can be on the stack, heap, global/static data. BASICALLY ANYWHERE! 🤯
- You allocated heap memory , using a pointer when you needed it. Once the memory is no longer needed, you delat with the memory,  but failed to deal with the pointer. THIS IS A DANGLING POINTER.
- When the memory that a pointer points to has been released , but the pointer is still alive that is a dangling pointer . **The pointer and the memory that it points to have independent lifetimes and scope.** This **is the root issue
- **HOUSE & HOUSE NUMBER ANALOGY:** Its like telling that there is a house number, but no house there though

```
Start             :  ✅🔢(pointer) -----------> ✅🏠(heap memory)
Dangling Pointer  :  ✅🔢(pointer) -----❌---->      ❌
```


### 👺 6.1) POINTERS : DANGLING POINTERS ON STACK
- this typically involved returning a local pointer on the call stack
- see  T2_dynamic_memory_allocation/dangling_pointer1_stack_demo.cpp

### 👺 6.2) POINTERS : DANGLING POINTERS ON HEAP
- see  T2_dynamic_memory_allocation/dangling_pointer2_heap_demo.cpp

```
int* p = new int(42);
delete p;
*p = 10;      // Invalid
```

| Pointer stored in | Pointing to | Object destroyed?      | Dangling?  |
| ----------------- | ----------- | ---------------------- | ---------  |
| Stack             | Heap        | Yes (`delete`)         | ✅         |
| Stack             | Stack       | Yes (function returns) | ✅         |
| Heap              | Heap        | Yes (`delete`)         | ✅         |
| Global            | Stack       | Yes (function returns) | ✅         |
| Global            | Heap        | Yes (`delete`)         | ✅         |

## 👺 7) HEAP &/or STACK: OTHER POINTER PROBLEMS
- 1) The 3 musketeer problem pointers 
   - **dereferencing dangling pointer:** Already discussed above
   - **dereferencing null pointer:** causes seg fault
   - **dereferencing uninitalized pointer:** causes undefined behaviour. If it ends up accessing memory that does not belong to your process, it causes seg fault
      ```
      int* ptr;
      *ptr = 10;     // Undefined behavior
      ```
   - 
- 2) **accessing an array out of bounds:** causes undefined behaviour. If it ends up accessing memory that does not belong to your process, it causes seg fault
      ```
      int a[10];
      a[1000] = 10;     // Undefined behavior
 - 3) **double deletion of a pointer:** undefined behaviour. many different outcomes possible
     - could cause seg fault
     - seeming to work immediately, crashing later
     - corrupting the heap.
     **EXCEPTION TO DOUBLE DELETION:**The only time a second deletion is completely safe is if the pointer evaluates to nullptr. Deleting a null pointer in C++ is explicitly guaranteed by the language standard to be a safe "no-op" (it does nothing).

## 👺 COMPOUND PROBLEMS
## 👺 8) HEAP: HEAP EXHAUSTION
- Heap Memory Exhaustion means running out of heap space.
- Heap exhaustion is rare in well designed applicatons.
- Large Memory Leaks are a common cause of Heap Exhaustion 
    - not all memory leaks cause heap exhaustion. Only very large ones typically do
    - A Large sustained Memory Leak is NOT THE ONLY cause of Heap Exhaustion, there could be other reasons
- Heap Exhaustion is a common cause of OOM: Out of Memory Error
    - Heap Exhaustion will 100% cause OOM
    - Heap Exhaustion is not the only cause of OOM, though

| Cause                                 | Common?           | Explanation                                                                       |
| ------------------------------------- | ----------------- | --------------------------------------------------------------------------------- |
| **Memory leaks**                      | ⭐⭐⭐⭐⭐ Very common | Memory is allocated but never freed, so heap usage continuously grows.            |
| **Allocating very large objects**     | ⭐⭐⭐⭐ Common       | A single allocation (or a few large ones) consumes most of the heap.              |
| **Unbounded data structures**         | ⭐⭐⭐⭐ Common       | Containers like `std::vector`, `std::map`, or caches keep growing without limits. |
| **Loading too much data into memory** | ⭐⭐⭐ Common        | Reading huge files or datasets entirely into memory.                              |
| **Infinite allocation loop**          | ⭐⭐⭐ Common        | Code repeatedly calls `new` or grows containers indefinitely.                     |
| **Memory fragmentation**              | ⭐⭐ Less common    | Enough total free memory exists, but not as one large contiguous block.           |
| **Process/container memory limits**   | ⭐⭐ Less common    | Docker, embedded systems, or OS limits prevent further allocations.               |


## 9) OOM: Out of Memory
| Situation                       | OOM?  | Heap exhausted?   |
| ------------------------------- | ----- | ----------------- |
| Heap completely full            | ✅ Yes | ✅ Yes             |
| Process memory limit reached    | ✅ Yes | ❌ Not necessarily |
| Virtual address space exhausted | ✅ Yes | ❌ Not necessarily |
| Memory fragmentation            | ✅ Yes | ❌ Not necessarily |
| OS refuses allocation           | ✅ Yes | ❌ Not necessarily |
| Stack overflow                  | ❌ No  | ❌ No              |


## 👺 10) SEGMENTATION FAULT: 

```
Segmentation fault (core dumped)
```
 - when u access invalid/illegal memory, that is a seg fault. 
 - can occur on the stack or heap
 - it could occur due to any of the following reasons. But **MEMORY LEAK IS NOT ONE OF THEM** Because a memory leak could not have accesses illegal memory

Categorizing them
- Usually causes a segfault
  - ✅ Stack overflow
  - ✅ Invalid stack pointer
  - ✅ Dereferencing nullptr
  - ✅ Dereferencing a wild pointer
Sometimes causes a segfault
  - ✅ Stack buffer overflow
  - ✅ Heap buffer overflow
  - ✅ Dangling pointer dereference
  - ✅ Out-of-bounds access
- DOES NOT CAUSE SEGFAULT/RARE
  - ❌ Memory leak: does not cause
  - ❌ Heap exhaustion: does not cause
  - ❌ OOM: does not cause
  - ❌ Double deletion : more often heap corruption/abort, than segfault




| #                                                                | Error               |                                                        Can cause a Segmentation Fault?                                                       | Notes |
| ---------------------------------------------------------------- | ------------------- | :------------------------------------------------------------------------------------------------------------------------------------------: | ----- |
| 🚨 **1)** Stack Overflow                                         | ✅ **Usually**       |             The stack grows into an unmapped guard page, causing a segfault (Linux/macOS) or `STATUS_STACK_OVERFLOW` on Windows.             |       |
| 😐 **2)** Stack Buffer Overflow                                  | ✅ **Sometimes**     |              Writing past a local array may overwrite valid stack memory (no immediate crash) or hit an invalid page (segfault).             |       |
| 😐 **3)** Invalid Stack Pointer                                  | ✅ **Usually**       |                       Using a corrupted or invalid stack pointer typically causes invalid memory accesses and crashes.                       |       |
| 😐 **4)** Heap Buffer Overflow                                   | ✅ **Sometimes**     |                                May segfault immediately, corrupt the heap and crash later, or appear to work.                                |       |
| 🚨 **5)** Memory Leak                                            | ❌ **No (directly)** |                                      Causes heap growth and possibly OOM, but not a segfault by itself.                                      |       |
| 🚨 **6)** Dangling Pointer                                       | ✅ **Sometimes**     |                      Dereferencing freed memory is undefined behavior. It may segfault, corrupt data, or appear to work.                     |       |
| 🚨 **7)** Null/Wild Pointer, Double Delete, Out-of-Bounds Access | **Mixed:**          |                                                             See breakdown below.                                                             |       |
| 😐 **8)** Heap Exhaustion                                        | ❌ **No (directly)** |                                  Causes allocation failure (`std::bad_alloc` or `nullptr`), not a segfault.                                  |       |
| 🚨 **9)** Out of Memory (OOM)                                    | ❌ **No (directly)** | Allocation failure or process termination. Can lead to a segfault only if the program mishandles the failure (e.g., dereferences `nullptr`). |       |


### Breaking Down #7


| Error                         | Can cause a Segmentation Fault? | Notes                                                                                                                           |
| ----------------------------- | :-----------------------------: | ------------------------------------------------------------------------------------------------------------------------------- |
| Dereferencing `nullptr`       |          ✅ **Usually**          | Null page is typically unmapped.                                                                                                |
| Dereferencing a wild pointer  |          ✅ **Usually**          | Random address often isn't mapped, though not guaranteed.                                                                       |
| Double deletion               |        ❌ **Not directly**       | More commonly causes heap corruption or an abort. It can lead to later crashes, including segfaults, due to undefined behavior. |
| Accessing beyond array bounds |         ✅ **Sometimes**         | Depends on whether the access stays within mapped memory.                                                                       |


# ------------------------------------------------------------------------




# 👺 II) CODE DEBUGGING TOOLS


The belowimage is for debugging dangling pointers. But it Works for all problems
![alt text](readme_imgs/cpp_pointers/debugging_dangling_pointers.png)

## 👺 2.1) ADDRESS SANITIZER : ANALYZING MEMORY LEAKS/ DANGLING POINTER

## 👺 1.1) ADDRESS SANITIZER: DANGLING POINTER ON STACK
- code in T2_dynamic_memory_allocation/dangling_pointer1_stack_demo.cpp
- run the following in a terminal


#### 👺 Address sanitizer 
- identifies correctly that the problem is on the stack: **stack-use-after-return on address 0x7654dcf00020 at ...**
- points to the wrong line of code **in returnPointer() /home/kssn/MOOC/udacity/udc-cpp-nanodeg/c3_memory_management/dangling_pointer1_stack_demo.cpp:14**


```
kssn@kssn-katana1:~/MOOC/udacity/udc-cpp-nanodeg/c3_memory_management$ g++ -std=c++17     -g     -O0     -Wall     -Wextra     -fsanitize=address,undefined     -fno-omit-frame-pointer     dangling_pointer1_stack_demo.cpp -o dangling_pointer1_stack_demo_address_sanitized.out
kssn@kssn-katana1:~/MOOC/udacity/udc-cpp-nanodeg/c3_memory_management$ ./dangling_pointer1_stack_demo_address_sanitized.out 
```


#### 👺 This is the output
```
returnPointer function:  a=10
returnPointer function: *p=10
returnPointer function:  p=0x7654dcf00020
Notice that the value of *p is junk, because its a dangling pointer
Notice that the value of p itself, which is an address is valid. Since the return by value(of the value of p) from the function works properly.
 REMINDER: return by value in c++ always works correctly ! Reread that if you didnt follow !
=================================================================
==13079==ERROR: AddressSanitizer: stack-use-after-return on address 0x7654dcf00020 at pc 0x5f8d9796013a bp 0x7ffeb600ff80 sp 0x7ffeb600ff70
READ of size 4 at 0x7654dcf00020 thread T0
    #0 0x5f8d97960139 in main /home/kssn/MOOC/udacity/udc-cpp-nanodeg/c3_memory_management/dangling_pointer1_stack_demo.cpp:31
    #1 0x7654df02a1c9 in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58
    #2 0x7654df02a28a in __libc_start_main_impl ../csu/libc-start.c:360
    #3 0x5f8d9795f244 in _start (/home/kssn/MOOC/udacity/udc-cpp-nanodeg/c3_memory_management/dangling_pointer1_stack_demo_address_sanitized.out+0x3244) (BuildId: 7676ad98a8819aa613edf622e1fd45fb89e3a814)

Address 0x7654dcf00020 is located in stack of thread T0 at offset 32 in frame
    #0 0x5f8d9795f318 in returnPointer() /home/kssn/MOOC/udacity/udc-cpp-nanodeg/c3_memory_management/dangling_pointer1_stack_demo.cpp:14

  This frame has 1 object(s):
    [32, 36) 'a' (line 15) <== Memory access at offset 32 is inside this variable
HINT: this may be a false positive if your program uses some custom stack unwind mechanism, swapcontext or vfork
      (longjmp and C++ exceptions *are* supported)
SUMMARY: AddressSanitizer: stack-use-after-return /home/kssn/MOOC/udacity/udc-cpp-nanodeg/c3_memory_management/dangling_pointer1_stack_demo.cpp:31 in main
Shadow bytes around the buggy address:
  0x7654dceffd80: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7654dceffe00: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7654dceffe80: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7654dcefff00: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7654dcefff80: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
=>0x7654dcf00000: f5 f5 f5 f5[f5]f5 f5 f5 00 00 00 00 00 00 00 00
  0x7654dcf00080: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7654dcf00100: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7654dcf00180: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7654dcf00200: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x7654dcf00280: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
Shadow byte legend (one shadow byte represents 8 application bytes):
  Addressable:           00
  Partially addressable: 01 02 03 04 05 06 07 
  Heap left redzone:       fa
  Freed heap region:       fd
  Stack left redzone:      f1
  Stack mid redzone:       f2
  Stack right redzone:     f3
  Stack after return:      f5
  Stack use after scope:   f8
  Global redzone:          f9
  Global init order:       f6
  Poisoned by user:        f7
  Container overflow:      fc
  Array cookie:            ac
  Intra object redzone:    bb
  ASan internal:           fe
  Left alloca redzone:     ca
  Right alloca redzone:    cb
==13079==ABORTING
kssn@kssn-katana1:~/MOOC/udacity/udc-cpp-nanodeg/c3_memory_management$ 

```

#### 👺 As a contrast you can run the same code without the address sanitizer options and see what happens
  - my code didnt crash . just printed out junk


```
kssn@kssn-katana1:~/MOOC/udacity/udc-cpp-nanodeg/c3_memory_management$ g++ -std=c++17 dangling_pointer1_stack_demo.cpp -o dangling_pointer1_stack_demo.out
kssn@kssn-katana1:~/MOOC/udacity/udc-cpp-nanodeg/c3_memory_management$ ./dangling_pointer1_stack_demo.out 
returnPointer function:  a=10
returnPointer function: *p=10
returnPointer function:  p=0x7ffed6edca3c
 

main function: Notice that the value of p itself, which is an address is valid/ correct. This is because the return by value(of the value of p) from the function works properly.(REMINDER: return by value in c++ always works correctly ! Reread that if you didnt follow !) 
main function: HOWEVER THOUGH THE DEREFERENCING IS JUNK. The value of *p is junk, because its a dangling pointer 

main function: *p=31691
main function:  p=0x7ffed6edca3c
```

## 👺 1.2) ADDRESS SANITIZER: DANGLING POINTER ON HEAP
- uncomment line 28,29 in T3_pointers_and_pointer_arithmetic/dangling_pointer2_heap_demo.cpp
- run the following in a terminal


#### 👺 Address sanitizer 
- - identifies correctly that the problem is on the heap: **heap-use-after-free on address 0x502000000010 ...**
- points to the wrong line of code **createDanglingPointer() /home/kssn/MOOC/udacity/udc-cpp-nanodeg/c3_memory_management/dangling_pointer2_heap_demo.cpp:28**




```
kssn@kssn-katana1:~/MOOC/udacity/udc-cpp-nanodeg/c3_memory_management$ g++ -std=c++17 \
    -g \
    -O0 \
    -Wall \
    -Wextra \
    -fsanitize=address,undefined \
    -fno-omit-frame-pointer \
    dangling_pointer2_heap_demo.cpp -o dangling_pointer2_heap_demo.out

 ASAN_OPTIONS=detect_leaks=1 ./dangling_pointer2_heap_demo.out
 ```

 #### 👺 This is the output of address sanitizer
 ```
 kssn@kssn-katana1:~/MOOC/udacity/udc-cpp-nanodeg/c3_memory_management$ ASAN_OPTIONS=detect_leaks=1 ./dangling_pointer2_heap_demo.out 
--- Demonstrating a Dangling Pointer ---
Allocated memory for an integer at address: 0x502000000010
Memory at 0x502000000010 has been freed.
The pointer 'ptr' is now a dangling pointer.
=================================================================
==11263==ERROR: AddressSanitizer: heap-use-after-free on address 0x502000000010 at pc 0x59484719dc95 bp 0x7fff4deb1b00 sp 0x7fff4deb1af0
READ of size 4 at 0x502000000010 thread T0
    #0 0x59484719dc94 in createDanglingPointer() /home/kssn/MOOC/udacity/udc-cpp-nanodeg/c3_memory_management/dangling_pointer2_heap_demo.cpp:28
    #1 0x59484719e7f6 in main /home/kssn/MOOC/udacity/udc-cpp-nanodeg/c3_memory_management/dangling_pointer2_heap_demo.cpp:65
    #2 0x761ae702a1c9 in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58
    #3 0x761ae702a28a in __libc_start_main_impl ../csu/libc-start.c:360
    #4 0x59484719d244 in _start (/home/kssn/MOOC/udacity/udc-cpp-nanodeg/c3_memory_management/dangling_pointer2_heap_demo.out+0x4244) (BuildId: 90a26c1c91ffff4cc3a3416a6a7c9922eeaba344)

0x502000000010 is located 0 bytes inside of 4-byte region [0x502000000010,0x502000000014)
freed by thread T0 here:
    #0 0x761ae80ff5e8 in operator delete(void*, unsigned long) ../../../../src/libsanitizer/asan/asan_new_delete.cpp:164
    #1 0x59484719d735 in createDanglingPointer() /home/kssn/MOOC/udacity/udc-cpp-nanodeg/c3_memory_management/dangling_pointer2_heap_demo.cpp:16
    #2 0x59484719e7f6 in main /home/kssn/MOOC/udacity/udc-cpp-nanodeg/c3_memory_management/dangling_pointer2_heap_demo.cpp:65
    #3 0x761ae702a1c9 in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58
    #4 0x761ae702a28a in __libc_start_main_impl ../csu/libc-start.c:360
    #5 0x59484719d244 in _start (/home/kssn/MOOC/udacity/udc-cpp-nanodeg/c3_memory_management/dangling_pointer2_heap_demo.out+0x4244) (BuildId: 90a26c1c91ffff4cc3a3416a6a7c9922eeaba344)

previously allocated by thread T0 here:
    #0 0x761ae80fe548 in operator new(unsigned long) ../../../../src/libsanitizer/asan/asan_new_delete.cpp:95
    #1 0x59484719d464 in createDanglingPointer() /home/kssn/MOOC/udacity/udc-cpp-nanodeg/c3_memory_management/dangling_pointer2_heap_demo.cpp:10
    #2 0x59484719e7f6 in main /home/kssn/MOOC/udacity/udc-cpp-nanodeg/c3_memory_management/dangling_pointer2_heap_demo.cpp:65
    #3 0x761ae702a1c9 in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58
    #4 0x761ae702a28a in __libc_start_main_impl ../csu/libc-start.c:360
    #5 0x59484719d244 in _start (/home/kssn/MOOC/udacity/udc-cpp-nanodeg/c3_memory_management/dangling_pointer2_heap_demo.out+0x4244) (BuildId: 90a26c1c91ffff4cc3a3416a6a7c9922eeaba344)

SUMMARY: AddressSanitizer: heap-use-after-free /home/kssn/MOOC/udacity/udc-cpp-nanodeg/c3_memory_management/dangling_pointer2_heap_demo.cpp:28 in createDanglingPointer()
Shadow bytes around the buggy address:
  0x501ffffffd80: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x501ffffffe00: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x501ffffffe80: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x501fffffff00: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x501fffffff80: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
=>0x502000000000: fa fa[fd]fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x502000000080: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x502000000100: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x502000000180: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x502000000200: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x502000000280: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
Shadow byte legend (one shadow byte represents 8 application bytes):
  Addressable:           00
  Partially addressable: 01 02 03 04 05 06 07 
  Heap left redzone:       fa
  Freed heap region:       fd
  Stack left redzone:      f1
  Stack mid redzone:       f2
  Stack right redzone:     f3
  Stack after return:      f5
  Stack use after scope:   f8
  Global redzone:          f9
  Global init order:       f6
  Poisoned by user:        f7
  Container overflow:      fc
  Array cookie:            ac
  Intra object redzone:    bb
  ASan internal:           fe
  Left alloca redzone:     ca
  Right alloca redzone:    cb
==11263==ABORTING
kssn@kssn-katana1:~/MOOC/udacity/udc-cpp-nanodeg/c3_memory_management$ 

  ```


#### 👺 As a contrast you can run the same code without the address sanitizer options and see what happens
  - my code didnt crash . just printed out junk

```
  kssn@kssn-katana1:~/MOOC/udacity/udc-cpp-nanodeg/c3_memory_management$ g++ -std=c++17 dangling_pointer2_heap_demo.cpp -o dangling_pointer2_heap_demo_address.out

kssn@kssn-katana1:~/MOOC/udacity/udc-cpp-nanodeg/c3_memory_management$ ./dangling_pointer2_heap_demo_address.out 
--- Demonstrating a Dangling Pointer ---
Allocated memory for an integer at address: 0x5db770f906c0
Memory at 0x5db770f906c0 has been freed.
The pointer 'ptr' is now a dangling pointer.
Attempting to read from the dangling pointer: -612954224
The dangerous dereferencing lines are commented out to prevent a crash.

--- Demonstrating Safe Pointer Usage ---
Allocated memory at address: 0x5db770f906c0
Memory freed and pointer set to nullptr.
The pointer is nullptr. This is the safe state.
```

