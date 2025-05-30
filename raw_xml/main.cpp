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

	const char* xml_input = 
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
	
	xml::string content_name;
	xml::string tag_name;
	parser.get_tag("book", 0, tag_name);
	parser.get_content("book/content/maintext", 0, content_name);

	std::cout << tag_name << std::endl;
	std::cout << content_name << std::endl;

	//for (auto& pair : parser.xml_table)
	//	std::cout << pair.first << " " << pair.second << std::endl;

	std::cin.get();
}