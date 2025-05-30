#pragma once

#include "xml_string.h"

namespace xml {

	template<typename T>
	size_t hash(const T& obj) = delete;
	
	template<typename key_t, typename value_t>
	class pair {
	public:
		key_t first;
		value_t second;
	};

	template<typename key_t, typename value_t>
	class unordered_map {
	public:	
		constexpr static size_t buffer_size = 1024 * 16;

		value_t& operator[](const key_t& key);
		value_t& operator[](key_t&& key);

		pair<key_t, value_t> buffer[buffer_size];
	private:
	};
}

#include "xml_unordered_map_templated.h"