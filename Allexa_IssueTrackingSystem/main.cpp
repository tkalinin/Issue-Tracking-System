#include <iostream>
#include "issueMethods.h"
#include <time.h>
#include <random>

using namespace std;

int main(){
    srand((unsigned) time(0));
    createIssuesFile();
    displayAllIssues();
    displaySpecificIssue();
    return 0;
}

