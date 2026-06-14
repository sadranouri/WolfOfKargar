#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include "company.hpp"
#include <vector>

using namespace std;


map<string, int> companiesFile(string companiesCSV);

struct SHdata
{
    string username;
    int credit;
    map<string, int> shares;
};

vector<SHdata> shareholdersFile(string shareholdersCSV);