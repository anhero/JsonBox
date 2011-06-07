#include <JsonBox/Array.h>

#include <JsonBox/Value.h>
#include <JsonBox/Grammar.h>

namespace JsonBox {
	
	void Array::output(std::ostream& output, bool indent,
					   bool escapeAll) const {
		unsigned int level = 0;
		this->output(output, level, indent, escapeAll);
	}
	
	void Array::output(std::ostream &output, unsigned int &level,
					   bool indent, bool escapeAll) const {
		output << '[';
		
		if(indent) {
			output << std::endl;
			++level;
		}
		
		for(Array::const_iterator i = begin(); i != end(); ++i) {
			
			if(i != begin()) {
				output << ",";
				if(indent) {
					output << std::endl;
				}
			}
			
			if(indent) {
				Value::outputNbTabs(output, level);
			}
			i->output(output, level, indent, escapeAll);
		}
		
		if(indent) {
			--level;
			output << std::endl;
			Value::outputNbTabs(output, level);
		}
		output << ']';
	}
	
	std::ostream& operator<<(std::ostream& output, const Array& a) {
		a.output(output);
		return output;
	}
}