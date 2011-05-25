#ifndef JB_VALUE_H
#define JB_VALUE_H

#include <string>
#include <vector>

#include "Type.h"
#include "Array.h"

namespace JsonBox {
	class Object;
	class Value {
	public:
		union ValueDataPointer {
			std::string* stringValue;
			int* intValue;
			double* doubleValue;
			Object* objectValue;
			Array* arrayValue;
			bool* boolValue;
			ValueDataPointer();
		};
		
		Value();
		Value(const Value& src);
		~Value();
		Value& operator=(const Value& src);

		Type::Enum getType() const;
		void setType();
		
		void setValue(ValueDataPointer newValuePointer, Type::Enum newType);
		
	private:
		ValueDataPointer valuePointer;
		Type::Enum type;
	};
}

#endif