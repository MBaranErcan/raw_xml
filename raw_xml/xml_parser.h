#pragma once
#include "xml_string.h"
#include "xml_unordered_map.h"

namespace xml {
	class parser {
	public:
		xml::string content_symbol = "c";
		xml::string tag_symbol = "t";
		xml::string array_seperator = ">";

		unordered_map<string, string> xml_table;

		void parse(const string& xml_input);
		void get_tag(const char* parent_tag, int32_t index, string& out_string);
		void get_content(const char* parent_tag, int32_t index, string& out_string);

	private:
	};
}

