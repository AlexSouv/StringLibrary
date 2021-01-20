#include "String.h"

namespace String
{
    string::string() : sz{0}, pChars{nullptr},space{0} {}

    string::string(const char* s) : sz{ strlen(s) },pChars{ new char[sz] }, space{ strlen(s) }               ///Constructor using a null-terminated C String
    {
        for(int i = 0; i < sz ; i++)
        {
            pChars[i] = s[i];
        }
    }

    string::string(const string& s) : sz{ s.sz }, pChars{ new char[s.sz] }, space{ s.sz }               ///copy constructor
    {
        for(int i = 0; i < sz; i++)
        {
            pChars[i] = s.pChars[i];
        }
    }

    string& string::operator=(const string& s)     ///copy assignment
    {
        if(this == &s)
        {
            return *this;
        }
        if(s.sz <= space)
        {
            for(int i = 0; i < s.sz; i++)
            {
                pChars[i] = s.pChars[i];
            }
            sz = s.sz;
            return *this;
        }
        char* p = new char[s.sz];
        for(int i = 0; i< s.sz; i++)
        {
            p[i] = s.pChars[i];
        }
        delete[] pChars;
        //sz = a.sz;
        space = sz = s.sz;
        pChars = p;
        return *this;
    }

    string& string::operator=(const char* s)       ///copy assignment using a null-terminated C String
    {
    //cout << "s: " << s << endl;
    sz = strlen(s);
    space = strlen(s);
    char* p = new char[sz];

    for(size_t i = 0; i < sz; i++)
    {
        p[i] = s[i];
        //cout << "p[" << i << "]:" << p[i] << endl;
    }
    delete[] pChars;
    pChars = p;
    return *this;

    }

    string& string::operator=(string&& s)          ///move assignment
    {
        cout << "Move" << endl;
        delete[] pChars;
        pChars = s.pChars;
        sz = s.sz;
        space = s.space;
        
        s.pChars = nullptr;
        s.sz = 0;
        return *this;
    }

    string::~string()
    {
        delete[] pChars;
    }

    char& string::operator[](size_t pos) { return pChars[pos]; }               ///set operator
    const char& string::operator[](size_t pos) const { return pChars[pos]; }   ///get operator

    void string::reserve(size_t n)
    {
        if(n <= space)
        {
            return;
        }
        char* p = new char[n];
        for(int i = 0; i < sz; i++)
        {
            p[i] = pChars[i];
        }
        delete[] pChars;
        pChars = p;
        space = n;
    }

    void string::push_back(const char c)                   ///push char c to the end
    {
        if(space == 0)
        {
            reserve(8);
        }
        else if(sz == space)
        {
            reserve(2 * space);
        }
        pChars[sz] = c;
        sz++;
    }

    size_t string::find(const char* s, size_t pos) const ///return index of first occurrence of s, SIZE_MAX if not found
    {
        size_t temp = 0;
        bool check = true;
        
        for(size_t i = pos; i < sz; i++)
        {
            size_t indexS = 0;
            check = true;
            
            if(pChars[i] == s[0])
            {
                temp = i;
                while((s[indexS] != '\0') && (check != false))
                {
                    if(pChars[indexS + i] != s[indexS])
                    {
                        check = false;
                    }
                    indexS++;
                }
                if(check == true)
                {
                    return temp;
                }
            }
        }
        return SIZE_MAX;
    }

bool operator==(const string& lhs, const string& rhs)  ///check equality (same size, all chars the same)
{
    if(lhs.size() != rhs.size())
    {
        return false; //If size is not equal return false
    }
    else        //Else do compare loop
    {
        for(int i = 0; i < lhs.size(); i++) //Because size are the same, can use lhs or rhs?
        {
            if(lhs[i] != rhs[i]) //If lhs[i] != rhs[i] return false
            {
                return false;
            }
        }
        return true; //If it goes through for loop without return false return true (both are equal)?
    }
}

bool operator==(const string& lhs, const char* rhs)    ///equality with null terminated C string
{
    bool check = false;
    if(lhs.size() != strlen(rhs))
    {
        check = false;
        return check;
    }
    for(int i = 0; i < lhs.size(); i++)      //Might need to change
    {
        if(lhs[i] != rhs[i])
        {
            check = false;
            return check;
        }
       // counter++;
    }
    //cout << "counter: " << counter << endl;
    check = true;
    return check;

}

bool operator>(const string& lhs, const string& rhs)   ///greater than operator, true if lhs > rhs
{

    for(int i = 0; i < lhs.size(); i++)
    {
        if(lhs[i] != rhs[i])
        {
            return lhs[i] > rhs[i];
        }

    }
    return lhs.size() > rhs.size();
}

string operator+(const string& lhs, const string& rhs) ///concatenate two MyStrings, return the result
{
    string temp;
    for(int i = 0; i < lhs.size(); i++)
    {
        temp.push_back(lhs[i]);
    }
    for(int i = 0; i < rhs.size(); i++)
    {
        temp.push_back(rhs[i]);
    }
    return temp;
}

ostream& operator<<(ostream& os, const string& s)
{
    for(int i = 0; i < s.size(); i++)
    {
        os << s[i];
    }
    return os;
}

istream& operator>>(istream& is, string& s)
{
    char c;
    while(is.get(c) && !(isspace(c)))
    {
        s.push_back(c);
    }
    return is;
}

}
