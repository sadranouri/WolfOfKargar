#pragma once
#include <iostream>
#include <vector>
#include "company.hpp"
#include "shareholder.hpp"
#include "readCSV.hpp"
#include "sellOrder.hpp"
#include "buyOrder.hpp"
#include <algorithm>
using namespace std;

class WolfOfKargar
{
public:
    WolfOfKargar(string companiesCSV, string shareholdersCSV);
    void run(string companiesCSV, string shareholdersCSV);
private:
    vector<Company> companies;
    vector<Shareholder> shareholders;
    void setVectors(string companiesCSV, string shareholdersCSV);
    void answerRequest(string request);
    void registering(string registerUsername, int registerCredit);
    void sellOrder(string username, int shares_count, string company, int share_price);
    void buyOrder(string username, int shares_count, string company, int share_price);
    void sellOrderMatcher(Company &company, int count, int price, SellOrder sellOrder, Shareholder &seller);
    void buyOrderMatcher(Company &company, int count, int price, BuyOrder buyOrder, Shareholder &buyer);
    void cancelOrder(int id);
    void reportPortfolio(string username);
    void freeSharesOutput(Shareholder &shareholder);
    void lockedSharesOutput(Shareholder &shareholder);
    void reportCompany(string company);
    int totalFreeAssets(Shareholder &shareholder);
    bool alreadyQueuedBuyOrderCheck(Shareholder &seller, Company &company);
    bool alreadyQueuedSellOrderCheck(Shareholder &buyer, Company &company);
    bool freeShareCheck(Shareholder &seller, Company &company, int count);
    bool freeCreditCheck(Shareholder &buyer, Company &company, int count, int price);
    
    int order_id;
    vector<SellOrder> inOrderSellOrders(Company &company);
    vector<BuyOrder> inOrderBuyOrders(Company &company);
};