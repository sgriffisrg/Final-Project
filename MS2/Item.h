// Name: Stephen Griffis	
// Seneca Student ID: 119051183
// Seneca email: sgriffis@myseneca.ca
// Date of completion:
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef ITEM_H
#define ITEM_H
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "Utilities.h"

class Item { //Item class declaration
	std::string m_name;
	std::string m_description;
	size_t m_serialNumber;
	size_t m_quantity;
public:
	static size_t m_widthField;
	Item(const std::string&);
	const std::string& getName() const { return m_name; }
	const unsigned int getSerialNumber() { return m_serialNumber++; }
	const unsigned int getQuantity() { return m_quantity; }
	void updateQuantity();
	void display(std::ostream&, bool) const;
};


#endif // !SDDS_ITEM_H