# SDF_TA



# Smart Library Management System

This is a console-based Smart Library Management System developed in C++ using object-oriented principles. It manages book inventory, members, transactions, and includes functionality for issuing, returning, fine calculation, and generating reports. Exception handling, STL usage, and custom data structures (like a doubly linked list) are used throughout the system.

## Features

- Manage books (add, issue, return)
- Manage members (register, track borrowed books)
- Handle issue/return transactions using `std::stack`
- Fine calculation based on due date and return time
- Custom `linkedlist<T>` template class for dynamic storage
- Exception handling for:
  - Invalid member ID
  - Book not available
  - Maximum issue limit exceeded
- UML-class-design-based architecture with aggregation and composition relationships

## Project Structure

- `classes.hpp` – Contains all class definitions (`Book`, `Member`, `Librarian`, `Library`, `Transaction`)
- `linkedlist.hpp` – Custom template-based doubly linked list
- `exceptions.hpp` – Inheritance-based exception hierarchy
- `main.cpp` – Program entry point demonstrating full functionality

## How to Compile and Run

``` bash
git clone https://github.com/Karvy-Singh/SDF_TA.git
cd ./SDF_TA/source
```

### On Linux

```bash

g++ -std=c++17 main.cpp -o main
./main
````

### On Windows (MinGW or WSL)

```bash
g++ -std=c++17 main.cpp -o main.exe
main.exe
```

> Ensure all header files (`classes.hpp`, `linkedlist.hpp`, `exceptions.hpp`) are in the same directory as `main.cpp`.

## Requirements

* C++17 or later
* g++ / MinGW or any C++ compiler supporting C++17
* Works on Linux, Windows (via g++), and WSL


