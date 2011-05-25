#include "Object.h"

namespace JsonBox {
	Object::Object(const std::string& newName, const Value& newValue) :
	name(newName), value(newValue) {
	}
	
	Object::Object(const Object& src) : name(src.name), value(src.value) {
	}
	
	Object& Object::operator=(const Object& src) {
		if(this != &src) {
			name = src.name;
			value = src.value;
		}
		return *this;
	}
	
	const std::string& Object::getName() const {
		return name;
	}
	
	void Object::setName(std::string const& newName) {
		name = newName;
	}
	
	Value& Object::getValue() {
		return value;
	}
	
	void Object::setValue(const Value& newValue) {
		value = newValue;
	}
}