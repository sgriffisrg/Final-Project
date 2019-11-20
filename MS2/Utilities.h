// Name: Stephen Griffis	
// Seneca Student ID: 119051183
// Seneca email: sgriffis@myseneca.ca
// Date of completion:
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SDDS_UTILITIES_H
#define SDDS_UTILITIES_H
#include <string>
#include <sstream>
#include <iostream>

class Utilities {
	size_t m_widthField = 1;
	
public:
	static char m_delimiter;
	void setFieldWidth(size_t width) { m_widthField = width; };
	size_t getFieldWidth() const { return m_widthField; }
	const std::string extractToken(const std::string&, size_t&, bool&);
	static void setDelimiter(const char delimit) { m_delimiter = delimit; }
	const char getDelimiter() const { return m_delimiter; }
};

#endif // !SDDS_UTILITIES_H