# ANALYZING MEMORY LEAKS/ DANGLING POINTERS

## 🎯 1) ADDRESS SANITIZER 

## 🎯 1.1) ADDRESS SANITIZER: DANGLING POINTER ON STACK
- code in T3_pointers_and_pointer_arithmetic/dangling_pointer1_stack_demo.cpp
- run the following in a terminal


#### 🎯 Address sanitizer 
- identifies correctly that the problem is on the stack: **stack-use-after-return on address 0x7654dcf00020 at ...**
- points to the wrong line of code **in returnPointer() /home/kssn/MOOC/udacity/udc-cpp-nanodeg/c3_memory_management/dangling_pointer1_stack_demo.cpp:14**


```
kssn@kssn-katana1:~/MOOC/udacity/udc-cpp-nanodeg/c3_memory_management$ g++ -std=c++17     -g     -O0     -Wall     -Wextra     -fsanitize=address,undefined     -fno-omit-frame-pointer     dangling_pointer1_stack_demo.cpp -o dangling_pointer1_stack_demo_address_sanitized.out
kssn@kssn-katana1:~/MOOC/udacity/udc-cpp-nanodeg/c3_memory_management$ ./dangling_pointer1_stack_demo_address_sanitized.out 
```


#### 🎯 This is the output
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

#### 🎯 As a contrast you can run the same code without the address sanitizer options and see what happens
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

## 🎯 1.2) ADDRESS SANITIZER: DANGLING POINTER ON HEAP
- uncomment line 28,29 in T3_pointers_and_pointer_arithmetic/dangling_pointer2_heap_demo.cpp
- run the following in a terminal


#### 🎯 Address sanitizer 
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

 #### 🎯 This is the output of address sanitizer
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


#### 🎯 As a contrast you can run the same code without the address sanitizer options and see what happens
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

