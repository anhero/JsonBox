#include <JsonBox/Value.h>

#include <cassert>
#include <stack>
#include <sstream>
#include <list>
#include <iomanip>
#include <fstream>

#include <JsonBox/Grammar.h>
#include <JsonBox/Convert.h>

namespace JsonBox {

	const std::string Value::EMPTY_STRING = std::string();
	const double Value::EMPTY_DOUBLE = 0.0;
	const Object Value::EMPTY_OBJECT = Object();
	const Array Value::EMPTY_ARRAY = Array();

	std::string Value::escapeMinimumCharacters(const std::string& str) {
		std::stringstream result;

		// For each character in the string.
		for(std::string::const_iterator i = str.begin(); i != str.end(); ++i) {
			if(*i == Strings::Std::QUOTATION_MARK) {
				result << Strings::Json::QUOTATION_MARK;
			} else if(*i == Strings::Std::REVERSE_SOLIDUS) {
				result << Strings::Json::REVERSE_SOLIDUS;
			} else if(*i == Strings::Std::BACKSPACE) {
				result << Strings::Json::BACKSPACE;
			} else if(*i == Strings::Std::FORM_FEED) {
				result << Strings::Json::FORM_FEED;
			} else if(*i == Strings::Std::LINE_FEED) {
				result << Strings::Json::LINE_FEED;
			} else if(*i == Strings::Std::CARRIAGE_RETURN) {
				result << Strings::Json::CARRIAGE_RETURN;
			} else if(*i == Strings::Std::TAB) {
				result << Strings::Json::TAB;
			} else if(*i >= '\0' && *i <= '\x1f') {
				result << Value::escapeToUnicode(*i);
			} else {
				result << *i;
			}
		}

		return result.str();
	}

	std::string Value::escapeAllCharacters(const std::string& str) {
		std::stringstream result;

		// For each character in the string.
		for(std::string::const_iterator i = str.begin(); i != str.end(); ++i) {
			if(*i == Strings::Std::QUOTATION_MARK) {
				result << Strings::Json::QUOTATION_MARK;
			} else if(*i == Strings::Std::REVERSE_SOLIDUS) {
				result << Strings::Json::REVERSE_SOLIDUS;
			} else if(*i == Strings::Std::SOLIDUS) {
				result << Strings::Json::SOLIDUS;
			} else if(*i == Strings::Std::BACKSPACE) {
				result << Strings::Json::BACKSPACE;
			} else if(*i == Strings::Std::FORM_FEED) {
				result << Strings::Json::FORM_FEED;
			} else if(*i == Strings::Std::LINE_FEED) {
				result << Strings::Json::LINE_FEED;
			} else if(*i == Strings::Std::CARRIAGE_RETURN) {
				result << Strings::Json::CARRIAGE_RETURN;
			} else if(*i == Strings::Std::TAB) {
				result << Strings::Json::TAB;
			} else if(*i >= '\0' && *i <= '\x1f') {
				result << Value::escapeToUnicode(*i);
			} else {
				result << *i;
			}

		}

		return result.str();
	}

	Value::Value() : type(Type::NULL_VALUE) {
		valuePointer.stringValue = NULL;
	}

	Value::Value(std::istream& input) : type(Type::NULL_VALUE) {
		valuePointer.stringValue = NULL;
		loadFromStream(input);
	}

	Value::Value(const std::string& newString) : type(Type::NULL_VALUE) {
		valuePointer.stringValue = NULL;
		setString(newString);
	}
	
	Value::Value(const char* newCString) : type(Type::NULL_VALUE) {
		valuePointer.stringValue = NULL;
		setString(std::string(newCString));
	}

	Value::Value(int newInt) : type(Type::NULL_VALUE) {
		valuePointer.intValue = NULL;
		setInt(newInt);
	}

	Value::Value(double newDouble) : type(Type::NULL_VALUE) {
		valuePointer.doubleValue = NULL;
		setDouble(newDouble);
	}

	Value::Value(const Object& newObject) : type(Type::NULL_VALUE) {
		valuePointer.objectValue = NULL;
		setObject(newObject);
	}

	Value::Value(const Array& newArray) : type(Type::NULL_VALUE) {
		valuePointer.arrayValue = NULL;
		setArray(newArray);
	}

	Value::Value(bool newBoolean) : type(Type::NULL_VALUE) {
		valuePointer.boolValue = NULL;
		setBoolean(newBoolean);
	}

	Value::Value(const Value& src) : type(Type::NULL_VALUE) {
		valuePointer.stringValue = NULL;
		setValue(src.valuePointer, src.type);
	}

	Value::~Value() {
		if(valuePointer.stringValue) {
			switch(type) {
			case Type::STRING:

				delete valuePointer.stringValue;

				break;
			case Type::INTEGER:

				delete valuePointer.intValue;

				break;
			case Type::DOUBLE:

				delete valuePointer.doubleValue;

				break;
			case Type::OBJECT:

				delete valuePointer.objectValue;

				break;
			case Type::ARRAY:

				delete valuePointer.arrayValue;

				break;
			case Type::BOOLEAN:

				delete valuePointer.boolValue;

				break;
			default:
				break;
			}
		}
	}

	Value& Value::operator=(const Value& src) {
		if(this != &src) {
			setValue(src.valuePointer, src.type);
		}

		return *this;
	}

	Type::Enum Value::getType() const {
		return type;
	}

	bool Value::isString() const {
		return type == Type::STRING;
	}

	bool Value::isInteger() const {
		return type == Type::INTEGER;
	}

	bool Value::isDouble() const {
		return type == Type::DOUBLE;
	}

	bool Value::isObject() const {
		return type == Type::OBJECT;
	}

	bool Value::isArray() const {
		return type == Type::ARRAY;
	}

	bool Value::isBoolean() const {
		return type == Type::BOOLEAN;
	}

	bool Value::isNull() const {
		return type == Type::NULL_VALUE;
	}

	const std::string& Value::getString() const {
		if(type == Type::STRING) {
			assert(valuePointer.stringValue);
			return *valuePointer.stringValue;
		} else {
			return EMPTY_STRING;
		}
	}

	void Value::setString(std::string const& newString) {
		setValue(ValueDataPointer(&newString), Type::STRING);
	}

	int Value::getInt() const {
		if(type == Type::INTEGER) {
			assert(valuePointer.intValue);
			return *valuePointer.intValue;
		} else {
			return EMPTY_INT;
		}
	}

	void Value::setInt(int newInt) {
		setValue(ValueDataPointer(&newInt), Type::INTEGER);
	}

	double Value::getDouble() const {
		if(type == Type::DOUBLE) {
			assert(valuePointer.doubleValue);
			return *valuePointer.doubleValue;
		} else {
			return EMPTY_DOUBLE;
		}
	}

	void Value::setDouble(double newDouble) {
		setValue(ValueDataPointer(&newDouble), Type::DOUBLE);
	}

	const Object& Value::getObject() const {
		if(type == Type::OBJECT) {
			assert(valuePointer.objectValue);
			return *valuePointer.objectValue;
		} else {
			return EMPTY_OBJECT;
		}
	}

	void Value::setObject(const Object& newObject) {
		setValue(ValueDataPointer(&newObject), Type::OBJECT);
	}

	const Array& Value::getArray() const {
		if(type == Type::ARRAY) {
			assert(valuePointer.arrayValue);
			return *valuePointer.arrayValue;
		} else {
			return EMPTY_ARRAY;
		}
	}

	void Value::setArray(const Array& newArray) {
		setValue(ValueDataPointer(&newArray), Type::ARRAY);
	}

	bool Value::getBoolean() const {
		if(type == Type::BOOLEAN) {
			assert(valuePointer.boolValue);
			return *valuePointer.boolValue;
		} else {
			return EMPTY_BOOL;
		}
	}

	void Value::setBoolean(bool newBoolean) {
		setValue(ValueDataPointer(&newBoolean), Type::BOOLEAN);
	}

	void Value::setNull() {
		ValueDataPointer tmp;
		tmp.stringValue = NULL;
		setValue(tmp, Type::NULL_VALUE);
	}

	void Value::loadFromString(std::string const& json) {
		std::stringstream jsonStream(json);
		loadFromStream(jsonStream);
	}
	
	void Value::loadFromStream(std::istream& input) {
		char currentCharacter;

		// We check that the stream is in UTF-8.
		char encoding[2];
		input.get(encoding[0]);
		input.get(encoding[1]);

		if(encoding[0] != '\0' && encoding[1] != '\0') {
			// We put the characters back.
			input.putback(encoding[1]);
			input.putback(encoding[0]);

			// Boolean value used to stop reading characters after the value
			// is done loading.
			bool noErrors = true;

			while(noErrors && input.good()) {
				input.get(currentCharacter);

				if(input.good()) {
					if(currentCharacter == Structural::BEGIN_END_STRING) {
						// The value to be parsed is a string.
						setString("");
						readString(input, *valuePointer.stringValue);
						noErrors = false;
					} else if(currentCharacter == Structural::BEGIN_OBJECT) {
						// The value to be parsed is an object.
						setObject(Object());
						readObject(input, *valuePointer.objectValue);
						noErrors = false;
					} else if(currentCharacter == Structural::BEGIN_ARRAY) {
						// The value to be parsed is an array.
						setArray(Array());
						readArray(input, *valuePointer.arrayValue);
						noErrors = false;
					} else if(currentCharacter == Literals::NULL_STRING[0]) {
						// We try to read the literal 'null'.
						if(!input.eof()) {
							input.get(currentCharacter);
							
							if(currentCharacter == Literals::NULL_STRING[1]) {
								if(!input.eof()) {
									input.get(currentCharacter);
									
									if(currentCharacter == Literals::NULL_STRING[2]) {
										if(!input.eof()) {
											input.get(currentCharacter);
											
											if(currentCharacter == Literals::NULL_STRING[3]) {
												setNull();
												noErrors = false;
											} else {
												std::cout << "invalid characters found" << std::endl;
											}
										} else {
											std::cout << "json input ends incorrectly" << std::endl;
										}
									} else {
										std::cout << "invalid characters found" << std::endl;
									}
								} else {
									std::cout << "json input ends incorrectly" << std::endl;
								}
							} else {
								std::cout << "invalid characters found" << std::endl;
							}
						} else {
							std::cout << "json input ends incorrectly" << std::endl;
						}
					} else if(currentCharacter == Numbers::MINUS ||
							  (currentCharacter >= Numbers::DIGITS[0] && currentCharacter <= Numbers::DIGITS[9])) {
						// Numbers can't start with zeroes.
						input.putback(currentCharacter);
						readNumber(input, *this);
						noErrors = false;
					} else if(currentCharacter == Literals::TRUE_STRING[0]) {
						// We try to read the boolean literal 'true'.
						if(!input.eof()) {
							input.get(currentCharacter);
							
							if(currentCharacter == Literals::TRUE_STRING[1]) {
								if(!input.eof()) {
									input.get(currentCharacter);
									
									if(currentCharacter == Literals::TRUE_STRING[2]) {
										if(!input.eof()) {
											input.get(currentCharacter);
											
											if(currentCharacter == Literals::TRUE_STRING[3]) {
												setBoolean(true);
												noErrors = false;
											}
										}
									}
								}
							}
						}
					} else if(currentCharacter == Literals::FALSE_STRING[0]) {
						// We try to read the boolean literal 'false'.
						if(!input.eof()) {
							input.get(currentCharacter);
							
							if(currentCharacter == Literals::FALSE_STRING[1]) {
								if(!input.eof()) {
									input.get(currentCharacter);
									
									if(currentCharacter == Literals::FALSE_STRING[2]) {
										if(!input.eof()) {
											input.get(currentCharacter);
											
											if(currentCharacter == Literals::FALSE_STRING[3]) {
												if(!input.eof()) {
													input.get(currentCharacter);
													
													if(currentCharacter == Literals::FALSE_STRING[4]) {
														setBoolean(false);
														noErrors = false;
													}
												}
											}
										}
									}
								}
							}
						}
					} else if(!isWhiteSpace(currentCharacter)) {
						std::cout << "Invalid character found: '" << currentCharacter << "'" << std::endl;
					}
				}
			}
		} else {
			std::cout << "File is not in UTF-8, not parsing." << std::endl;
		}
	}

	void Value::loadFromFile(const std::string& filePath) {
		std::ifstream file;
		file.open(filePath.c_str());

		if(file.is_open()) {
			loadFromStream(file);
			file.close();
		} else {
			std::cout << "Failed to open file to load the json: " << filePath << std::endl;
		}
	}

	void Value::writeToStream(std::ostream& output, bool indent,
	                          bool escapeAll) const {
		this->output(output, indent, escapeAll);
	}

	void Value::writeToFile(const std::string& filePath, bool indent,
	                        bool escapeAll) const {
		std::ofstream file;
		file.open(filePath.c_str());

		if(file.is_open()) {
			writeToStream(file, indent, escapeAll);
			file.close();
		} else {
			std::cout << "Failed to open file to write the json into: " << filePath << std::endl;
		}
	}

	Value::ValueDataPointer::ValueDataPointer(): stringValue(NULL) {
	}

	Value::ValueDataPointer::ValueDataPointer(const std::string* newConstStringValue) :
		constStringValue(newConstStringValue) {
	}

	Value::ValueDataPointer::ValueDataPointer(const int* newConstIntValue) :
		constIntValue(newConstIntValue) {
	}

	Value::ValueDataPointer::ValueDataPointer(const double* newConstDoubleValue) :
		constDoubleValue(newConstDoubleValue) {
	}

	Value::ValueDataPointer::ValueDataPointer(const Object* newConstObjectValue) :
		constObjectValue(newConstObjectValue) {
	}

	Value::ValueDataPointer::ValueDataPointer(const Array* newConstArrayValue) :
		constArrayValue(newConstArrayValue) {
	}

	Value::ValueDataPointer::ValueDataPointer(const bool* newConstBoolValue) :
		constBoolValue(newConstBoolValue) {
	}

	bool Value::isHexDigit(char digit) {
		return (digit >= Numbers::DIGITS[0] && digit <= Numbers::DIGITS[9]) || (digit >= Numbers::DIGITS[10] && digit <= Numbers::DIGITS[15]) ||
		       (digit >= Numbers::DIGITS[16] && digit <= Numbers::DIGITS[21]);
	}

	bool Value::isWhiteSpace(char whiteSpace) {
		return whiteSpace == Whitespace::SPACE ||
		       whiteSpace == Whitespace::HORIZONTAL_TAB ||
		       whiteSpace == Whitespace::NEW_LINE ||
		       whiteSpace == Whitespace::CARRIAGE_RETURN;
	}

	void Value::readString(std::istream& input, std::string& result) {
		bool noErrors = true, noUnicodeError = true;
		char currentCharacter, tmpCharacter;
		std::stringstream constructing;
		std::string tmpStr(4, ' ');
		std::stringstream tmpSs;
		int32_t tmpInt;
		String32 tmpStr32;
		unsigned int tmpCounter;

		// As long as there aren't any errors and that we haven't reached the
		// end of the input stream.
		while(noErrors && !input.eof()) {
			input.get(currentCharacter);
			
			if(input.good()) {
				if(currentCharacter & 0x80) { // 0x80 --> 10000000
					// The character is part of an utf8 character.
					constructing << currentCharacter;
				} else if(currentCharacter == Strings::Json::Escape::BEGIN_ESCAPE) {
					if(!input.eof()) {
						input.get(tmpCharacter);
						
						switch(tmpCharacter) {
							case Strings::Json::Escape::QUOTATION_MARK:
								constructing << Strings::Std::QUOTATION_MARK;
								break;
							case Strings::Json::Escape::REVERSE_SOLIDUS:
								constructing << Strings::Std::REVERSE_SOLIDUS;
								break;
							case Strings::Json::Escape::SOLIDUS:
								constructing << Strings::Std::SOLIDUS;
								break;
							case Strings::Json::Escape::BACKSPACE:
								constructing << Strings::Std::BACKSPACE;
								break;
							case Strings::Json::Escape::FORM_FEED:
								constructing << Strings::Std::FORM_FEED;
								break;
							case Strings::Json::Escape::LINE_FEED:
								constructing << Strings::Std::LINE_FEED;
								break;
							case Strings::Json::Escape::CARRIAGE_RETURN:
								constructing << Strings::Std::CARRIAGE_RETURN;
								break;
							case Strings::Json::Escape::TAB:
								constructing << Strings::Std::TAB;
								break;
							case Strings::Json::Escape::BEGIN_UNICODE:
								// TODO: Check for utf16 surrogate pairs.
								tmpCounter = 0;
								tmpStr.clear();
								tmpStr = "    ";
								noUnicodeError = true;
								
								while(tmpCounter < 4 && !input.eof()) {
									input.get(tmpCharacter);
									
									if(isHexDigit(tmpCharacter)) {
										tmpStr[tmpCounter] = tmpCharacter;
									} else {
										noUnicodeError = false;
										std::cout << "Invalid \\u character, skipping it." << std::endl;
									}
									
									++tmpCounter;
								}
								
								if(noUnicodeError) {
									tmpSs.str("");
									tmpSs << std::hex << tmpStr;
									tmpSs >> tmpInt;
									tmpStr32.clear();
									tmpStr32.push_back(tmpInt);
									tmpStr = Convert::encodeToUTF8(tmpStr32);
									constructing << tmpStr;
								}
								
								break;
							default:
								break;
						}
					}
				} else if(currentCharacter == '"') {
					result = constructing.str();
					noErrors = false;
				} else {
					constructing << currentCharacter;
				}
			}
		}
	}

	void Value::readObject(std::istream& input, Object& result) {
		bool noErrors = true;
		char currentCharacter;
		std::string tmpString;

		while(noErrors && !input.eof()) {
			input.get(currentCharacter);

			if(input.good()) {
				if(currentCharacter == Structural::BEGIN_END_STRING) {
					// We read the object's member's name.
					readString(input, tmpString);
					currentCharacter = input.peek();
					// We read white spaces until the next non white space.
					readToNonWhiteSpace(input, currentCharacter);
					
					if(!input.eof()) {
						
						// We make sure it's the right character.
						if(currentCharacter == Structural::NAME_SEPARATOR) {
							// We read until the value starts.
							readToNonWhiteSpace(input, currentCharacter);
							
							if(!input.eof()) {
								// We put the character back and we load the value
								// from the stream.
								input.putback(currentCharacter);
								result[tmpString].loadFromStream(input);
								
								while(!input.eof() && currentCharacter != Structural::VALUE_SEPARATOR &&
									  currentCharacter != Structural::END_OBJECT) {
									input.get(currentCharacter);
								}
								
								if(currentCharacter == Structural::END_OBJECT) {
									// We are done reading the object.
									noErrors = false;
								}
							}
						}
					}
				} else if(currentCharacter == Structural::END_OBJECT) {
					noErrors = false;
				} else if(!isWhiteSpace(currentCharacter)) {
					std::cout << "Expected '\"', got '" << currentCharacter << "', ignoring it." << std::endl;
				}
			}
		}
	}

	void Value::readArray(std::istream& input, Array& result) {
		bool notDone = true;
		char currentChar;
		while(notDone && !input.eof()) {
			input.get(currentChar);

			if(input.good()) {
				if(currentChar == Structural::END_ARRAY) {
					notDone = false;
				} else if(!isWhiteSpace(currentChar)) {
					input.putback(currentChar);
					result.push_back(Value());
					result.back().type = Type::UNKNOWN;
					result.back().loadFromStream(input);
					if(result.back().type == Type::UNKNOWN) {
						result.pop_back();
					}
					
					while(!input.eof() && currentChar != ',' &&
						  currentChar != Structural::END_ARRAY) {
						input.get(currentChar);
					}
					
					if(currentChar == Structural::END_ARRAY) {
						notDone = false;
					}
				}
			}
		}
	}

	void Value::readNumber(std::istream& input, JsonBox::Value& result) {
		bool notDone = true, inFraction = false, inExponent = false;
		char currentCharacter;
		std::stringstream constructing;

		if(!input.eof() && input.peek() == Numbers::DIGITS[0]) {
			// We make sure there isn't more than one zero.
			input.get(currentCharacter);

			if(input.peek() == '0') {
				notDone = false;
			} else {
				input.putback(currentCharacter);
			}
		}

		while(notDone && !input.eof()) {
			input.get(currentCharacter);

			if(currentCharacter == '-') {
				if(constructing.str().empty()) {
					constructing << currentCharacter;
				} else {
					std::cout << "Expected a digit, '.', 'e' or 'E', got '" << currentCharacter << "' instead, ignoring it." << std::endl;
				}
			} else if(currentCharacter >= '0' && currentCharacter <= '9') {
				constructing << currentCharacter;
			} else if(currentCharacter == '.') {
				if(!inFraction && !inExponent) {
					inFraction = true;
					constructing << currentCharacter;
				}
			} else if(currentCharacter == 'e' || currentCharacter == 'E') {
				if(!inExponent) {
					inExponent = true;
					constructing << currentCharacter;

					if(!input.eof() && (input.peek() == '-' || input.peek() == '+')) {
						input.get(currentCharacter);
						constructing << currentCharacter;
					}
				}
			} else {
				input.putback(currentCharacter);
				notDone = false;
			}
		}

		if(inFraction || inExponent) {
			double doubleResult;
			constructing >> doubleResult;
			result.setDouble(doubleResult);
		} else {
			int intResult;
			constructing >> intResult;
			result.setInt(intResult);
		}
	}

	void Value::readToNonWhiteSpace(std::istream& input, char& currentCharacter) {
		do {
			input.get(currentCharacter);
		} while(!input.eof() && isWhiteSpace(currentCharacter));
	}

	void Value::outputNbTabs(std::ostream& output, unsigned int nbTabs) {
		for(unsigned int i = 0; i < nbTabs; ++i) {
			output << '\t';
		}
	}

	std::string Value::escapeToUnicode(char charToEscape) {
		std::stringstream result;

		if(charToEscape >= '\0' && charToEscape <= '\x1f') {
			result << "\\u00";
			result << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(charToEscape);
		}

		return result.str();
	}

	void Value::setValue(ValueDataPointer newValuePointer,
	                     Type::Enum newType) {
		if(newType != Type::UNKNOWN) {
			if(type != Type::NULL_VALUE && type != newType) {
				// The current type isn't null and the new type is different.
				switch(type) {
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

				type = newType;

				switch(type) {
				case Type::STRING:
					valuePointer.stringValue = new std::string(*newValuePointer.constStringValue);
					break;
				case Type::INTEGER:
					valuePointer.intValue = new int(*newValuePointer.constIntValue);
					break;
				case Type::DOUBLE:
					valuePointer.doubleValue = new double(*newValuePointer.constDoubleValue);
					break;
				case Type::OBJECT:
					valuePointer.objectValue = new Object(*newValuePointer.constObjectValue);
					break;
				case Type::ARRAY:
					valuePointer.arrayValue = new Array(*newValuePointer.constArrayValue);
					break;
				case Type::BOOLEAN:
					valuePointer.boolValue = new bool(*newValuePointer.constBoolValue);
					break;
				default:
					break;
				}
			} else if(type == newType) {
				// The new value is of the same type.
				switch(type) {
				case Type::STRING:
					assert(valuePointer.stringValue && newValuePointer.constStringValue);
					*valuePointer.stringValue = *newValuePointer.constStringValue;
					break;
				case Type::INTEGER:
					assert(valuePointer.intValue && newValuePointer.constIntValue);
					*valuePointer.intValue = *newValuePointer.constIntValue;
					break;
				case Type::DOUBLE:
					assert(valuePointer.doubleValue && newValuePointer.constDoubleValue);
					*valuePointer.doubleValue = *newValuePointer.doubleValue;
					break;
				case Type::OBJECT:
					assert(valuePointer.objectValue && newValuePointer.constObjectValue);
					*valuePointer.objectValue = *newValuePointer.constObjectValue;
					break;
				case Type::ARRAY:
					assert(valuePointer.arrayValue && newValuePointer.constArrayValue);
					*valuePointer.arrayValue = *newValuePointer.constArrayValue;
					break;
				case Type::BOOLEAN:
					assert(valuePointer.boolValue && newValuePointer.constBoolValue);
					*valuePointer.boolValue = *newValuePointer.constBoolValue;
					break;
				default:
					break;
				}
			} else {
				// The current type is null and the new type isn't
				type = newType;

				switch(type) {
				case Type::STRING:
					valuePointer.stringValue = new std::string(*newValuePointer.constStringValue);
					break;
				case Type::INTEGER:
					valuePointer.intValue = new int(*newValuePointer.constIntValue);
					break;
				case Type::DOUBLE:
					valuePointer.doubleValue = new double(*newValuePointer.constDoubleValue);
					break;
				case Type::OBJECT:
					valuePointer.objectValue = new Object(*newValuePointer.constObjectValue);
					break;
				case Type::ARRAY:
					valuePointer.arrayValue = new Array(*newValuePointer.constArrayValue);
					break;
				case Type::BOOLEAN:
					valuePointer.boolValue = new bool(*newValuePointer.constBoolValue);
					break;
				default:
					break;
				}
			}
		}
	}

	void Value::output(std::ostream& output, bool indent,
	                   bool escapeAll) const {
		unsigned int level = 0;
		this->output(output, level, indent, escapeAll);
	}

	void Value::output(std::ostream& output, unsigned int& level, bool indent,
	                   bool escapeAll) const {
		switch(type) {
		case Type::STRING:

			if(escapeAll) {
				output << '"' << Value::escapeAllCharacters(getString()) << '"';
			} else {
				output << '"' << Value::escapeMinimumCharacters(getString()) << '"';
			}

			break;
		case Type::INTEGER:
			output << getInt();
			break;
		case Type::DOUBLE:
			output << getDouble();
			break;
		case Type::OBJECT:
			getObject().output(output, level, indent, escapeAll);
			break;
		case Type::ARRAY:
			getArray().output(output, level, indent, escapeAll);
			break;
		case Type::BOOLEAN:
			output << ((getBoolean()) ? ("true") : ("false"));
			break;
		case Type::NULL_VALUE:
			output << "null";
			break;
		default:
			break;
		}

	}

	std::ostream& operator<<(std::ostream& output, const Value& v) {
		v.output(output);
		return output;
	}
}
