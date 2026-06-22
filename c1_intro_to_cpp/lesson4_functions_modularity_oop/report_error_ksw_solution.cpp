/*
Your program is logging system errors but the error message is optional.

Implement a reportError message that utilizes pointers to model this and handle
errors that dont have an error message.

If message is not null, print "ERROR: <message>".

If message is null, print "No error message provided."
*/
#include <iostream>
#include <string>
using namespace std;

void reportError(string *msg_ptr){
    if(msg_ptr != nullptr){
        cout<<"\n ERROR: "<<*msg_ptr; 
    } else{
        cout<<"\n No error message provided.";
    }
    cout<<"\n";
}

int main() {
    std::string msg = "Camera stream failed.";
    reportError(&msg);         // Should print error
    reportError(nullptr);      // Should handle gracefully
    return 0;
}
