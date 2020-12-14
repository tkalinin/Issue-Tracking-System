/*
Bug Tracker Project
A class to create and edit bug report submissions stored in a .csv file

Timofei Kalinin
12/2/2020
*/

#pragma once
#include <iostream>
#include <fstream>

class EditList {

protected:
	std::fstream file;
	std::string fileName;
	std::string fileNameFull;

    std::string name;
    int ID;
    std::string desc;
    std::string priority;
    std::string status;


public:
	EditList(std::string inName);
	~EditList();
	//Functions
	std::string updateStatus();
	void createReport();
	void editReport();
	int createID();
};
