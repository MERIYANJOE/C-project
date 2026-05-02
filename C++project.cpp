#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
class Student {
public:
    int id;
    char name[50];
    int age;

    void input() {
        cout << "Enter ID: ";
        cin >> id;
        cout << "Enter Name: ";
        cin.ignore();
        cin.getline(name, 50);
        cout << "Enter Age: ";
        cin >> age;
    }

    void display() {
        cout << "\nID: " << id;
        cout << "\nName: " << name;
        cout << "\nAge: " << age << endl;
    }
};
void addStudent() {
    Student s;
    ofstream file("students.dat", ios::binary | ios::app);

    s.input();
    file.write((char*)&s, sizeof(s));

    file.close();
    cout << "Student Added Successfully!\n";
}
void displayStudents() {
    Student s;
    ifstream file("students.dat", ios::binary);

    while (file.read((char*)&s, sizeof(s))) {
        s.display();
        cout << "-------------------";
    }

    file.close();
}
void updateStudent() {
    int id, found = 0;
    cout << "Enter ID to update: ";
    cin >> id;

    fstream file("students.dat", ios::binary | ios::in | ios::out);
    Student s;

    while (file.read((char*)&s, sizeof(s))) {
        if (s.id == id) {
            cout << "Existing Record:";
            s.display();

            cout << "\nEnter New Details:\n";
            s.input();

            int pos = -1 * sizeof(s);
            file.seekp(pos, ios::cur);
            file.write((char*)&s, sizeof(s));

            cout << "Record Updated!\n";
            found = 1;
            break;
        }
    }

    if (!found)
        cout << "Record Not Found!\n";

    file.close();
}
void deleteStudent() {
    int id;
    cout << "Enter ID to delete: ";
    cin >> id;

    ifstream file("students.dat", ios::binary);
    ofstream temp("temp.dat", ios::binary);

    Student s;
    int found = 0;

    while (file.read((char*)&s, sizeof(s))) {
        if (s.id != id) {
            temp.write((char*)&s, sizeof(s));
        } else {
            found = 1;
        }
    }

    file.close();
    temp.close();

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
        cout << "Record Deleted!\n";
    else
        cout << "Record Not Found!\n";
}

int main() {
    int choice;

    do {
        cout << "\n--- Student Management System ---\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Update Student\n";
        cout << "4. Delete Student\n";
        cout << "5. Exit\n";
        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: updateStudent(); break;
            case 4: deleteStudent(); break;
            case 5: cout << "Exiting...\n"; break;
            default: cout << "Invalid Choice!\n";
        }

    } while (choice != 5);

    return 0;
}