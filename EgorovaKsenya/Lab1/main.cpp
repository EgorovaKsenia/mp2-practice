#include "polinom.h"
int main()
{
	char number;
	string s1, s2;
	Polinom p1, p2;
	double con;
	cout << "�������� �������" << endl;
	cout << "1.������� 2 ��������" << endl;
	cout << "2.������� 2 ��������" << endl;
	cout << "3.�������� 2 ��������" << endl;
	cout << "4.�������� ������� �� �����" << endl;
	cout << "5.�����" << endl;
	do
	{
		cout << "���������:" << endl;
		cin >> number;
		switch (number)
		{
		case '1':
		{
			cout << "������� ������ �������: ";
			cin >> s1;
			p1 = s1;
			cout << "������� ������ �������: ";
			cin >> s2;
			p2 = s2;
			cout << "���������: " << p1 + p2 << endl << endl;
			break;
		}
		case '2':
		{
			cout << "������� ������ �������: ";
			cin >> s1;
			p1 = s1;
			cout << "������� ������ �������: ";
			cin >> s2;
			p2 = s2;
			cout << "���������: " << p1 - p2 << endl << endl;
			break;
		}
		case '3':
		{
			cout << "������� ������ �������: ";
			cin >> s1;
			p1 = s1;
			cout << "������� ������ �������: ";
			cin >> s2;
			p2 = s2;
			cout << "���������: " << p1 * p2 << endl << endl;
			break;
		}
		case '4':
		{
			cout << "������� �������: ";
			cin >> s1;
			p1 = s1;
			cout << "������� �����: ";
			cin >> con;
			cout << "���������: " << con * p1 << endl << endl;
			break;
		}

		}
	} 	while (number != '5');
	return 0;
}