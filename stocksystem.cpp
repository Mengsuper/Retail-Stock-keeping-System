//
//  stocksystem.cpp
//  HW3code
//
//  Created by LI MENG on 2016-06-13.
//  Copyright © 2016 LI MENG. All rights reserved.
//

#include "stocksystem.h"

#include <iostream>
using namespace std;

StockSystem::StockSystem()
{
    balance = 100000.00;
}


//choice 1: Print balance
double StockSystem::GetBalance()
{
    return balance;
}


//Choice 3: Add a new SKU
bool StockSystem::StockNewItem(StockItem item)
{
    if (records.Contains(item))
        return false;
    else
        return records.Insert(item);
}


//Choice 4: Edit item description
bool StockSystem::EditStockItemDescription(int itemsku, string desc)
{
    StockItem* stockitem = records.Retrieve(StockItem(itemsku, "", 0));
    if (stockitem == NULL)
        return false;
    else
        //return records.Insert(stockitem);
        return stockitem->SetDescription(desc);
    
}


//Choice 5: Edit item price
bool StockSystem::EditStockItemPrice(int itemsku, double retailprice)
{
    StockItem* stockitem = records.Retrieve(StockItem(itemsku, "", 0));
    if (stockitem != NULL && retailprice >= 0)
        return stockitem->SetPrice(retailprice);
    else
        return false;
}


//Choice 6: Restock an item

bool StockSystem::Restock(int itemsku, int quantity, double unitprice)
{
    StockItem* stockitem = records.Retrieve(StockItem(itemsku, "", 0));
    if (stockitem != NULL &&  quantity>=0 && unitprice>=0 && balance >= quantity*unitprice)
        {
            if (quantity + stockitem->GetStock() < 1000)
            {
                balance -= quantity * unitprice;
                stockitem->SetStock(stockitem->GetStock() + quantity);
                return true;
            }
            else
            {
                balance -= (1000-stockitem->GetStock()) * unitprice;
                stockitem->SetStock(1000);
                return true;
            }
        }
    else
        return false;


}

//Choice 7: Sell an item

bool StockSystem::Sell(int itemsku, int quantity)
{
    StockItem* stockitem = records.Retrieve(StockItem(itemsku, "", 0));
    if (stockitem != NULL &&  quantity>=0 && stockitem->GetStock()>0)
    {
        if (stockitem->GetStock() > quantity)
        {
            stockitem->SetStock(stockitem->GetStock()-quantity);
            balance += quantity * stockitem->GetPrice();
            return true;
        }
        else
        {
            stockitem->SetStock(0);
            balance += stockitem->GetStock() * stockitem->GetPrice();
            return true;
        }
    }
    
    return false;
    
}