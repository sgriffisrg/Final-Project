// Name: Stephen Griffis	
// Seneca Student ID: 119051183
// Seneca email: sgriffis@myseneca.ca
// Date of completion:
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include "CustomerOrder.h"

size_t CustomerOrder::m_widthField = 0;

CustomerOrder::CustomerOrder() {
	m_name = "";
	m_product = "";
	m_cntItem = 0;
	m_lstItem = nullptr;
}

CustomerOrder::CustomerOrder(std::string& line) {
	std::vector<std::string> products;
	Utilities util;
	size_t pos;
	const char delimit = util.getDelimiter();
	bool check = true;
	std::string dummy = line;
	std::string extracted;
	int count = 0;
	try {
		extracted = util.extractToken(line, pos, check);
		m_name = extracted;
		dummy.erase(0, pos);
		pos += dummy.find(delimit) + 1;
	}
	catch (const char* msg) {
		std::cerr << msg << std::endl;
	}
	while (check) {
		try {
			extracted = util.extractToken(line, pos, check);
			dummy.erase(0, pos);
			pos += dummy.find(delimit) + 1;
			count++;
			products.push_back(extracted);
		}
		catch (const char* msg) {
			std::cerr << msg << std::endl;
		}
	}
}