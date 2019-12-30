#pragma once
#include "List.h"
#include "Data.h"
#include <iostream>
#include <fstream>
#include <regex>
#include <string>

template<class T>
class Table
{
public:
	Table();
	Table(int h, int w);
	Table(int h, int w, T* data);
	Table(string name_file);

	~Table();
public:
	void resize(int h, int w);
	T* get(int h, int w);
	void set(int h, int w, T* data);
	void null(int w);
	int get_h();
	int get_w();
	void print();
	void read_from_file(string name_file);
	void write_in_file(string name_file);
	void clear();
	void swap_column(int num1, int num2);
	void sort(int num);
	void sort();


private:

	List<List<T>>* lists;
	int w;
	int h;
};

template<class T>
inline Table<T>::Table()
{
	lists = new List<List<T>>();
	w = 0;
	h = 0;
}

template<class T>
inline Table<T>::Table(int h, int w)
{
	lists = new List<List<T>>(w);
	for (int i = 0; i < w; i++)
	{
		lists->set(i, new List<T>(h));
	}
	this->w = w;
	this->h = h;
}

template<class T>
inline Table<T>::Table(int h, int w, T* data) : Table<T>(h, w)
{
	for (int i = 0; i < w; i++)
		for (int j = 0; j < h; j++)
			lists->get(i)->set(j, data);
}

template<class T>
inline Table<T>::Table(string name_file)
{
	read_from_file(name_file);
}

template<class T>
inline Table<T>::~Table()
{
	for (int i = 0; i < w; i++)
	{
		lists->get(i)->~List();
	}
	delete lists;
}

template<class T>
inline void Table<T>::resize(int h, int w)
{
	if (h < 0 || w < 0) throw;

	if (w == 0 && h == 0)
	{
		clear();
	}
	else
	{
		lists->resize(w);
		if (this->w - w < 0)
		{
			for (int i = this->w; i < w; i++)
			{
				lists->set(i, new List<T>(h));
			}
		}
		this->w = w;
		int h1 = this->h - h;
		if (h1 != 0)
		{
			for (int i = 0; i < w; i++)
			{
				lists->get(i)->resize(h);
			}
		}
		this->h = h;
	}
}

template<class T>
inline T* Table<T>::get(int h, int w)
{
	if (h < 0 || w < 0 || w >= this->w || h >= this->h) throw;
	return lists->get(w)->get(h);
}

template<class T>
inline void Table<T>::set(int h, int w, T* data)
{
	if (h < 0 || w < 0 || w >= this->w || h >= this->h) throw;
	lists->get(w)->set(h, data);
}

inline void Table<object>::set(int h, int w, object* data)
{
	if (h < 0 || w < 0||w  >= this->w || h >= this->h) throw;
	
	
	if (lists->get(w)->get_start() != nullptr)
	{
		if (data->type() == lists->get(w)->get_start()->type())
			lists->get(w)->set(h, data);
	}
	else if (h == 0)
		lists->get(w)->set(h, data);
	else delete data;
}


template<class T>
inline void Table<T>::null(int w)
{
	if (w < 0 || w >= this->w) throw;
	for (int i = 0; i < h; i++)
	{
		lists->get(w)->set(i, nullptr);
	}
}

template<class T>
inline int Table<T>::get_h()
{
	return h;
}

template<class T>
inline int Table<T>::get_w()
{
	return w;
}

template<class T>
inline void Table<T>::print()
{

}

template<class T>
inline void Table<T>::read_from_file(string name_file)
{

}

template<class T>
inline void Table<T>::write_in_file(string name_file)
{
}

inline void Table<object>::write_in_file(string name_file)
{
	ofstream out(name_file);

	if (out.is_open())
	{
		for (int i = 0; i < w; i++)
		{
			string classname = "class NULL";
			if (lists->get(i)->get_start() != nullptr)
				classname = lists->get(i)->get_start()->type_string();
			out << classname + ": ";
			for (int j = 0; j < h; j++)
			{
				if (lists->get(i)->get(j) != nullptr)
				{
					out << "|" + lists->get(i)->get(j)->get_string() + "| ";
				}
			}
			out << "# \n";
		}
	}
}

template<class T>
inline void Table<T>::clear()
{
	delete lists;
	lists = new List<List<T>>;
	h = 0;
	w = 0;
}

template<class T>
inline void Table<T>::swap_column(int num1, int num2)
{
	if (num1 < 0 || num2 < 0 || num1 >= w || num2 >= w) throw;
	lists->swap(lists->get_node(num1), lists->get_node(num2));
}

template<class T>
inline void Table<T>::sort(int num)
{
	if (num < 0 || num >= w) throw;
	lists->get(num)->sort();
}

template<class T>
inline void Table<T>::sort()
{
	for (int i = 0; i < w; i++)
	{
		sort(i);
	}
}

inline void Table<object>::read_from_file(string name_file)
{

	ifstream in(name_file);


	if (in.is_open())
	{
		clear();
		string all_file_str;
		string line;
		while (getline(in, line))
			all_file_str += line + " ";

		regex regularColumn(
			"([\\s]*)"
			"([\\w\\s]+)"
			"(:\\s)"
			"([.]*[^#]+)"
			"(#)"
		);
		regex regularCell(
			"(|)"
			"([.]*[^|]+)"
			"(|\\s)"
		);
		cmatch resultColumn;
		cmatch resultCell;

		while (regex_search(all_file_str.c_str(), resultColumn, regularColumn))
		{
			string classname = resultColumn[2].str();
			string str_cells = resultColumn[4].str();
			int w_tmp = w + 1;
			resize(h, w_tmp);
			int h_tmp = 0;


			while (regex_search(str_cells.c_str(), resultCell, regularCell))
			{
				if (resultCell[2].str() != " ")
				{
					h_tmp++;
					if (h_tmp > h)
					{
						resize(h_tmp, w);
					}
					object* new_obj;
					if (classname == typeid(Int).name())
						new_obj = new Int(resultCell[2].str());
					else if (classname == typeid(Double).name())
						new_obj = new Double(resultCell[2].str());
					else if (classname == typeid(Bin).name())
						new_obj = new Bin(resultCell[2].str());
					else if (classname == typeid(String).name())
						new_obj = new String(resultCell[2].str());
					else new_obj = nullptr;
					lists->get_end()->set(h_tmp - 1, new_obj);
				}
				str_cells = resultCell.suffix();
			}
			all_file_str = resultColumn.suffix();
		}
	}
}

inline void Table<object>::print()
{

	List < vector < string >> strings_;
	string class_null = "class NULL";

	vector<size_t> max_lens;
	for (int j = 0; j < w; j++) 
	{
		vector<string>* column = new vector<string>;

		for (int i = 0; i < h; i++) 
		{
			string add;
			if (lists->get(j)->get(i) != nullptr)
				add += lists->get(j)->get(i)->get_string();
			else
				add += "NULL";
			add += " | ";
			column->push_back(add);
		}

		size_t max_len = 0;
		for (int i = 0; i < h; i++) 
		{
			auto len_str = (*column)[i].length();
			if (len_str > max_len) 
			{
				max_len = len_str;
			}
		}
		// Учитываем название столбика при подсчёте длины
		
		auto len_of_name = class_null.length() + 2;
		if (lists->get(j)->get_start() != nullptr)
			len_of_name = (lists->get(j)->get_start()->type_string()).length() + 2;

		if (len_of_name > max_len) {
			max_len = len_of_name;
		}
		max_lens.push_back(max_len);
		// Теперь знаем максимальную длину строки в столбце
		for (int row = 0; row < h; row++) 
		{
			auto len_of_current_str = (*column)[row].length();
			if (len_of_current_str < max_len) {
				for (int i = 0; i < max_len - len_of_current_str; i++)
					(*column)[row] = " " + (*column)[row];
			}
		}
		strings_.push_end(column);
	}
	// Вывод названий столбиков
	for (int col = 0; col < w; col++) 
	{

		auto name_len = class_null.length() + 2;
		if (lists->get(col)->get_start() != nullptr)
			name_len = (lists->get(col)->get_start()->type_string()).length() + 2;
		if (name_len < max_lens[col]) {
			for (int i = 0; i < max_lens[col] - name_len; i++)
				std::cout << " ";
		}
		if (lists->get(col)->get_start() != nullptr)
			cout << lists->get(col)->get_start()->type_string() << "| ";
		else
			cout << class_null << "| ";
	}
	cout << "\n";
	for (int col = 0; col < w; col++) 
	{
		for (int i = 0; i < max_lens[col]; i++)
			cout << "-";
	}
	cout << "\n";
	// Вывод столбцов
	for (int row = 0; row < h; row++) 
	{
		for (int col = 0; col < w; col++) 
		{
			cout << (*strings_.get(col))[row];
		}
		cout << "\n";
		for (int col = 0; col < w; col++) 
		{
			for (int i = 0; i < max_lens[col]; i++)
				cout << "-";
		}
		cout << "\n";
	}
}
