#ifndef JB_ARRAY_H
#define JB_ARRAY_H

#include <iostream>
#include <deque>

namespace JsonBox {
	class Value;
	class Array : public std::deque<Value> {
		friend class Value;
		friend std::ostream& operator<<(std::ostream& output, const Array& a);
	private:
		void output(std::ostream& output, bool indent = true,
					bool escapeAll = true) const;
		void output(std::ostream& output, unsigned int& level,
					bool indent = true,
					bool escapeAll = true) const;
	};
}

#endif