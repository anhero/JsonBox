#ifndef JB_OBJECT_H
#define JB_OBJECT_H

#include <iostream>
#include <map>
#include <string>

namespace JsonBox {
	class Value;
	/**
	 * Represents a JSON object. It's a map with added methods. So the JSON
	 * object type can be used the same way as a standard STL map of string and
	 * Value, but can be more easily output in a stream.
	 * @see JsonBox::Value
	 */
	class Object : public std::map<std::string, Value> {
		friend class Value;
		/**
		 * Output operator overload for the JSON object. Outputs in standard JSON
		 * format. Indents the output and esapes all characters.
		 * @param output Output stream in which to write the object's JSON.
		 * @param o Object to output into the stream.
		 * @return Output stream filled with the JSON code.
		 */
		friend std::ostream& operator<<(std::ostream& output, const Object& o);
	private:
		/**
		 * Outputs the object in JSON format.
		 * @param output Output stream used to output the value in JSON format.
		 * @param indent Specifies if the JSON being output must be indented or
		 * not. False is to output the JSON in compact format.
		 * @param escapeAll Specifies if the strings must escape all characters
		 * or only the minimum.
		 * @see JsonBox::Object::output(std::ostream& output, unsigned int& level, bool indent, bool escapeAll)
		 */
		void output(std::ostream& output, bool indent = true,
					bool escapeAll = true) const;
		
		/**
		 * Outputs the object in JSON format. This is the internal recursive
		 * version.
		 * @param output Output stream used to output the value in JSON format.
		 * @param level Indentation level. It's used only if the indent
		 * parameter is set to true.
		 * @param indent Specifies if the JSON being output must be indented or
		 * not. False is to output the JSON in compact format.
		 * @param escapeAll Specifies if the strings must escape all characters
		 * or only the minimum.
		 * @see JsonBox::Object::output(std::ostream& output, bool indent, bool escapeAll)
		 */
		void output(std::ostream& output, unsigned int& level,
					bool indent = true, bool escapeAll = true) const;
	};
}

#endif