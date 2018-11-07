#include	<iostream>
#include	<stdexcept>
#include	<string>
#include	"GroceryCheckout.h"

using namespace std;

bool GroceryInventory::AddItem(const string& name, int quantity,
							   float price, bool taxable)
{
	if (myMap.find(name) == myMap.end()) {
		GroceryItem jjj = GroceryItem(name, quantity, price, taxable);
		myMap[name] = jjj;
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
{
	ifstream file(fileName);
	string name;
	Receipt c;
	c.subtotal_ = 0;

	if (file.is_open())
	{
		while (true)
		{
			file >> name;
			if (!file.fail())
			{
				GroceryItem* b = FindItem(name);
				ReceiptItem a = ReceiptItem(name, b->price_);
				b->quantity_--;

				c.item_.push_back(a);
				c.subtotal_ += b->price_;
				c.taxAmount_ = c.subtotal_ * newTaxRate;
				c.total_ = c.subtotal_ + c.taxAmount_;
			}
			else
			{
				break;
			}
		}
		file.close();
		// Ask prof about taxrate error
		//cout << c.subtotal_ << " " << c.taxAmount_ << " " << c.total_ << endl;
		return c;
	}
	else
	{
		cout << "Could not open file " + fileName << endl;
	}

}

GroceryItem*	GroceryInventory::FindItem(const string& name)
{
	try {
		return &myMap.at(name);
	}
	catch (out_of_range e) {
		return nullptr;
	}
}

bool GroceryInventory::RemoveItem(const string& name)
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
{
	newTaxRate = taxRate / 100;
}

size_t GroceryInventory::Size()
{
	return myMap.size();
}
