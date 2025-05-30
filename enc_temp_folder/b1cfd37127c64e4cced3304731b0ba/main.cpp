#include "xml_string.h"
#include "xml_unordered_map.h"
#include "xml_parser.h"

//int main() {
//
//	xml::string mstring("3");
//
//	std::cout << "<" + mstring << std::endl;
//
//	std::cin.get();
//}

//int main() {
//
//	xml::unordered_map<xml::string, xml::string> table;
//	table["as"] = "1";
//
//	for (xml::pair<xml::string, xml::string>& pair : table)
//		std::cout << "entry: " << pair.first << " " << pair.second << std::endl;
//
//	std::cin.get();
//}



int main() {

	xml::string xml_input = 
	"<book>"
		"<content page_number=\"12\" text=\"hello\">"
			"<maintext>"
				"hello2"
			"</maintext>"
		"</content>"
		"<author>"
		"oscar wilde"
		"</author>"
	"</book>"
	"<mehmet>"
		"jedi"
	"</mehmet>"
	;

	xml::parser parser;
	
	parser.parse(xml_input);

	for (auto& pair : parser.xml_table)
		std::cout << pair.first << " " << pair.second << std::endl;

	//for (size_t i = 0; i < parser.xml_table.buffer_size; i++)
	//	if (!parser.xml_table.buffer[i].first.empty())
	//		std::cout << parser.xml_table.buffer[i].first << " " << parser.xml_table.buffer[i].second << std::endl;

	std::cin.get();
}