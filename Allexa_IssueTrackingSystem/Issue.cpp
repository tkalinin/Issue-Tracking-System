#include <iostream>
#include "Issue.h"

Issue::Issue(int i, string n, string d, string s, string p){
    id = i;
    name = n;
    //type = t;
    description = d;
    status = s;
    priority = p;
}

Issue::~Issue(){}

void Issue::displayIssue(){
    cout << "ID: " << id << endl;
    cout << "Issue name: " << name << endl;
    cout << "Priority Level: " << priority << endl;
    cout << "Description: " << description << endl;
    cout << "Completion status: " << status << endl;
}

//search by string
void Issue::searchTerm(string term) {
    string a = name;
    string b = description;
    string c = status;
    string d = priority;
    
    //check for matching strings
    if (a == term || b == term || c == term || d == term) {
        //displays matches
        displayIssue();
        cout << endl;
    }
}

//search by int ID
void Issue::searchID(int id_s) {
    //checks for matching int ID
    if (id == id_s) {
        //displays matches
        displayIssue();
        cout << endl;
    }
}