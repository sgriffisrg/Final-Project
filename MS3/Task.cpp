#include "Task.h"

Task::Task(const std::string& str) : Item(str) {
	m_pNextTask = nullptr;
}


void Task::runProcess(std::ostream& os) {
	
	if (!m_orders.empty()) {
		if (!m_orders.back().getOrderFillState()) {

			m_orders.back().fillItem(*this, os);
		}
	}
}

bool Task::moveTask() {
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

void Task::setNextTask(Task& src) {
	m_pNextTask = &src;
}


bool Task::getCompleted(CustomerOrder& order) {
	if (!m_orders.empty()) {
		if (m_orders.back().getOrderFillState()) {
			order = std::move(m_orders.back());
			m_orders.pop_back();
			return true;
		}
	}
	return false;
}

void Task::validate(std::ostream& os) {
	if (m_pNextTask == nullptr)
		os << getName() << "--> END OF LINE" << std::endl;
	else {
		os << getName() << "--> " << m_pNextTask->getName() << std::endl;
	}
}

Task& Task::operator+=(CustomerOrder&& order) {
	m_orders.push_front(std::move(order));
	return *this;
}

