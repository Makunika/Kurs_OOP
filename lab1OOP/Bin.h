#pragma once
#include "object.h"
#include <iostream>
#include <locale>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include "bigint/BigIntegerLibrary.hh"
using namespace std;

class Bin : public object
{
public:
		//������������
		Bin(int a);
		Bin(const Bin& obj); //����������� �����������
		Bin(const Bin&& obj) noexcept;
		Bin(const string& b);
		Bin(const char* arr, int n); //n - ������ �������, ��� ������ ������� ������ ���� 1 ��� 0, ����� ���� ������ ����� �������� ������
		Bin(); // ��� ����� 0
		//����������
		~Bin();

public:
		//������ �������� ������
		string      get_string() const;
		int			cmp(const object& b) const;
		string		type_string() const;
		int			type() const;
		void		add(const object& obj);
		object*		get_copy();
		void		set_value(string str);
		ostream& write_to_bin_stream(std::ostream& stream);
		istream& read_from_bin_stream(std::istream& stream);
public:
		//������
		void        write_bit();
		void        write_dec();
		double      get_double_value() const;
		char&       get_ref_elem(int raz);
		BigInteger  get_big_int_value() const;
		void        add(const Bin& b); // ��������� � ����� ���� b
		void        sub(const Bin& b); //���������� � ����� -b
		bool        compare(const Bin& b);
		void        invers_all_num(); //������ �������
		int         size();

		friend Bin  operator+(const Bin& a, const Bin& b);
		friend Bin  operator+(const Bin& a, const int num);
		friend Bin  operator-(const Bin& a, const Bin& b);
		friend Bin  operator-(const Bin& a, const int num);
		friend Bin  operator*(const Bin& a, const Bin& b);
		friend Bin  operator*(const Bin& a, const int num);
		friend bool operator==(const Bin& a, const Bin& b);
		friend bool operator!=(const Bin& a, const Bin& b);
		friend bool operator>(const Bin& a, const Bin& b);
		friend bool operator<(const Bin& a, const Bin& b);
		friend bool operator>=(const Bin& a, const Bin& b);
		friend bool operator<=(const Bin& a, const Bin& b);
		Bin& operator++(int);
		Bin& operator--(int);
		Bin  operator--(   );
		Bin  operator++(   );
		Bin operator+=(int);
		Bin operator+=(const Bin& bin);
		Bin operator-=(int);
		Bin operator-=(const Bin& bin);
		Bin& operator=(const Bin&& bin);
		Bin& operator=(const Bin& bin);

		friend ostream& operator<<(ostream& out, const Bin& bin);
		friend istream& operator>>(istream& in, Bin& bin);

		void* operator new(size_t size);
		void operator delete(void* ptr);


		int& operator[](int k);
		operator int();
		operator double();
		operator float();
		operator bool();
		operator double* ();



private:
		void fill(int a);
		void plus1();
		void minus1();
		void invers();
		void re_size(int n);

		

private:
		int razryad_;
		vector<char> array_;
};

