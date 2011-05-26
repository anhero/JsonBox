#include <iostream>
#include <string>

#include "Value.h"
#include "Object.h"

int main (int argc, const char * argv[]) {
	JsonBox::Object o;
	o.setValue("myName", JsonBox::Value(123));
	o.setValue("myOtherMember", JsonBox::Value("asld\\kfn"));
	o.setValue("hahaha", JsonBox::Value(true));
	o.setValue("adamo", JsonBox::Value(129.09));
	JsonBox::Value v(o);
	std::cout << v << std::endl;
    return 0;
}

