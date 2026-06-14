#ifndef SHAREHOLDER_HPP
#define SHAREHOLDER_HPP

#include <iostream>
#include <string>
#include <map>
#include "company.hpp"

struct CreditInfo {
    int total = 0;
    int locked = 0;
    int free() const { return total - locked; }
};

struct ShareInfo {
    int total = 0;
    int locked = 0;
    int free() const { return total - locked; }
};

class Shareholder {
public:
    Shareholder(std::string username, int credit);
    
    Shareholder(std::string username, int credit, std::map<std::string, int> initial_shares); 
    
    std::string getUsername();
    CreditInfo& getCredit();
    std::map<std::string, ShareInfo>& getShares();
    
    void lockShares(Company company, int count);
    void lockCredit(int count, int price);
    void sellShares(Company company, int count);
    void pay(int count, int price);
    void getPaid(int count, int price);
    void freeShares(SellOrder sellOrder, Company company, int count);
    void freeCredit(BuyOrder buyOrder, int count, int price);
    void payImmediate(int count, int price);
    void sellSharesImmediate(Company company, int count);
    void receiveShares(Company company, int count);
private:
    std::string username_;
    CreditInfo credit_;
    std::map<std::string, ShareInfo> shares_;
};

#endif