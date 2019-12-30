#include "Double.h"

Double::Double()
{
	value = 0;
}

Double::Double(double x)
{
	value = x;
}

Double::Double(int x)
{
	value = x;
}

Double::Double(string str)
{
	set_value(str);
}

int Double::cmp(const object& obj) const
{
	if (obj.type() != type()) throw;
	int x = ((const Double&)obj).value;
	if (x == value) return 0;
	if (value > x) return 1;
	else return -1;
}

std::string Double::get_string() const
{
	return to_string(value);
}

void Double::set_value(std::string str)
{
	value = atof(str.c_str());
}

void Double::add(const object& obj)
{
	if (obj.type() != type()) throw;
	value += ((const Double&)obj).value;
}

object* Double::get_copy()
{
	Double* tmp = new Double(*this);
	return tmp;
}

std::string Double::type_string() const
{
	return typeid(Double).name();
}

int Double::type() const
{
	return typeid(Double).hash_code();
}

ostream& Double::write_to_bin_stream(std::ostream& stream)
{
	stream.write((char*)&value, sizeof(value));
	return stream;
}

istream& Double::read_from_bin_stream(std::istream& stream)
{
	stream.read((char*)&value, sizeof(value));
	return stream;
}
