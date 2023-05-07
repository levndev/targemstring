#include <string>
#include <cstring>
#include <iosfwd>
#include <istream>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include "String.h"

constexpr std::size_t default_capacity = 16;
constexpr std::size_t default_input_buffer_size = 16;
#define DEBUG_PRINT std::cout << "Debug : " << __FUNCTION__ << " line " << __LINE__ << std::endl;
// Конструкторы
String::String() : _length(0), _capacity(default_capacity), _chars(new char[default_capacity]()) {
    #ifdef DEBUG
    DEBUG_PRINT
    #endif
}
String::String(int capacity) : _length(0), _capacity(capacity), _chars(new char[capacity]()) {
    #ifdef DEBUG
    DEBUG_PRINT
    #endif
}

String::String(const char* ptr)  {
    if (ptr == nullptr)
        throw std::invalid_argument("Null string");
	_length = std::strlen(ptr);
	_capacity = _length * 2;
	_chars = new char[_capacity];
	std::copy(ptr, ptr + _length, _chars);
	_chars[_length] = 0;
    #ifdef DEBUG
    DEBUG_PRINT
    #endif
}

// Copy конструктор
String::String(const String& original) : _length(original._length), _capacity(original._capacity) {
	_chars = new char[_capacity];
	std::copy(original._chars, original._chars + original._length, _chars);
    _chars[_length] = 0;
    #ifdef DEBUG
    DEBUG_PRINT
    #endif
}

// Move конструктор
// Если после мува оригинал остается живым, то необходимо обязательно использовать String::reset(), иначе в будущем [] даст SegFault
String::String(String&& original) noexcept : _chars(original._chars), _length(original._length), _capacity(original._capacity) {
	original._chars = nullptr;
    original._length = 0;
    original._capacity = 0;
    #ifdef DEBUG
    DEBUG_PRINT
    #endif
}

String::~String() {
	delete[] _chars;
    #ifdef DEBUG
    DEBUG_PRINT
    #endif
}

// Операторы
char String::operator[](std::size_t i) const {
    return _chars[i];
}

char& String::operator[](std::size_t i) {
    return _chars[i];
}

// Copy assignment Использует copy-and-swap
String& String::operator=(String other) {
	std::swap(other._chars, _chars);
	_length = other._length;
	_capacity = other._capacity;
	return *this;
}

String& String::operator+=(const String& other) {
	std::size_t totalLength = _length + other._length;
	if (totalLength + 1 >= _capacity) {
		String newString = *this + other;
		*this = newString;
	}
	else {
		std::copy(other.begin(), other.end(), end());
		_length = totalLength;
		_chars[_length] = 0;
	}
	return *this;
}

String& String::operator+=(const char* other) {
    std::size_t other_length = std::strlen(other);
    std::size_t totalLength = _length + other_length;
	if (totalLength + 1 >= _capacity) {
		String newString = *this + other;
		*this = newString;
	}
	else {
		std::copy(other, other + other_length, _chars + _length);
		_length = totalLength;
		_chars[_length] = 0;
	}
	return *this;
}

// Внешние операторы
String operator+(const String& lhs, const String& rhs) {
	char* buffer = new char[lhs._length + rhs._length + 1];
	std::copy(lhs.begin(), lhs.end(), buffer);
	std::copy(rhs.begin(), rhs.end(), buffer + lhs._length);
	buffer[lhs._length + rhs._length] = 0;
    String result = String(buffer);
    delete[] buffer;
	return result;
}

String operator+(const String& lhs, const char* rhs) {
    std::size_t rhs_length = std::strlen(rhs);
	char* buffer = new char[lhs._length + rhs_length + 1];
	std::copy(lhs.begin(), lhs.end(), buffer);
	std::copy(rhs, rhs + rhs_length, buffer + lhs._length);
	buffer[lhs._length + rhs_length] = 0;
	String result = String(buffer);
    delete[] buffer;
	return result;
}

String operator+(const char* lhs, const String& rhs) {
	return rhs + lhs;
}

bool operator==(const String& lhs, const String &rhs) {
    return std::strcmp(lhs._chars, rhs._chars) == 0;
}

bool operator!=(const String& lhs, const String &rhs) {
    return !(lhs == rhs);
}

bool operator<(const String& lhs, const String &rhs) {
    return std::strcmp(lhs._chars, rhs._chars) < 0;
}

bool operator>(const String& lhs, const String &rhs) {
    return rhs < lhs;
}

bool operator<=(const String& lhs, const String &rhs) {
    return !(lhs > rhs);
}

bool operator>=(const String& lhs, const String &rhs) {
    return !(lhs < rhs);
}

std::ostream& operator<<(std::ostream& os, const String& rhs) {
    os << rhs.c_str();
    return os;
}

std::istream& operator>>(std::istream& is, String& rhs) {
    bool done = false;
    char* buffer = new char[default_input_buffer_size]();
    char* begin = buffer;
    int to_extract = default_input_buffer_size;
    while(!done) {
        try {
            is.getline(begin, to_extract);
        }
        catch(...) {
            delete[] buffer;
            return is;
        }
        if (is.rdstate() == std::ios_base::failbit) {
            std::size_t length = std::strlen(buffer);
            char* new_buffer = new char[length * 2]();
            std::copy(buffer, buffer + length, new_buffer);
            delete[] buffer;
            buffer = new_buffer;
            begin = new_buffer + length;
            is.clear();
        }
        else if (is.rdstate() == std::ios_base::eofbit) {
            std::size_t length = std::strlen(buffer);
            buffer[length] = 0;
            done = true;
        }
        else {
            done = true;
        }
    }
    int length = std::strlen(buffer);
    rhs += buffer;
    delete[] buffer;
    return is;
}

// Другие функции
char& String::at(std::size_t i) {
    if (i < 0 || i >= _length) {
        throw std::out_of_range("String index out of range");
    }
    return (*this)[i];
}

size_t String::length() const {
	return _length;
}

size_t String::capacity() const {
	return _capacity;
}

bool String::empty() const {
    return _length == 0;
}

const char* String::c_str() const {
	return _chars;
}

char* String::begin() const {
    return _chars;
}

char* String::end() const {
    return _chars + _length;
}

// Зануляет первый элемент, эффективно очищая строку
void String::clear() {
    _length = 0;
    _chars[0] = 0;
}

// Полностью сбрасывает строку удаляя буфер и создавая новый с дефолтным размером
void String::reset() {
    _length = 0;
    delete[] _chars;
    _chars = new char[default_capacity]();
    _capacity = default_capacity;
}