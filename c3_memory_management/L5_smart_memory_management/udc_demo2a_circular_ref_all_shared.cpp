/*

THIS CODE DEMOS THAT WHEN THERE IS A CIRCULAR REFERENCE WITH ALL SHARED POINTERS, 
IT CAUSES MEMORY LEAK
Notice When circularRefDemo() ends, that destructors of A and B are never called,
This is a memory leak !


---- When the end of the function is reached:  BRIEF EXPLANATION----
Local b_sptr is destroyed: B count goes from 2 to 1.
Local a_sptr is destroyed: A count goes from 2 to 1.
A remains owned by B::a_shared_ptr.
B remains owned by A::b_shared_ptr.

Because neither count reaches zero, neither object is destroyed. 
This is a memory leak.s because there is a memory leak

---- When the end of the function is reached:  DETAILED EXPLANATION----
- Local variables are destroyed first. 
- b_sptr was created after a_sptr, so b_sptr is destroyed first. b_sptr is a shared pointer, so its destructor is called, b_sptr.~shared_ptr();
- b_sptr.~shared_ptr() - The destructor of the shared_ptr, decreases the strong reference count in B’s control block:
    B strong count: 2 → 1
- The new count of the B control block is checked. Because the count is 1, nothing is done to the heap B object.
   B::~B() is not called. 
   Hence now the heap memory associated with b_sptr i.e. B cannot be released

- next a_sptr is destroyed. a_sptr is a shared pointer, so its destrouctor is called, a_sptr.~shared_ptr();
- a_sptr.~shared_ptr() - The destructor of the shared_ptr, decreases the strong reference count in A’s control block:
    A strong count: 2 → 1
- The new count of the A control block is checked. Because the count is 1, nothing is done to the heap A object.
   A::~A() is not called. 
   Hence now the heap memory associated with a_sptr i.e. A cannot be released

- so in heap memory A (with A::b_shared_ptr), B(with B::a_shared_ptr), A control block, B control block are all alive
when the code exits (with no way of accessing them). HENCE THIS IS A MEMORY LEAK


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
              cout << "A Destroyed !"<<endl;
           }
};

class B {
    public:
        shared_ptr<A> a_shared_ptr; // shared pointer back to A
        B() { cout <<"B Constructed !"<<endl;}
        ~B() {cout <<"B Destructor!"<<endl;
              // Calling use_count() on a null std::shared_ptr returns 0. safe to use on null
              cout <<"a_shared_ptr.use_count"<<a_shared_ptr.use_count()<<endl;              
              cout << "B Destroyed !"<<endl;
           }
     
};


void circularRefDemo_all_shared() {
    cout<<"------- Circular Reference(all shared) Demo -------"<<endl;
    shared_ptr<A> a_sptr = make_shared<A>();
    shared_ptr<B> b_sptr = make_shared<B>();

    cout<<"\n \n A and B, both ref, right after creation. Should be 1 each, for a_sptr, b_sptr, rest should be 0"<<endl;
    cout << "A ref count (a_sptr.use_count()): "<< a_sptr.use_count()<<endl;
    cout << "B ref count (b_sptr.use_count(): "<< b_sptr.use_count()<<endl;
    cout << "A's-B ref count (a_sptr->b_shared_ptr.use_count())     : "<< a_sptr->b_shared_ptr.use_count()<<endl;
    cout << "B's-A ref count (b_sptr->a_shared_ptr.use_count()): "<< b_sptr->a_shared_ptr.use_count()<<endl;

    /*
    This copies the shared_ptr b_sptr into a_sptr->b_shared_ptr.
    It does not create a new B object. 
    After the assignment, there are two separate shared_ptr objects that share ownership of the same B object:
    b_sptr ──────────┐
                 ├──► same B object
    a_sptr->b_shared_ptr ───┘
    */

    a_sptr->b_shared_ptr = b_sptr; // A owns B. share pointer is copied to another shared pointer
    b_sptr->a_shared_ptr = a_sptr; // B also owns A
    
    cout<<"\n \n A and B, both ref, after circular creation. Should be 2 each"<<endl;
    cout << "A ref count (a_sptr.use_count()): "<< a_sptr.use_count()<<endl;
    cout << "B ref count (b_sptr.use_count(): "<< b_sptr.use_count()<<endl;
    cout << "A's-B ref count (a_sptr->b_shared_ptr.use_count())     : "<< a_sptr->b_shared_ptr.use_count()<<endl;
    cout << "B's-A ref count (b_sptr->a_shared_ptr.use_count()): "<< b_sptr->a_shared_ptr.use_count()<<endl;
    cout<<"------- Exiting Circular Reference(all shared) Demo -------"<<endl;


    /* What happens when scope ends */
    cout<<"\n\n Notice that destructors of A and B are never called, this is because there is a memory leak.";
    cout<<"See start of code for details"<<endl;
    
}


int main(){

    circularRefDemo_all_shared();
}