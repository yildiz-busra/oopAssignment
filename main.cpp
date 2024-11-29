#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
using namespace std;
#define N 125

class Student {
    private:
        string* name;
        string* studentNo;
        float* midterm;
        float* secondExam;
        float* assignment;
        float* final;
        int* attendance;
        float* avrg;
    public:
        Student();
        ~Student();
        void readFromCSV(const string& filename);
        void average();
        void print(int,string);
};

Student :: Student(){
    name = new string[N];
    studentNo = new string[N];
    midterm = new float[N];
    secondExam = new float[N];
    assignment = new float[N];
    final = new float[N];
    attendance = new int[N];
    avrg = new float[N];
    
}

Student :: ~Student() {
    delete[] name;
    delete[] studentNo;
    delete[] midterm;
    delete[] secondExam;
    delete[] assignment;
    delete[] final;
    delete[] attendance;
    delete[] avrg;
}

void Student :: readFromCSV(const string& filename){
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }
    string line;
    getline(file, line); //başlık satırını atla

    int i=0;
    while(getline(file,line) && i<N){
        stringstream ss(line);
        string temp;

        getline(ss, name[i], ',');
        getline(ss, studentNo[i], ',');
        getline(ss, temp, ',');
        midterm[i]=stof(temp);
        getline(ss, temp, ',');
        secondExam[i]=stof(temp); 
        getline(ss, temp, ',');
        assignment[i]=stof(temp);
        getline(ss, temp, ',');
        final[i]=stof(temp);
        getline(ss, temp, '\n');
        attendance[i]=stoi(temp);

        i++;
    }
    file.close();

}

void Student :: average(){
    int i=0;
    while(i<N){
        avrg[i] = midterm[i]*0.2 + secondExam[i]*0.2 + assignment[i]*0.2 + final[i]*0.4; 
        i++;
        }
}

void Student :: print(int a=-1,string fl=""){
    ofstream file;
    if (!fl.empty()) {
        file.open(fl); 
        if (!file.is_open()) {
            cerr << "Error writing output file!" << endl;
            return;
        }
    }

    ostream& output = fl.empty() ? cout : file;

    output<<left<<setw(25)<<"Öğrenci Adı"<<right<<setw(10)<<"Numara"<<right<<setw(10)<<"Ortalama"<<endl;
    output<<string(45, '-')<<endl;

    int i=0;
    if(a==0){
        while(i<N){
            if(avrg[i]<50){
                output<<left<<setw(25)<<name[i]<<right<<setw(10)<<studentNo[i]<<right<<setw(10)<<avrg[i]<<endl;
            }
            i++;
        }
    }
    if(a==1){
        while(i<N){
            if(avrg[i]>=50){
                output<<left<<setw(25)<<name[i]<<right<<setw(10)<<studentNo[i]<<right<<setw(10)<<avrg[i]<<endl;
            }
            i++;
        }  
    }
    else{
        while(i<N){
            output<<left<<setw(25)<<name[i]<<right<<setw(10)<<studentNo[i]<<right<<setw(10)<<avrg[i]<<endl;
            i++;
        }
        
    }
    file.close();
}

int main(){
    Student student;
    int a;
    student.readFromCSV("input.csv");
    student.average();
    student.print(1,"");

}