#include "xml_string.h"
#include "xml_unordered_map.h"

//int main() {
//
//	xml::string my_string1("hello world");
//	xml::string my_string2;
//
//	my_string1 = my_string1 + 'a';
//
//	std::cout << my_string1 << std::endl;
//
//	std::cin.get();
//}

int main() {

	xml::unordered_map<xml::string, xml::string> table;

	table["book"] = "Hey you!";

	std::cout << table["xd"] << std::endl;
	std::cout << table["book"] << std::endl;
	
	table["book"] = "I have written the standard library without heap tonight!";

	std::cout << table["book"] << std::endl;

	table["fuck yeah"] = "wanna check it out?";

	std::cout << table["fuck yeah"] << std::endl;


	std::cin.get();
}
