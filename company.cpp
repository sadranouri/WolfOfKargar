#include <iostream>
#include <vector>
#include <algorithm>
#include "company.hpp"
#include "sellOrder.hpp"
#include "buyOrder.hpp"
using namespace std;


Company::Company(string name, int price)
{
    setData(name, price);
}


void Company::setData(string name, int price)
{
    name_ = name;
    price_ = price;
}


string Company::getName() const
{
    return name_;
}


void Company::addSellOrder(SellOrder sellOrder)
{
    sellOrders.push_back(sellOrder);
}


void Company::addBuyOrder(BuyOrder buyOrder)
{
    buyOrders.push_back(buyOrder);
}


vector<SellOrder>& Company::getSellOrders()
{
    return sellOrders;
}


vector<BuyOrder>& Company::getBuyOrders()
{
    return buyOrders;
}


void Company::removeSellOrder(SellOrder sellOrder)
{
    sellOrders.erase(remove(sellOrders.begin(), sellOrders.end(), sellOrder), sellOrders.end());
}


void Company::removeBuyOrder(BuyOrder buyOrder)
{
    buyOrders.erase(remove(buyOrders.begin(), buyOrders.end(), buyOrder), buyOrders.end());
}


void Company::changePrice(int price)
{
    price_ = price;
}


int Company::getPrice() const
{
    return price_;
}


void Company::addSoldShare(SoldShare soldShare)
{
    soldShares.push_back(soldShare);
}


void Company::addBoughtShare(BoughtShare boughtShare)
{
    boughtShares.push_back(boughtShare);
}


vector<SoldShare> Company::getSoldShares()
{
    return soldShares;
}


vector<BoughtShare> Company::getBoughtShares()
{
    return boughtShares;
}