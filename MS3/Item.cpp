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
	size_t count = 0;
	const char delimit = util.getDelimiter();
	size_t pos = 0;
	bool check = true;

	while (check) {
		count++;
		std::string extracted;
		std::string dummy = str;
		try {
			extracted = util.extractToken(str, pos, check);
			dummy.erase(0, pos);
			count != 4 ? pos += dummy.find(delimit) + 1 : pos += dummy.size();

			if (count == 1)
				m_name = extracted;
			else if (count == 2)
				m_serialNumber = stoi(extracted);
			else if (count == 3)
				m_quantity = stoi(extracted);
			else if (count == 4)
				m_description = extracted;
		}
		catch (const char* msg) {
			std::cerr << msg << std::endl;
		}
	}

	m_widthField = m_widthField < util.getFieldWidth() ? util.getFieldWidth() : m_widthField;
}

void Item::updateQuantity() {
	if (m_quantity - 1 >= 0)
		m_quantity--;
}

void Item::display(std::ostream& out, bool check) const {

	out << std::left<< std::setw(m_widthField-8)  << m_name << std::right <<"["; out.width(6); out.fill('0'); out << m_serialNumber << "]";
	out.fill(' ');

	if (check) {
		out << std::setw(m_widthField) << std::left << " Quantity: " + std::to_string(m_quantity) << "Description: " << m_description << std::endl;
	}
	else {
		out << std::endl;
	}

}