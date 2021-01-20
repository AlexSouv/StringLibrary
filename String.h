#ifndef STRING_H_INCLUDED
#define STRING_H_INCLUDED

#include <iostream>
#include <cstring>
#include <fstream>

using std::ostream; using std::istream; using std::cin; using std::cout; using std::endl;
using std::ofstream; using std::ifstream; using std::streambuf; using std::ios;

namespace String  ///to avoid naming conflicts
{
    class string
    {
        private:

            size_t sz;
            char *pChars;
            size_t space;

        public:

            string();
            string(const char* s);                  ///Constructor using a null-terminated C String
            string(const string& s);                ///copy constructor
            string& operator=(const string& s);     ///copy assignment
            string& operator=(const char* s);       ///copy assignment using a null-terminated C String
            ///string(string&& s);                  ///move constructor, not needed (compiler copy elision)
            string& operator=(string&& s);          ///move assignment
            ~string();

            char& operator[](size_t pos);               ///set operator
            const char& operator[](size_t pos) const;   ///get operator
            void reserve(size_t n);
            void push_back(const char c);                   ///push char c to the end
            size_t capacity() const { return space; }        /// current available space
            size_t size() const {return sz; }               ///current length of pChars
            size_t find(const char* s, size_t pos = 0) const; ///return index of first occurrence of s, SIZE_MAX if not found
    };

    bool operator==(const string& lhs, const string& rhs);  ///check equality (same size, all chars the same)
    bool operator==(const string& lhs, const char* rhs);    ///equality with null terminated C string
    bool operator>(const string& lhs, const string& rhs);   ///greater than operator, true if lhs > rhs
    string operator+(const string& lhs, const string& rhs); ///concatenate two MyStrings, return the result
    ostream& operator<<(ostream& os, const string& s);
    istream& operator>>(istream& is, string& s);
}
#endif // STRING_H_INCLUDED
