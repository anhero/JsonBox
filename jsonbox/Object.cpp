#include "Object.h"

namespace JsonBox {
	Object::Object(){
	}
	
	Object::Object(const Object& src) : values(src.values) {
	}
	
	Object& Object::operator=(const Object& src) {
		if(this != &src) {
			values = src.values;
		}
		return *this;
	}
	
	Value* Object::getValue(const std::string& name) {
		std::map<std::string, Value>::iterator value = values.find(name);
		if(value != values.end()) {
			return &value->second;
		} else {
			return NULL;
		}
	}
	
	void Object::setValue(const std::string& name, const Value& value) {
		values[name] = value;
	}
	
	bool Object::containsValue(const std::string& name) const {
		return values.find(name) != values.end();
	}
	
	std::ostream& operator<<(std::ostream& output, const Object& o) {
		output << '{';
		for(std::map<std::string, Value>::const_iterator i = o.values.begin();
			i != o.values.end(); ++i) {
			if(i != o.values.begin()) {
				output << ", ";
			}
			output << '"' << Value::escapeCharacters(i->first) << "\" : " << i->second;
		}
		output << '}';
		return output;
	}
}