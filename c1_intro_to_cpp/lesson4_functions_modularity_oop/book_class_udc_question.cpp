/*
You're building a simple eBook reader app. Each book needs to store and manage its own information.

Your task is to design a Book class that:

    Stores:

        The book's title

        The author

        The pageCount

    Uses private member variables

    Uses public setter and getter methods to interact with those variables

After building the class, create a few Book objects in main() and demonstrate how to set and 
get their information.
*/

#include <iostream>
#include <string>

class Book {
    // TODO: Declare private member variables: title, author, pageCount

public:
    // TODO: Write setter methods: setTitle, setAuthor, setPageCount

    // TODO: Write getter methods: getTitle, getAuthor, getPageCount
};

int main() {
    // Create book objects
    Book b1, b2;

    // TODO: Use setters to assign book data
    // TODO: Use getters to print book details

    return 0;
}

/*
Expected output:
Book 1:
Title: The Pragmatic Programmer
Author: Andy Hunt
Pages: 352

Book 2:
Title: Clean Code
Author: Robert C. Martin
Pages: 464
*/