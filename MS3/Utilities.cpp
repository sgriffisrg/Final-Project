// Name: Stephen Griffis	
// Seneca Student ID: 119051183
// Seneca email: sgriffis@myseneca.ca
// Date of completion:
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include "Utilities.h"

char Utilities::m_delimiter = '\0';

const std::string Utilities::extractToken(const std::string& str, size_t& pos, bool& check){
	std::string dummy = str;
	dummy.erase(0, pos);
	std::stringstream ss(dummy);
	std::getline(ss, dummy, m_delimiter);
	if (ss) {
		if (dummy.size() > 0) {
			if (dummy.size() > m_widthField) {
				m_widthField = dummy.size();
			}
		}
		else {
			throw "No Token Found Between Delimiters!";
		}
	}
	else {
		check = false;
	}
	return dummy;
}