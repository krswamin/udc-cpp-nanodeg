# include <iostream>
using namespace std;


// Demo1: Heap Memory is always accessed by pointers
// This demo shows the proper way - a pointer should be created, memory released and pointer set to nullptr
void demo1_heap_proper_pointer() {
  cout<<"\n\n"<<endl;
  cout << "-------Demo1 : Heap - Safe Pointer Usage -------"<<endl;

  int *p = new int(37);
  cout <<"*p = "<<*p<<endl; // prints 37

  *p = *p + 1;
  cout <<"*p after adding 1: "<<*p<<endl; // prints 38

  *p = *p * 2;
  cout <<"*p after multiplying 2: "<<*p<<endl; // prints 76

  *p = *p -1;
  cout <<"*p after subtracting 1: "<<*p<<endl; // prints 75

  *p = *p /3;
  cout <<"*p after dividing by 3: "<<*p<<endl; // prints 15

  delete p; // heap memory pointed to by p is released, hence no memory leak
  p = nullptr;  //prevents a dangling pointer

  p = new int(42);
  cout<<endl;
  cout<<"p points to new location"<<endl;
  cout <<"*p = "<<*p<<endl; // prints 42
  delete p; // heap memory pointed to by p is released, hence no memory leak
  p = nullptr;  //prevents a dangling pointer

  cout << "----------------------------------------------------------"<<endl;
  }

// Demo2: Using the dereferencing operator with pointers is cumbersome . It makes the code unreadable
// A a reference to the dereferenced pointer  could be used instead
// But there is a problem here,  because the reference becomes dangling
void demo2_heap_proper_pointer_but_dangling_reference(){

  cout<<"\n\n"<<endl;
  cout << "-------Demo2 : Heap - Safe Pointer Usage, But Dangling Reference -------"<<endl;

  int *p = new int(37);
  
  cout <<"*p = "<<*p<<endl; // prints 37
  // This is a reference to the dereferenced pointer, 
  // IMPORTANT: Pay attention . This is a reference to the variable in the memory location point to by p
  // if p is reassigned a new address, the reference cannot be reassigned to that new address
  // If you wanted the reference to change address then it should a reference to  the pointer itsefl like
  // int* &r = p , not int &r = p. 
  int &r = *p;

  r = r+1;
  cout <<" r after adding 1: "<<r<<endl; // prints 38
  cout <<"*p after adding 1: "<<*p<<endl; // prints 38

  r = r * 2;
  cout <<" r after multiplying by 2: "<<*p<<endl; // prints 76
  cout <<"*p after multiplying by 2: "<<*p<<endl; // prints 76

  r = r -1;
  cout <<" r after subtracting 1: "<<*p<<endl; // prints 75
  cout <<"*p after subtracting 1: "<<*p<<endl; // prints 75

  r = r /3;
  cout <<" r after dividing by 3: "<<*p<<endl; // prints 15
  cout <<"*p after dividing by 3: "<<*p<<endl; // prints 15

  delete p; // heap memory pointed to by p is released
  p = nullptr;  //prevents a dangling pointer

  // But this leads to a dangling reference 'r'
  //  i) r cannot be reassigned since references cannot be reassigned
  // ii) 
  cout<<endl;
  cout<<"p has been deleted(memory pointed to by p has been deleted). r is a DANGLING REFERENCE. NOTHING CAN BE DONE ABOUT IT HERE AT THIS POINT";
  cout<<endl;

  p = new int(42);
  cout<<endl;
  cout<<"p points to new location"<<endl;
  cout <<"*p = "<<*p<<endl; // prints 42
  delete p; // heap memory pointed to by p is released
  p = nullptr;  //prevents a dangling pointer

  cout << "----------------------------------------------------------"<<endl;
}


// Demo3: I dont like using the dereferencing operator . It makes the code unreadable
// I could use a reference to the dereferenced pointer instead
// But the reference could become dangling. This has been solved here by limiting the scope of r
void demo3_heap_proper_pointer_and_reference(){

  cout<<"\n\n"<<endl;
  cout << "-------Demo3 : Heap- Safe Pointer , Safe Reference Usage-------"<<endl;

  int *p = new int(37);
  
  cout <<"*p = "<<*p<<endl; // prints 37

  {
    // This is a reference to the dereferenced pointer, 
    // IMPORTANT: Pay attention . This is a reference to the variable in the memory location point to by p
    // if p is reassigned a new address, the reference cannot be reassigned to that new address
    // If you wanted the reference to change address then it should a reference to  the pointer itsefl like
    // int* &r = p , not int &r = p. 
    int &r = *p;

    r = r+1;
    cout <<" r after adding 1: "<<r<<endl; // prints 38
    cout <<"*p after adding 1: "<<*p<<endl; // prints 38

    r = r * 2;
    cout <<" r after multiplying by 2: "<<*p<<endl; // prints 76
    cout <<"*p after multiplying by 2: "<<*p<<endl; // prints 76

    r = r -1;
    cout <<" r after subtracting 1: "<<*p<<endl; // prints 75
    cout <<"*p after subtracting 1: "<<*p<<endl; // prints 75

    r = r /3;
    cout <<" r after dividing by 3: "<<*p<<endl; // prints 15
    cout <<"*p after dividing by 3: "<<*p<<endl; // prints 15
   
    cout<<endl;
    cout<<" Scope of reference-r ends here. The memory and the pointer associated with it are still alive";
  }

  delete p; // heap memory pointed to by p is released
  p = nullptr;  //prevents a dangling pointer

  cout<<endl;
  cout<<"p has been deleted(memory pointed to by p has been deleted).  "<<endl;
  cout<<"reference-r was deleted way ahead within its scope. There is DANGLING REFERENCE ";
  cout<<endl;

  p = new int(42);
  cout<<endl;
  cout<<"p points to new location"<<endl;
  cout <<" *p = "<<*p<<endl; // prints 42
  delete p; // heap memory pointed to by p is released
  p = nullptr;  //prevents a dangling pointer

  cout << "----------------------------------------------------------"<<endl;
}


int main(){

    demo1_heap_proper_pointer();
    demo2_heap_proper_pointer_but_dangling_reference();
    demo3_heap_proper_pointer_and_reference();

}