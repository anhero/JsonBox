#ifndef JB_OBJECT_H
#define JB_OBJECT_H

#include <iostream>
#include <map>
#include <string>

namespace JsonBox {
	class Value;
	class Object : public std::map<std::string, Value> {
		friend class Value;
		friend std::ostream& operator<<(std::ostream& output, const Object& o);
	private:
		void output(std::ostream& output, bool indent = true,
					bool escapeAll = true) const;
		void output(std::ostream& output, unsigned int& level,
					bool indent = true, bool escapeAll = true) const;
	};
}

#endif