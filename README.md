# Student Record Management System

A simple **C++ console-based Student Record Management System** built using **Object-Oriented Programming (OOP), STL, and file handling**.

This project is designed to demonstrate practical C++ concepts while remaining easy to explain in interviews.

## Features

- Add a new student
- View all student records
- Search for a student by ID
- Update student details
- Delete a student
- Sort students by marks
- Persistent data storage using a text file
- Input validation
- Menu-driven console interface

## Technologies

- C++
- OOP
- STL `vector`
- STL algorithms
- File Handling with `fstream`
- Standard library strings and streams

## Project Structure

```text
CPP_Student_Record_Management_System/
│
├── main.cpp
├── README.md
├── .gitignore
└── students.txt
```

## C++ Concepts Demonstrated

### 1. Classes and Objects

The `Student` class stores:

- Student ID
- Name
- Age
- Course
- Marks

The `StudentManager` class handles the complete record-management logic.

### 2. Encapsulation

Student data members are private and are accessed through public getter and setter functions.

### 3. STL Vector

All student records are stored in:

```cpp
vector<Student> students;
```

This makes it easy to add, remove, search, and iterate through records.

### 4. File Handling

Student records are stored in `students.txt`.

The program uses:

- `ifstream` to read records
- `ofstream` to save records

The data remains available even after the program is closed.

### 5. STL Algorithms

The project uses `sort()` to arrange students according to marks.

### 6. Lambda Function

A lambda function is used as the sorting comparator:

```cpp
[](const Student& a, const Student& b) {
    return a.getMarks() > b.getMarks();
}
```

## How Data Is Stored

Each student is stored in one line using `|` as a separator:

```text
101|Rahul Kumar|20|Computer Science|87.5
```

The `serialize()` function converts an object into a text representation.

The `deserialize()` function converts the stored text back into a `Student` object.

## How to Run

### Windows

Install a C++ compiler such as MinGW/G++.

Open PowerShell or Command Prompt in the project folder:

```bash
g++ -std=c++17 main.cpp -o student_manager.exe
```

Run:

```bash
.\student_manager.exe
```

### Linux / macOS

Compile:

```bash
g++ -std=c++17 main.cpp -o student_manager
```

Run:

```bash
./student_manager
```

## Example Menu

```text
========================================
     STUDENT RECORD MANAGEMENT SYSTEM
========================================
1. Add Student
2. View All Students
3. Search Student
4. Update Student
5. Delete Student
6. Sort by Marks
7. Exit
========================================
```

## Time Complexity

| Operation | Complexity |
|---|---|
| Add Student | O(1) average |
| Search Student | O(n) |
| Update Student | O(n) |
| Delete Student | O(n) |
| View Students | O(n) |
| Sort by Marks | O(n log n) |

Here, `n` is the number of student records.

## Interview Explanation

### What did you build?

> I built a console-based Student Record Management System in C++. It supports CRUD operations such as adding, viewing, searching, updating, and deleting student records. I used OOP to structure the application, STL vector to store records, standard algorithms for sorting, and file handling to persist the data.

### Why did you use a vector?

> I used a vector because the number of students can change dynamically. It provides convenient insertion, deletion, iteration, and access to records.

### How is data persistent?

> I store the records in a text file using `ofstream`. When the program starts, it reads the file using `ifstream` and reconstructs the Student objects.

### What OOP concepts did you use?

> I used classes, objects, encapsulation, constructors, private data members, and public getter/setter methods.

### What STL concepts did you use?

> I used `vector` for storing student records, `sort` for sorting records, and standard string/stream utilities for input and file processing.

### What is the complexity of searching?

> Searching by student ID is O(n) because the program checks the records sequentially.

### What is the complexity of sorting?

> Sorting uses the standard sorting algorithm and takes O(n log n) time.

## Possible Future Improvements

- Add a graphical user interface
- Use SQLite/MySQL instead of a text file
- Add login/authentication
- Add GPA calculation
- Export records to CSV
- Add multiple sorting options
- Add role-based access

## Resume Description

### Option 1

**Student Record Management System | C++**

- Developed a menu-driven student record management system using C++ OOP and STL, supporting CRUD operations, search, and marks-based sorting.
- Implemented persistent file storage using `fstream` and managed records dynamically using `vector` and standard algorithms.

### Option 2

**Student Record Management System | C++**

- Built a C++ console application for managing student records with add, search, update, delete, and sorting functionality.
- Applied OOP, STL containers, file handling, and algorithmic concepts for efficient record management.

## Author

**Angalakuduru Varshith**
