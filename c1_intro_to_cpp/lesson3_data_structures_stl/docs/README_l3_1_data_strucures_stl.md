# Data Structures and STL
- Use the correct data structures and STL to prevent bugs. Dont reinvent the wheel

## Arrays and Vectors
- Arrays: 
  - Static. 
  - allocated on the stack
  - cannot grow or shrink
  - efficient when you know the size at compile time 
  - creating a really large array when you dont need the size is inefficient. just use a vector then
- Vectors:
  - Dynamic,
  - allocated on the heap
  - can grow or shrink
  - when you need to frequently add/ remove items. When you dont know the size at compile time

  ```
  // KEY TAKEAWAY:
  // vector::at() trades a small runtime cost for defined, safe behavior.


  int arr[3] = {1,2,3};
  vector<int> v1 = {10,20,30};

  // Following will not cause compile time error. c++ does not check for bounds for raw arrays
  // Runtime undefined behaviour: could or could not crash. Depends if it goes past valid memory or not
  cout<< arr[3] ; 


  // Following will not cause compile time error. c++ does not check for bounds when using the square bracket indexing
  // Runtime undefined behaviour: could or could not crash. Depends if it goes past valid memory or not
  cout<< v1[3] ; 
  
  // Following will not cause compile time error either. 
  // Runtime it checks for bounds. So it will cause runtime exception
  cout<< v1.at(3); 
  ```

