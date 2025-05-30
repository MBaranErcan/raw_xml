#pragma once
#include "xml_unordered_map.h"

namespace {
	int64_t _int_abs(int64_t i) {
		return (i < 0 ? -i : i);
	}

	int64_t _int_pow(int64_t b, int64_t e) {
		int64_t pow = 1;
		for (int64_t i = 0; i < _int_abs(e); i++)
			pow = pow * b;
		return pow;
	}
}

template<>
size_t xml::hash<xml::string>(const xml::string& obj) {
	constexpr size_t prime_constant = 32 - 1;
	size_t size = obj.size();

	size_t hashCode = 0;
	for (size_t i = 0; i < size; i++) {
		hashCode += obj.at(i) * _int_pow(prime_constant, i);
	}
	return hashCode;
}

template<typename key_t, typename value_t>
value_t& xml::unordered_map<key_t, value_t>::operator[](const key_t& key) {
	size_t index = hash(key);
	for (size_t i = 0; i < buffer_size; i++) {
		pair<key_t, value_t>& candidate = buffer[(index + i) % buffer_size];
		if (candidate.first == key) {
			return candidate.second;
		}
		else if (candidate.first.empty()) {
			candidate.first = key;
			candidate.second = value_t();
			return candidate.second;
		}
	}

	//	error overflow
	//
}

template<typename key_t, typename value_t>
value_t& xml::unordered_map<key_t, value_t>::operator[](key_t&& key) {
	size_t index = hash(key);
	for (size_t i = 0; i < buffer_size; i++) {
		pair<key_t, value_t>& candidate = buffer[(index + i) % buffer_size];
		if (candidate.first == key) {
			return candidate.second;
		}
		else if (candidate.first.empty()) {
			candidate.first = key;
			return candidate.second;
		}
	}

	//	error overflow
	//
}
