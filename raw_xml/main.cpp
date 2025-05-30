#include "xml_string.h"
#include "xml_unordered_map.h"
#include "xml_parser.h"

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

//int main() {
//
//	xml::unordered_map<xml::string, xml::string> table;
//
//	table["book"] = "Hey you!";
//
//	std::cout << table["xd"] << std::endl;
//	std::cout << table["book"] << std::endl;
//	
//	table["book"] = "I have written the standard library without heap tonight!";
//
//	std::cout << table["book"] << std::endl;
//
//	table["fuck yeah"] = "wanna check it out?";
//
//	std::cout << table["fuck yeah"] << std::endl;
//
//
//	std::cin.get();
//}

xml::string xml_input = "<book><content page_number=\"12\" text=\"hello\"><text>hello2</text></content><author>oscar wilde</author></book><mehmet>jedi</mehmet>";

int main() {
	
	xml::parser parser;

	parser.parse(xml_input);

	for (size_t i = 0; i < parser.xml_table.buffer_size; i++)
		if (!parser.xml_table.buffer[i].first.empty())
			std::cout << parser.xml_table.buffer[i].first << " " << parser.xml_table.buffer[i].second << std::endl;

	std::cin.get();

}