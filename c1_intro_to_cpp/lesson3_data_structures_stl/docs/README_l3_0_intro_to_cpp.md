# Intro to CPP

## Lesson Overview: Takeaway
- DATA STRUCTURES in STL
  - mainly Arrays vs Vectors. 
  - use appropriate containers based on task.
- ITERATORS & ALGOS for STL CONTAINERS  
  - iterators are not pointers. They are objects that behave like pointers
  - use existing algos , dont reinvent the wheel
  - iterators: container.begin() & container.end() [ like vector.begin() & vector.end()].
  - algos like reverse, sort, find, etc. use container.begin() & container.end(). 
  - some algos like find return an iterator as well.  
    - auto it = std::find(v.begin(), v.end(), 42); 
    - the return could be sth diffferent from container.begin() or container.end(). 
    - If the value is found → iterator points to the found element 
    - If not found → returns v.end() 
- STRING OPERATIONS
  - stringstream for reading from /writing to strings. 
  - string manipulation using stringstream
- FILE OPERATIONS
  - filestream for reading from /writing to files
- ERROR HANDLING
   - cerr
   - cassert
- RAII : memory management. Basics

Note: 
- Knowing and learning string operations and file operations seems boring/trivial. But thinking about it is essential to read data logs etc. This is fundamental to power the "DATA LAYER" of any application such as games etc. :) 