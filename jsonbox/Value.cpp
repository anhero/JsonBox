#include "Value.h"

#include <cassert>
#include <stack>

namespace JsonBox {
	
	const std::string Value::EMPTY_STRING = std::string();
	const double Value::EMPTY_DOUBLE = 0.0;
	const Object Value::EMPTY_OBJECT = Object();
	const Array Value::EMPTY_ARRAY = Array();
	
	std::string Value::escapeCharacters(const std::string& str) {
		std::string result = str;
		for(size_t i = 0; i < result.length(); ++i) {
			if(result[i] == '"') {
				result.replace(i, 2, "\\\"");
				++i;
			} else if(result[i] == '\\') {
				result.replace(i, 2, "\\\\");
				++i;
			} else if(result[i] == '/') {
				result.replace(i, 2, "\\/");
				++i;
			} else if(result[i] == '\b') {
				result.replace(i, 2, "\\b");
				++i;
			} else if(result[i] == '\f') {
				result.replace(i, 2, "\\f");
				++i;
			} else if(result[i] == '\n') {
				result.replace(i, 2, "\\n");
				++i;
			} else if(result[i] == '\r') {
				result.replace(i, 2, "\\r");
				++i;
			} else if(result[i] == '\t') {
				result.replace(i, 2, "\\t");
				++i;
			}
			// TODO: Should we output unicode characters? (PLEASE NO)
		}
		return result;
	}
	
	Value::Value() : type(Type::NULL_VALUE) {
		valuePointer.stringValue = NULL;
	}
	
	Value::Value(std::ifstream& file) : type(Type::NULL_VALUE) {
		valuePointer.stringValue = NULL;
		loadFromFile(file);
	}
	
	Value::Value(const std::string& newString) : type(Type::NULL_VALUE) {
		valuePointer.stringValue = NULL;
		setString(newString);
	}
	
	Value::Value(const char* newString) : type(Type::NULL_VALUE) {
		valuePointer.stringValue = NULL;
		setString(newString);
	}
	
	Value::Value(int newInt) : type(Type::NULL_VALUE) {
		valuePointer.intValue = NULL;
		setInt(newInt);
	}
	
	Value::Value(double newDouble) : type(Type::NULL_VALUE) {
		valuePointer.doubleValue = NULL;
		setDouble(newDouble);
	}
	
	Value::Value(const Object& newObject) : type(Type::NULL_VALUE) {
		valuePointer.objectValue = NULL;
		setObject(newObject);
	}
	
	Value::Value(const Array& newArray) : type(Type::NULL_VALUE) {
		valuePointer.arrayValue = NULL;
		setArray(newArray);
	}
	
	Value::Value(bool newBoolean) : type(Type::NULL_VALUE) {
		valuePointer.boolValue = NULL;
		setBoolean(newBoolean);
	}
	
	Value::Value(const Value& src) : type(Type::NULL_VALUE) {
		valuePointer.stringValue = NULL;
		setValue(src.valuePointer, src.type);
	}
	
	Value::~Value() {
		switch (type) {
			case Type::STRING:
				if(valuePointer.stringValue) {
					delete valuePointer.stringValue;
				}
				break;
			case Type::INTEGER:
				if(valuePointer.intValue) {
					delete valuePointer.intValue;
				}
				break;
			case Type::DOUBLE:
				if(valuePointer.doubleValue) {
					delete valuePointer.doubleValue;
				}
				break;
			case Type::OBJECT:
				if(valuePointer.objectValue) {
					delete valuePointer.objectValue;
				}
				break;
			case Type::ARRAY:
				if(valuePointer.arrayValue) {
					delete valuePointer.arrayValue;
				}
				break;
			case Type::BOOLEAN:
				if(valuePointer.boolValue) {
					delete valuePointer.boolValue;
				}
				break;
			default:
				break;
		}
	}
	
	Value& Value::operator=(const Value& src) {
		if(this != &src) {
			setValue(src.valuePointer, src.type);
		}
		return *this;
	}
	
	Type::Enum Value::getType() const {
		return type;
	}
	
	bool Value::isString() const {
		return type == Type::STRING;
	}
	
	bool Value::isInteger() const {
		return type == Type::INTEGER;
	}
	
	bool Value::isDouble() const {
		return type == Type::DOUBLE;
	}
	
	bool Value::isObject() const {
		return type == Type::OBJECT;
	}
	
	bool Value::isArray() const {
		return type == Type::ARRAY;
	}
	
	bool Value::isBoolean() const {
		return type == Type::BOOLEAN;
	}

	bool Value::isNull() const {
		return type == Type::NULL_VALUE;
	}
	
	const std::string& Value::getString() const {
		if(type == Type::STRING) {
			assert(valuePointer.stringValue);
			return *valuePointer.stringValue;
		} else {
			return EMPTY_STRING;
		}
	}
	
	void Value::setString(std::string const& newString) {
		setValue(ValueDataPointer(&newString), Type::STRING);
	}
	
	int Value::getInt() const {
		if(type == Type::INTEGER) {
			assert(valuePointer.intValue);
			return *valuePointer.intValue;
		} else {
			return EMPTY_INT;
		}
	}
	
	void Value::setInt(int newInt) {
		setValue(ValueDataPointer(&newInt), Type::INTEGER);
	}
	
	double Value::getDouble() const {
		if(type == Type::DOUBLE) {
			assert(valuePointer.doubleValue);
			return *valuePointer.doubleValue;
		} else {
			return EMPTY_DOUBLE;
		}
	}
	
	void Value::setDouble(double newDouble) {
		setValue(ValueDataPointer(&newDouble), Type::DOUBLE);
	}
	
	const Object& Value::getObject() const {
		if(type == Type::OBJECT) {
			assert(valuePointer.objectValue);
			return *valuePointer.objectValue;
		} else {
			return EMPTY_OBJECT;
		}
	}
	
	void Value::setObject(const Object& newObject) {
		setValue(ValueDataPointer(&newObject), Type::OBJECT);
	}
	
	const Array& Value::getArray() const {
		if(type == Type::ARRAY) {
			assert(valuePointer.arrayValue);
			return *valuePointer.arrayValue;
		} else {
			return EMPTY_ARRAY;
		}
	}
	
	void Value::setArray(const Array& newArray) {
		setValue(ValueDataPointer(&newArray), Type::ARRAY);
	}
	
	bool Value::getBoolean() const {
		if(type == Type::BOOLEAN) {
			assert(valuePointer.boolValue);
			return *valuePointer.boolValue;
		} else {
			return EMPTY_BOOL;
		}
	}
	
	void Value::setBoolean(bool newBoolean) {
		setValue(ValueDataPointer(&newBoolean), Type::BOOLEAN);
	}
	
	void Value::loadFromFile(std::ifstream& file) {
		if(file.is_open()) {
			std::cout << "Trying to read from a file. Not implemented yet." << std::endl;
		}
	}
	
	void Value::loadFromFile(const std::string& filePath) {
		std::ifstream file;
		file.open(filePath.c_str());
		loadFromFile(file);
		file.close();
	}
	
	void Value::writeToFile(std::ofstream& file) const {
		if(file.is_open()) {
			file << *this;
		}
	}
	
	void Value::writeToFile(const std::string& filePath) const {
		std::ofstream file;
		file.open(filePath.c_str());
		writeToFile(file);
		file.close();
	}
	
	Value::ValueDataPointer::ValueDataPointer(): stringValue(NULL) {
	}
	
	Value::ValueDataPointer::ValueDataPointer(const std::string* newConstStringValue) :
	constStringValue(newConstStringValue) {
	}
	
	Value::ValueDataPointer::ValueDataPointer(const int* newConstIntValue) :
	constIntValue(newConstIntValue) {
	}
	
	Value::ValueDataPointer::ValueDataPointer(const double* newConstDoubleValue) :
	constDoubleValue(newConstDoubleValue) {
	}
	
	Value::ValueDataPointer::ValueDataPointer(const Object* newConstObjectValue) :
	constObjectValue(newConstObjectValue) {
	}
	
	Value::ValueDataPointer::ValueDataPointer(const Array* newConstArrayValue) :
	constArrayValue(newConstArrayValue) {
	}
	
	Value::ValueDataPointer::ValueDataPointer(const bool* newConstBoolValue) :
	constBoolValue(newConstBoolValue) {
	}
	
	void Value::setValue(ValueDataPointer newValuePointer,
						 Type::Enum newType) {
		if (type != Type::NULL_VALUE && type != newType) {
			// The current type isn't null and the new type is different.
			switch (type) {
				case Type::STRING:
					if(valuePointer.stringValue) {
						delete valuePointer.stringValue;
						valuePointer.stringValue = NULL;
					}
					break;
				case Type::INTEGER:
					if(valuePointer.intValue) {
						delete valuePointer.intValue;
						valuePointer.intValue = NULL;
					}
					break;
				case Type::DOUBLE:
					if(valuePointer.doubleValue) {
						delete valuePointer.doubleValue;
						valuePointer.doubleValue = NULL;
					}
					break;
				case Type::OBJECT:
					if(valuePointer.objectValue) {
						delete valuePointer.objectValue;
						valuePointer.objectValue = NULL;
					}
					break;
				case Type::ARRAY:
					if(valuePointer.arrayValue) {
						delete valuePointer.arrayValue;
						valuePointer.arrayValue = NULL;
					}
					break;
				case Type::BOOLEAN:
					if(valuePointer.boolValue) {
						delete valuePointer.boolValue;
						valuePointer.boolValue = NULL;
					}
					break;
				default:
					break;
			}
			type = newType;
			switch (type) {
				case Type::STRING:
					valuePointer.stringValue = new std::string(*newValuePointer.constStringValue);
					break;
				case Type::INTEGER:
					valuePointer.intValue = new int(*newValuePointer.constIntValue);
					break;
				case Type::DOUBLE:
					valuePointer.doubleValue = new double(*newValuePointer.constDoubleValue);
					break;
				case Type::OBJECT:
					valuePointer.objectValue = new Object(*newValuePointer.constObjectValue);
					break;
				case Type::ARRAY:
					valuePointer.arrayValue = new Array(*newValuePointer.constArrayValue);
					break;
				case Type::BOOLEAN:
					valuePointer.boolValue = new bool(*newValuePointer.constBoolValue);
					break;
				default:
					break;
			}
		} else if(type == newType) {
			// The new value is of the same type.
			switch (type) {
				case Type::STRING:
					assert(valuePointer.stringValue && newValuePointer.constStringValue);
					*valuePointer.stringValue = *newValuePointer.constStringValue;
					break;
				case Type::INTEGER:
					assert(valuePointer.intValue && newValuePointer.constIntValue);
					*valuePointer.intValue = *newValuePointer.constIntValue;
					break;
				case Type::DOUBLE:
					assert(valuePointer.doubleValue && newValuePointer.constDoubleValue);
					*valuePointer.doubleValue = *newValuePointer.doubleValue;
					break;
				case Type::OBJECT:
					assert(valuePointer.objectValue && newValuePointer.constObjectValue);
					*valuePointer.objectValue = *newValuePointer.constObjectValue;
					break;
				case Type::ARRAY:
					assert(valuePointer.arrayValue && newValuePointer.constArrayValue);
					*valuePointer.arrayValue = *newValuePointer.constArrayValue;
					break;
				case Type::BOOLEAN:
					assert(valuePointer.boolValue && newValuePointer.constBoolValue);
					*valuePointer.boolValue = *newValuePointer.constBoolValue;
					break;
				default:
					break;
			}
		} else {
			// The current type is null and the new type isn't
			type = newType;
			switch (type) {
				case Type::STRING:
					valuePointer.stringValue = new std::string(*newValuePointer.constStringValue);
					break;
				case Type::INTEGER:
					valuePointer.intValue = new int(*newValuePointer.constIntValue);
					break;
				case Type::DOUBLE:
					valuePointer.doubleValue = new double(*newValuePointer.constDoubleValue);
					break;
				case Type::OBJECT:
					valuePointer.objectValue = new Object(*newValuePointer.constObjectValue);
					break;
				case Type::ARRAY:
					valuePointer.arrayValue = new Array(*newValuePointer.constArrayValue);
					break;
				case Type::BOOLEAN:
					valuePointer.boolValue = new bool(*newValuePointer.constBoolValue);
					break;
				default:
					break;
			}
		}
	}
	
	std::ostream& operator<<(std::ostream& output, const Value& v) {
		switch (v.type) {
			case Type::STRING:
				output << '"' << Value::escapeCharacters(v.getString()) << '"';
				break;
			case Type::INTEGER:
				output << v.getInt();
				break;
			case Type::DOUBLE:
				output << v.getDouble();
				break;
			case Type::OBJECT:
				output << v.getObject();
				break;
			case Type::ARRAY:
				output << v.getArray();
				break;
			case Type::BOOLEAN:
				output << ((v.getBoolean()) ? ("true") : ("false"));
				break;
			case Type::NULL_VALUE:
				output << "null";
				break;
			default:
				break;
		}
		return output;
	}
	
	std::ostream& operator<<(std::ostream& output, const Array& a) {
		output << '[';
		for(Array::const_iterator i = a.begin(); i != a.end(); ++i) {
			if(i != a.begin()) {
				output << ", ";
			}
			output << *i;
		}
		output << ']';
		return output;
	}
	
	std::ostream& operator<<(std::ostream& output, const Object& o) {
		output << '{';
		for(std::map<std::string, Value>::const_iterator i = o.begin();
			i != o.end(); ++i) {
			if(i != o.begin()) {
				output << ", ";
			}
			output << '"' << Value::escapeCharacters(i->first) << "\" : " << i->second;
		}
		output << '}';
		return output;
	}
}
