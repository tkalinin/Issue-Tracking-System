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

