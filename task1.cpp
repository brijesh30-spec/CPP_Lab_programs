// Task 1 (Weeks 1-6): Student Management using C++ OOP
// Student class with encapsulation, parameterized constructor, overloaded functions,
// static member (student count), friend function and overloaded > operator (compare by marks).
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// ---------- Topic 1: From C to C++ (namespace, const, reference) ----------
namespace Util {
    const int SUBJECTS = 3;                       // const instead of #define
    void printLine(char ch = '-', int n = 52) {   // default arguments
        cout << string(n, ch) << "\n";
    }
}

class Student {
private:                                          // Encapsulation: data is hidden
    string name;
    int    rollNo;
    int   *marks;                                 // dynamic memory for subject marks
    static int studentCount;                      // static member: counts students

public:
    // Parameterized constructor (Topic 4)
    Student(string n, int roll, int m1, int m2, int m3)
        : name(n), rollNo(roll), marks(new int[Util::SUBJECTS]) {
        marks[0] = m1; marks[1] = m2; marks[2] = m3;
        ++studentCount;
        cout << "  [Constructor] Student " << name << " (Roll " << rollNo << ") created\n";
    }
    // Copy constructor: deep copy so two objects never share the same array
    Student(const Student &s)
        : name(s.name + " (copy)"), rollNo(s.rollNo), marks(new int[Util::SUBJECTS]) {
        for (int i = 0; i < Util::SUBJECTS; i++) marks[i] = s.marks[i];
        ++studentCount;
        cout << "  [Copy ctor]   Copy of " << s.name << " created\n";
    }
    // Destructor frees dynamic memory
    ~Student() {
        delete[] marks;
        --studentCount;
        cout << "  [Destructor]  Student " << name << " destroyed\n";
    }

    // Inline getters (Topic 2 / Topic 3)
    inline string getName()  const { return name; }
    inline int    getRollNo() const { return rollNo; }
    inline int    totalMarks() const { return marks[0] + marks[1] + marks[2]; }
    inline double average()   const { return totalMarks() / 3.0; }

    // Overloaded functions (Topic 2): same name, different parameters
    void updateMarks(int subject, int value) {                 // change one subject
        if (subject >= 0 && subject < Util::SUBJECTS && value >= 0 && value <= 100)
            marks[subject] = value;
    }
    void updateMarks(int m1, int m2, int m3) {                 // change all subjects
        updateMarks(0, m1); updateMarks(1, m2); updateMarks(2, m3);
    }
    void display() const {                                     // default: brief
        cout << "  Roll " << rollNo << " | " << left << setw(8) << name
             << " | Total: " << totalMarks() << "\n";
    }
    void display(bool detailed) const {                        // overloaded: detailed
        display();
        if (detailed)
            cout << "      Marks: " << marks[0] << ", " << marks[1] << ", " << marks[2]
                 << " | Average: " << fixed << setprecision(2) << average() << "\n";
    }

    // Static member function (Topic 5)
    static int getStudentCount() { return studentCount; }

    // Friend function (Topic 5): can read private data
    friend void showGrade(const Student &s);

    // Overloaded > operator (Topic 6): compare students by marks
    bool operator>(const Student &other) const {
        return totalMarks() > other.totalMarks();
    }
    // Overloaded << for easy printing
    friend ostream &operator<<(ostream &os, const Student &s) {
        return os << s.name << " [Roll " << s.rollNo << ", Total " << s.totalMarks() << "]";
    }
};

int Student::studentCount = 0;                    // definition of static member

void showGrade(const Student &s) {                // friend: accesses private marks[]
    double avg = (s.marks[0] + s.marks[1] + s.marks[2]) / 3.0;
    char grade = avg >= 90 ? 'A' : avg >= 75 ? 'B' : avg >= 60 ? 'C' : 'D';
    cout << "  " << s.name << ": average " << fixed << setprecision(2) << avg
         << " -> Grade " << grade << "\n";
}

void swapMarks(int &a, int &b) { int t = a; a = b; b = t; }     // reference parameters

int main() {
    cout << "=== Student Management System ===\n";

    cout << "\n--- Constructors (parameterized, copy) ---\n";
    Student s1("Asha", 101, 88, 92, 95);
    Student s2("Ravi", 102, 70, 65, 80);
    Student s3("Meena", 103, 90, 85, 78);
    Student s4(s2);                                // copy constructor

    cout << "\n--- Encapsulation & overloaded display() ---\n";
    s1.display();
    s2.display(true);
    s3.display(true);

    cout << "\n--- Overloaded updateMarks() ---\n";
    s2.updateMarks(1, 75);                         // one subject
    s2.updateMarks(72, 75, 82);                    // all subjects
    s2.display(true);

    cout << "\n--- Static member: student count ---\n";
    cout << "Students created so far: " << Student::getStudentCount() << "\n";
    {
        Student temp("Temp", 999, 50, 50, 50);
        cout << "Inside block: " << Student::getStudentCount() << "\n";
    }
    cout << "After block : " << Student::getStudentCount() << "\n";

    cout << "\n--- Friend function showGrade() ---\n";
    showGrade(s1); showGrade(s2); showGrade(s3);

    cout << "\n--- Overloaded > operator (compare by marks) ---\n";
    cout << s1 << " > " << s2 << " ? " << (s1 > s2 ? "Yes" : "No") << "\n";
    cout << s2 << " > " << s3 << " ? " << (s2 > s3 ? "Yes" : "No") << "\n";
    const Student &topper = (s1 > s3) ? ((s1 > s2) ? s1 : s2) : ((s3 > s2) ? s3 : s2);
    cout << "Topper: " << topper.getName() << "\n";

    cout << "\n--- Reference parameters (C to C++) ---\n";
    int x = 10, y = 20;
    swapMarks(x, y);
    cout << "After swapMarks: x=" << x << " y=" << y << "\n";

    cout << "\nProgram ending, destructors run:\n";
    return 0;
}
