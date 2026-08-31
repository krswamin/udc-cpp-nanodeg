# include<iostream>
# include<memory>
using namespace std;


void print_shared_info(const shared_ptr<int>& shared){
    cout << " shared info\n" 
         << " shared ptr address  : " << &shared<<'\n'
         << " Heap Object Address : " << shared.get() << '\n'
         << " Heap Object Value   : " <<*shared<< '\n'
         << " use_count           : " << shared.use_count() << endl;
}

void print_weak_info(const weak_ptr<int>& weak)
{   
    cout << "weak ptr address : " << &weak<<'\n';
    cout << "weak.use_count (= shared.use_count) : " << weak.use_count() << '\n';
    cout << "weak.expired     : " << boolalpha << weak.expired() << '\n';

    if (auto locked = weak.lock()) {
        cout << "lock() succeeded   : true\n";
        cout << "lock ptr address   : " << &locked<<'\n';
        cout << "Heap Object address: " << locked.get() << '\n';
        cout << "Heap Object value  : " << *locked << '\n';
        // locked is now another shared owner.
        cout << "locked.use_count after lock(): " << locked.use_count() << '\n';
    } else {
        cout << "lock() succeeded: false\n";
        cout << "Object is no longer accessible\n";
    }
}

void test1(){
    cout <<"\n\n============== TEST 1===================== ";
    shared_ptr<int> shared = make_shared<int>(42);
    cout<<"\n Shared pointer details, right after creation:"<<endl;
    print_shared_info(shared);

    weak_ptr<int> weak1 = shared;
    cout<<"\n\n Shared pointer details, after weak1:"<<endl;
    print_shared_info(shared);
    cout<<"\n Weak pointer details, after weak1:"<<endl;
    print_weak_info(weak1);

    weak_ptr<int> weak2 = shared;
    cout<<"\n\n Shared pointer details, after weak2:"<<endl;
    print_shared_info(shared);
    cout<<"\n Weak pointer details, after weak2:"<<endl;
    print_weak_info(weak2);   
}


// TEST 2: The same shared pointer can be locked many times
// locked just generates another shared pointer (from a weak pointer)
void test2(){
    
    // Test2
    cout <<"\n\n============== TEST 2===================== ";
    shared_ptr<int> shared = make_shared<int>(42);
    cout<<"\n Shared pointer details, right after creation:"<<endl;
    print_shared_info(shared);

    weak_ptr<int> weak1 = shared;
    cout<<"\n\n Shared pointer details, after weak1:"<<endl;
    print_shared_info(shared);
    cout<<"\n Weak pointer details, after weak1:"<<endl;
    cout << "weak1 ptr address : " << &weak1<<'\n';
    cout << "weak1.use_count (= shared.use_count)   : " << weak1.use_count() << '\n';
    cout << "weak1.expired     : " << boolalpha << weak1.expired() << '\n';
    
    auto locked1 = weak1.lock();
    if (locked1) {
        cout << "lock() succeeded   : true\n";
        cout << "lock ptr address   : " << &locked1<<'\n';
        cout << "Heap Object address: " << locked1.get() << '\n';
        cout << "Heap Object value  : " << *locked1 << '\n';
        // locked is now another shared owner.
        cout << "locked.use_count after lock(): " << locked1.use_count() << '\n';
    } else {
        cout << "lock() succeeded: false\n";
        cout << "Object is no longer accessible\n";
    }

    weak_ptr<int> weak2 = shared;
    cout<<"\n\n Shared pointer details, after weak2:"<<endl;
    print_shared_info(shared);
    cout<<"\n Weak pointer details, after weak2:"<<endl;
    cout << "weak ptr address : " << &weak2<<'\n';
    cout << "weak.use_count (= shared.use_count)   : " << weak2.use_count() << '\n';
    cout << "weak.expired     : " << boolalpha << weak2.expired() << '\n';
    
    auto locked2 = weak2.lock();
    if (locked2) {
        cout << "lock() succeeded   : true\n";
        cout << "lock ptr address   : " << &locked2<<'\n';
        cout << "Heap Object address: " << locked2.get() << '\n';
        cout << "Heap Object value  : " << *locked2 << '\n';
        // locked is now another shared owner.
        cout << "locked.use_count after lock(): " << locked2.use_count() << '\n';
    } else {
        cout << "lock() succeeded: false\n";
        cout << "Object is no longer accessible\n";
    }  
}

// TEST 3 demos: the same weak pointer can be locked more than once
// locked just generates another shared pointer (from a weak pointer)

// also demos what happens when u keep resetting the locked ptrs (locked ptrs are shared ptrs)
void test3(){
    
    // Test3
    cout <<"\n\n============== TEST 3===================== ";
    shared_ptr<int> shared = make_shared<int>(42);
    cout<<"\n Shared pointer details, right after creation:"<<endl;
    print_shared_info(shared);

    weak_ptr<int> weak1 = shared;
    cout<<"\n\n Shared pointer details, after weak1:"<<endl;
    print_shared_info(shared);
    cout<<"\n Weak pointer details, after weak1:"<<endl;
    cout << "weak1 ptr address : " << &weak1<<'\n';
    cout << "weak1.use_count (= shared.use_count)   : " << weak1.use_count() << '\n';
    cout << "weak1.expired     : " << boolalpha << weak1.expired() << '\n';
    
    auto locked1 = weak1.lock();
    if (locked1) {
        cout << "locked1 succeeded   : true\n";
        cout << "locked1 ptr address   : " << &locked1<<'\n';
        cout << "Heap Object address: " << locked1.get() << '\n';
        cout << "Heap Object value  : " << *locked1 << '\n';
        // locked is now another shared owner.
        cout << "locked1.use_count after lock(): " << locked1.use_count() << '\n';
    } else {
        cout << "locked1 succeeded: false\n";
        cout << "Object is no longer accessible\n";
    }

    weak_ptr<int> weak2 = shared;
    cout<<"\n\n Shared pointer details, after weak2:"<<endl;
    print_shared_info(shared);
    cout<<"\n Weak pointer details, after weak2:"<<endl;
    cout << "weak2 ptr address : " << &weak2<<'\n';
    cout << "weak2.use_count (= shared.use_count) : " << weak2.use_count() << '\n';
    cout << "weak2.expired     : " << boolalpha << weak2.expired() << '\n';
    
    auto locked2 = weak1.lock();
    if (locked2) {
        cout << "locked2 succeeded   : true\n";
        cout << "locked2 ptr address : " << &locked2<<'\n';
        cout << "Heap Object address : " << locked2.get() << '\n';
        cout << "Heap Object value   : " << *locked2 << '\n';
        // locked is now another shared owner.
        cout << "locked2.use_count after lock(): " << locked2.use_count() << '\n';
    } else {
        cout << "locked2 succeeded: false\n";
        cout << "Object is no longer accessible\n";
    }  
    
    cout<<"\n\n";
    cout << "shared.use_count  : " << shared.use_count()  << '\n';
    cout << "locked1.use_count : " << locked1.use_count() << '\n';
    cout << "locked2.use_count : " << locked2.use_count() << '\n';

    locked1.reset();
    cout<<"\n locked1.reset(): locked1 is a nullptr"      << '\n';
    cout << "shared.use_count  : " << shared.use_count()  << '\n';
    cout << "locked1.use_count : " << locked1.use_count() << '\n';
    cout << "locked2.use_count : " << locked2.use_count() << '\n';

    locked2.reset();
    cout<<"\n locked2.reset(): locked1 & locked 2 are nullptrs"  << '\n';
    cout << "shared.use_count  : " << shared.use_count()  << '\n';
    cout << "locked1.use_count : " << locked1.use_count() << '\n';
    cout << "locked2.use_count : " << locked2.use_count() << '\n';
}


// TEST 4 demos: what happens when the shared pointer is released 9when locked1, locked2
// what happens to locked1, locked2 use counte (locked pointers are shared pointers)

// It also demos that , you can get more locked pointers from the weak that originally pointer to the shared,
// as long as the shared resource still exists
void test4(){
    
    // Test4
    cout <<"\n\n============== TEST 4===================== ";
    shared_ptr<int> shared = make_shared<int>(42);

    weak_ptr<int> weak1 = shared;
    auto locked1 = weak1.lock();

    weak_ptr<int> weak2 = shared;   
    auto locked2 = weak2.lock();
    
    cout<<"\n\n";
    cout << "shared.use_count  : " << shared.use_count()  << '\n';
    cout << "locked1.use_count : " << locked1.use_count() << '\n';
    cout << "locked2.use_count : " << locked2.use_count() << '\n';

    shared.reset();
    cout<<"\n shared.reset(): shared is a nullptr, ";
    cout<<"\n locked pointers are still shared pointers, so their use count will remain" << '\n';
    cout << "shared.use_count  : " << shared.use_count()  << '\n';
    cout << "locked1.use_count : " << locked1.use_count() << '\n';
    cout << "locked2.use_count : " << locked2.use_count() << '\n';

    auto locked3 = weak1.lock();
    cout<<"\n\n locked3"<<endl;
    if (locked3) {
        cout << "locked3 succeeded   : true\n";
        cout << "locked3 ptr address : " << &locked3<<'\n';
        cout << "Heap Object address : " << locked3.get() << '\n';
        cout << "Heap Object value   : " << *locked3 << '\n';
        // locked is now another shared owner.
        cout << "locked3.use_count after lock(): " << locked3.use_count() << '\n';
    } else {
        cout << "locked3 succeeded: false\n";
        cout << "Object is no longer accessible\n";
    }

    cout<<"\n\n Release all locked and shared. see if you can get a new locked"<<"\n";
    locked1.reset();
    locked2.reset();
    locked3.reset();
    auto locked4 = weak1.lock();
    cout<<"locked4"<<endl;
    if (locked3) {
        cout << "locked4 succeeded   : true\n";
        cout << "locked4 ptr address : " << &locked4<<'\n';
        cout << "Heap Object address : " << locked4.get() << '\n';
        cout << "Heap Object value   : " << *locked4 << '\n';
        // locked is now another shared owner.
        cout << "locked4.use_count after lock(): " << locked4.use_count() << '\n';
    } else {
        cout << "locked4 succeeded: false\n";
        cout << "Object is no longer accessible\n";
    }

}



int main(){
    test1();
    test2();
    test3();
    test4();
}