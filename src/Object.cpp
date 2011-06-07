#include <JsonBox/Object.h>

#include <JsonBox/Value.h>

namespace JsonBox {
	void Object::output(std::ostream& output, bool indent,
						bool escapeAll) const {
		unsigned int level = 0;
		this->output(output, level, indent, escapeAll);
	}
	
	void Object::output(std::ostream& output, unsigned int& level,
						bool indent, bool escapeAll) const {
		output << '{';
		if(indent) {
			output << std::endl;
			++level;
		}
		
		for(std::map<std::string, Value>::const_iterator i = begin();
			i != end(); ++i) {
			if(i != begin()) {
				output << ",";
				if(indent) {
					output << std::endl;
				}
			}
			
			if(indent) {
				Value::outputNbTabs(output, level);
				if(escapeAll) {
					output << '"' << Value::escapeAllCharacters(i->first) << "\" : ";
				} else {
					output << '"' << Value::escapeMinimumCharacters(i->first) << "\" : ";
				}
			} else {
				if(escapeAll) {
					output << '"' << Value::escapeAllCharacters(i->first) << "\":";
				} else {
					output << '"' << Value::escapeMinimumCharacters(i->first) << "\":";
				}
			}
			i->second.output(output, level, indent, escapeAll);
		}
		
		if(indent) {
			--level;
			output << std::endl;
			Value::outputNbTabs(output, level);
		}
		output << '}';
	}
	
	std::ostream& operator<<(std::ostream& output, const Object& o) {
		o.output(output);
		return output;
	}
}