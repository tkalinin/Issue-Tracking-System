#pragma once
#include <map>
#include "Issue.h"
using namespace std;

int randomID();
void createIssue();
void createIssueMap(int, string, string, string, string);
void displayAllIssues();
void createIssuesFile();

//TODO
//void appendIssueToFile();
//void displaySpecificIssue(int);
//void updateIssue();
//...

