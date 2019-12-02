#ifndef TASK_H
#define TASK_H
#include <iostream>
#include <deque>
#include <string>
#include "Item.h"
#include "CustomerOrder.h"

class Task : public Item {
	std::deque<CustomerOrder> m_orders;
	Task* m_pNextTask;
public:
	Task(const std::string&);
	Task(const Task&) = delete;
	Task& operator=(Task&) = delete;
	Task(Task&&) = delete;
	Task& operator=(Task&&) = delete;
	void runProcess(std::ostream&);
	bool moveTask();
	void setNextTask(Task&);
	bool getCompleted(CustomerOrder&);
	void validate(std::ostream&);
	Task& operator+=(CustomerOrder&&);
};

#endif // !TASK_H