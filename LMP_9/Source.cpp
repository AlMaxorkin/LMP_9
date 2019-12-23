#include <iostream>
#include <ios>
#include <fstream>
#include <string>
#include <windows.h>

using namespace std;

struct child
{
	int d;
	int m;
	int y;
	child(string str)
	{
		int i = 0;
		while (str[i] != ' ')
		{
			i++;
		}
		str = str.substr(i + 1);
		int dot1, dot2;
		dot1 = str.find('.');
		dot2 = str.substr(dot1+1).find('.') + str.substr(0,dot1+1).length();
	
		d = atoi(str.substr(0, dot1).c_str());
		m = atoi(str.substr(dot1 + 1, dot2 - dot1 - 1).c_str());
		y = atoi(str.substr(dot2 + 1).c_str());
	}
};

bool compare(string str1, string str2)
{
	child person1(str1);
	child person2(str2);

	int date1 = person1.y * 10000 + person1.m * 100 + person1.d;
	int date2 = person2.y * 10000 + person2.m * 100 + person2.d;

	return date1 < date2;
}

void Merge_Sort(string path)
{
	string str1, str2;
	int k = 1, i = 0, j = 0, counter = 0;
	ifstream f(path);
	if (f.is_open())
		cout << "Файл открыт! \n\n";
	else
	{
		cout << "Ошибка открытия файла!\n";
		return;
	}

	while (!f.eof())
	{
		getline(f, str1);
		counter++;
	}
	f.close();

	while (k < counter)
	{
		ifstream main_in(path);
		ofstream split_out_1("D:\\smsort_1.txt"); 
		ofstream split_out_2("D:\\smsort_2.txt");

		if (!main_in.eof())
			getline(main_in, str1);
		while (!main_in.eof())
		{
			for (i = 0; i < k && !main_in.eof(); i++)
			{
				split_out_1 << str1;
				split_out_1 << "\n";
				getline(main_in, str1);
			}
			for (j = 0; j < k && !main_in.eof(); j++)
			{
				split_out_2 << str1;
				split_out_2 << "\n";
				getline(main_in, str1);
			}
		}

		split_out_1.close();
		split_out_2.close();
		main_in.close();

		ofstream main_out(path);
		ifstream split_in_1("D:\\smsort_1.txt");
		ifstream split_in_2("D:\\smsort_2.txt");

		if (!split_in_1.eof()) 
			getline(split_in_1,str1);
		if (!split_in_2.eof()) 
			getline(split_in_2,str2);
	
		while (!split_in_1.eof() && !split_in_2.eof())
		{
			i = 0;
			j = 0;
			while (i < k && j < k && !split_in_1.eof() && !split_in_2.eof())
			{
				if (compare(str1, str2))
				{
					main_out << str1;
					main_out << "\n";
					getline(split_in_1, str1);
					i++;
				}
				else
				{
					main_out << str2;
					main_out << "\n";
					getline(split_in_2, str2);
					j++;
				}
			}

			while (i < k && !split_in_1.eof())
			{
				main_out << str1;
				main_out << "\n";
				getline(split_in_1, str1);
				i++;
			}
			while (j < k && !split_in_2.eof())
			{
				main_out << str2;
				main_out << "\n";
				getline(split_in_2, str2);
				j++;
			}
		}
		while (!split_in_1.eof())
		{
			main_out << str1;
			main_out << "\n";
			getline(split_in_1, str1);
		}
		while (!split_in_2.eof())
		{
			main_out << str2;
			main_out << "\n";
			getline(split_in_2, str2);
		}
		split_in_2.close(); 
		split_in_1.close();
		main_out.close();
		k *= 2;
	}
}

int main()
{
	setlocale(LC_ALL, "rus");
	string path = "D:\\FILE_FOR_SORT.txt";	

	Merge_Sort(path);
	return 0;
}