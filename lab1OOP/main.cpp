#include "Tree.h"
#include "Table.h"
#include "Data.h"
#include <regex>
#include <iostream>
using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");




	//Bin bin1, bin2, bin3, bin4, bin5;
	//cout << "Введите число bin1: ";
	//cin >> bin1;
	//cout << "Введите число bin2: ";
	//cin >> bin2;
	//cout << "Введите число bin3: ";
	//cin >> bin3;
	//bin1 = bin2;
	//cout << "bin4 = bin1 + bin2: " << (bin4 = bin1 + bin2) << endl;
	//cout << "bin4++: " << (bin4++) << endl;
	//cout << "bin4 -= bin1: " << (bin4 -= bin1) << endl;
	//cout << "bin4 > bin1?: " << (bin4 > bin1) << endl;
	//cout << "bin5 = bin3 * bin1: " << (bin5 = bin3 * bin1) << endl;

	Table<object> table;
	
	//int b = 20;
	table.interface();
	//for (int i = 0; i < table.get_w() - 1; i++)
	//{
	//	for (int j = 0; j < table.get_h(); j++)
	//	{
	//		b--;
	//		table.set(j, i, new Int(b));
	//	}
	//}

	//for (int i = 0; i < table.get_h(); i++)
	//{
	//	table.set(i, table.get_w() - 1, new String("Hello, it is " + to_string(table.get_h() - i) + " wow"));
	//}

	//table.print();
	//table.sort(0);
	////table.set(2, 0, new String("5"));
	//table.print();

	//table.null(2);
	//table.set(0, 2, new Int(5));
	//table.set(2, 2, new Int(1));
	//table.print();
	//table.сsort();
	//table.print();

	table.read_from_file("123.txt");
	table.print();
	table.sort(0);
	table.print();



	table.write_in_file("543.txt");
	table.read_from_file("543.txt");
	table.print();
	table.clear();
	getchar();
	return 0;
}





