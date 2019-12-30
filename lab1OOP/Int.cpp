#include "Int.h"

Int::Int()
{
	value = 0;
}

Int::Int(int data)
{
	value = data;
}

Int::Int(string data)
{
	set_value(data);
}

int Int::cmp(const object& obj) const
{
	if (obj.type() != type()) throw;
	int x = ((const Int&)obj).value;
	if (x == value) return 0;
	if (value > x) return 1;
	else return -1;
}

std::string Int::get_string() const
{
	return to_string(value);
}

void Int::set_value(std::string str)
{
	value = stoi(str);
}

void Int::add(const object& obj)
{
	if (obj.type() != type()) throw;
	value += ((const Int&)obj).value;
}

object* Int::get_copy()
{
	Int* tmp = new Int(*this);
	return tmp;
}

std::string Int::type_string() const
{
	return typeid(Int).name();
}

int Int::type() const
{
	return typeid(Int).hash_code();
}

ostream& Int::write_to_bin_stream(std::ostream& stream)
{
	stream.write((char*)&value, sizeof(value));
	return stream;
}

istream& Int::read_from_bin_stream(std::istream& stream)
{
	stream.read((char*)&value, sizeof(value));
	return stream;
}
