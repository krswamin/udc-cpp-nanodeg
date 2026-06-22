/*
stringstream
- std::stringstream is a stream object that:
- Stores text in an internal string buffer
- Supports stream operations like >>, <<, getline
- It behaves just like std::cin / std::cout, but the source is memory, not I/O.

*/


# include <iostream>
# include <sstream>
using namespace std;

int main(){
    string line1 = "001, -1.234, 4.67, 45.87,  rear radar";    
    string line2 = "002, -2.126, 10.43, 62.91, front radar";  
    string serial_num_str, roll_str, pitch_str, yaw_str, radar_str;
    string str_h, str_w;
    
    int serial_num;
    float roll, pitch, yaw;
    char comma;
    string radar_position;

    // String stream object canbe used for input or output    
    // string stream for reading a string
    stringstream ss1(line1); // Initialise ss1 using constructor
    stringstream ss2, ss3;
    ss2<<line2;
    ss3 <<"hello"<<" "<<"world !"<<" "<<"Ok Bye !";

    // Get the internal string using .str() and print it to standard output (console)
    cout<<"ss1.str(): "<< ss1.str()<<"\n";
    cout<<"ss2.str(): "<< ss2.str()<<"\n";
    cout<<"ss3.str(): "<< ss3.str()<<"\n";

    // string stream for writing into a string
    // >> writes until the next space
    // operator>> does not modify that string.It only moves the stream’s read position (cursor) forward    cout<<"\n\n";
    cout<<"\n --- Notice that the ss3 string remains the same, only the read position cursor moves -------\n";
    cout<<"ss3.str(): "<< ss3.str()<<", stream position cursor: " <<ss3.tellg()<<"\n";
    ss3 >> str_h;
    cout<<"str_h:"<<str_h<<"\n";
    cout<<"ss3.str(): "<< ss3.str()<<", stream position cursor: " <<ss3.tellg()<<"\n";
    ss3 >> str_w;    
    cout<<"str_w:"<<str_w<<"\n";
    cout<<"ss3.str(): "<< ss3.str()<<", stream position cursor: " <<ss3.tellg()<<"\n";

    // Read the serial number, roll, pitch yaw into strings
    // line(string) --> read into ss1(string stream) --> write into roll, pitch,yaw(strings)
    getline(ss1, serial_num_str, ',');
    getline(ss1, roll_str, ',');
    getline(ss1, pitch_str, ',');
    getline(ss1, yaw_str, ',');
    getline(ss1, radar_str, ',');
    cout<<"\n --- Reading based on comma delimiter into strings -------\n";
    cout<<"serial_num_str: "<< serial_num_str <<"\n";
    cout<<"roll_str : "<< roll_str <<"\n";
    cout<<"pitch_str: "<< pitch_str <<"\n";
    cout<<"yaw_str  : "<< yaw_str <<"\n";
    cout<<"radar_str  : "<< radar_str <<"\n";

    // Read the serial number, roll, pitch yaw into strings
    // line(string) --> read into ss1(string stream) --> write into roll, pitch,yaw(strings)
    ss2>>serial_num>>comma>>roll>>comma>>pitch>>comma>>yaw>>comma>>radar_position;
    cout<<"\n --- Reading based on comma delimiter into ints , char and floats-------\n";
    cout<<"serial_num: "<< serial_num<<"\n";
    cout<<"roll  : "<< roll <<"\n";
    cout<<"pitch : "<< pitch <<"\n";
    cout<<"yaw   : "<< yaw <<"\n";
    cout<<"radar_position  : "<< radar_position <<"\n";


    
}