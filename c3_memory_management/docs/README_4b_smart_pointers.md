# SMART POINTERS
- smart pointers are a raii wrapper around raw pointers
- corner stone of modern c++ memory management, helps avoid a lot of the major problems that arise from dealing with raw pointers
- std:: unique_ptr for exclusive ownership
- std:: shared_ptr for shared ownership

-----

code
- 1) Make a wrapper around new, delete: constructor, destructor
