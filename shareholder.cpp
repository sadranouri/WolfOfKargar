#include <iostream>
#include <map>
#include "shareholder.hpp"
#include "company.hpp"
using namespace std;


Shareholder::Shareholder(string username, int credit)
{
    username_ = username;
    credit_.total = credit;
}


Shareholder::Shareholder(string username, int credit, map<string, int> initial_shares)
{
    username_ = username;
    credit_.total = credit;
  
    for(auto const& share : initial_shares)
    {
        shares_[share.first].total = share.second;
    }
}


string Shareholder::getUsername()
{
    return username_;
}


map<string, ShareInfo>& Shareholder::getShares()
{
    return shares_;
}


CreditInfo& Shareholder::getCredit()
{
    return credit_;
}


void Shareholder::lockShares(Company company, int count) {
    shares_[company.getName()].locked += count;
}


void Shareholder::lockCredit(int count, int price)
{
    credit_.locked += count * price;
}


void Shareholder::sellShares(Company company, int count) {
    shares_[company.getName()].locked -= count;
    shares_[company.getName()].total -= count;
}


void Shareholder::pay(int count, int price)
{
    credit_.locked -= count * price;
    credit_.total -= count * price;
}


void Shareholder::getPaid(int count, int price)
{
    credit_.total += count * price;
}


void Shareholder::freeShares(SellOrder sellOrder, Company company, int count)
{
    shares_[company.getName()].locked -= count;
}

void Shareholder::freeCredit(BuyOrder buyOrder, int count, int price)
{
    credit_.locked -= count * price;
}


void Shareholder::payImmediate(int count, int price)
{
    credit_.total -= count * price; 
}


void Shareholder::sellSharesImmediate(Company company, int count)
{
    shares_[company.getName()].total -= count; 
}


void Shareholder::receiveShares(Company company, int count)
{
    shares_[company.getName()].total += count;
}