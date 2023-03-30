#pragma once
#include <iostream>
#include <fstream>

class JsonValue {
  public:
    virtual ~JsonValue() = 0;
    virtual void print(std::ostream& out) const = 0;
    struct Pair {
        JsonValue* value;
        char* name;
    };
};
class NullValue : public JsonValue {
  public:
    NullValue();
    void print(std::ostream& out) const override;
};
class NumberValue : public JsonValue {
    int number;

  public:
    NumberValue(int number);
    void print(std::ostream& out) const override;
};
class BoolValue : public JsonValue {
    bool x;

  public:
    BoolValue(bool x);
    void print(std::ostream& out) const override;
};
class StringValue : public JsonValue {
    char* value;

  public:
    StringValue(const char* sir);
    ~StringValue();
    void print(std::ostream& out) const override;
};
class ArrayValue : public JsonValue {
    JsonValue* value[16];
    int count;

  public:
    ArrayValue();
    void add(JsonValue* value);
    void print(std::ostream& out) const override;
};
class ObjectValue : public JsonValue {
    Pair* Value[16];
    int count;

  public:
    ObjectValue();
    ~ObjectValue();
    void add(const char* name, JsonValue* value);
    void print(std::ostream& out) const override;
    explicit operator unsigned() const;
};
