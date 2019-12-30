#pragma once

#include <iostream>
#include <locale>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;

class object
{
public:
    virtual int             cmp(const object& obj) const = 0;
    virtual std::string     get_string() const
    {
        return "NULL";
    }
    virtual void            set_value(std::string str) = 0;
    virtual void            add(const object& obj) = 0;
    virtual object*         get_copy() = 0;
    virtual string          type_string() const = 0;
    virtual int             type() const = 0;
    virtual ostream&        write_to_bin_stream(std::ostream& stream) = 0;
    virtual istream&        read_from_bin_stream(std::istream& stream) = 0;


};

