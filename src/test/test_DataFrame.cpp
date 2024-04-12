#include "../DataFrame.h"
#include <bits/stdc++.h>

using namespace std;

struct User{
    int id;
    int age;
    char name[50];
} typedef User;

class DataFrameUser : public DataFrame<User> {
    private:
        vector<User> data;
    public:
        void print() {
            cout 
                << right << setw(3) << ""
                << right << setw(3) << "ID"
                << right << setw(20) << "Name" 
                << right << setw(10) << "Age"
                << endl;
            for (int i = 0; i < data.size(); i++) {
                cout 
                    << right << setw(3) << i
                    << right << setw(3) << data[i].id
                    << right << setw(20) << data[i].name 
                    << right << setw(10) << data[i].age
                    << endl;
            }
        }
        void append(User data) {
            this->data.push_back(data);
        }
        int size() {
            return data.size();
        }
};

int main() {
    DataFrameUser df;
    df.append({1, 20, "John"});
    df.append({2, 30, "Doe"});
    df.print();
    cout << "Size: " << df.size() << endl;

    return 0;
}
