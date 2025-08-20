#include <bits/stdc++.h>
#include <crtdbg.h>
class String
{
private:
    char *str;
    int size;
    void print(std::ostream &os)
    {
        os << str;
    }

public:
    // Default constructor
    String() : str(nullptr), size(0) {};
    // Parameterized constructor
    // - explicit is used to oblige casting
    // String s = std::string("Name"); # Error
    // String s = String(std::string("Name")); # No Error
    explicit String(char str[])
    {
        this->size = strlen(str);
        this->str = new char[size + 1];
        memcpy(this->str, str, this->size + 1);
        std::cout << "Parameterized constructor called: str = " << this->str << ", size = " << this->size << std::endl;
    }
    // Destructor
    ~String()
    {
        delete[] str;
        str = nullptr;
        std::cout << "Destructor Called" << std::endl;
    }
    // Overload printing
    friend std::ostream &operator<<(std::ostream &os, String &obj);
    // Length
    int len() { return this->size; }

    // Copy constructor
    String(const String &obj)
    {
        this->str = new char[obj.size + 1];
        this->size = obj.size;
        memcpy(this->str, obj.str, this->size + 1);
        std::cout << "Copy constructor called: str = " << this->str << ", size = " << this->size << std::endl;
    }

    // Copy assignment
    String &operator=(String &obj)
    {
        if (this == &obj)
        {
            return *this;
        }
        if (this->str)
        {
            delete[] this->str;
            std::cout << "Old data deleted before copying" << std::endl;
        }
        this->str = new char[obj.size + 1];
        this->size = obj.size;
        memcpy(this->str, obj.str, this->size + 1);
        std::cout << "Copy assignment called: str = " << this->str << ", size = " << this->size << std::endl;
        return *this;
    }

    // Move constructor
    String(String &&obj)
    {
        this->str = obj.str;
        this->size = obj.size;
        obj.str = nullptr;
        obj.size = 0;
        std::cout << "Move constructor called: str = " << this->str << ", size = " << this->size << std::endl;
    }

    // Move assignment
    String &operator=(String &&obj)
    {
        if (&obj == this)
        {
            return *this;
        }
        if (obj.str == nullptr)
        {
            std::cout << "Move assignment called with empty object" << std::endl;
            return *this;
        }
        if (this->str)
        {
            delete[] this->str;
            std::cout << "Old data deleted before moving" << std::endl;
        }
        this->str = obj.str;
        this->size = obj.size;
        obj.str = nullptr;
        obj.size = 0;
        std::cout << "Move assignment called: str = " << this->str << ", size = " << this->size << std::endl;
        return *this;
    }

    // Concatenation operators
    String &operator+=(char str[])
    {
        // Assign new data
        int newSize = this->size + strlen(str);
        char *newStr = new char[newSize + 1];
        memcpy(newStr, this->str, this->size);
        memcpy(newStr + this->size, str, strlen(str) + 1);

        // Remove old data
        delete[] this->str;

        this->size = newSize;
        this->str = newStr;

        newStr = nullptr;

        std::cout << "Concat operator called: str = " << this->str << ", size = " << this->size << std::endl;

        return *this;
    }

    String &operator+=(String &obj)
    {
        return *this += obj.str;
    }
};
std::ostream &operator<<(std::ostream &os, String &obj)
{
    if (obj.str != nullptr)
        obj.print(os);
    else
        os << "String is empty";
    return os;
}

int main()
{
    // Check Memory leakage
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    // Test parameterized constructor
    std::cout << "Test paramaterized constructor" << std::endl
              << "----------------------------------" << std::endl;
    String s("Hamid");
    // Test print
    std::cout << s << std::endl;
    std::cout << "----------------------------------" << std::endl;

    // Test that implicit conversion not working because of explicit keyword
    // String s7 = "Hamid"; #error

    // Test copy constructor
    std::cout << "Test copy constructor" << std::endl
              << "----------------------------------" << std::endl;
    String s1(s);
    // Test print
    std::cout << s1 << std::endl;
    std::cout << "----------------------------------" << std::endl;

    // Test concat operator
    std::cout << "Test concat operator" << std::endl
              << "----------------------------------" << std::endl;
    s1 += "oooo";
    // Test print
    std::cout << s1 << std::endl;
    std::cout << "----------------------------------" << std::endl;

    // Test concat operator
    std::cout << "Test obj concat operator" << std::endl
              << "----------------------------------" << std::endl;
    s1 += s;
    // Test print
    std::cout << s1 << std::endl;
    std::cout << "----------------------------------" << std::endl;

    // Test copy assignment
    std::cout
        << "Test copy assignment" << std::endl
        << "----------------------------------" << std::endl;
    // 1- No old data
    std::cout << "1- No old data scenario" << std::endl;
    String s2;
    s2 = s;
    std::cout << s2 << std::endl
              << std::endl;

    // 2- With old data
    std::cout << "2- Old data scenario" << std::endl;
    String s3("Ahmed");
    s3 = s;
    // Test print
    std::cout << s3 << std::endl;
    std::cout << "----------------------------------" << std::endl;

    // Test move constructor
    std::cout << "Test move constructor" << std::endl
              << "----------------------------------" << std::endl;
    String s4(std::move(s3));
    // Test print
    std::cout << s3 << std::endl
              << std::endl;
    // Test print
    std::cout << s4 << std::endl;
    std::cout << "----------------------------------" << std::endl;

    // Test move assignment
    std::cout
        << "Test move assignment" << std::endl
        << "----------------------------------" << std::endl;
    // 1- No old data
    std::cout << "1- No old data scenario" << std::endl;
    String s5;
    s5 = std::move(s4);
    // Test print
    std::cout << s4 << std::endl;
    // Test print
    std::cout << s5 << std::endl
              << std::endl;

    // 2- With old data
    std::cout << "2- Old data scenario" << std::endl;
    String s6("Ali");
    s6 = std::move(s5);
    // Test print
    std::cout << s5 << std::endl;
    std::cout << s6 << std::endl;
    std::cout << "----------------------------------" << std::endl;

    return 0;
}