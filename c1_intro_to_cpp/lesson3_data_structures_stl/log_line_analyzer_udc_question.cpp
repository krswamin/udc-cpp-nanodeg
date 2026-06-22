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

int main() {
    std::string log = "[2025-07-14 10:15:32] ERROR: Camera stream failed to start";

    // TODO: Extract timestamp
    // TODO: Extract log level
    // TODO: Extract message

    // Print all parts (timestamp, log level, message)
    // If log level is "ERROR", print a warning prefix

    return 0;
}
