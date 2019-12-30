#include "Bin.h"

Bin::Bin()
{
	//сбрасывает все к нулям
	fill(0);
}


Bin::Bin(const Bin& obj)
{
	razryad_ = obj.razryad_;
	array_ = obj.array_;
}

Bin::Bin(const Bin&& obj) noexcept
{
	array_ = obj.array_;
	razryad_ = obj.razryad_;
	obj.array_.~vector();
}

//Bin::Bin(Bin&& obj)
//{
//	array_ = obj.array_;
//	razryad_ = obj.razryad_;
//	obj.array_.clear();
//
//}

//конструктор в массив
Bin::Bin(int a)
{
	//сбрасывает все к нулям
	fill(0);
	//для отрицательных
	if (a < 0) array_[0] = 1;
	//запись в массив
	int i = razryad_ - 1;
	for (; a != 0; i--)
	{
		array_[i] = abs(a % 2);
		a /= 2;
	}
	//в доп. код, если a < 0
	if (array_[0] == 1)
	{
		invers();
		plus1();
	}
}


//конструктор-строка
Bin::Bin(const string& b)
{
	//перевод в инт
	BigInteger num = stringToBigInteger(b);

	//сбрасывает все к нулям
	fill(0);

	//для отрицательных
	if (num < 0)
	{
		array_[0] = 1;
		num.negate(num);
	}

	//запись в массив
	razryad_ += ((int)num.getLength() - 1 > 0 ? (int)num.getLength() - 1 : 0)* razryad_;
	array_.resize(razryad_, 0);
	int i = razryad_ - 1;
	while (num > 0)
	{
		array_[i] = (num % 2).toInt();
		num /= 2;
		i--;
	}

	if (array_[0] == 1)
	{
		invers();
		plus1();
	}
}

Bin::Bin(const char* arr, int n)
{
	arr[0] == 1 ? fill(1) : fill(0);
	if (n > razryad_) re_size(n - razryad_);

	for (int i = razryad_ - 1; n <= 0; i--, n--)
	{
		array_[i] = arr[n];
		if (!(array_[i] == 0 || array_[i] == 1))
		{
			fill(0);
			break;
		}
	}
}



Bin::~Bin()
{
	array_.clear();
}

void Bin::write_bit()
{
	for (int j = 0; j < razryad_; j++)
		cout << int(array_[j]);
	cout << endl;
}

void Bin::write_dec()
{
	cout << get_string() << endl;
}

char& Bin::get_ref_elem(const int raz)
{
	static char *c = nullptr;
	return raz < razryad_ && raz >= 0 ? array_[raz] : *c;
}



double Bin::get_double_value() const
{
	Bin tmp(*this);
	if (array_[0] == 1) tmp.invers();

	double dec = 0;
	double pwr = 1;
	for (int i = 0; i < razryad_ - 1; i++)
	{
		dec += tmp.array_[tmp.razryad_ - 1 - i] * pwr;
		pwr *= 2;
	}
	if (array_[0] == 1)
	{
		dec = -1 * dec--;
	}
	return dec;
}


string Bin::get_string() const
{
	if (razryad_ > 64) return bigIntegerToString(Bin::get_big_int_value());
	else
	{
		string num = to_string(Bin::get_double_value());
		auto pos = num.find(',');
		if (pos != string::npos) num.erase(pos);
		return num;
	}

}	

void Bin::add(const Bin& b)
{
	Bin tmp(b);
	int shift = 0;
	int razryad_tmp = abs(razryad_ - tmp.razryad_);
	

	if (razryad_ < tmp.razryad_)
			re_size(razryad_tmp);
	else
			tmp.re_size(razryad_tmp);


	for (int i = 0; i < razryad_; i++)
	{
		array_[razryad_ - 1 - i] += shift;
		if (i < razryad_)
			array_[razryad_ - 1 - i] += tmp.array_[tmp.razryad_ - 1 - i];
		shift = 0;
		if (1 < array_[razryad_ - 1 - i])
		{
			if (array_[razryad_ - 1 - i] == 3)
			{
				array_[razryad_ - 1 - i] = 1;
				shift = 1;
			}
			else
			{
				array_[razryad_ - 1 - i] = 0;
				shift = 1;
			}
		}
	}
}

void Bin::sub(const Bin& b)
{
	invers_all_num();
	add(b);
	invers_all_num();
}

bool Bin::compare(const Bin& b)
{
	if (razryad_ > b.razryad_)
	{
		for (int i = 0; i < razryad_-b.razryad_; i++)
		{
			if (array_[i] != array_[razryad_ - b.razryad_]) return false;
		}
		for (int i = razryad_-b.razryad_-1; i < b.razryad_; i++)
		{
			if (array_[i + razryad_ - b.razryad_] != b.array_[i]) return false;
		}
	}
	if (razryad_ < b.razryad_)
	{
		for (int i = 0; i < b.razryad_ - razryad_; i++)
		{
			if (b.array_[i] != b.array_[b.razryad_ - razryad_]) return false;
		}
		for (int i = b.razryad_ - razryad_-1; i < razryad_; i++)
		{
			if (b.array_[i  + b.razryad_ - razryad_] != array_[i]) return false;
		}
	}
	if (razryad_ == b.razryad_)
	{
		for (int i = 0; i < razryad_; i++)
		{
			if (b.array_[i] != array_[i]) return false;
		}
	}


	return true;
}

int Bin::cmp(const object& b) const
{
	if (b.type() != type()) throw;
	Bin tmp(*this);
	tmp.sub((const Bin &)b);
	Bin tmp2;
	if (tmp == tmp2) return 0;
	if (tmp.array_[0] == 0) return 1;
	else return -1;
}

string Bin::type_string() const
{
	return typeid(Bin).name();
}

int Bin::type() const
{
	return typeid(Bin).hash_code();
}

void Bin::add(const object& obj)
{
	Bin::add((const Bin&)obj);
}

object* Bin::get_copy()
{
	Bin* tmp = new Bin(*this);
	return tmp;
}

void Bin::set_value(string str)
{
	*this = Bin(str);
}

ostream& Bin::write_to_bin_stream(std::ostream& stream)
{
	stream.write((char*)&razryad_, sizeof(razryad_));
	for (int i = 0; i < array_.size(); i++)
	{
		stream.write((char*)&array_[i], sizeof(array_[i]));
	}
	return stream;
}

istream& Bin::read_from_bin_stream(std::istream& stream)
{
	stream.read((char*)&razryad_, sizeof(razryad_));
	array_.resize(razryad_);
	for (int i = 0; i < array_.size(); i++)
	{
		stream.read((char*)&array_[i], sizeof(array_[i]));
	}
	return stream;
}

BigInteger Bin::get_big_int_value() const
{
	Bin tmp(*this);
	if (array_[0] == 1) tmp.invers();
	BigInteger pwr = 1;
	BigInteger dec = 0;
	for (int j = 0; j < razryad_ - 1; j++)
	{
		if (tmp.array_[tmp.array_.size() - 1 - j] == 1) dec = dec + pwr;
		pwr *= 2;
	}
	if (array_[0] == 1)
	{
		dec = dec + 1;
		dec.negate(dec);
	}
	return dec;
}

Bin& Bin::operator++(int)
{
	plus1();
	return *this;
}

Bin& Bin::operator--(int)
{
	minus1();
	return *this;
}

Bin Bin::operator--()
{
	Bin tmp = Bin(*this);
	(*this)--;
	return tmp;
}

Bin Bin::operator++()
{
	Bin tmp = Bin(*this);
	(*this)++;
	return tmp;
}

Bin Bin::operator+=(int num)
{
	Bin tmp(num);
	add(tmp);
	return *this;
}

Bin Bin::operator+=(const Bin& bin)
{
	Bin tmp(bin);
	add(tmp);
	return *this;
}

Bin Bin::operator-=(int num)
{
	*this = *this + (-num);
	return *this;
}

Bin Bin::operator-=(const Bin& bin)
{
	*this = *this - bin;
	return *this;
}

Bin& Bin::operator=(const Bin&& bin)
{
	if (&bin == this)
		return *this;

	array_.clear();
	array_ = bin.array_;
	razryad_ = bin.razryad_;
	bin.array_.~vector();

	return *this;
}

Bin& Bin::operator=(const Bin& bin)
{
	if (bin == *this)
		return *this;
	array_ = bin.array_;
	razryad_ = bin.razryad_;
	return *this;

}

void* Bin::operator new(size_t size)
{
	return malloc(size);
}

void Bin::operator delete(void* ptr)
{
	free(ptr);
}

int& Bin::operator[](int k)
{
	return (int &)array_.at(k);
}

Bin::operator int()
{
	return (int)get_double_value();
}

Bin::operator double()
{
	return get_double_value();
}

Bin::operator float()
{
	return (float)get_double_value();
}

Bin::operator bool()
{
	return (bool)get_double_value();
}

Bin::operator double* ()
{
	double* tmp = new double;
	*tmp = get_double_value();
	return tmp;
}

void Bin::fill(const int a)
{
	razryad_ = sizeof(int) * 8;
	array_.resize(razryad_, char(a));
}

void Bin::plus1()
{
	for (int j = razryad_ - 1; j >= 0; j--)
	{
		if (array_[j] == 1) array_[j] = 0;
		else {
			array_[j] = 1;
			break;
		}
	}
}
void Bin::minus1()
{
	for (int j = razryad_ - 1; j >= 0; j--)
	{
		if (array_[j] == 0) array_[j] = 1;
		else {
			array_[j] = 0;
			break;
		}
	}
}

void Bin::invers()
{
	for (int j = 1; j < razryad_; j++)
	{
		if (array_[j] == 1) array_[j] = 0;
		else array_[j] = 1;
	}
}

void Bin::invers_all_num()
{
	invers();
	if (array_[0] == 0)
	{
		array_[0] = 1;
		plus1();
	}
	else
	{
		array_[0] = 0;
		plus1();
	}
}

int Bin::size()
{
	return razryad_;
}

void Bin::re_size(int n)
{
	for (int i = 0; i < n; i++)
	{
		razryad_++;
		array_.resize(razryad_, char(0));
		std::rotate(array_.rbegin(), array_.rbegin() + 1, array_.rend());
		if (array_[1] == 1)
		{
			array_[0] = 1;
		}
		else array_[0] = 0;
	}
}

Bin operator+(const Bin& a, const Bin& b)
{
	Bin tmp(a);
	tmp.add(b);
	return tmp;
}

Bin operator+(const Bin& a, const int num)
{
	Bin tmp(num);
	return a + tmp;
}

Bin operator-(const Bin& a, const Bin& b)
{
	Bin tmp(a);
	tmp.sub(b);
	return tmp;
}

Bin operator-(const Bin& a, const int num)
{
	return a + (-num);
}

Bin operator*(const Bin& a, const Bin& b)
{
	Bin bin;
	if (b.razryad_ <= 32) 
	{
		double tmp = b.get_double_value();
		bin = Bin(a);
		for (int i = 0; i < tmp - 1; i++)
		{
			bin = bin + a;
		}
	}
	else if (a.razryad_ <= 32)
	{
		double tmp = a.get_double_value();
		bin = Bin(b);
		for (int i = 0; i < tmp - 1; i++)
		{
			bin = bin + b;
		}
	}
	else
	{
		BigInteger tmp;
		tmp = a.get_big_int_value();
		bin = Bin(b);
		for (BigInteger i = 0; i < tmp - 1; i++)
		{
			bin = bin + a;
		}
	}
	return bin;
}

Bin operator*(const Bin& a, const int num)
{
	Bin tmp(num);
	return a * tmp;
}

bool operator==(const Bin& a, const Bin& b)
{
	Bin tmp(a);
	return tmp.compare(b);
}

bool operator!=(const Bin& a, const Bin& b)
{
	return !(a == b);
}

bool operator>(const Bin& a, const Bin& b)
{
	Bin tmp(a);
	return tmp.cmp(b) == 1;
}

bool operator<(const Bin& a, const Bin& b)
{
	return !(a > b) && a != b;
}

bool operator>=(const Bin& a, const Bin& b)
{
	return !(a < b);
}

bool operator<=(const Bin& a, const Bin& b)
{
	return !(a > b);
}

ostream& operator<<(ostream& out, const Bin& bin)
{
	out << bin.get_string();
	return out;
}

istream& operator>>(istream& in, Bin& bin)
{
	string str;
	in >> str;
	bin = Bin(str);
	return in;
}



//////////////////////////////////////NO BIGINT////////////////////////////////////
//Bin::Bin(const string& b)
//{
//	//перевод в инт
//	vector<int> lnum;
//	const int base = 1000 * 1000 * 1000;
//
//	for (int i = b.length(); i > 0; i -= 9)
//	{
//		if (i < 9)
//			lnum.push_back(atoi(b.substr(0, i).c_str()));
//		else
//			lnum.push_back(atoi(b.substr(i - 9, 9).c_str()));
//	}
//	while (lnum.size() > 1 && lnum.back() == 0)
//		lnum.pop_back();
//	//сбрасывает все к нулям
//	fill(0);
//	//для отрицательных
//	if (lnum.back() < 0)
//	{
//		array_[0] = 1;
//		lnum.back() = abs(lnum.back());
//	}
//	//запись в массив
//	razryad_ = array_.size() * lnum.size();
//	array_.resize(razryad_, 0);
//	int i = razryad_ - 1;
//	while (lnum.size() != 1 || lnum.front() != 0)
//	{
//		int carry = 0;
//		for (int i = (int)lnum.size() - 1; i >= 0; --i) {
//			long long cur = lnum[i] + carry * 1ll * base;
//			lnum[i] = int(cur / 2);
//			carry = int(cur % 2);
//		}
//		while (lnum.size() > 1 && lnum.back() == 0)
//			lnum.pop_back();
//		array_[i] = carry;
//		i--;
//	}
//	if (array_[0] == 1)
//	{
//		invers();
//		plus1();
//	}
//}