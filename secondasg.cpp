#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
using namespace std;

const int MAX_STUDENTS = 100;
const int MAX_COURSES = 10;

class Course {
private:
    string courseName;
    string courseNumber;
    int creditHours;
    char grade;

public:
    void setCourse(const string& cName, const string& cNumber, int cHours, char cGrade) {
        courseName = cName;
        courseNumber = cNumber;
        creditHours = cHours;
        grade = cGrade;
    }

    int getCreditHours() const {
        return creditHours;
    }

    char getGrade() const {
        return grade;
    }

    string getCourseNumber() const {
        return courseNumber;
    }

    void printCourse(ofstream& outputFile) const {
        outputFile << setw(10) << courseNumber << setw(15) << courseName
                   << setw(10) << creditHours << setw(8) << grade << endl;
    }
};

class PersonType {
protected:
    string firstName;
    string lastName;

public:
    void setName(const string& fName, const string& lName) {
        firstName = fName;
        lastName = lName;
    }

    string getName() const {
        return firstName + " " + lastName;
    }
};

class StudentType : public PersonType {
private:
    int studentID;
    bool isTuitionPaid;
    int numCourses;
    Course courses[MAX_COURSES];

public:
    void setStudentDetails(const string& fName, const string& lName, int sID, bool tuitionPaid, int nCourses) {
        setName(fName, lName);
        studentID = sID;
        isTuitionPaid = tuitionPaid;
        numCourses = nCourses;
    }

    void addCourse(int index, const string& courseName, const string& courseNumber, int creditHours, char grade) {
        if (index >= 0 && index < MAX_COURSES) {
            courses[index].setCourse(courseName, courseNumber, creditHours, grade);
        }
    }

    double calculateGPA() const {
        double totalPoints = 0.0;
        int totalCredits = 0;

        for (int i = 0; i < numCourses; ++i) {
            int credits = courses[i].getCreditHours();
            char grade = courses[i].getGrade();
            double gradePoint;

            switch (grade) {
                case 'A': gradePoint = 4.0; break;
                case 'B': gradePoint = 3.0; break;
                case 'C': gradePoint = 2.0; break;
                case 'D': gradePoint = 1.0; break;
                case 'F': gradePoint = 0.0; break;
                default: gradePoint = 0.0;
            }

            totalPoints += credits * gradePoint;
            totalCredits += credits;
        }

        return (totalCredits > 0) ? totalPoints / totalCredits : 0.0;
    }

    void printReport(ofstream& outputFile, int tuitionFeePerCredit) const {
        outputFile << "Öğrenci adı: " << getName() << "\n"
                   << "Öğrenci No: " << studentID << "\n"
                   << "Ders sayısı: " << numCourses << "\n";

        if (isTuitionPaid) {
            outputFile << setw(10) << "Ders No" << setw(15) << "Ders Adı"
                       << setw(10) << "Kredi" << setw(8) << "Not" << "\n";

            for (int i = 0; i < numCourses; ++i) {
                courses[i].printCourse(outputFile);
            }

            int totalCredits = 0;
            for (int i = 0; i < numCourses; ++i) {
                totalCredits += courses[i].getCreditHours();
            }

            outputFile << "Toplam kredi: " << totalCredits << "\n"
                       << "Dönem ortalamsı: " << fixed << setprecision(2)
                       << calculateGPA() << "\n";
        } else {
            outputFile << "Notlar harç ücreti ödenmediği için gösterilememektedir..\n";
            int totalBill = 0;
            for (int i = 0; i < numCourses; ++i) {
                totalBill += courses[i].getCreditHours() * tuitionFeePerCredit;
            }
            outputFile << "Toplam harç: " << totalBill << " TL\n";
        }

        outputFile << "---------------------------------------\n";
    }
};

int main() {
    ifstream inputFile("input.txt");
    ofstream outputFile("output.txt");

    if (!inputFile) {
        cerr << "Girdi dosyası açılamadı.\n";
        return 1;
    }

    if (!outputFile) {
        cerr << "Çıktı dosyası açılamadı.\n";
        return 1;
    }

    int numStudents, tuitionPerCredit;
    inputFile >> numStudents >> tuitionPerCredit;

    StudentType students[MAX_STUDENTS];

    for (int i = 0; i < numStudents; ++i) {
        string firstName, lastName, courseName, courseNumber;
        int studentID, numCourses, creditHours;
        char isTuitionPaid, grade;

        inputFile >> firstName >> lastName >> studentID >> isTuitionPaid >> numCourses;

        students[i].setStudentDetails(firstName, lastName, studentID, (isTuitionPaid == 'Y'), numCourses);

        for (int j = 0; j < numCourses; ++j) {
            inputFile >> courseName >> courseNumber >> creditHours >> grade;
            students[i].addCourse(j, courseName, courseNumber, creditHours, grade);
        }
    }

    for (int i = 0; i < numStudents; ++i) {
        students[i].printReport(outputFile, tuitionPerCredit);
    }

    inputFile.close();
    outputFile.close();

    return 0;
}
