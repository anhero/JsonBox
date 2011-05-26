#ifndef JB_OBJECT_H
#define JB_OBJECT_H

#include <string>
#include <map>

#include "Value.h"

namespace JsonBox {
	class Object {
	public:
		Object(const std::string& newName = std::string(),
			   const Value& newValue = Value());
		Object(const Object& src);
		Object& operator=(const Object& src);
		
		const std::string& getName() const;
		void setName(const std::string& newName);
		
		Value& getValue();
		void setValue(const Value& newValue);
	private:
		std::string name;
		Value value;
	};
}

#endif