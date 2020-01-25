#include "Task.h"

Task::Task(const std::string& str) : Item(str) { //sets to safe state
	m_pNextTask = nullptr;
}


void Task::runProcess(std::ostream& os) { //runs one task
	
	if (!m_orders.empty()) {
		if (!m_orders.back().getOrderFillState()) {

			m_orders.back().fillItem(*this, os);
		}
	}
}

bool Task::moveTask() { //moves the order to be next in line to be filled
	if (m_pNextTask != nullptr) {
		if (!m_orders.empty()) {
			if (m_orders.back().getItemFillState(getName())) {
				*m_pNextTask += std::move(m_orders.back());
				m_orders.pop_back();
				return true;
			}
		}
	}
	return false;
}

void Task::setNextTask(Task& src) { //sets the next task
	m_pNextTask = &src;
}


bool Task::getCompleted(CustomerOrder& order) { //takes off the order if completed
	if (!m_orders.empty()) {
		if (m_orders.back().getOrderFillState()) {
			order = std::move(m_orders.back());
			m_orders.pop_back();
			return true;
		}
	}
	return false;
}

void Task::validate(std::ostream& os) { //checks if there is a task in line 
	if (m_pNextTask == nullptr)
		os << getName() << "--> END OF LINE" << std::endl;
	else {
		os << getName() << "--> " << m_pNextTask->getName() << std::endl;
	}
}

Task& Task::operator+=(CustomerOrder&& order) { //operator overloaded
	m_orders.push_front(std::move(order));
	return *this;
}

