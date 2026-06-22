/*
You're building a tool for engineers to inspect log output from a device. Here's a sample log line:
"[2025-07-14 10:15:32] ERROR: Camera stream failed to start"

You need to parse this string to extract:

    The timestamp

    The severity level (INFO, ERROR, WARN, etc.)

    The actual log message

Store the log line in a std::string.

Use .find() and .substr() to extract:

    The timestamp (between [ and ])

    The log level (between ] and :)

    The message (after the colon)

Print the extracted parts cleanly.

If the level is "ERROR", print a warning message (just prefix with !!!).
*/

#include <iostream>
#include <string>
#include<sstream>
#include<algorithm>
using namespace std;

void trim_inplace(string& s) {
    s.erase(s.begin(), find_if(s.begin(), s.end(),
                                    [](unsigned char c){ return !std::isspace(c); }));
    s.erase(find_if(s.rbegin(), s.rend(),
                         [](unsigned char c){ return !std::isspace(c); }).base(),
            s.end());
}

int main() {
    string log = "[2025-07-14 10:15:32] ERROR: Camera stream failed to start";
    
    stringstream ss(log);
    string dontcare, timestamp, loglevel, message;

    // TODO: Extract timestamp
    // TODO: Extract log level
    // TODO: Extract message
    getline(ss, dontcare, '[');
    getline(ss, timestamp, ']'); trim_inplace(timestamp);
    getline(ss, loglevel, ':');  trim_inplace(loglevel);
    getline(ss, message);        trim_inplace(message);

    // Print all parts (timestamp, log level, message)
    // If log level is "ERROR", print a warning prefix
    cout<<"Timestamp: "<< timestamp<<"\n";
    if(loglevel =="ERROR"){
        cout<<"LogLevel WARNING:"<<loglevel<<"\n";
    } else {
        cout<<"LogLevel: "<<loglevel<<"\n";
    }
    cout<<"Message: "<<message<<"\n";

    return 0;
}
