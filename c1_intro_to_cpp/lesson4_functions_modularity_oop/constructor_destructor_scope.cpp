#include <iostream>

class Widget {
public:
    Widget() { std::cout << "C"; }  
    ~Widget() { std::cout << "D"<<std::endl; } // Note if you don't use the endl , the buffer doesnt get flushed. so it wont print the D
};

int main() {
    {
        Widget w1;
        std::cout << "M";
    }
    std::cout << "E";
    std::cout<<"\n";

    
    Widget w2;
    std::cout << "-M2-";    
    std::cout << "-E2-";
    std::cout<<"\n";

    return 0;
}