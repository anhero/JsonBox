#ifndef JB_TYPE_H
#define JB_TYPE_H

namespace JsonBox {
	/**
	 * Contains the enum that represents the different types a Value can have.
	 * @see JsonBox::Value
	 * @see JsonBox::Type::Enum
	 */
	namespace Type {
		/**
		 * Represents the different types a value can be. A value can only be
		 * one of these types at a time. The UNKNOWN type is only used
		 * temporarily internally when loading values from an input stream or
		 * file.
		 */
		enum Enum {
			STRING,
			INTEGER,
			DOUBLE,
			OBJECT,
			ARRAY,
			BOOLEAN,
			NULL_VALUE,
			UNKNOWN
		};
	}
}

#endif