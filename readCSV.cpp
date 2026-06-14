#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include "company.hpp"
#include <vector>

using namespace std;


map<string, int> companiesFile(string companiesCSV)
{
    map<string, int> companiesData;
    ifstream file(companiesCSV);
    string line;
    getline(file, line);

    while(getline(file, line))
    {
        istringstream ss(line);
        string name;
        string stringPrice;
        int price;

        if(getline(ss, name, ','))
        {
            if(getline(ss, stringPrice))
            {
                price = stoi(stringPrice);
            }
        }
        companiesData[name] = price;
    }
    return companiesData;
}



struct SHdata
{
    string username;
    int credit;
    map<string, int> shares; 
};

vector<SHdata> shareholdersFile(string shareholdersCSV)
{
    vector<SHdata> shareholdersData;
    ifstream file(shareholdersCSV);
    string line;
    
    getline(file, line);

    while(getline(file, line))
    {
        if(line.empty() || line == "\r") continue;

        istringstream ss(line);
        string username;
        string stringCredit;
        int credit;
        string allSharesString;

        
        if(getline(ss, username, ','))
        {
            
            if(getline(ss, stringCredit, ','))
            {
                credit = stoi(stringCredit);

                SHdata currentShareholder;
                currentShareholder.username = username;
                currentShareholder.credit = credit;

                if(getline(ss, allSharesString))
                {
                    istringstream sharesStream(allSharesString);
                    string singleSharePair;

                    while(getline(sharesStream, singleSharePair, ';'))
                    {
                        istringstream pairStream(singleSharePair);
                        string companyName;
                        string stringNumberOfShares;

                        if(getline(pairStream, companyName, ':') && getline(pairStream, stringNumberOfShares))
                        {
                            currentShareholder.shares[companyName] = stoi(stringNumberOfShares);
                        }
                    }
                }
                
                shareholdersData.push_back(currentShareholder);
            }
        }
    }
    return shareholdersData;
}