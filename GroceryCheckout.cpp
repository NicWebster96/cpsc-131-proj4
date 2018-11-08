#include	<iostream>
#include	<stdexcept>
#include	<string>
#include	"GroceryCheckout.h"

using namespace std;

bool GroceryInventory::AddItem(const string& name, int quantity,
							   float price, bool taxable)
//If there is no duplicate, find() will return an iterator == end iterator.
{
	if (myMap.find(name) == myMap.end()) {  
		GroceryItem newItem = GroceryItem(name, quantity, price, taxable);
		myMap[name] = newItem;
		return true;
	}
	else {
		return false;
	}

}

void GroceryInventory::CreateFromFile(const string& fileName)
{
    ifstream	file(fileName);
	string		name;
	float		price;
	int			quantity;
	bool		taxable;
	
	if (file.is_open())
	{
		while (true)
		{
			file >> name >> quantity >> price >> taxable;
			if (!file.fail())
			{
				AddItem(name, quantity, price, taxable);
			}
			else
			{
				break;
			}
         }
        file.close();
    }
	else
	{
        cout << "Could not open file " + fileName << endl;
    }
	
	return;
}


Receipt GroceryInventory::CreateReceipt(const string& fileName)
//Reads a file containing the item names and finds the item with same
// name in GroceryItem. Adds all the prices together, if taxable multiply
// tax amount by price of that item and add it to total. Returns Receipt type.
{
	ifstream file(fileName);
	string name;
	Receipt newRcpt;
	newRcpt.subtotal_ = 0.0;
	newRcpt.taxAmount_ = 0.0;

	if (file.is_open())
	{
		while (true)
		{
			file >> name;
			if (!file.fail())
			{
				GroceryItem* grocItm = FindItem(name);
				ReceiptItem rcptItm = ReceiptItem(name, grocItm->price_);

				newRcpt.item_.push_back(rcptItm);
				newRcpt.subtotal_ += grocItm->price_;
				if (grocItm->taxable_) { newRcpt.taxAmount_ = grocItm->price_ * newTaxRate; }
				newRcpt.total_ = newRcpt.subtotal_ + newRcpt.taxAmount_;

				grocItm->quantity_--;
			}
			else
			{
				break;
			}
		}
		file.close();
		return newRcpt;
	}
	else
	{
		cout << "Could not open file " + fileName << endl;
	}

}

GroceryItem*	GroceryInventory::FindItem(const string& name)
//Returns reference to mapped value with key name. Otherwise, it
// throws out of range exception and catch returns nullptr.
{
	try {
		return &myMap.at(name);
	}
	catch (out_of_range e) {
		return nullptr;
	}
}

bool GroceryInventory::RemoveItem(const string& name)
//Removes item from map with given name. Return false if item not found.
{
	if (myMap.find(name) != myMap.end()) {
		myMap.erase(name);
		return true;
	}
	else {
		return false;
	}
}

void GroceryInventory::SetTaxRate(float taxRate)
//Sets tax rate.
{
	newTaxRate = taxRate / 100;
}

size_t GroceryInventory::Size()
{
	return myMap.size();
}
