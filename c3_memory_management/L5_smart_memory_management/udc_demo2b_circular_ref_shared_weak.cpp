/*

THIS CODE DEMOS THAT WHEN THERE IS A CIRCULAR REFERENCE INVOLVING ONE SHARED AND ONE WEAK POINTER, 
it DOES NOT CAUSE memory leaks. It in fact breaks the circular reference problem

compare with L5_smart_memory_management/udc_demo2a_circular_ref_all_shared.out
(which does cause memory leak)


Keep in mind the following. When the end of the function is reached
- Local variables are destroyed first
- Variable are destroyed in reverse order of their creaton. example b_sptr was created after a_sptr, so b_sptr is destroyed first.
- When destructors are called, 
  - the destructor body is executed until }. 
  - Object's data members are destroyed after } i.e. after the closing curly brace!"<<endl;
  - only after the object's data members are destroyed , the destructor actually finishes


============== ORDER OF VARIABLE AND MEMORY RELEASE @ THE END OF circularRefDemo ==============

--------------------------------- CODE OUTPUT---------------------------------------------------

------- Circular Reference(shared-weak) Demo -------
A Constructed !
B Constructed !
A is still alive ! Lock Succeeded ! sharedA.use_count()2
A and B, both ref should be 1
A ref count (a_sptr.use_count()): 1
B ref count (b_sptr.use_count(): 2
A's-B ref count (a_sptr->b_shared_ptr.use_count())     : 2
B's-A ref count (b_sptr->a_weak_ptr.use_count()): 1
------- Exiting Circular(shared-weak) Reference Demo -------
A Destructor!
b_shared_ptr.use_count1
A Destructor body ends. Object's data members will be destroyed after } i.e. the closing curly brace!
B Destructor!
a_weak_ptr.use_count0
B Destructor body ends. Object's data members will be destroyed after } i.e. the closing curly brace!

----------------------------------- END CODE OUTPUT---------------------------------------------------------------

Based on the code output it seems like B is destroyed last. 
This is because the object's data members are destroyed after the Destructor's }i.e the closing curly brace
But For true order of events see below


------------------- VARIABLE DESTRUCTION SEQUENCE ---------------------------------------------------

 b_sptr shared pointer's destructor is called, b_sptr.~shared_ptr();
- b_sptr.~shared_ptr(): 
    - B count : 2 → 1: b_sptr.~shared_ptr(), decreases the strong reference count in B’s control block:
    - B in heap memory is not deleted yet since A::b_shared_ptr, that points to B, still exists

a_sptr shared pointer's destructor is called, a_sptr.~shared_ptr();
a_sptr.~shared_ptr()
    - A count  1 → 0                     - a_sptr.~shared_ptr(), decreases the strong reference count in A’s control block:
    - B::a_weak_ptr = weakptr            - Now based on A control block, A can be deleted from Heap memory
    - A::~A() body                       - i.e. Enter A's destructor, ane execute ~A() body until } (except destroying local variables)
    - Exit the ~A() body at }            - then begin destroying A::data members
        - Destroy A::b_shared_ptr i.e A::b_shared_ptr.~shared_ptr()
            - B count : 1 → 0                - A::b_shared_ptr.~shared_ptr(), decreases the strong reference count in B’s control block:
            - B's control block is 0 now. so B can be deleted from heap memory 
            - Enter and execute B::~B() body
            - Exit the ~B() body at }     - then begin destroying B::data members
            - B::a_weak_ptr.~weak_ptr()
            - B destruction finishes
        - A::b_shared_ptr destruction finishes
    - A destruction finishes
 -------------------END: VARIABLE DESTRUCTION SEQUENCE ---------------------------------------------------

*/


#include <iostream>
#include <memory> // Header for std::unique_ptr
#include <utility> // For std::move
using namespace std;

class A; // Forward Declaration
class B; // Forward Declaration

class A {
    public:
        shared_ptr<B> b_shared_ptr;
        A() { cout << "A Constructed !"<<endl;}
        ~A() {cout <<"A Destructor!"<<endl;
              // Calling use_count() on a null std::shared_ptr returns 0. safe to use on null
              cout <<"b_shared_ptr.use_count"<<b_shared_ptr.use_count()<<endl;        
              cout << "A Destructor body ends. Object's data members will be destroyed after } i.e. the closing curly brace!"<<endl;
           }
};

class B {
    public:
        weak_ptr<A> a_weak_ptr; // Weak Pointer back to A
        B() { cout << "B Constructed !"<<endl;}
        ~B() {cout <<"B Destructor!"<<endl;
              // Calling use_count() on a null std::weak_ptr returns 0. safe to use on null
              // Also safe to call on a weak pointer whose, shared pointer has gone null
              // besides bool has not been implemented in weak_ptr, so if(a_weak_ptr) cannot be called
              cout <<"a_weak_ptr.use_count"<<a_weak_ptr.use_count()<<endl;              
             cout << "B Destructor body ends. Object's data members will be destroyed after } i.e. the closing curly brace!"<<endl;
           }
        void checkA(){
            // Note: before calling checkA, a_weak_ptr has to be assigned , 
            // Note that the constructor does not assign a_weak_ptr
            // This is likely taken care of in main
            if (auto sharedA = a_weak_ptr.lock()) {
                cout<<"A is still alive ! Lock Succeeded ! sharedA.use_count()"<<sharedA.use_count()<<endl;
            } else {
                cout<<"A has been destroyed ! Lock Failed !"<<endl;
            }
        }
      
};


void circularRefDemo() {
    cout<<"------- Circular Reference(shared-weak) Demo -------"<<endl;
    shared_ptr<A> a_sptr = make_shared<A>();
    shared_ptr<B> b_sptr = make_shared<B>();

    /*
    This copies the shared_ptr b_sptr into a_sptr->b_shared_ptr.
    It does not create a new B object. 
    After the assignment, there are two separate shared_ptr objects that share ownership of the same B object:
    b_sptr ──────────┐
                 ├──► same B object
    a_sptr->b_shared_ptr ───┘
    */

    a_sptr->b_shared_ptr = b_sptr; // A owns B. share pointer is copied to another shared pointer
    b_sptr->a_weak_ptr = a_sptr; // B observes A weakly.  a weak pointer is created from a shared pointer
    
    b_sptr->checkA(); //A Should be alive
    
    cout<<"A and B, both ref should be 1"<<endl;
    cout << "A ref count (a_sptr.use_count()): "<< a_sptr.use_count()<<endl;
    cout << "B ref count (b_sptr.use_count(): "<< b_sptr.use_count()<<endl;
    cout << "A's-B ref count (a_sptr->b_shared_ptr.use_count())     : "<< a_sptr->b_shared_ptr.use_count()<<endl;
    cout << "B's-A ref count (b_sptr->a_weak_ptr.use_count()): "<< b_sptr->a_weak_ptr.use_count()<<endl;
    cout<<"------- Exiting Circular(shared-weak) Reference Demo -------"<<endl;
}


int main(){
    circularRefDemo();
}