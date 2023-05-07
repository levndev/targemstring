#include <cstddef>
#include <iosfwd>
#ifndef MYSTRING_H
#define MYSTRING_H

class String {
private:
	char* _chars{};
	std::size_t _length{};
	std::size_t _capacity{};
public:
	// Конструкторы
	String();
	String(int capacity);

	explicit String(const char* ptr);

	// Copy конструктор
	String(const String& original);

	// Move конструктор
	// Если после мува оригинал остается живым, то необходимо обязательно использовать String::reset(), иначе в будущем [] даст SegFault
	String(String&& original) noexcept;

	~String();

	// Операторы
	char operator[](std::size_t i) const;
	char& operator[](std::size_t i);
	// Copy assignment использует copy-and-swap
	String& operator=(String other);
	String& operator=(const char* other);
	String& operator+=(const String& other);
	String& operator+=(const char* other);

	friend std::istream& operator>>(std::istream& is, String& rhs);
	// Другие функции
	char& at(std::size_t i);
	void append(const char* str, std::size_t str_length);
	size_t length() const;
	size_t capacity() const;
	bool empty() const;
	char* begin() const;
	char* end() const;
	const char* c_str() const;
	// Зануляет первый элемент, эффективно очищая строку
	void clear();
	// Полностью сбрасывает строку удаляя буфер и создавая новый с дефолтным размером
	void reset();
};

char* concat(const char* lhs, std::size_t lhs_length, const char* rhs, std::size_t rhs_length);

//Внешние операторы
String operator+(const String& lhs, const String& rhs);
String operator+(const String& lhs, const char* rhs);
String operator+(const char* lhs, const String& rhs);
bool operator==(const String& lhs, const char* rhs);
bool operator!=(const String& lhs, const char* rhs);
bool operator==(const String& lhs, const String &rhs);
bool operator!=(const String& lhs, const String &rhs);
std::ostream& operator<<(std::ostream& os, const String& rhs);
#endif