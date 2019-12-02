#include "LineManager.h"

LineManager::LineManager(const std::string& str, std::vector<Task*>& tasks, std::vector<CustomerOrder>& orders) {
	m_cntCustomerOrder = orders.size();
	std::ifstream file(str);
	int count = 0;

	if (!file) {
		throw std::string("Unable to open the file.");
	}

	while (!file.eof()) {
		Utilities util;
		std::string dummy;
		util.setDelimiter('|');
		char delimit = util.getDelimiter();
		std::getline(file, dummy);
		const std::string record = dummy;
		size_t pos = 0;
		bool check = true;
		std::vector<std::string> extracted;
		

		while (check) {
			std::string extr;
			try {
				extr = util.extractToken(record, pos, check);
				extracted.push_back(extr);
				pos += (dummy.find(delimit) + 1) > 0 ? dummy.find(delimit) + 1 : pos += dummy.size();
			}
			catch (const char* msg) {
				std::cerr << msg << std::endl;
			}

		}
		count++;
		Task* one;
		std::for_each(tasks.begin(), tasks.end(), [&](Task* task) {
			if (task->getName() == extracted[0]) {
				one = task;
				if (count == 1)
					front = task;
			}
		});
		if (extracted.size() > 1) {
			std::for_each(tasks.begin(), tasks.end(), [&](Task* task) {

				if (task->getName() == extracted[1]) {	
					one->setNextTask(*task);
				}
			});
		}
		
	}
	for (size_t i = 0; i < orders.size(); i++) {
		ToBeFilled.push_front(std::move(orders[i]));
	}
	std::for_each(tasks.begin(), tasks.end(), [&](Task* task) {
		AssemblyLine.push_back(task);
	});
	file.close();
}

bool LineManager::run(std::ostream& os) {
	bool check = false;

	if (!ToBeFilled.empty()) {
		*front += std::move(ToBeFilled.back());	
		ToBeFilled.pop_back();
	}

	std::for_each(AssemblyLine.begin(), AssemblyLine.end(), [&](Task* task) {
		task->runProcess(os);
	});
	
	CustomerOrder order;

	std::for_each(AssemblyLine.begin(), AssemblyLine.end(), [&](Task* task) {
		task->moveTask();
		if (task->getCompleted(order)) {
			Completed.push_back(std::move(order));
		}
	});
	if (Completed.size() == m_cntCustomerOrder) {
		check = true;
	}

	return check;
}

void LineManager::displayCompleted(std::ostream& os) const {
	for (auto i = Completed.begin(); i != Completed.end(); i++) {
		i->display(os);
	}
}

void LineManager::validateTasks() const {
	for (Task* i : AssemblyLine) {
		i->validate(std::cout);
	}
}