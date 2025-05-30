#pragma once

#include "xml_string.h"
#include "xml_assert.h"

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
	class unordered_map;

	template<typename key_t, typename value_t>
	class unordered_map_iterator {
		friend unordered_map<key_t, value_t>;
	public:

		pair<key_t, value_t>& operator*();
		void operator++();
		bool operator==(const unordered_map_iterator& other) const;
		bool operator!=(const unordered_map_iterator& other) const;

	private:
		unordered_map_iterator(const unordered_map<key_t, value_t>& owner, pair<key_t, value_t>* pointer = nullptr);

		const unordered_map<key_t, value_t>& owner;
		pair<key_t, value_t>* pointer = nullptr;
	};

	template<typename key_t, typename value_t>
	class unordered_map {
	public:	
		constexpr static size_t buffer_size = 1024 * 16;

		value_t& operator[](const key_t& key);
		value_t& operator[](key_t&& key);

		unordered_map_iterator<key_t, value_t> find(const key_t& key) const;

		unordered_map_iterator<key_t, value_t> begin() const;
		unordered_map_iterator<key_t, value_t> end() const;

		pair<key_t, value_t> buffer[buffer_size];
	private:
	};
}

#include "xml_unordered_map_templated.h"