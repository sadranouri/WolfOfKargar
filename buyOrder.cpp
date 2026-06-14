#include "buyOrder.hpp"
#include "shareholder.hpp"
#include "company.hpp"

BuyOrder::BuyOrder(Shareholder &buyer, int shares_cont, Company &company, int s_price, int order_id)
    : buyer_(&buyer), shares_count_(shares_cont), company_(&company), share_price_(s_price), order_id_(order_id) {}

Shareholder& BuyOrder::getBuyer() 
{
    return *buyer_;
}

int BuyOrder::getSharesCount()
{
    return shares_count_;
}

/*int BuyOrder::getSharePrice() 
{
    return share_price_;
}

int BuyOrder::getOrderId()
{
    return order_id_;
}*/