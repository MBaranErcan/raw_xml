#pragma once
// define XML_INCLUDE_IOSTREAM before including this file to be able to print xml::string
#define XML_INCLUDE_IOSTREAM
#define XML_INCLUDE_STDINT

#ifdef XML_INCLUDE_STDINT
#include "stdint.h"
#else
typedef unsigned long long size_t;
typedef unsigned long long uint64_t;
typedef long long int64_t;
typedef unsigned int uint32_t;
typedef int int32_t;
#endif
#ifdef XML_INCLUDE_IOSTREAM
#include <iostream>
#endif

namespace xml {

	class string;

	class string_bank {
		friend string;
	private:
		constexpr static size_t buffer_size = 1024 * 32;
	public:

		string_bank() = default;
		~string_bank() = default;

		void clear();
		string malloc(size_t size);
		void realloc(string& string, size_t new_size);
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
		constexpr static size_t max_string_size = 512;
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
		bool empty() const;

		size_t find(char character, size_t pos = 0) const;
		size_t find_last_of(char character) const;
		string substr(size_t offset, size_t count) const;

		string& insert(size_t pos, const string& other);
		string& insert(size_t pos, const char* other);
		string& insert(size_t pos, const string& other, size_t subpos, size_t sublen);
		string& insert(size_t pos, const char* other, size_t subpos, size_t sublen);
		string& insert(size_t pos, char other);

		char& operator[](size_t offset);
		bool operator==(const string& other) const;
		bool operator==(const char* other) const;
		bool operator!=(const string& other) const;
		bool operator!=(const char* other) const;

		xml::string& operator+=(const string& other);
		xml::string& operator+=(const char* other);
		xml::string& operator+=(char other);
		
		xml::string operator+(const string& other0);
		xml::string operator+(const char* other);
		xml::string operator+(const char other);

		friend xml::string operator+(const string& rhs, const string& lhs);
		friend xml::string operator+(const char* rhs, const string& lhs);
		friend xml::string operator+(char rhs, const string& lhs);

#ifdef XML_INCLUDE_IOSTREAM
		friend std::ostream& operator<<(std::ostream& stream, const xml::string& xml_string);
#endif

		constexpr static size_t npos = -1;

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

