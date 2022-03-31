#include "polinom.h"

int main()
{
	setlocale(LC_ALL, "Russian");

	char number;
	string s1, s2;
	Polinom p1, p2;
	double con;
	cout << "Выберите функцию" << endl;
	cout << "1.Сложить 2 полинома" << endl;
	cout << "2.Вычесть 2 полинома" << endl;
	cout << "3.Умножить 2 полинома" << endl;
	cout << "4.Умножить полином на число" << endl;
	cout << "5.Выход" << endl;
	do
	{
		cout << "Выполнить:" << endl;
		cin >> number;
		switch (number)
		{
		case '1':
		{
			cout << "Введите первый полином: ";
			cin >> s1;
			p1 = s1;
			cout << "Введите второй полином:: ";
			cin >> s2;
			p2 = s2;
			cout << "Результат: " << p1 + p2 << endl << endl;
			break;
		}
		case '2':
		{
			cout << "Введите первый полином: ";
			cin >> s1;
			p1 = s1;
			cout << "Введите второй полином: ";
			cin >> s2;
			p2 = s2;
			cout << "Результат: " << p1 - p2 << endl << endl;
			break;
		}
		case '3':
		{
			cout << "Введите первый полином: ";
			cin >> s1;
			p1 = s1;
			cout << "Введите второй полином: ";
			cin >> s2;
			p2 = s2;
			cout << "Результат: " << p1 * p2 << endl << endl;
			break;
		}
		case '4':
		{
			cout << "Введите полином: ";
			cin >> s1;
			p1 = s1;
			cout << "Введите число: ";
			cin >> con;
			cout << "Результат: " << con * p1 << endl << endl;
			break;
		}

		}
	} while (number != '5');
	return 0;
}