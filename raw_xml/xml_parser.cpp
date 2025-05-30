#include "xml_parser.h"

void xml::parser::parse(const string& xml_input)
{
	bool in_tag = false;
	bool is_tag_closing = false;
	string parent_tag_name;
	string current_value_name;

	bool is_intag_tag_happening = false;
	bool is_intag_value_happening = false;
	string intag_tag_name;
	string intag_value_name;

	for (int i = 0; i < xml_input.size(); i++) {
		const char& current = xml_input.at(i);

		if (current == ' ' || current == '\n' || current == '\t' || current == '\r') {
			if (!in_tag) {
				current_value_name += current;
				continue;
			}

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
					xml_table[parent_tag_name] += array_seperator + (tag_symbol + current_value_name);

				parent_tag_name += (parent_tag_name != "" ? string("/") : "") + current_value_name;
			}
			else {
				size_t right_slash_index = parent_tag_name.find_last_of('/');
				if (right_slash_index != string::npos)
					parent_tag_name = parent_tag_name.substr(0, right_slash_index);
				else
					parent_tag_name = "";
			}

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

void xml::parser::get_tag(const char* parent_tag, int32_t index, xml::string& out_string){
	
	out_string.resize(0);
	
	if (xml_table.find(parent_tag) != xml_table.end()){
		string& entries = xml_table[parent_tag];
		

		size_t seperator_index = -1;
		for (int32_t seperator_counter = 0; seperator_counter < index;) {
			seperator_index++;
			entries.find(array_seperator.at(0), seperator_index);
			
			if (seperator_index == string::npos)
				return;

			if (entries.at(seperator_index + 1) == tag_symbol.at(0))
				seperator_counter++;
		}

		out_string.insert(0, entries.substr())
	}
}

void xml::parser::get_content(const char* parent_tag, int32_t index, xml::string& out_string) {

}

