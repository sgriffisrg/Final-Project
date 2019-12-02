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
	size_t pos = 0;
	const char delimit = util.getDelimiter();
	bool check = true;
	std::string extracted;
	int count = 0;

	while (check) {
		std::string dummy = line;
		try {
			extracted = util.extractToken(line, pos, check);
			dummy.erase(0, pos);
			pos += (dummy.find(delimit) + 1) > 0 ? dummy.find(delimit) + 1 : pos += dummy.size();
			if (count == 0) {
				m_name = extracted;
				
				count++;
			}
			else if(count == 1) {
				m_product = extracted;
				count++;
			}
			else {
				products.push_back(extracted);
				m_cntItem++;
			}
		}
		catch (const char* msg) {
			std::cerr << msg << std::endl;
		}
	}
	m_cntItem--;
	m_widthField = m_widthField < util.getFieldWidth() ? util.getFieldWidth() : m_widthField;

	count = 0;
	m_lstItem = new ItemInfo*[m_cntItem];

	for (size_t i = 0; i < m_cntItem; i++){//std::vector<std::string>::iterator i = products.begin(); i != products.end(); i++, count++) {
		m_lstItem[i] = new ItemInfo(products[i]);
	}
}

CustomerOrder::~CustomerOrder() {
	delete[] m_lstItem;
}

CustomerOrder::CustomerOrder(const CustomerOrder& src) {
	throw std::string("Unable to make copies of the class CustomerOrder");
}

CustomerOrder::CustomerOrder(CustomerOrder&& src) noexcept {
	*this = std::move(src);
}

CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) {
	m_name = src.m_name;
	m_product = src.m_product;
	m_cntItem = src.m_cntItem;
	m_lstItem = src.m_lstItem;

	src.m_name = "";
	src.m_product = "";
	src.m_cntItem = 0;
	src.m_lstItem = nullptr;
	return *this;
}

bool CustomerOrder::getItemFillState(std::string str) const {
	for (size_t i = 0; i < m_cntItem; i++) {
		if (m_lstItem[i]->m_itemName == str) {
			return m_lstItem[i]->m_fillState;
		}
	}
	return true;
}

bool CustomerOrder::getOrderFillState() const{
	bool flag = true;

	for (size_t i = 0; i < m_cntItem; i++) {
		if (!m_lstItem[i]->m_fillState)
			flag = false;
	}
	return flag;
}

void CustomerOrder::fillItem(Item& item, std::ostream& os) {
	for (size_t i = 0; i < m_cntItem; i++) {
		if (m_lstItem[i]->m_itemName == item.getName()) {
			if (item.getQuantity() > 0) {
				item.updateQuantity();
				m_lstItem[i]->m_fillState = true;
				m_lstItem[i]->m_serialNumber = item.getSerialNumber();
				os << "Filled " << m_name << ", " << m_product << '[' << m_lstItem[i]->m_itemName << ']' << std::endl;
			}
			else {
				os << "Unable to fill " << m_name << ", " << m_product << '[' << m_lstItem[i]->m_itemName << ']' << std::endl;
			}
		}
	}
}

void CustomerOrder::display(std::ostream& os) const{
	os << m_name << " - " << m_product << std::endl;

	for (size_t i = 0; i < m_cntItem; i++) {
		std::string temp = m_lstItem[i]->m_fillState ? "FILLED" : "MISSING";
		os << "["; os.width(6); os.fill('0'); os << m_lstItem[i]->m_serialNumber << "]"; os.fill(' '); os << std::setw(m_widthField) << m_lstItem[i]->m_itemName << " - ";
		os << temp << std::endl;
	}
}