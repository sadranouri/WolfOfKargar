#include "sellOrder.hpp"
#include "shareholder.hpp"
#include "company.hpp"

SellOrder::SellOrder(Shareholder &seller, int shares_cont, Company &company, int share_price, int order_id)
    : seller_(&seller), shares_count_(shares_cont), company_(&company), share_price_(share_price), order_id_(order_id) {}

Shareholder& SellOrder::getSeller() 
{
    return *seller_;
}

int SellOrder::getSharesCount()
{
    return shares_count_;
}

int SellOrder::getSharePrice() 
{
    return share_price_;
}

int SellOrder::getOrderId()
{
    return order_id_;
}

Company SellOrder::getCompany()
{
    return *company_;
}