#pragma once
// define XML_INCLUDE_IOSTREAM before including this file to be able to print xml::string
#define XML_INCLUDE_IOSTREAM

#include "stdint.h"
#ifdef XML_INCLUDE_IOSTREAM
#include <iostream>
#endif

namespace xml {

	class string;

	class string_bank {
		friend string;
	private:
		constexpr static size_t buffer_size = 1024 * 1024;
	public:

		string_bank() = default;
		~string_bank() = default;

		void clear();
		string malloc(size_t size);
		void relloc(string& string, size_t new_size);
		void free(string& string);

		//void defragment_buffer(const unordered_map& unordered_map);

	private:
		size_t buffer_iterator = 0;
		char buffer[buffer_size];
	};

	// it owns its data
	class string {
	private:
		friend string_bank;
		constexpr static size_t max_string_size = 1024;
	public:

		string(const char* global_string);
		string() = default;
		~string();
		string(const string& other);
		string(string&& other);
		string& operator=(const string& other);
		string& operator=(string&& other);

		const char* c_str() const;
		void reserve(size_t new_size);
		void resize(size_t new_size);

		char* begin() const;
		char* end() const;

		size_t size() const;
		size_t capacity() const;
		char at(size_t offset) const;
		bool empty();

		char& operator[](size_t offset);
		bool operator==(const string& other);
		bool operator==(const char* other);
		bool operator!=(const string& other);
		bool operator!=(const char* other);

		xml::string& operator+=(const string& other);
		xml::string& operator+=(const char* other);
		xml::string& operator+=(char other);
		
		xml::string operator+(const string& other0);
		xml::string operator+(const char* other);
		xml::string operator+(const char other);

	private:
		string(size_t begin, size_t end);
		size_t _begin = 0;
		size_t _end = 0;
		size_t _capacity_end = 0;

		size_t min(size_t a, size_t b);
		size_t max(size_t a, size_t b);

	public:
		static string_bank bank;
	};
};

#ifdef XML_INCLUDE_IOSTREAM
std::ostream& operator<<(std::ostream& stream, const xml::string& xml_string);
#endif