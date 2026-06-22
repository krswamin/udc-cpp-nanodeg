/*
Update your Book class to support:

    A default constructor that initializes the book with empty/default values

    A parameterized constructor that sets the book’s title, author, and page count

    A destructor that prints a message when a Book object is destroyed "Destorying book : <title>"

Then update your main() function to create books using both constructors.
*/
#include <iostream>
#include <string>

class Book {
private:
    std::string title;
    std::string author;
    int pageCount;

public:
    // TODO: Add a default constructor
    // TODO: Add a parameterized constructor
    // TODO: Add a destructor

    // Getters
    std::string getTitle() { 
        return title; 
    }
    std::string getAuthor() { 
        return author; 
    }
    int getPageCount() { 
        return pageCount; 
    }
};

int main() {
    //TODO: Use the default constructor to initialize a defaultBook

    //TODO: Use the parametrized constructor to initialize b1 and b2
    
    std::cout << "Default Book:\n";
    std::cout << "Title: " << defaultBook.getTitle() << "\n";
    std::cout << "Author: " << defaultBook.getAuthor() << "\n";
    std::cout << "Pages: " << defaultBook.getPageCount() << "\n\n";

    std::cout << "Book 1:\n";
    std::cout << "Title: " << b1.getTitle() << "\n";
    std::cout << "Author: " << b1.getAuthor() << "\n";
    std::cout << "Pages: " << b1.getPageCount() << "\n";

    std::cout << "Book 2:\n";
    std::cout << "Title: " << b2.getTitle() << "\n";
    std::cout << "Author: " << b2.getAuthor() << "\n";
    std::cout << "Pages: " << b2.getPageCount() << "\n";

    return 0;
}
