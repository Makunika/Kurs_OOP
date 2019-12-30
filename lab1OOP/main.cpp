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

	Table<object> table(3,3);
	

	table.read_from_file("123.txt");
	table.print();
	table.sort();
	table.write_in_file("543.txt");
	table.read_from_file("543.txt");
	table.print();
	table.clear();
	getchar();
	return 0;
}



