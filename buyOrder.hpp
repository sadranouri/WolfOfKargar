#ifndef BUYORDER_HPP
#define BUYORDER_HPP

#include <iostream>
using namespace std;


class Shareholder;
class Company;

class BuyOrder
{
public:
    BuyOrder(Shareholder &buyer, int shares_cont, Company &company, int s_price, int order_id);
    Shareholder& getBuyer();
    int getSharesCount();
    int getSharePrice();
    int getOrderId();
    bool operator==(const BuyOrder &other) const{
        return order_id_ == other.order_id_;
    }
private:
    Shareholder *buyer_;
    int shares_count_;
    Company *company_;
    int share_price_;
    int order_id_;
};

#endif