#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Student {
private:
    int id;
    string name;
    int age;
    string course;
    double marks;

public:
    Student() : id(0), age(0), marks(0.0) {}

    Student(int id, const string& name, int age, const string& course, double marks)
        : id(id), name(name), age(age), course(course), marks(marks) {}

    int getId() const { return id; }
    string getName() const { return name; }
    int getAge() const { return age; }
    string getCourse() const { return course; }
    double getMarks() const { return marks; }

    void setName(const string& value) { name = value; }
    void setAge(int value) { age = value; }
    void setCourse(const string& value) { course = value; }
    void setMarks(double value) { marks = value; }

    void display() const {
        cout << left
             << setw(8) << id
             << setw(25) << name
             << setw(8) << age
             << setw(20) << course
             << fixed << setprecision(2) << marks << '\n';
    }

    string serialize() const {
        ostringstream out;
        out << id << "|" << name << "|" << age << "|" << course << "|" << marks;
        return out.str();
    }

    static bool deserialize(const string& line, Student& student) {
        string idStr, name, ageStr, course, marksStr;
        stringstream ss(line);

        if (!getline(ss, idStr, '|') ||
            !getline(ss, name, '|') ||
            !getline(ss, ageStr, '|') ||
            !getline(ss, course, '|') ||
            !getline(ss, marksStr)) {
            return false;
        }

        try {
            int id = stoi(idStr);
            int age = stoi(ageStr);
            double marks = stod(marksStr);
            student = Student(id, name, age, course, marks);
        } catch (...) {
            return false;
        }

        return true;
    }
};

class StudentManager {
private:
    vector<Student> students;
    const string filename = "students.txt";

    void clearInput() {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    int readInt(const string& prompt) {
        int value;
        while (true) {
            cout << prompt;
            if (cin >> value) {
                clearInput();
                return value;
            }
            cout << "Invalid input. Please enter a number.\n";
            clearInput();
        }
    }

    double readMarks() {
        double marks;
        while (true) {
            cout << "Enter marks (0-100): ";
            if (cin >> marks && marks >= 0 && marks <= 100) {
                clearInput();
                return marks;
            }
            cout << "Marks must be between 0 and 100.\n";
            clearInput();
        }
    }

    int findStudentIndex(int id) const {
        for (size_t i = 0; i < students.size(); ++i) {
            if (students[i].getId() == id) {
                return static_cast<int>(i);
            }
        }
        return -1;
    }

    void saveToFile() const {
        ofstream file(filename);

        if (!file) {
            cout << "Error: Could not save records.\n";
            return;
        }

        for (const Student& student : students) {
            file << student.serialize() << '\n';
        }
    }

    void loadFromFile() {
        ifstream file(filename);

        if (!file) {
            return;
        }

        string line;
        while (getline(file, line)) {
            if (line.empty()) {
                continue;
            }

            Student student;
            if (Student::deserialize(line, student)) {
                students.push_back(student);
            }
        }
    }

    void printHeader() const {
        cout << "\n"
             << left
             << setw(8) << "ID"
             << setw(25) << "Name"
             << setw(8) << "Age"
             << setw(20) << "Course"
             << "Marks\n";
        cout << string(75, '-') << '\n';
    }

public:
    StudentManager() {
        loadFromFile();
    }

    void addStudent() {
        cout << "\n--- Add Student ---\n";

        int id = readInt("Enter student ID: ");

        if (findStudentIndex(id) != -1) {
            cout << "A student with this ID already exists.\n";
            return;
        }

        string name;
        cout << "Enter name: ";
        getline(cin, name);

        int age = readInt("Enter age: ");

        string course;
        cout << "Enter course: ";
        getline(cin, course);

        double marks = readMarks();

        students.emplace_back(id, name, age, course, marks);
        saveToFile();

        cout << "Student added successfully.\n";
    }

    void viewStudents() const {
        cout << "\n--- Student Records ---\n";

        if (students.empty()) {
            cout << "No student records found.\n";
            return;
        }

        printHeader();

        for (const Student& student : students) {
            student.display();
        }
    }

    void searchStudent() const {
        cout << "\n--- Search Student ---\n";

        int id = readInt("Enter student ID: ");
        int index = findStudentIndex(id);

        if (index == -1) {
            cout << "Student not found.\n";
            return;
        }

        printHeader();
        students[index].display();
    }

    void updateStudent() {
        cout << "\n--- Update Student ---\n";

        int id = readInt("Enter student ID: ");
        int index = findStudentIndex(id);

        if (index == -1) {
            cout << "Student not found.\n";
            return;
        }

        string name;
        cout << "Enter new name: ";
        getline(cin, name);

        int age = readInt("Enter new age: ");

        string course;
        cout << "Enter new course: ";
        getline(cin, course);

        double marks = readMarks();

        students[index].setName(name);
        students[index].setAge(age);
        students[index].setCourse(course);
        students[index].setMarks(marks);

        saveToFile();

        cout << "Student updated successfully.\n";
    }

    void deleteStudent() {
        cout << "\n--- Delete Student ---\n";

        int id = readInt("Enter student ID: ");
        int index = findStudentIndex(id);

        if (index == -1) {
            cout << "Student not found.\n";
            return;
        }

        students.erase(students.begin() + index);
        saveToFile();

        cout << "Student deleted successfully.\n";
    }

    void sortByMarks() {
        cout << "\n--- Sort by Marks ---\n";

        if (students.empty()) {
            cout << "No student records found.\n";
            return;
        }

        sort(students.begin(), students.end(),
             [](const Student& a, const Student& b) {
                 return a.getMarks() > b.getMarks();
             });

        saveToFile();
        cout << "Records sorted by marks in descending order.\n";
        viewStudents();
    }

    void run() {
        while (true) {
            cout << "\n========================================\n";
            cout << "     STUDENT RECORD MANAGEMENT SYSTEM\n";
            cout << "========================================\n";
            cout << "1. Add Student\n";
            cout << "2. View All Students\n";
            cout << "3. Search Student\n";
            cout << "4. Update Student\n";
            cout << "5. Delete Student\n";
            cout << "6. Sort by Marks\n";
            cout << "7. Exit\n";
            cout << "========================================\n";

            int choice = readInt("Enter your choice: ");

            switch (choice) {
                case 1:
                    addStudent();
                    break;
                case 2:
                    viewStudents();
                    break;
                case 3:
                    searchStudent();
                    break;
                case 4:
                    updateStudent();
                    break;
                case 5:
                    deleteStudent();
                    break;
                case 6:
                    sortByMarks();
                    break;
                case 7:
                    cout << "Thank you for using the system.\n";
                    return;
                default:
                    cout << "Invalid choice. Please select 1-7.\n";
            }
        }
    }
};

int main() {
    StudentManager manager;
    manager.run();
    return 0;
}
