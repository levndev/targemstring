#include <cstring>
#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include "String.h"
int test_count = 0;
int tests_failed = 0;
#define IS_TRUE(x) { if (!(x)) { std::cout << __FUNCTION__ << " failed on line " << __LINE__ << std::endl; tests_failed++; } test_count++; }

void run_tests() {
    IS_TRUE(String("").empty());
    IS_TRUE(String("Test").length() == 4);
    IS_TRUE(String("Test").capacity() == 8);
    {
        String test = String("Test");
        IS_TRUE(test == test);
    }
    IS_TRUE(String("Test") == String("Test"));
    IS_TRUE(String("Test") == "Test");
    IS_TRUE(String("Test") != String("Test 2"));
    IS_TRUE(String("Test") != "Test 2");
    IS_TRUE(String("Hello ") + String("world!") == String("Hello world!"));
    {
        String test = String("Hello ");
        test += String("world!");
        IS_TRUE(test == String("Hello world!"));
    }
    {
        String test = "Hello ";
        test += "world!";
        IS_TRUE(test == "Hello world!");
    }
    {
        // строка в 5 символов + строка в 10 символов - capacity дложна быть 2 * 15 = 30
        String test = "12345";
        test += "0123456789";
        IS_TRUE(test.capacity() == 30);
    }
    {
        String test = "abcd";
        IS_TRUE(test[0] == 'a');
        IS_TRUE(test[1] == 'b');
        IS_TRUE(test[2] == 'c');
        IS_TRUE(test[3] == 'd');
        test[1] = 'c';
        test[2] = 'b';
        IS_TRUE(test[0] == 'a');
        IS_TRUE(test[1] == 'c');
        IS_TRUE(test[2] == 'b');
        IS_TRUE(test[3] == 'd');
        IS_TRUE(test == "acbd");
        String test2 = test;
        String test3 = String(test);
        test[1] = '_';
        test[2] = '_';
        IS_TRUE(test == "a__d");
        IS_TRUE(test2 == "acbd");
        IS_TRUE(test3 == "acbd");
        test.clear();
        IS_TRUE(test == "");
        IS_TRUE(test.length() == 0);
        IS_TRUE(test.capacity() == 8);
    }
    std::cout << "All tests finished, " << tests_failed << " out of " << test_count << " tests failed" << std::endl;
}

bool case_insensitive_greater(const String& lhs, const String& rhs) {
    char * lhs_copy = new char[lhs.length()];
    char * rhs_copy = new char[rhs.length()];
    std::transform(lhs.begin(), lhs.end(), lhs_copy, ::tolower);
    std::transform(rhs.begin(), rhs.end(), rhs_copy, ::tolower);
    int result = std::strcmp(lhs_copy, rhs_copy);
    delete[] lhs_copy;
    delete[] rhs_copy;
    return result > 0;
}

// аргумент test - запускает тесты
int main(int argc, char ** args)
{
    if (argc > 1) {
        if (std::strcmp(args[1], "test") == 0) {
            run_tests();
        }
    }
    else {
        std::vector<String> strings = std::vector<String>();
        std::cout << "Введите кол-во строк:" << std::endl;
        int string_count = 0;
        std::cin >> string_count;
        if (string_count < 1)
            return 0;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Введите " << string_count << " строк" << std::endl;
        for (int i = 0; i < string_count; i++) {
            String line = String();
            std::cin >> line;
            strings.push_back(line);
        }
        std::sort(strings.begin(), strings.end(), case_insensitive_greater);
        std::cout << "Результат: " << std::endl;
        for (int i = 0; i < string_count; i++) {
            std::cout << strings[i] << std::endl;
        }
    }
}