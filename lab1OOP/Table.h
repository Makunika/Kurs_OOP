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
	void set_name_column(int w, string name);
	void null(int w);
	int get_h();
	int get_w();
	void print();
	void read_from_file(string name_file);
	void write_in_file(string name_file);
	void clear();
	void swap_column(int num1, int num2);
	void csort(int num);
	void csort();
	void sort(int num);
	void interface();


private:
	List<string>* name_column;
	List<List<T>>* lists;
	int w;
	int h;

private:
	//draw
	void draw_menu(int pos, vector<string>* menu);
};

template<class T>
inline Table<T>::Table()
{
	lists = new List<List<T>>();
	name_column = new List<string>();
	w = 0;
	h = 0;
}

template<class T>
inline Table<T>::Table(int h, int w)
{
	name_column = new List<string>(w);
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
	delete name_column;
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
		name_column->resize(w);
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

template<class T>
inline void Table<T>::set_name_column(int w, string name)
{
	if ( w < 0 || w >= this->w ) throw;
	name_column->set(w, new string(name));
}

inline void Table<object>::set(int h, int w, object* data)
{
	if (h < 0 || w < 0||w  >= this->w || h >= this->h) throw;
	
	if (data->type_string() == lists->get(w)->type_string_in_list())
		lists->get(w)->set(h, data);
	else if (lists->get(w)->type_string_in_list() == "class NULL")
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
			string name_col = "";
			if (name_column->get(i) != nullptr)
				name_col = *name_column->get(i);
			string classname = lists->get(i)->type_string_in_list();
			out << "(" + name_col + ")" + classname + ": ";
			for (int j = 0; j < h; j++)
			{
				if (lists->get(i)->get(j) != nullptr)
				{
					out << "|" + lists->get(i)->get(j)->get_string() + "| ";
				}
				else
				{
					out << "|NULL| ";
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
	delete name_column;
	name_column = new List<string>;
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
inline void Table<T>::csort(int num)
{
	if (num < 0 || num >= w) throw;
	lists->get(num)->sort();
}

template<class T>
inline void Table<T>::csort()
{
	for (int i = 0; i < w; i++)
	{
		csort(i);
	}
}

template<class T>
inline void Table<T>::sort(int num)
{
	if (num < 0 || num >= w) throw;
	bool swapped;
	for (int i = 0; i < h - 1; i++)
	{
		swapped = false;
		for (int j = 0; j < h - i - 1; j++)
		{
			if (get(j, num) == nullptr)
			{
				for (int k = 0; k < w; k++)
					List<T>::swap(lists->get(k)->get_node(j), lists->get(k)->get_node(j + 1));
				swapped = true;
			}
			else if (*(get(j, num)) > *(get(j+1, num)))
			{
				for (int k = 0; k < w; k++)
					List<T>::swap(lists->get(k)->get_node(j), lists->get(k)->get_node(j + 1));
				swapped = true;
			}
		}
		if (swapped == false)
			break;
	}

}

template<class T>
inline void Table<T>::draw_menu(int pos, vector<string>* menu)
{
	system("cls");

	for (int i = 0; i < menu->size(); i++)
	{
		if (pos == i)
			cout << " -->";
		cout << "  " + (*menu)[i] << endl;
	}
}

inline void Table<object>::sort(int num)
{
	if (num < 0 || num >= w) throw;
	bool swapped;
	for (int i = 0; i < h - 1; i++)
	{
		swapped = false;
		for (int j = 0; j < h - i - 1; j++)
		{
			if (get(j, num) == nullptr)
			{
				for (int k = 0; k < w; k++)
					List<object>::swap(lists->get(k)->get_node(j), lists->get(k)->get_node(j + 1));
				swapped = true;
			}
			else if (get(j, num)->cmp(*(get(j + 1, num))) == 1)
			{
				for (int k = 0; k < w; k++)
					List<object>::swap(lists->get(k)->get_node(j), lists->get(k)->get_node(j + 1));
				swapped = true;
			}
		}
		if (swapped == false)
			break;
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
			"([\(]+)"
			"([\\w\\s]*)"
			"([\)]+)"
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
			string classname = resultColumn[6].str();
			string str_cells = resultColumn[8].str();
			int w_tmp = w + 1;
			resize(h, w_tmp);
			int h_tmp = 0;
			name_column->set(w - 1, new string(resultColumn[3].str()));

			while (regex_search(str_cells.c_str(), resultCell, regularCell))
			{
				if (resultCell[2].str() != " ")
				{

					h_tmp++;
					if (h_tmp > h)
						resize(h_tmp, w);

					if (resultCell[2].str() == "NULL")
					{
						object* new_obj = nullptr;
						lists->get_end()->set(h_tmp - 1, new_obj);
					}
					else
					{
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
	string name_null = "()";

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
			size_t len_str = (*column)[i].length();
			if (len_str > max_len)
			{
				max_len = len_str;
			}
		}
		// Учитываем название столбика при подсчёте длины

		if (name_column->get(j) != nullptr)
			name_null = "(" + *name_column->get(j) + ")";
		else name_null = "()";
		size_t len_of_name = name_null.length() + lists->get(j)->type_string_in_list().length() + 2;


		if (len_of_name > max_len) {
			max_len = len_of_name;
		}
		max_lens.push_back((int)max_len);
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
		string name_col = "()";
		if (name_column->get(col) != nullptr)
			name_col = "(" + *name_column->get(col) + ")";

		size_t name_len = lists->get(col)->type_string_in_list().length() + 2;
		name_len += name_col.length();



		if (name_len < max_lens[col]) {
			for (int i = 0; i < max_lens[col] - name_len; i++)
				std::cout << " ";
		}
		cout << name_col + lists->get(col)->type_string_in_list() << "| ";
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



//for interface
#define BUTTON_ENTER 13
#define BUTTON_UP 72
#define BUTTON_DOWN 80
#include <conio.h>

template<class T>
inline void Table<T>::interface()
{
}

inline void Table<object>::interface()
{
	system("color 0C");
	vector<string> menu = {
		"Set size",
		"Set cell",
		"Get cell",
		"Null column",
		"Print",
		"Read file",
		"Write file",
		"Set name column",
		"Swap column",
		"Sort by column",
		"Sort column",
		"Sort all",
		"Exit"
	};

	int pos = 0;
	draw_menu(pos, &menu);
	while (true)
	{
		switch (_getch())
		{
		case BUTTON_ENTER:
		{// enter
			if (pos == 0)
			{
				int h, w;
				system("cls");
				do
				{
					cout << "New size:" << endl << "h = ";
					cin >> h;
				} while (h < 0);
				do
				{
					cout << "w = ";
					cin >> w;
				} while (w < 0);
				resize(h, w);
				getchar();
				getchar();
			}
			else if (pos == 1) //set
			{
				print();
				int h, w;
				system("cls");
				do
				{
					cout << "h = ";
					cin >> h;
				} while (h < 0 || h >= this->h);
				do
				{
					cout << "w = ";
					cin >> w;
				} while (w < 0 || w >= this->w);
				if (lists->get(w)->type_string_in_list() != "class NULL")
					cout << "Enter " + lists->get(w)->type_string_in_list() + ": ";
				else
				{
					object* new_obj;
					while (true)
					{
						string name_class;
						string buff;
						cout << "Enter name new class: ";
						cin >> buff;
						name_class = "class " + buff;
						if (name_class == typeid(Int).name())
						{
							new_obj = new Int();
							break;
						}
						else if (name_class == typeid(Double).name())
						{
							new_obj = new Double();
							break;
						}
						else if (name_class == typeid(Bin).name())
						{
							new_obj = new Bin();
							break;
						}
						else if (name_class == typeid(String).name())
						{
							new_obj = new String();
							break;
						}
					}
					set(h, w, new_obj);
					cout << "Enter " + lists->get(w)->type_string_in_list() + ": ";
				}
				string data;
				cin >> data;
				if (get(h,w) != nullptr)
					get(h, w)->set_value(data);
				else
				{
					object* new_obj = nullptr;
					if (lists->get(w)->type_string_in_list() == typeid(Int).name())
						new_obj = new Int(data);
					else if (lists->get(w)->type_string_in_list() == typeid(Double).name())
						new_obj = new Double(data);
					else if (lists->get(w)->type_string_in_list() == typeid(Bin).name())
						new_obj = new Bin(data);
					else if (lists->get(w)->type_string_in_list() == typeid(String).name())
						new_obj = new String(data);
					set(h, w, new_obj);
				}
				print();
				getchar();
				getchar();
			}
			else if (pos == 2) //get
			{
				int h, w;
				system("cls");
				do
				{
					cout << "h = ";
					cin >> h;
				} while (h < 0 || h >= this->h);
				do
				{
					cout << "w = ";
					cin >> w;
				} while (w < 0 || w >= this->w);
				cout << get(h, w)->get_string() << endl;
				getchar();
				getchar();
			}
			else if (pos == 3) //null
			{
				print();
				int w;
				system("cls");
				do
				{
					cout << "Null column = ";
					cin >> w;
				} while (w < 0 || w >= this->w);
				null(w);
			}
			else if (pos == 4) //print
			{
				system("cls");
				print();
				getchar();
				getchar();
			}
			else if (pos == 5) //read file
			{
				system("cls");
				string file;
				cout << "Enter name file (*.txt): ";
				cin >> file;
				read_from_file(file);
				print();
				getchar();
				getchar();
			}
			else if (pos == 6) //write file
			{
				system("cls");
				string file;
				cout << "Enter name file (*.txt): ";
				cin >> file;
				write_in_file(file);
				getchar();
				getchar();
			}
			else if (pos == 7) //set name column
			{
				system("cls");
				int w;
				do
				{
					cout << "Enter column = ";
					cin >> w;
				} while (w < 0 || w >= this->w);
				string name;
				cout << "Enter new name column: ";
				cin >> name;
				set_name_column(w, name);
				print();
				getchar();
				getchar();
			}
			else if (pos == 8) //swap column
			{
				system("cls");
				print();
				int w1, w2;
				do
				{
					cout << "Enter 1 column = ";
					cin >> w1;
				} while (w1 < 0 || w1 >= this->w);
				do
				{
					cout << "Enter 2 column = ";
					cin >> w2;
				} while (w2 < 0 || w2 >= this->w);
				swap_column(w1, w2);
				print();
				getchar();
				getchar();
			}
			else if (pos == 9) //Sort by column
			{
				system("cls");
				print();
				int w;
				do
				{
					cout << endl << "Enter column = ";
					cin >> w;
				} while (w < 0 || w >= this->w);

				clock_t cl = clock();
				sort(w);
				clock_t delta = clock() - cl;




				print();
				cout << endl << "Time: " << delta << endl;
				getchar();
				getchar();
			}
			else if (pos == 10) //Sort column
			{
				system("cls");
				print();
				int w;
				do
				{
					cout << endl << "Enter column = ";
					cin >> w;
				} while (w < 0 || w >= this->w);
				csort(w);
				print();
				getchar();
				getchar();
			}
			else if (pos == 11) //Sort all
			{
				system("cls");
				print();
				csort();
				print();
				getchar();
				getchar();
			}
			else if (pos == 12)
			{
				system("color 0F");
				return;
			}
			draw_menu(pos, &menu);
			break;
		}
		case BUTTON_UP:
		{// up
			if (pos > 0)
				draw_menu(--pos, &menu);
			break;
		}
		case BUTTON_DOWN:
		{// down
			if (pos < menu.size())
				draw_menu(++pos, &menu);
			break;
		}
		}

	}
}



