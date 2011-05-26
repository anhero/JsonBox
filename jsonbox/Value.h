#ifndef JB_VALUE_H
#define JB_VALUE_H

#include <string>
#include <vector>
#include <iostream>

#include "Type.h"

namespace JsonBox {
	class Object;
	class Value;
	typedef std::vector<Value> Array;
	class Value {
		friend std::ostream& operator<<(std::ostream& output, const Value& v);
	public:
		static std::string escapeCharacters(const std::string& str);
		
		Value();
		Value(const std::string& newString);
		Value(const char* newString);
		Value(int newInt);
		Value(double newDouble);
		Value(const Object& newObject);
		Value(const Array& newArray);
		Value(bool newBoolean);
		Value(const Value& src);
		~Value();
		Value& operator=(const Value& src);

		Type::Enum getType() const;
		bool isString() const;
		bool isInteger() const;
		bool isDouble() const;
		bool isObject() const;
		bool isArray() const;
		bool isBoolean() const;
		bool isNull() const;
		
		const std::string& getString() const;
		void setString(const std::string& newString);
		
		int getInt() const;
		void setInt(int newInt);
		
		double getDouble() const;
		void setDouble(double newDouble);
		
		const Object& getObject() const;
		void setObject(const Object& newObject);
		
		const Array& getArray() const;
		void setArray(const Array& newArray);
		
		bool getBoolean() const;
		void setBoolean(bool newBoolean);
		
	private:
		union ValueDataPointer {
			std::string* stringValue;
			int* intValue;
			double* doubleValue;
			Object* objectValue;
			Array* arrayValue;
			bool* boolValue;
			
			const std::string* constStringValue;
			const int* constIntValue;
			const double* constDoubleValue;
			const Object* constObjectValue;
			const Array* constArrayValue;
			const bool* constBoolValue;
			
			ValueDataPointer();
			ValueDataPointer(const std::string* newConstStringValue);
			ValueDataPointer(const int* newConstIntValue);
			ValueDataPointer(const double* newConstDoubleValue);
			ValueDataPointer(const Object* newConstObjectValue);
			ValueDataPointer(const Array* newConstArrayValue);
			ValueDataPointer(const bool* newConstBoolValue);
		};
		static const std::string EMPTY_STRING;
		static const int EMPTY_INT = 0;
		static const double EMPTY_DOUBLE;
		static const Object EMPTY_OBJECT;
		static const Array EMPTY_ARRAY;
		static const bool EMPTY_BOOL = false;
		ValueDataPointer valuePointer;
		Type::Enum type;
		void setValue(ValueDataPointer newValuePointer,
					  Type::Enum newType);
	};
	std::ostream& operator<<(std::ostream& output, const Array& a);
}

#endif