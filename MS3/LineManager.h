#ifndef LINEMANAGER_H
#define LINEMANAGER_H
#include <vector>
#include <deque>
#include <string>
#include <algorithm>
#include <fstream>
#include "Utilities.h"
#include "Task.h"
#include "CustomerOrder.h"

class LineManager {
	std::vector<Task*> AssemblyLine;
	std::deque<CustomerOrder> ToBeFilled;
	std::deque<CustomerOrder> Completed;
	unsigned int m_cntCustomerOrder;
	Task* front;
public:
	LineManager(const std::string&, std::vector<Task*>&, std::vector<CustomerOrder>&);
	bool run(std::ostream&);
	void displayCompleted(std::ostream&) const;
	void validateTasks() const;
};

#endif // !LINEMANAGER_H
