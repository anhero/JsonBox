#include <JsonBox/Indenter.h>

namespace JsonBox {
	Indenter::Indenter() : atStartOfLine(true) {
	}

	std::streambuf::int_type Indenter::operator()(std::streambuf &destination,
	                                              std::streambuf::int_type character) {
		if (atStartOfLine && character != '\n') {
			destination.sputc('\t');
		}

		atStartOfLine = (character == '\n');
		return destination.sputc(std::streambuf::traits_type::to_char_type(character));
	}
}
