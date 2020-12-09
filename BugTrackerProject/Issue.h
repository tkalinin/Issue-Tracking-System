#pragma once
#include <string>
using namespace std;

class Issue{
    private:
    int id;
    string name;
    //string type; //stretch goal
    string description;
    string status;
    string priority;

    public:
    Issue(int id, string name, string description, string status, string priority);
    ~Issue();
    void displayIssue();


};