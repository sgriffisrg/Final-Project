// Name: Stephen Griffis	
// Seneca Student ID: 119051183
// Seneca email: sgriffis@myseneca.ca
// Date of completion:
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include "Item.h"

size_t Item::m_widthField = 0;

Item::Item(const std::string& str) {
	Utilities util;
	const char delimit = util.getDelimiter();
	size_t pos = str.find(delimit);
	std::vector<std::string> container;
	bool check = true;
	while (check) {
		std::string extracted;
		std::string dummy = str;
		extracted = util.extractToken(str, pos, check);
		
		dummy.erase(0, pos);
		
		pos += dummy.find(delimit);
		std::cout << delimit << std::endl;

		if (extracted.size() > 0) {
			container.push_back(std::move(extracted));
		}
		
	}
	m_widthField = m_widthField < util.getFieldWidth() ? util.getFieldWidth() : m_widthField;
}

void Item::updateQuantity() {
	if (m_quantity - 1 >= 0)
		m_quantity--;
}

void Item::display(std::ostream& out, bool check) const {

	out << std::setw(m_widthField) << std::left << m_name << "[" << std::setw(6) << m_serialNumber << "]" << std::endl;

	if (check) {
		out << std::setw(m_widthField) << std::left << "Quantity: " + m_quantity << "Description: " + m_description << std::endl;
	}
	else {
		out << std::endl;
	}

}