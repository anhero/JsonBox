#ifndef JB_OBJECT_H
#define JB_OBJECT_H

#include <string>
#include <map>
#include <iostream>

#include "Value.h"

namespace JsonBox {
	class Object {
		friend std::ostream& operator<<(std::ostream& output, const Object& o);
	public:
		Object();
		Object(const Object& src);
		Object& operator=(const Object& src);
		
		Value* getValue(const std::string& name);
		void setValue(const std::string& name, const Value& value);
		
		bool containsValue(const std::string& name) const;
	private:
		std::map<std::string, Value> values;
	};
}

#endif