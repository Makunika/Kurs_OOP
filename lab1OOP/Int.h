#pragma once
#include "object.h"
class Int :
	public object
{
public:
	Int();
	Int(int data);
    Int(string data);
public:
    int             cmp(const object& obj) const;
    string          get_string() const;
    void            set_value(string str);
    void            add(const object& obj);
    object*         get_copy();
    string          type_string() const;
    int             type() const;
    ostream&        write_to_bin_stream(std::ostream& stream);
    istream&        read_from_bin_stream(std::istream& stream);

public:
    int value;
};

