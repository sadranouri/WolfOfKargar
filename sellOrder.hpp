#ifndef SELLORDER_HPP
#define SELLORDER_HPP

#include <iostream>
using namespace std;


class Shareholder;
class Company;

class SellOrder
{
public:   
    SellOrder(Shareholder &seller, int shares_cont, Company &company, int share_price, int order_id);
    Shareholder& getSeller();
    int getSharesCount();
    int getSharePrice();
    int getOrderId();
    Company getCompany();
    bool operator==(const SellOrder &other)const{
        return order_id_ == other.order_id_;
    }
private:
    Shareholder *seller_;
    int shares_count_;
    Company *company_;
    int share_price_;
    int order_id_;
};

#endif