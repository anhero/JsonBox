#include "Value.h"

#include "Object.h"

namespace JsonBox {
	
	Value::ValueDataPointer::ValueDataPointer(): stringValue(NULL) {
	}
	
	Value::Value() : type(Type::NULL_VALUE) {
	}
	
	Value::Value(const Value& src) : type(src.type) {
		setValue(src.valuePointer, src.type);
	}
	
	void Value::setValue(ValueDataPointer newValuePointer, Type::Enum newType) {
		if (type != Type::NULL_VALUE) {
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
		}
		type = newType;
		switch (type) {
			case Type::STRING:
				valuePointer.stringValue = new std::string(*newValuePointer.stringValue);
				break;
			case Type::INTEGER:
				valuePointer.intValue = new int(*newValuePointer.intValue);
				break;
			case Type::DOUBLE:
				valuePointer.doubleValue = new double(*newValuePointer.doubleValue);
				break;
			case Type::OBJECT:
				valuePointer.objectValue = new Object(*newValuePointer.objectValue);
				break;
			case Type::ARRAY:
				valuePointer.arrayValue = new Array(*newValuePointer.arrayValue);
				break;
			case Type::BOOLEAN:
				valuePointer.boolValue = new bool(*newValuePointer.boolValue);
				break;
			default:
				break;
		}
	}
}
