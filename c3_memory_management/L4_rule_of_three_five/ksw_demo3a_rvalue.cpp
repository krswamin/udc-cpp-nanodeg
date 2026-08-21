/*
Code demos rvalues vs lvalues
See relevant README for details c3_memory_management/docs/README_3b_classes_pointers_problems.md
*/
# include<iostream>
using namespace std;

/*
Note you can only have function overloading based on lvalue references and rvalue references
It is not easy/straightforward/perhaps impossible to do function overloading based on just lvalues and rvalues (i.e you would need  a reference to them)
*/ 

void process(int& x) {
    cout<< "This is a int lvalue reference: "<<x<<endl;
}

void process(int&& x) {
    cout<< "This is a int rvalue reference: "<<x<<endl;
}

void process(float& x) {
    cout<< "This is a float lvalue reference: "<<x<<endl;
}

void process(float&& x) {
    cout<< "This is a float rvalue reference: "<<x<<endl;
}

void process(double& x) {
    cout<< "This is a double lvalue reference: "<<x<<endl;
}

void process(double&& x) {
    cout<< "This is a double rvalue reference: "<<x<<endl;
}

int main(){
    int a= 10;
    process(a);
    process(456743);
    process(a+170);
    process(12.5); // this is double by default
    process(12.5f); // this is float, you'd have to explicitly call it float
}


