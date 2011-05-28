#include <iostream>
#include <string>

#include "Value.h"

int main (int argc, const char * argv[]) {
	JsonBox::Object o;
	o["myName"] = JsonBox::Value(123);
	o["myOtherMember"] = JsonBox::Value("asld\\kfn");
	o["hahaha"] = JsonBox::Value(true);
	o["adamo"] = JsonBox::Value(129.09);
	JsonBox::Value v(o);
	v.writeToFile("/Users/alabranche/lol2.txt");
	JsonBox::Value v2;
	v2.loadFromFile("/Users/alabranche/test.txt");
	std::cout << v2 << std::endl;
    return 0;
}

