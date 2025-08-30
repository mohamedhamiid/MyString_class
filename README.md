# MyString Class

A modern C++ implementation of a custom String class featuring complete memory management, move semantics, operator overloading, and essential string operations.

## Features

- **Complete RAII (Resource Acquisition Is Initialization)** with proper constructors and destructor
- **Move semantics** for efficient resource management (C++11)
- **Rule of Five** implementation (destructor, copy constructor, copy assignment, move constructor, move assignment)
- **Comprehensive operator overloading** for natural string operations
- **Memory leak detection** integration with Visual Studio's CRT debug heap
- **Iterator support** with begin/end methods for range-based loops
- **Essential string methods** (substring, find, length)

## Class Overview

```cpp
class String {
private:
    char* str;    // Dynamic character array
    int size;     // String length (excluding null terminator)
    
public:
    // Constructors and Destructor
    String();                           // Default constructor
    explicit String(const char* str);   // Parameterized constructor
    String(const String& obj);          // Copy constructor
    String(String&& obj);               // Move constructor
    ~String();                          // Destructor
    
    // Assignment Operators
    String& operator=(const String& obj);   // Copy assignment
    String& operator=(String&& obj);        // Move assignment
    
    // Operator Overloads
    String& operator+=(const char* str);     // Concatenation with C-string
    String& operator+=(String& obj);         // Concatenation with String object
    char& operator[](int index);             // Subscript operator
    bool operator==(const String& obj);      // Equality comparison
    bool operator!=(const String& obj);      // Inequality comparison
    bool operator<(const String& obj);       // Less than comparison
    bool operator>(const String& obj);       // Greater than comparison
    
    // Stream Operators (friend functions)
    friend std::ostream& operator<<(std::ostream& os, const String& obj);
    friend std::istream& operator>>(std::istream& is, String& obj);
    
    // String Methods
    char* begin();                          // Iterator begin
    char* end();                            // Iterator end
    int len() const;                        // Get string length
    String substr(int start, int length);   // Extract substring
    int find(char x);                       // Find character position
};
```

## Usage Examples

### Basic Construction and Output

```cpp
#include "String.h"

int main() {
    // Default constructor
    String s1;
    
    // Parameterized constructor
    String s2("Hello, World!");
    std::cout << s2 << std::endl;  // Output: Hello, World!
    
    // Explicit keyword prevents implicit conversion
    // String s3 = "Test";        // ❌ Error - implicit conversion blocked
    String s3 = String("Test");   // ✅ Correct - explicit conversion
    
    return 0;
}
```

### Copy Semantics

```cpp
String original("Original String");

// Copy constructor
String copy1(original);
std::cout << copy1 << std::endl;  // Output: Original String

// Copy assignment
String copy2;
copy2 = original;
std::cout << copy2 << std::endl;  // Output: Original String

// Self-assignment protection is built-in
copy2 = copy2;  // Safe operation
```

### Move Semantics (Efficient Resource Transfer)

```cpp
String source("Move me!");

// Move constructor - transfers ownership
String moved1(std::move(source));
std::cout << source << std::endl;  // Output: String is empty
std::cout << moved1 << std::endl;  // Output: Move me!

// Move assignment
String moved2;
moved2 = std::move(moved1);
std::cout << moved1 << std::endl;  // Output: String is empty
std::cout << moved2 << std::endl;  // Output: Move me!
```

### String Operations

```cpp
String str("Hello");

// Concatenation
str += " World";           // Concatenate C-string
std::cout << str;          // Output: Hello World

String suffix("!");
str += suffix;             // Concatenate String object
std::cout << str;          // Output: Hello World!

// Subscript access
char first = str[0];       // 'H'
str[0] = 'h';             // Modify: "hello World!"

// Comparison operators
String str1("ABC");
String str2("ABC");
if (str1 == str2) {
    std::cout << "Strings are equal" << std::endl;
}

// Size-based comparison
String short_str("Hi");
String long_str("Hello");
if (short_str < long_str) {
    std::cout << "short_str is shorter" << std::endl;
}
```

### String Methods

```cpp
String text("Programming");

// Get length
int length = text.len();    // Returns 11

// Extract substring
String sub = text.substr(0, 7);  // Returns "Program"
std::cout << sub << std::endl;

// Find character
int pos = text.find('g');   // Returns 3 (first occurrence)
int not_found = text.find('z'); // Returns -1

// Range-based loop support
for (char c : text) {
    std::cout << c << " ";
}
```

### Input/Output Operations

```cpp
String userInput;

// Input from user
std::cout << "Enter a string: ";
std::cin >> userInput;

// Output to console
std::cout << "You entered: " << userInput << std::endl;
```

## Key Design Decisions

### Explicit Constructor
The parameterized constructor is marked `explicit` to prevent unintended implicit conversions:
```cpp
String s = "Hello";        // ❌ Compilation error
String s = String("Hello"); // ✅ Explicit construction required
```

### Memory Management
- **RAII principle**: Resources acquired in constructor, released in destructor
- **Deep copying**: Copy operations create independent memory allocations
- **Move semantics**: Efficient resource transfer without unnecessary copying
- **Self-assignment protection**: Safe assignment operations

### Operator Overloading Philosophy
- **Natural syntax**: Operators behave intuitively like built-in types
- **Consistent semantics**: Operations follow standard C++ conventions
- **Efficient implementation**: Minimize unnecessary memory allocations

## Memory Safety Features

- **Automatic cleanup**: Destructor ensures no memory leaks
- **Null pointer safety**: Checks for null pointers in critical operations
- **Self-assignment protection**: Prevents issues with `obj = obj`
- **Move semantics**: Prevents unnecessary deep copies for temporary objects
- **Visual Studio integration**: Uses `_CrtSetDbgFlag` for leak detection

## Performance Considerations

- **Move semantics**: O(1) resource transfer instead of O(n) copying
- **In-place concatenation**: `operator+=` modifies existing object efficiently
- **Minimal allocations**: Careful memory management reduces fragmentation
- **Iterator support**: Enables efficient range-based loops

## Building and Testing

### Prerequisites
- C++11 or later compiler
- Visual Studio (for memory leak detection features)

### Compilation
```bash
g++ -std=c++11 main.cpp -o mystring_test
```

### Running Tests
The main function includes comprehensive tests for all features:
```bash
./mystring_test
```

## Memory Leak Detection

The implementation includes Visual Studio's CRT Debug Heap integration:
```cpp
_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
```

This automatically reports memory leaks when the program terminates in debug builds.

## Limitations and Future Enhancements

### Current Limitations
- **Fixed buffer size** for input operations (1024 characters)
- **Basic comparison logic** (size-based for `<` and `>` operators)
- **No bounds checking** in subscript operator
- **Limited string methods** compared to std::string

### Potential Enhancements
- Add bounds checking with exception handling
- Implement more string methods (replace, trim, split)
- Add support for Unicode/UTF-8
- Implement string_view compatibility
- Add capacity management for better performance
- Enhanced comparison operators (lexicographic ordering)

## Thread Safety

⚠️ **Not thread-safe**: This implementation is not designed for concurrent access. External synchronization required for multi-threaded usage.

## License

This is an educational implementation demonstrating modern C++ concepts including move semantics, operator overloading, and RAII principles.

---

**Note**: This implementation prioritizes educational value and demonstrates core C++ concepts. For production use, consider `std::string` or other mature string libraries that provide additional features, optimizations, and safety guarantees.
