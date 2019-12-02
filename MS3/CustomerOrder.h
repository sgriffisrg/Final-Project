// Name: Stephen Griffis	
// Seneca Student ID: 119051183
// Seneca email: sgriffis@myseneca.ca
// Date of completion:
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef CUSTOMERORDER_H
#define CUSTOMERORDER_H
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>
#include "Item.h"
#include "Utilities.h"

struct ItemInfo
{
	std::string m_itemName;
	unsigned int m_serialNumber = 0;
	bool m_fillState = false;

	ItemInfo(std::string src) : m_itemName(src) {};
};

class CustomerOrder {
	std::string m_name;
	std::string m_product;
	unsigned int m_cntItem;
	ItemInfo** m_lstItem;
	static size_t m_widthField;

public:
	CustomerOrder();
	CustomerOrder(std::string&);
	CustomerOrder(const CustomerOrder&);
	~CustomerOrder();
	CustomerOrder& operator=(CustomerOrder&) = delete;
	CustomerOrder(CustomerOrder&&) noexcept;
	CustomerOrder& operator=(CustomerOrder&&);
	bool getItemFillState(std::string) const;
	bool getOrderFillState() const;
	void fillItem(Item&, std::ostream&);
	void display(std::ostream&) const;

};

#endif // !CUSTOMERORDER_H