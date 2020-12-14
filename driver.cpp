/*
Bug Tracker Project
A class to create and edit bug report submissions stored in a .csv file

Timofei Kalinin
12/2/2020
*/

#include <iostream>
#include "EditList.h"

int main() {

    std::string fileName = "buglist";
    EditList* list1 = new EditList(fileName);
    //Testing creating a file
    list1->createReport();
    //Testing editing an existing bug report
    //list1->editReport();
    return 0;
}
