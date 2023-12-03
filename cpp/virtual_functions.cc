#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

static int prof_cur_id = 1;
static int stud_cur_id = 1;
class Person {
    public: 
        string name;
        int age;
        virtual void getdata(){;}
        virtual void putdata(){;}
};

class Professor : public Person{

    public:
        int publications;
        int cur_id;
        Professor(){
            cur_id = prof_cur_id;
            prof_cur_id++;
        }
        void getdata(){
            cin >> name >> age >> publications;
        }
        void putdata(){
            cout << name << " " << age << " " << publications << " " << cur_id << endl;
        }

};

class Student : public Person{
    public:
        int cur_id = 1;
        vector<int> marks;
        Student(){
            cur_id = stud_cur_id;
            stud_cur_id++;
        }
        void getdata(){
            cin >> name >> age;
            int mark;
            for(int i = 0; i < 6; i++){
                cin >> mark;
                marks.push_back(mark);
            }
        }

        void putdata(){
            int totalMarks = 0;
            for(int mark : marks){
                totalMarks += mark;
            }
            cout << name << " " << age << " " << totalMarks << " " << cur_id << endl;
        }
};

int main(){

    int n, val;
    cin>>n; //The number of objects that is going to be created.
    Person *per[n];

    for(int i = 0;i < n;i++){

        cin>>val;
        if(val == 1){
            // If val is 1 current object is of type Professor
            per[i] = new Professor;

        }
        else per[i] = new Student; // Else the current object is of type Student

        per[i]->getdata(); // Get the data from the user.

    }

    for(int i=0;i<n;i++)
        per[i]->putdata(); // Print the required output for each object.

    return 0;

}

