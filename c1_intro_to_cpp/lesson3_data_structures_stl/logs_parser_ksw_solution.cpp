/*
Instructions:

Open logs.txt using std::ifstream.

Read each line using std::getline(file, line).

Use a std::stringstream to split each line using , as the delimiter.

Store the parsed fields in:

    std::string timestamp

    std::string level

    std::string message

Print each part clearly.

If level is "ERROR", print "!!! This is an error."
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

int main(){
    string filename = "logs.txt";

    // Read the file contents into a fstream object called fs
    fstream fs(filename);
    if (!fs) {
        throw std::runtime_error("Failed to open file:" + filename);
    }

    string line;    
    string timestamp, error_level, error_message;
    stringstream ss; 
    int line_count = 0;
    while(getline(fs,line)){  
        // Must reset the content and clear the error flags for the string stream object always
        // Otherwise the new lines keep getting appended
        // The correct thing to do is stringstream ss(line);  i.e construct new stringstream from line
        // But keeping the below uglier version just to draw attention to it . LOL !
        ss.str("");       // reset the content
        ss.clear();       // clear error flags      
        ss<<line;
       
        getline(ss,timestamp, ',');
        getline(ss,error_level, ',');
        getline(ss,error_message);   // Skip the comma for the error message. Reads until a newline

        // Display everything
        // Note you should be trimming the whitespaces before displaying. 
        // But skipping for the sake of simplicity
        cout<< "\n Line Number: "<<line_count;
        cout<< "\n Timestamp: "<<timestamp;
        cout<< "\n Error Level: "<<error_level;
        cout<< "\n Error Message: "<<error_message;
        cout<<"\n";
        
        line_count++;
    }
    
    // Close the file. 
    // When the fstream object goes out of scope, its destructor is called automatically anyway. 
    // So this is not necessary strictly. But generally good practise. 
    fs.close();  
}