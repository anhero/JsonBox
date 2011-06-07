#ifndef JB_ARRAY_H
#define JB_ARRAY_H

#include <iostream>
#include <deque>

namespace JsonBox {
	class Value;
	/**
	 * Represents an array of values in JSON. It's a deque with added methods.
	 * So it can be used the same way as a standard STL deque, but can be more
	 * easily output in a stream.
	 * @see JsonBox::Value
	 */
	class Array : public std::deque<Value> {
		friend class Value;
		/**
		 * Output operator overload for the JSON array. Outputs in standard JSON
		 * format. Indents the output and esapes all characters.
		 * @param output Output stream in which to write the array's JSON.
		 * @param a Array to output into the stream.
		 * @return Output stream filled with the JSON code.
		 */
		friend std::ostream& operator<<(std::ostream& output, const Array& a);
	private:
		/**
		 * Outputs the array in JSON format.
		 * @param output Output stream used to output the value in JSON format.
		 * @param indent Specifies if the JSON being output must be indented or
		 * not. False is to output the JSON in compact format.
		 * @param escapeAll Specifies if the strings must escape all characters
		 * or only the minimum.
		 * @see JsonBox::Array::output(std::ostream& output, unsigned int& level, bool indent, bool escapeAll)
		 */
		void output(std::ostream& output, bool indent = true,
					bool escapeAll = true) const;
		
		/**
		 * Outputs the array in JSON format. This is the internal recursive
		 * version.
		 * @param output Output stream used to output the value in JSON format.
		 * @param level Indentation level. It's used only if the indent
		 * parameter is set to true.
		 * @param indent Specifies if the JSON being output must be indented or
		 * not. False is to output the JSON in compact format.
		 * @param escapeAll Specifies if the strings must escape all characters
		 * or only the minimum.
		 * @see JsonBox::Array::output(std::ostream& output, bool indent, bool escapeAll)
		 */
		void output(std::ostream& output, unsigned int& level,
					bool indent = true,
					bool escapeAll = true) const;
	};
}

#endif