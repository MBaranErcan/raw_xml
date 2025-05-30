#include "xml_string.h"

xml::string xml::string_bank::malloc(size_t size)
{
	size_t begin = buffer_iterator;
	buffer_iterator += size;
	size_t end = buffer_iterator;

	return xml::string(begin, end);
}

void xml::string_bank::relloc(string& string, size_t new_size)
{
	bool is_on_top_of_buffer = (size_t)string._end == buffer_iterator;
	size_t old_begin = string._begin;
	size_t old_size = string.size();

	if (is_on_top_of_buffer)
		buffer_iterator = string._begin;

	xml::string new_string = malloc(new_size);

	string._end += new_string._begin - old_begin;
	string._begin = new_string._begin;
	string._capacity_end = new_string._capacity_end;

	new_string._begin = 0;
	new_string._end = 0;
	new_string._capacity_end = 0;

	if (!is_on_top_of_buffer) {
		for (size_t i = 0; i < old_size; i++)
			string[i] = (buffer[old_begin + i]);
	}
}

void xml::string_bank::free(string& string)
{
	if ((size_t)string._end == buffer_iterator)
		buffer_iterator = string._begin;

	string._begin = 0;
	string._end = 0;
	string._capacity_end = 0;
}


// --------------------------------------------------------------------

xml::string_bank xml::string::bank;

xml::string::string(size_t begin, size_t end) :
	_begin(begin), _end(end), _capacity_end(end) {}

xml::string::string(const char* global_string)
{
	size_t string_size = 0;
	for (size_t i = 0; i < max_string_size && *(global_string + i) != '\0'; i++)
		string_size++;

	resize(string_size);

	for (size_t i = 0; i < string_size; i++)
		(*this)[i] = *(global_string + i);
}

xml::string::~string()
{
	bank.free(*this);
}

xml::string::string(const string& other)
{
	resize(other.size());

	for (size_t i = 0; i < size(); i++)
		(*this)[i] = other.at(i);
}

xml::string::string(string&& other)
{
	this->_begin = other._begin;
	this->_end = other._end;
	this->_capacity_end = other._capacity_end;

	other._begin = 0;
	other._end = 0;
	other._capacity_end = 0;
}

xml::string& xml::string::operator=(const string& other)
{
	this->resize(other.size());

	for (size_t i = 0; i < size(); i++)
		(*this)[i] = other.at(i);

	return *this;
}

xml::string& xml::string::operator=(string&& other)
{
	this->_begin = other._begin;
	this->_end = other._end;
	this->_capacity_end = other._capacity_end;

	other._begin = 0;
	other._end = 0;
	other._capacity_end = 0;

	return *this;
}


const char* xml::string::c_str() const
{
	return begin();
}

void xml::string::reserve(size_t new_size)
{
	if (size() < new_size)
		bank.relloc(*this, new_size);
}

void xml::string::resize(size_t new_size)
{
	if (capacity() < new_size)
		bank.relloc(*this, new_size);

	size_t extra_size = new_size - size();
	for (size_t i = _end; i < new_size; i++)
		(*this)[i] = '\0';

	_end = _begin + new_size;
}

char* xml::string::begin() const
{
	return &(bank.buffer[_begin]);
}

char* xml::string::end() const
{
	return &(bank.buffer[_end]);
}

size_t xml::string::size() const {
	return _end - _begin;
}

size_t xml::string::capacity() const
{
	return _capacity_end - _begin;
}

char xml::string::at(size_t offset) const {
	//if (offset >= size())
	//	error;

	return *(begin() + offset);
}

bool xml::string::empty()
{
	return size() == 0;
}

size_t xml::string::find_last_of(char character)
{
	for (size_t i = size() - 1; i >= 0; i--)
		if (at(i) == character)
			return i;

	return npos;
}

xml::string xml::string::substr(size_t offset, size_t count)
{
	xml::string new_string;
	new_string.resize(count);
	for (size_t i = 0; i < count; i++)
		new_string[count] = at(offset + i);

	return new_string;
}

char& xml::string::operator[](size_t offset)
{
	//if (offset >= size())
	//	error

	return *(begin() + offset);
}

bool xml::string::operator==(const string& other)
{
	if (size() != other.size())
		return false;

	for (size_t i = 0; i < size(); i++) {
		if (at(i) != other.at(i))
			return false;
	}
	return true;
}


bool xml::string::operator==(const char* other)
{
	size_t other_string_size = 0;
	for (size_t i = 0; i < max_string_size && *(other + i) != '\0'; i++)
		other_string_size++;

	if (size() != other_string_size)
		return false;

	for (size_t i = 0; i < size(); i++) {
		if (at(i) != *(other + i))
			return false;
	}
	return true;
}

bool xml::string::operator!=(const string& other) {
	return !(*this == other);
}

bool xml::string::operator!=(const char* other)
{
	return !(*this == other);
}

xml::string& xml::string::operator+=(const string& other)
{
	size_t size_needed = size() + other.size();

	if (capacity() < size_needed)
		reserve(max(size() * 2, size_needed));

	for (size_t i = 0; i < other.size(); i++)
		(*this)[size() + i] = other.at(i);

	_end += other.size();

	return *this;
}

xml::string& xml::string::operator+=(const char* other)
{
	size_t other_string_size = 0;
	for (size_t i = 0; i < max_string_size && *(other + i) != '\0'; i++)
		other_string_size++;

	size_t size_needed = size() + other_string_size;

	if (capacity() < size_needed)
		reserve(max(size() * 2, size_needed));

	for (size_t i = 0; i < other_string_size; i++)
		(*this)[size() + i] = *(other + i);

	_end += other_string_size;

	return *this;
}

xml::string& xml::string::operator+=(char other)
{
	size_t other_string_size = 1;

	size_t size_needed = size() + other_string_size;

	if (capacity() < size_needed)
		reserve(max(size() * 2, size_needed));

	for (size_t i = 0; i < other_string_size; i++)
		(*this)[size() + i] = other;

	_end += other_string_size;

	return *this;
}

xml::string xml::string::operator+(const string& other)
{
	xml::string new_string(*this);
	new_string += other;
	return new_string;
}

xml::string xml::string::operator+(const char* other)
{
	xml::string new_string(*this);
	new_string += other;
	return new_string;
}

xml::string xml::string::operator+(const char other)
{
	xml::string new_string(*this);
	new_string += other;
	return new_string;
}

void xml::string_bank::clear()
{
	buffer_iterator = 0;
	for (size_t i = 0; i < buffer_size; i++)
		buffer[i] = 0;
}

size_t xml::string::min(size_t a, size_t b)
{
	return a < b ? a : b;
}

size_t xml::string::max(size_t a, size_t b)
{
	return a > b ? a : b;

}

#ifdef XML_INCLUDE_IOSTREAM
std::ostream& operator<<(std::ostream& stream, const xml::string& xml_string)
{
	for (size_t i = 0; i < xml_string.size(); i++)
		stream << xml_string.at(i);
	return stream;
}
#endif