#include "String.h"
#include "String.h"

String::String()
{
	str = "0";
}

String::String(string str)
{
	this->str = str;
}

int String::cmp(const object& obj) const
{
	if (obj.type() != type()) throw;
	if (((const String&)obj).str == str) return 0;
	if (str > ((const String&)obj).str) return 1;
	else return -1;
}

string String::get_string() const
{
	return str;
}

void String::set_value(string str)
{
	this->str = str;
}

void String::add(const object& obj)
{
	if (obj.type() != type()) throw;
	str += ((const String&)obj).str;
}

object* String::get_copy()
{
	String* new_str = new String(str);
	return new_str;
}

string String::type_string() const
{
	return typeid(String).name();
}

int String::type() const
{
	return typeid(String).hash_code();
}

ostream& String::write_to_bin_stream(std::ostream& stream)
{
	stream.write((char*)str.c_str(), sizeof(str));
	return stream;
}

istream& String::read_from_bin_stream(std::istream& stream)
{
	stream.read((char*)str.c_str(), sizeof(str));
	return stream;
}
