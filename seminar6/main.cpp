#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Jason.h"


// Implement the following classes that represents json objects:
// - base class JsonValue with an abstract destructor and an abstract print function that takes an ostream&
// - NullValue: represents a null
// - NumberValue: stores a number
// - BoolValue: stores a bool
// - StringValue: stores a string (max size 255)
// - ArrayValue: stores an array of values (max 16); the add function will take a value pointer and add it to the array
// - ObjectValue: stores an array of pairs of (name, value) (max 16); the add function will take a string for name and a
//      pointer for the value and add it. Also add a cast operator to unsigned that returns the number of nodes.
// You may have all the class declarations in a single header, and all the definitions in a cpp.
// The print function will print the tree in such a way that the output is valid json
// (check here: https://jsonlint.com/)

// Bonus 1: make the print function constant.
// Bonus 2: make sure there are no memory leaks.
// Bonus 3: add a command line argument that says whether the output should go to stdout or to a file, and which file.
// Bonus 4: make the print function print with proper indentation with the help of a new argument.

// class JsonValue {
// public:
//     virtual ~JsonValue() = 0;
//
//     virtual void print(std::ostream& out) = 0;
// };

int main() {
    auto array_numbers = new ArrayValue();
    array_numbers->add(new NumberValue(5));
    array_numbers->add(new NumberValue(10));
    array_numbers->add(new NumberValue(15));

    auto array_strings = new ArrayValue();
    array_strings->add(new StringValue("abc"));
    array_strings->add(new StringValue("def"));
    array_strings->add(new StringValue("ghi"));

    auto subobject = new ObjectValue();
    subobject->add("email", new StringValue("t@gmail.com"));
    subobject->add("name", new StringValue("T"));
    subobject->add("online", new BoolValue(true));

    auto object = new ObjectValue();
    object->add("n", new NullValue());
    object->add("array_numbers", array_numbers);
    object->add("array_strings", array_strings);
    object->add("info", subobject);

    std::cout << "Top node has " << (unsigned) *object << " subnodes\n";

    object->print(std::cout);
}
