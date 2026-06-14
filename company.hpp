#ifndef COMPANY_HPP
#define COMPANY_HPP
#include <iostream>
#include <vector>
#include <string>
#include "sellOrder.hpp"
#include "buyOrder.hpp"
using namespace std;

struct SoldShare {
    int shares_count;
    int price;
    int id;
};

struct BoughtShare {
    int shares_count;
    int price;
    int id; 
};

class Company {
public:
    Company(std::string name, int price);
    void setData(std::string name, int price);
    string getName() const;
    void addSellOrder(SellOrder sellOrder);
    void addBuyOrder(BuyOrder buyOrder);
    vector<SellOrder>& getSellOrders();
    vector<BuyOrder>& getBuyOrders();
    void removeSellOrder(SellOrder sellOrder);
    void removeBuyOrder(BuyOrder buyOrder);
    void changePrice(int price);
    void addSoldShare(SoldShare soldShare);
    void addBoughtShare(BoughtShare boughtShare);
    vector<SoldShare> getSoldShares();
    vector<BoughtShare> getBoughtShares();
    int getPrice() const;
    bool operator<(const Company &other) const {
        return name_ < other.name_;
    }
private:
    string name_;
    int price_;
    vector<SellOrder> sellOrders;
    vector<BuyOrder> buyOrders;
    vector<SoldShare> soldShares;
    vector<BoughtShare> boughtShares;
};

#endif