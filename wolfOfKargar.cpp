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

WolfOfKargar::WolfOfKargar(string companiesCSV, string shareholdersCSV)
{
    order_id = 1;
    run(companiesCSV, shareholdersCSV);
}

void WolfOfKargar::run(string companiesCSV, string shareholdersCSV)
{
    setVectors(companiesCSV, shareholdersCSV);

    string request;
    answerRequest(request);
}


void WolfOfKargar::setVectors(string companiesCSV, string shareholdersCSV)
{
    for(auto companie: companiesFile(companiesCSV))
    {
        companies.push_back(Company(companie.first, companie.second));
    }


    for(auto shData : shareholdersFile(shareholdersCSV))
    {
        shareholders.push_back(Shareholder(shData.username, shData.credit, shData.shares));
    }
}

void WolfOfKargar::answerRequest(string request)
{
    while(cin >> request)
    {
        if(request == "register")
        {
            string registerUsername;
            int registerCredit;
            cin >> registerUsername >> registerCredit;
            registering(registerUsername, registerCredit);
        }
        else if(request == "sell_order")
        {
            string username;
            int shares_count;
            string company;
            int share_price; 
            cin >> username >> shares_count >> company >> share_price;
            sellOrder(username, shares_count, company, share_price);
        }
        else if(request == "buy_order")
        {
            string username;
            int shares_count;
            string company;
            int share_price;
            cin >> username >> shares_count >> company >> share_price;
            buyOrder(username, shares_count, company, share_price);
        }
        else if(request == "cancel_order")
        {
            int id;
            cin >> id;
            cancelOrder(id);
        }
        else if(request == "report_portfolio")
        {
            string username;
            cin >> username;
            reportPortfolio(username);
        }
        else if(request == "report_company")
        {
            string company;
            cin >> company;
            reportCompany(company);
        }
    }
}

void WolfOfKargar::registering(string registerUsername, int registerCredit)
{
    vector<Shareholder>::iterator it = find_if(shareholders.begin(), shareholders.end(), [registerUsername](Shareholder &o)
    {
        return o.getUsername() == registerUsername;
    });

    if(it != shareholders.end())
    {
        cout << registerUsername << " already exists." << endl;
    }
    else
    {
        cout << registerUsername << " registered successfully." << endl;
        shareholders.push_back(Shareholder(registerUsername, registerCredit));
    }
}

void WolfOfKargar::sellOrder(string username, int shares_count, string company, int share_price)
{
    vector<Shareholder>::iterator it = find_if(shareholders.begin(), shareholders.end(), [username](Shareholder &a) {
        return a.getUsername() == username;
    });
    vector<Company>::iterator it2 = find_if(companies.begin(), companies.end(), [company](Company &a){
        return a.getName() == company;
    });
    
    Shareholder &seller = *it;
    Company &comp = *it2;

    if(alreadyQueuedBuyOrderCheck(seller, comp))
    {
        cout << username << " already has a buy order queued for " << company << "." << endl;
        return;
    }
    else if(!freeShareCheck(seller, comp, shares_count))
    {
        cout << "Insufficient free shares." << endl;
        return;
    }
    
    SellOrder newSellOrder(seller, shares_count, comp, share_price, order_id);
    order_id++;
    comp.addSellOrder(newSellOrder);
    sellOrderMatcher(comp, shares_count, share_price, newSellOrder, seller);
}

void WolfOfKargar::buyOrder(string username, int shares_count, string company, int share_price)
{
    vector<Shareholder>::iterator it = find_if(shareholders.begin(), shareholders.end(), [username](Shareholder &a) {
        return a.getUsername() == username;
    });
    vector<Company>::iterator it2 = find_if(companies.begin(), companies.end(), [company](Company &a) {
        return a.getName() == company;
    });
    
    Shareholder &buyer = *it;
    Company &comp = *it2;

    if(alreadyQueuedSellOrderCheck(buyer, comp)) 
    {
        cout << username << " already has a sell order queued for " << company << "." << endl;
        return;
    }
    else if(!freeCreditCheck(buyer, comp, shares_count, share_price))
    {
        cout << "Insufficient free credit." << endl;
        return;
    }

    BuyOrder newBuyOrder(buyer, shares_count, comp, share_price, order_id);
    order_id++;
    comp.addBuyOrder(newBuyOrder);
    buyOrderMatcher(comp, shares_count, share_price, newBuyOrder, buyer);
}

bool WolfOfKargar::alreadyQueuedBuyOrderCheck(Shareholder &buyer, Company &company)
{
    vector<BuyOrder> &orders = company.getBuyOrders();
    auto it = find_if(orders.begin(), orders.end(), [&](BuyOrder &a){
        return a.getBuyer().getUsername() == buyer.getUsername();
    });
    return it != orders.end();
}

bool WolfOfKargar::alreadyQueuedSellOrderCheck(Shareholder &seller, Company &company)
{
    vector<SellOrder> &orders = company.getSellOrders();
    auto it = find_if(orders.begin(), orders.end(), [&](SellOrder &a){
        return a.getSeller().getUsername() == seller.getUsername();
    });
    return it != orders.end();
}

bool WolfOfKargar::freeShareCheck(Shareholder &seller, Company &company, int count)
{
    return seller.getShares()[company.getName()].free() >= count;
}

bool WolfOfKargar::freeCreditCheck(Shareholder &buyer, Company &company, int count, int price)
{
    return buyer.getCredit().free() >= (price * count);
}

void WolfOfKargar::sellOrderMatcher(Company &company, int count, int price, SellOrder sellOrder, Shareholder &seller)
{
    vector<BuyOrder> &buy_orders = company.getBuyOrders();
    vector<BuyOrder>::iterator it = find_if(buy_orders.begin(), buy_orders.end(), [&](BuyOrder &a){
        return a.getSharesCount() == count && a.getSharePrice() == price;
    });
    if(it == buy_orders.end())
    {
        cout << "Order " << sellOrder.getOrderId() << " queued." << endl;
        seller.lockShares(company, count);
    }
    else
    {
        SoldShare newSoldShare;
        newSoldShare.id = sellOrder.getOrderId();
        newSoldShare.shares_count = count;
        newSoldShare.price = price;
        company.addSoldShare(newSoldShare);
        cout << "Order " << sellOrder.getOrderId() << " matched with order " << (*it).getOrderId() << "." << endl;
        
        vector<Shareholder>::iterator it2 = find_if(shareholders.begin(), shareholders.end(), [&](Shareholder &a){
            return a.getUsername() == (*it).getBuyer().getUsername();
        });

        (*it2).pay(count, price);
        seller.getPaid(count, price);
        seller.sellSharesImmediate(company, count);
        (*it2).receiveShares(company, count);
        company.changePrice(price);
        
        company.removeBuyOrder((*it));
        company.removeSellOrder(sellOrder);
    }
}

void WolfOfKargar::buyOrderMatcher(Company &company, int count, int price, BuyOrder buyOrder, Shareholder &buyer)
{
    vector<SellOrder> &sell_orders = company.getSellOrders();
    vector<SellOrder>::iterator it = find_if(sell_orders.begin(), sell_orders.end(), [&](SellOrder &a){
        return a.getSharesCount() == count && a.getSharePrice() == price;
    });
    if(it == sell_orders.end())
    {
        cout << "Order " << buyOrder.getOrderId() << " queued." << endl;
        buyer.lockCredit(count, price);
    }
    else
    {
        BoughtShare newBoughtShare;
        newBoughtShare.id = buyOrder.getOrderId();
        newBoughtShare.shares_count = count;
        newBoughtShare.price = price;
        company.addBoughtShare(newBoughtShare);
        cout << "Order " << buyOrder.getOrderId() << " matched with order " << (*it).getOrderId() << "." << endl;
        
        vector<Shareholder>::iterator it2 = find_if(shareholders.begin(), shareholders.end(), [&](Shareholder &a){
            return a.getUsername() == (*it).getSeller().getUsername();
        });

        (*it2).getPaid(count, price);
        buyer.payImmediate(count, price);
        (*it2).sellShares(company, count);
        buyer.receiveShares(company, count);
        company.changePrice(price);
        
        company.removeSellOrder((*it));
        company.removeBuyOrder(buyOrder);
    }
}


void WolfOfKargar::cancelOrder(int id)
{
    for (auto &c : companies) {
        auto &buy_orders = c.getBuyOrders();
        auto buy_it = find_if(buy_orders.begin(), buy_orders.end(), [&](BuyOrder &bo){
            return bo.getOrderId() == id;
        });
        if(buy_it != buy_orders.end())
        {
            auto buyer = find_if(shareholders.begin(), shareholders.end(), [&](Shareholder s){
                return s.getUsername() == (*buy_it).getBuyer().getUsername();
            });
            (*buyer).freeCredit((*buy_it), (*buy_it).getSharesCount(), (*buy_it).getSharePrice());
            cout << "Canceled order " << id << "." << endl;
            c.removeBuyOrder(*buy_it);
            return;
        }
        

        auto &sell_orders = c.getSellOrders();
        auto sell_it = find_if(sell_orders.begin(), sell_orders.end(), [&](SellOrder &so){
            return so.getOrderId() == id;
        });
        if(sell_it != sell_orders.end())
        {
            auto seller = find_if(shareholders.begin(), shareholders.end(), [&](Shareholder s){
                return s.getUsername() == (*sell_it).getSeller().getUsername();
            });
            (*seller).freeShares((*sell_it), (*sell_it).getCompany(), (*sell_it).getSharesCount());
            cout << "Canceled order " << id << "." << endl;
            c.removeSellOrder(*sell_it);
            return;
        }
    }
    cout << "Order " << id << " not found." << endl;
}

void WolfOfKargar::reportPortfolio(string username)
{
    vector<Shareholder>::iterator sh = find_if(shareholders.begin(), shareholders.end(), [&](Shareholder &a){
        return a.getUsername() == username;
    });
    if(sh == shareholders.end())
    {
        cout << username << " not found." << endl;
    }
    else
    {
        cout << username << " Portfolio" << endl;
        cout << "Total free assets: $" << totalFreeAssets(*sh) << endl;
        cout << "Free credit: $" << (*sh).getCredit().free() << endl;
        cout << "Locked credit: $" << (*sh).getCredit().locked << endl;
        cout << "Free shares:" << endl;
        freeSharesOutput(*sh);
        cout << "Locked shares:" << endl;
        lockedSharesOutput(*sh);
    }
}

int WolfOfKargar::totalFreeAssets(Shareholder &shareholder)
{
    int total_free_assets = 0;
    for(const auto &share : shareholder.getShares())
    {
        auto it = find_if(companies.begin(), companies.end(), [&](Company &c){
            return c.getName() == share.first;
        });
        
        if(it != companies.end()) {
            total_free_assets += (it->getPrice() * share.second.free());
        }
    }
    total_free_assets += shareholder.getCredit().free();
    return total_free_assets;
}

void WolfOfKargar::freeSharesOutput(Shareholder &shareholder)
{
    int free_share_number = 1;
    for (auto it = shareholder.getShares().begin(); it != shareholder.getShares().end(); ++it)
    {
        if(it->second.free() > 0)
        {
            cout << free_share_number << ". " << it->first << ": " << it->second.free() << endl;
            free_share_number++;
        }
    }
    
    if (free_share_number == 1) 
    {
        cout << "(empty)" << endl;
    }
}

void WolfOfKargar::lockedSharesOutput(Shareholder &shareholder)
{
    int locked_share_number = 1;
    for (auto it = shareholder.getShares().begin(); it != shareholder.getShares().end(); ++it)
    {
        if(it->second.locked > 0)
        {
            cout << locked_share_number << ". " << it->first << ": " << it->second.locked << endl;
            locked_share_number++;
        }
    }
    
    if (locked_share_number == 1) 
    {
        cout << "(empty)" << endl;
    }
}


void WolfOfKargar::reportCompany(string company)
{
    cout << company << " report" << endl;
    vector<Company>::iterator it = find_if(companies.begin(), companies.end(), [&](Company &c){
        return c.getName() == company;
    });

    if(it == companies.end())
    {
        cout << company << " not found." << endl;
        return;
    }

    cout << "Current price: $" << (*it).getPrice() << endl;
    
    
    cout << "sell queue:" << endl;
    vector<SellOrder> sell_orders = inOrderSellOrders(*it);
    if(sell_orders.empty())
    {
        cout << "(empty)" << endl;
    }
    else
    {
        int order_number = 1;
        for(auto so = sell_orders.begin(); so != sell_orders.end(); ++so)
        {
            cout << order_number << ". Shares: " << (*so).getSharesCount() << " - Price: $" << (*so).getSharePrice() << " - ID: " << (*so).getOrderId() << endl;
            order_number++;
        }
    }


    cout << "buy queue:" << endl;
    vector<BuyOrder> buy_orders = inOrderBuyOrders(*it);
    if(buy_orders.empty())
    {
        cout << "(empty)" << endl;
    }
    else
    {
        int order_number = 1;
        for(auto bo = buy_orders.begin(); bo != buy_orders.end(); ++bo)
        {
            cout << order_number << ". Shares: " << (*bo).getSharesCount() << " - Price: $" << (*bo).getSharePrice() << " - ID: " << (*bo).getOrderId() << endl;
            order_number++;
        }
    }
}


vector<SellOrder> WolfOfKargar::inOrderSellOrders(Company &company)
{
    vector<SellOrder> sellOrders = company.getSellOrders();
    sort(sellOrders.begin(), sellOrders.end(), [](SellOrder a, SellOrder b){
        if(a.getSharePrice() == b.getSharePrice())
        {
            return a.getOrderId() < b.getOrderId();
        }
        return a.getSharePrice() < b.getSharePrice();
    });
    return sellOrders;
}


vector<BuyOrder> WolfOfKargar::inOrderBuyOrders(Company &company)
{
    vector<BuyOrder> buyOrders = company.getBuyOrders();
    sort(buyOrders.begin(), buyOrders.end(), [](BuyOrder a, BuyOrder b){
        if(a.getSharePrice() == b.getSharePrice())
        {
            return a.getOrderId() < b.getOrderId();
        }
        return a.getSharePrice() > b.getSharePrice();
    });
    return buyOrders;
}

int main(int argc, char* argv[])
{
    string companiesCSV = argv[1];
    string shareholdersCSV = argv[2];

    WolfOfKargar runProject(companiesCSV, shareholdersCSV);
    return 0;
}