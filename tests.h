#include <iostream>
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
        String test = "Hello ";
        test += test;
        IS_TRUE(test == "Hello Hello ");
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
    {
        String test1 = String("test2");
        String test2 = String(std::move(test1));
        test1 += "test1";
        IS_TRUE(test1 == "test1");
        IS_TRUE(test2 == "test2");
    }
    {
        String test1 = String("test2");
        String test2 = String(std::move(test1));
        test1 = "test1";
        IS_TRUE(test1 == "test1");
        IS_TRUE(test2 == "test2");
    }
    {
        String test = String("gfedcba");
        std::sort(test.begin(), test.end());
        IS_TRUE(test == "abcdefg");
    }
    std::cout << "All tests finished, " << tests_failed << " out of " << test_count << " tests failed" << std::endl;
}