/*
Bug Tracker Project
A class to create and edit bug report submissions stored in a .csv file

Timofei Kalinin
12/2/2020
*/
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "EditList.h"

    //============================================================================
    //Constructor
    //Purpose:  set up the key variables
    //
    //Description:  File name is passed to this class from outside
    //============================================================================
    EditList::EditList(std::string inName) {
        fileName = inName;
        fileNameFull = fileName + ".csv";
        ID = 0;
	}

	//============================================================================
    //updateStatus() Function
    //Purpose:  Update bug report's status column
    //
    //Description:  Asks user to pick an option for status definition
    //              Returns a string with new status
    //============================================================================
	std::string EditList::updateStatus() {
	    int statusOption = 999;
	    std::string statusTemp;
	    std::cout << "\nChoose status: Type number 1, 2, 3 or 0.\n\n1) Will fix\n2) Will not fix\n3) Fixed\n\n\n0) Skip this step.\n" << std::endl;
        while(1) {
            std::cin >> statusOption;
            //validate input
            if(std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(123, '\n');
                std::cout << "ERROR: Wrong input. Try again." << std::endl;
                 //break out if the output is valid and is one of the choice options
                std::cin >> statusOption;
            }
            else {
                if(statusOption >= 0 && statusOption <= 3) {
                    break;
                }
                else
                    std::cout << "ERROR: Please enter only numbers 1, 2, 3 or 0." << std::endl;
            }
        }
        //define the status
        switch(statusOption) {
            case 1:
                statusTemp = "Will fix";
                break;
            case 2:
                statusTemp = "Will not fix";
                break;
            case 3:
                statusTemp = "Fixed";
                break;
            case 0:
                statusTemp = "NEW";
                break;
        }

        return statusTemp;
	}

    //============================================================================
    //editReport() Function
    //Purpose:  Edit an existing bug report entry
    //
    //Description:  Open an existing bug report file, and create a new file with updated
    //              information. Ask the user which bug report to update, and ask for new
    //              information. Then traverse the old file line by line, save the data in
    //              a string vector. Insert the updated data into a new file.
    //============================================================================
	void EditList::editReport() {
        //new file with updated reports
        std::fstream fileNew;
        std::string fileNameNewFull = fileName + "_new.csv";

        //open existing file
        file.open(fileNameFull, std::ios::in);
        //create a new file
        fileNew.open(fileNameNewFull, std::ios::out);
        //number of the bug report to be updated
        int reportID;
        //what field to update, by column number
        int columnNum, i;
        int index = 1;
        //boolean for whether the bug report exists
        bool reportExists;
        //updated info provided by the user
        std::string newInfo;
        //storing file data
        std::string line, word;
        std::vector<std::string> row;

        //ask which report to update, user will provide ID #
        std::cout << "Which bug report would you like to update?" << std::endl;
        std::cout << "Please provide its ID # (ie. 2)" << std::endl;

        //get input and validate
        while(true) {
            if(std::cin >> reportID) {
                break;
            }
            else {
                std::cout << "Wrong input. Please enter an integer number" << std::endl;
                std::cin.clear();
                std::cin.ignore(123,'\n');
            }
        }

        //ask which field of the report to update
        std::cout << "Which field of the report would you like to update?" << std::endl;
        std::cout << "\n1) Title\n2) Description\n3) Priority\n4) Status" << std::endl;
        std::cout << "Type a number corresponding to your desired option (ie. 1 for Title)" << std::endl;
        //get input and validate
        while(true) {
            std::cin >> columnNum;
            if (columnNum >= 1 && columnNum <= 4)
                break;
            else
                std::cout << "Wrong input. Try again." << std::endl;
        }
        //ID takes the first column, so increment columnNum by 1
        columnNum++;

        //ask for new info to be inserted for either Title, Description or Priority
        switch(columnNum) {
            case 2:
            {
                std::cout << "Enter new title: ";
                std::cin >> newInfo;
                break;
            }
            case 3:
            {
                std::cout << "Enter new description: ";
                std::cin >> newInfo;
                break;
            }
            case 4:
            {
                std::cout << "Enter new priority: ";
                std::cin >> newInfo;
                break;
            }
            case 5:
            {
                newInfo = updateStatus();
                break;
            }
        }

        //traverse the file one line at a time
        while(!file.eof()) {
            row.clear();

            //read a row from the file and put it into a stringstream
            std::getline(file, line);
            std::stringstream s(line);

            //use the string stream to split the row into columns
            while(getline(s, word, ',')) {
                //store each column's content in a vector
                row.push_back(word);
            }

            //if the ID of row matches the user's input, insert new data into appropriate column
            //had trouble before with to_string(), so using stringstream to convert int to string instead
            std::string temp;
            std::stringstream tempSS;
            tempSS << reportID;
            tempSS >> temp;

            //insert new info if the ID matches and it's the right column
            if(row[0] == temp) {
                reportExists = true;
                row[columnNum-1] = newInfo;

                if(!file.eof()) {
                    for(i = 0; i < 4; i++) {
                        //write updated data to new file
                        fileNew << row[i] << ", ";
                    }
                    fileNew << row[4] << "\n";
                }
                index++;
            }
            //insert old info if it's not the report we want edited
            else {
                if(!file.eof()) {
                    for(i = 0; i < 4; i++) {
                        //writing other data to new file
                        fileNew << row[i] << ", ";
                    }
                    fileNew << row[4] << "\n";
                }
            }
            if(file.eof())
                break;
        }
        if(!reportExists)
            std::cout << "Bug report not found" << std::endl;

        file.close();
        fileNew.close();

        //remove existing file
        std::remove(fileNameFull.c_str());
        //rename new file with updated reports
        rename(fileNameNewFull.c_str(), fileNameFull.c_str());
	}

	//============================================================================
    //createID() Function
    //Purpose:  Create a unique ID for the bug report being submitted
    //
    //Description:  Reads through the .csv file and counts the number of filled rows.
    //              Each row is 1 bug report and ID is incremented by 1
    //============================================================================
	int EditList::createID() {
        std::string temp;
        int tempID = 1;
        file.open(fileName, std::ios::in);
        //count the # of rows, where each row is 1 bug report
        //increment the ID variable by # of filled rows
        while(getline(file, temp)) {
            tempID++;
        }
        file.close();

        return tempID;
	}

	//============================================================================
    //createReport() Function
    //Purpose:  creates a new bug report submission by appending to the .csv file
    //
    //Description:  opens the file, asks for user input, writes the input into the file and closes it.
    //              Also calls createID() to generate a unique ID number for the report
    //============================================================================
	void EditList::createReport() {
        std::string temp;
        ID = createID();
        file.open(fileName, std::ios::out | std::ios::app);

        //ask user to enter bug info
        //this may need some try/catch checks, such as the input being empty
        std::cout << "Enter title: ";
        std::getline(std::cin, name);
        std::cout << "Description: ";
        std::getline(std::cin, desc);
        std::cout << "Priority: ";
        std::getline(std::cin, priority);
        //Status choice
        status = updateStatus();

        //write to file
        file << ID << "," << name << "," << desc << "," << priority << "," << status << "\n";
        std::cout << "Report successfully created." << std::endl;

        file.close();
	}

    //============================================================================
    //Destructor
    //Purpose:  Clean up
    //
    //Description:  Deletes created variables after the work is finished
    //============================================================================
	EditList::~EditList() {
        //code
	}
