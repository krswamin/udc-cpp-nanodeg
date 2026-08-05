# 🎯 1) GOLANG's HANDLING of the VIRTUAL ADDRESS SPACE

- The important concept is **virtual address space is provided by the operating system. Hence it is the same for c++, golang, python etc.**
- The main differences are in memory management within that address space:

```
 High Memory Addresses
+-------------------------------------------+
|      Goroutine Stacks                     |
|                                           |
|  Goroutine 1 Stack                        |
|  Goroutine 2 Stack                        |
|  Goroutine 3 Stack                        |
|  ...                                      |
|                                           |
|  (Each starts small and grows/shrinks     |
|   automatically as needed.)               |
+-------------------------------------------+
|                                           |
|          Unused / Free Space              |
|                                           |
+-------------------------------------------+
|               Go Heap                     |
|                                           |
|  - Heap objects                           |
|  - Garbage-collected memory               |
|  - Runtime allocator (spans, caches)      |
|                                           |
+-------------------------------------------+
|       Go Runtime Metadata                 |
|                                           |
|  - GC metadata                            |
|  - Scheduler structures                   |
|  - Heap management structures             |
+-------------------------------------------+
|  BSS Segment                              |
|  Uninitialized package/global variables   |
+-------------------------------------------+
|  Data Segment                             |
|  Initialized package/global variables     |
+-------------------------------------------+
|  Read-only Data (.rodata)                 |
|  String constants, constant tables        |
+-------------------------------------------+
|  Text (Code) Segment                      |
|  Program code + Go runtime code           |
+-------------------------------------------+
 Low Memory Addresses
 ```


## Comparison With C++

| C++                                               | Go                                              |
| ------------------------------------------------- | ----------------------------------------------- |
| One stack per thread                              | One stack per goroutine (many stacks)           |
| Heap managed by `new`/`delete` or `malloc`/`free` | Heap managed by Go runtime + GC                 |
| Programmer frees heap memory                      | Garbage collector frees unreachable heap memory |
| Static/Data/BSS/Text                              | Same concept                                    |


**Important difference #1: STACK**
C++ diagram shows a single stack:
```
Stack
```
In Go, it's better to think of it as:
```
Stacks

+------------------+
| Goroutine #1     |
+------------------+

+------------------+
| Goroutine #2     |
+------------------+

+------------------+
| Goroutine #3     |
+------------------+

```

**Important difference #2: HEAP**
- In C++ HEAP is managed by the programmer
- In golang HEAP is managed by the garbage collector

## -------------------------------- THE END ---------------------------------------------
