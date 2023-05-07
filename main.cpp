#include <cstring>
#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include "String.h"
#include "tests.h"

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
        for (int i = 0; i < string_count; i++) {
            std::cout << strings[i] << std::endl;
        }
        std::sort(strings.begin(), strings.end(), case_insensitive_greater);
        std::cout << "Результат: " << std::endl;
        for (int i = 0; i < string_count; i++) {
            std::cout << strings[i] << std::endl;
        }
    }
}