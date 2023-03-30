#define _CRT_SECURE_NO_WARNINGS

#include "Jason.h"
#include <fstream>
#include <cstring>
#include <iostream>

using namespace std;

BoolValue::BoolValue(bool x) {
    this->x = x;
}
void BoolValue::print(std::ostream& out) const {
    if (x == 1) {
        out << "true";
    } else {
        out << "false";
    }
}
NullValue::NullValue(){};

void NullValue::print(std::ostream& out) const {
    out << "Null";
}
JsonValue::~JsonValue(){};

StringValue::StringValue(const char* sir) {
    this->value = new char[256];
    strcpy(this->value, sir);
}

StringValue::~StringValue() {
    delete[](this->value);
}

void StringValue::print(std::ostream& out) const {
    out << "\"" << this->value << "\"";
}

NumberValue::NumberValue(int number) {
    this->number = number;
}

void NumberValue::print(std::ostream& out) const {
    out << '"' << this->number << '"';
}
ArrayValue::ArrayValue() {
    this->count = 0;
}
void ArrayValue::add(JsonValue* value) {
    if (this->count >= 16)
        return;
    this->value[count] = value;
    this->count++;
}
void ArrayValue::print(std::ostream& out) const {
    out << '[';
    for (int i = 0; i < this->count; i++) {
        if (i != 0) {
            out << ", ";
        }
        value[i]->print(out);
    }
    out << ']';
}

ObjectValue::ObjectValue() {
    this->count = 0;
    for (int i = 0; i < 16; i++) {
        this->Value[i] = new Pair;
        this->Value[i]->name = new char[256];
        this->Value[i]->value = nullptr;
    }
}
ObjectValue::~ObjectValue() {
    for (int i = 0; i < 16; i++) {
        delete[] this->Value[i]->name;
        delete this->Value[i];
    }
}
void ObjectValue::add(const char* name, JsonValue* value) {
    if (this->count >= 16)
        return;

    strcpy(this->Value[this->count]->name, name);
    this->Value[this->count]->value = value;
    this->count++;
}
void ObjectValue::print(std::ostream& out) const {
    out << "{";
    for (int i = 0; i < count; i++) {
        if (i != 0)
            out << ", ";
        out << "\"" << this->Value[i]->name << "\":";
        this->Value[i]->value->print(out);
    }
    out << "}";
}
ObjectValue::operator unsigned() const {
    return this->count;
}