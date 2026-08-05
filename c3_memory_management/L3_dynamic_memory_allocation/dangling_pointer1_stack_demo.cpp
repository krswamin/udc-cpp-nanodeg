/* To demonstrate a dangling pointer on a stack, you will have to use a function
Ans then return a local pointer within a function stack whose life/scope has ended

MORAL OF THE STORY: 
- Never return local pointers
- Never return local references either (this is not demoed in this code)
You can return local variables: only their value is returned
*/

# include <iostream>
using namespace std;

// This function is to demonstrate dangling pointer on a stack
int* returnPointer(){
    int a = 10;
    int *p = &a;
    cout<<"returnPointer function:  a="<<a<<endl;
    cout<<"returnPointer function: *p="<<*p<<endl;
    cout<<"returnPointer function:  p="<<p<<endl;

    return p; // DANGER ! You must never return local pointers
}


int main(){

    int *p = returnPointer();

    cout<<" \n\n";
    cout<< "main function: Notice that the value of p itself, which is an address is valid/ correct. This is because the return by value(of the value of p) from the function works properly.";
    cout<< "(REMINDER: return by value in c++ always works correctly ! Reread that if you didnt follow !) "<<endl;
    cout<< "main function: HOWEVER THOUGH THE DEREFERENCING IS JUNK. The value of *p is junk, because its a dangling pointer \n"<<endl;
    cout<< "main function: *p="<<*p<<endl;
    cout<< "main function:  p="<< p<<endl;
    
}