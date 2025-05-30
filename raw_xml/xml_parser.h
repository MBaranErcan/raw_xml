#pragma once
#include "xml_string.h"
#include "xml_unordered_map.h"

#include "string"
#include "unordered_map"

namespace xml {
	class parser {
	public:
		std::string content_symbol = "c";
		std::string tag_symbol = "t";
		std::string array_seperator = ">";

		std::unordered_map<std::string, std::string> xml_table;

		void parse(const std::string& xml_input) {

			bool in_tag = false;
			bool is_tag_closing = false;
			std::string parent_tag_name;
			std::string current_value_name;

			bool is_intag_tag_happening = false;
			bool is_intag_value_happening = false;
			std::string intag_tag_name;
			std::string intag_value_name;

			for (int i = 0; i < xml_input.size(); i++) {
				const char& current = xml_input.at(i);

				if (current == ' ' || current == '\n' || current == '\t' || current == '\r') {
					if (!in_tag)
						continue;

					if (is_intag_value_happening) {
						xml_table[parent_tag_name + "/" + current_value_name + "/" + intag_tag_name] += array_seperator + (content_symbol + intag_value_name);
						intag_tag_name = "";
						intag_value_name = "";
					}

					is_intag_tag_happening = true;
					is_intag_value_happening = false;
				}
				else if (current == '<') {
					if (parent_tag_name != "" && current_value_name != "")
						xml_table[parent_tag_name] += array_seperator + (in_tag ? tag_symbol : content_symbol) + current_value_name;

					in_tag = true;
					is_intag_tag_happening = false;
					is_intag_value_happening = false;
					is_tag_closing = false;
					current_value_name = "";
				}
				else if (current == '>') {
					if (!is_tag_closing) {

						if (is_intag_value_happening) {
							xml_table[parent_tag_name + "/" + current_value_name + "/" + intag_tag_name] += array_seperator + (content_symbol + intag_value_name);
							intag_tag_name = "";
							intag_value_name = "";
						}

						if (parent_tag_name != "" && current_value_name != "")
							xml_table[parent_tag_name] += (tag_symbol + current_value_name);

						parent_tag_name += (parent_tag_name != "" ? std::string("/") : "") + current_value_name;
					}
					else {
						size_t right_slash_index = parent_tag_name.find_last_of('/');
						if (right_slash_index != std::string::npos)
							parent_tag_name = parent_tag_name.substr(0, right_slash_index);
						else
							parent_tag_name = "";
					}

					std::cout << parent_tag_name << std::endl;


					in_tag = false;
					is_intag_tag_happening = false;
					is_intag_value_happening = false;
					is_tag_closing = false;
					current_value_name = "";
				}
				else if (current == '/') {
					in_tag = true;
					is_intag_tag_happening = false;
					is_intag_value_happening = false;
					is_tag_closing = true;
					current_value_name = "";
				}
				else if (current == '=') {

					xml_table[parent_tag_name + "/" + current_value_name] += array_seperator + tag_symbol + intag_tag_name;

					is_intag_tag_happening = false;
					is_intag_value_happening = true;
				}
				else {
					if (!is_intag_tag_happening && !is_intag_value_happening)
						current_value_name += current;
					if (current == '\"')
						continue;
					else if (is_intag_tag_happening) {
						intag_tag_name += current;
					}
					else if (is_intag_value_happening) {
						intag_value_name += current;
					}
				}
			}
		}

	private:

	};
}

