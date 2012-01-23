#include <JsonBox/IndentCanceller.h>

namespace JsonBox {
	IndentCanceller::IndentCanceller() {
	}

	std::streambuf::int_type IndentCanceller::operator()(std::streambuf &destination,
	                                                     std::streambuf::int_type character) {
		return (character != '\n' && character != '\t') ? (destination.sputc(std::streambuf::traits_type::to_char_type(character))) : (0);
	}
}
