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
inline size_t xml::hash<xml::string>(const xml::string& obj) {
	constexpr size_t prime_constant = 32 - 1;
	size_t size = obj.size();

	size_t hashCode = 0;
	for (size_t i = 0; i < size; i++) {
		hashCode += obj.at(i) * _int_pow(prime_constant, i);
	}
	return hashCode + 10041405866739416012;
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

	xml_assert(false, "unordered_buffer::operator[] is overflowed");
	return buffer[0].second;
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

	xml_assert(false, "unordered_buffer::operator[] is overflowed");
	return buffer[0].second;
}

template<typename key_t, typename value_t>
xml::unordered_map_iterator<key_t, value_t> xml::unordered_map<key_t, value_t>::find(const key_t& key) const
{
	size_t index = hash(key);
	for (size_t i = 0; i < buffer_size; i++) {
		const pair<key_t, value_t>& candidate = buffer[(index + i) % buffer_size];
		if (candidate.first == key) {
			return xml::unordered_map_iterator<key_t, value_t>(*this, (xml::pair<key_t, value_t>*) & buffer[index + i]);
		}
		else if (candidate.first.empty()) {
			return end();
		}
	}
	return end();
}

template<typename key_t, typename value_t>
xml::unordered_map_iterator<key_t, value_t> xml::unordered_map<key_t, value_t>::begin() const
{
	xml::unordered_map_iterator<key_t, value_t> iterator(*this, (xml::pair<key_t, value_t>*) & buffer[0]);
	++iterator;
	return iterator;
}

template<typename key_t, typename value_t>
xml::unordered_map_iterator<key_t, value_t> xml::unordered_map<key_t, value_t>::end() const
{
	return xml::unordered_map_iterator<key_t, value_t>(*this, (xml::pair<key_t, value_t>*)&buffer[buffer_size]);
}

template<typename key_t, typename value_t>
xml::unordered_map_iterator<key_t, value_t>::unordered_map_iterator(const unordered_map<key_t, value_t>& owner, pair<key_t, value_t>* pointer) :
	owner(owner), pointer(pointer) {
}

template<typename key_t, typename value_t>
xml::pair<key_t, value_t>& xml::unordered_map_iterator<key_t, value_t>::operator*()
{
	xml_assert(pointer != nullptr, "unordered_map_interator::operator*() is called but pointer was nullptr");
	return *pointer;
}
template<typename key_t, typename value_t>
void xml::unordered_map_iterator<key_t, value_t>::operator++()
{
	xml_assert(pointer != nullptr, "unordered_map_interator::operator++() is called but pointer was nulllptr)");
	for (pointer++; pointer < owner.end().pointer; pointer++) {
		if (!pointer->first.empty())
			return;
	}
	return;
}


template<typename key_t, typename value_t>
bool xml::unordered_map_iterator<key_t, value_t>::operator==(const unordered_map_iterator& other) const
{
	if (pointer == nullptr) return false;
	if (other.pointer == nullptr) return false;
	return pointer == other.pointer;
}

template<typename key_t, typename value_t>
bool xml::unordered_map_iterator<key_t, value_t>::operator!=(const unordered_map_iterator& other) const
{
	return !(*this).operator==(other);
}