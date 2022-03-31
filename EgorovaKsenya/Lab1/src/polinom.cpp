#include "Polinom.h"
using namespace std;


list<monom> Polinom::similar_terms(list <monom> sp) //Создание списка с мономами по строке
{
	list<monom> res;
	sp.Reset();
	res.Reset();
	monom tmp;

	Node<monom>* p = sp.Getcurrent();
	sp.Step();

	if (sp.IsNotOver())
	{
		sp.Reset();

		while (sp.IsNotOver())
		{
			tmp.coeff = sp.Getcurrent()->data.coeff;
			tmp.abc = sp.Getcurrent()->data.abc;

			while ((sp.Getcurrent()->data.abc == sp.Getcurrent()->next->data.abc) && (sp.IsNotOver()))
			{
				tmp.coeff += sp.Getcurrent()->next->data.coeff;
				sp.Step();
			}

			if (tmp.coeff)
			{
				res.Insert(tmp);
				res.Step();
			}

			if (sp.Getcurrent())
				sp.Step();
		}
		res.Reset();
		if (res.Getcurrent()->data.abc == 0 && res.Getcurrent()->data.coeff == 0)
			res.InsertAfter(res.Getcurrent(), NULL);
	}
	else
		res = sp;

	return res;
}


Polinom::Polinom(string pol)  //Разбор строки
{
	list<monom> res;
	while (pol.length())
	{
		string part;
		monom temp;
		int pos = 1;
		while (pos < pol.length() && pol[pos] != '+' && pol[pos] != '-')
			pos++;
		part = pol.substr(0, pos);              // substr 
		pol.erase(0, pos);                      // erase
		pos = 0;
		while (part[pos] != 'x' && part[pos] != 'y' && part[pos] != 'z' && pos < part.length())
			pos++;

		string c = part.substr(0, pos);          // с - коэф part
		if (c == "+" || c.length() == 0)
			temp.coeff = 1;
		else
			if (c == "-")
				temp.coeff = -1;
			else
				temp.coeff = stod(c);            // stod извлекает число с плавающей точкой из строки

		part.erase(0, pos);                       // удаляем коэф
		part += ' ';
		int a[3] = { 100,10,1 };
		for (int i = 0; i < 3; i++)
		{
			pos = part.find((char)(120 + i));     // 120 - код символа x, 121 - y, 122 - z
			if (pos > -1)
			{
				if (part[pos + 1] != '^')
					part.insert(pos + 1, "^1");
				temp.abc += a[i] * stoi(part.substr(pos + 2, 1));   // stoi преобразует последовательность символов в целое число.
				part.erase(pos, 3);
			}
		}
		Plist.Insert(temp);

	}
	Plist = similar_terms(Plist);
}


//Конструктор копирования
Polinom::Polinom(const Polinom& pol)
{
	Plist = pol.Plist;
}

//Присваивание
Polinom& Polinom:: operator=(const Polinom& pol)
{
	Plist = pol.Plist;
	return *this;
}


//Сложение полиномов
Polinom Polinom::operator+(const Polinom& pol) const
{
	Polinom res;
	Polinom pthis = *this;
	Polinom p = pol;

	pthis.Plist.Reset();
	p.Plist.Reset();
	res.Plist.Reset();

	while (pthis.Plist.IsNotOver() && p.Plist.IsNotOver())
	{
		if (pthis.Plist.Getcurrent()->data > p.Plist.Getcurrent()->data)
		{
			res.Plist.InsertToTail(p.Plist.Getcurrent()->data);
			p.Plist.Step();
			res.Plist.Step();
		}
		else
			if (pthis.Plist.Getcurrent()->data < p.Plist.Getcurrent()->data)
			{
				res.Plist.InsertToTail(pthis.Plist.Getcurrent()->data);
				pthis.Plist.Step();
				res.Plist.Step();
			}
			else
			{
				double new_coeff = pthis.Plist.Getcurrent()->data.coeff + p.Plist.Getcurrent()->data.coeff;
				if (new_coeff)
				{
					monom temp(new_coeff, pthis.Plist.Getcurrent()->data.abc);
					res.Plist.InsertToTail(temp);
					res.Plist.Step();
				}
				pthis.Plist.Step();
				p.Plist.Step();
			}
	}
	while (pthis.Plist.IsNotOver())
	{
		res.Plist.InsertToTail(pthis.Plist.Getcurrent()->data);
		pthis.Plist.Step();
		res.Plist.Step();
	}
	while (p.Plist.IsNotOver())
	{
		res.Plist.InsertToTail(p.Plist.Getcurrent()->data);
		p.Plist.Step();
		res.Plist.Step();
	}
	return res;
}

//Умножение на константу слева
Polinom Polinom::operator*(const double a) const
{
	Polinom res;
	if (a)
	{
		res = *this;
		res.Plist.Reset();
		while (res.Plist.IsNotOver())
		{
			res.Plist.Getcurrent()->data.coeff *= a;
			res.Plist.Step();
		}
	}
	return res;
}

//Умножение полиномов
Polinom Polinom::operator*(const Polinom& pol) const
{
	Polinom res;
	Polinom pthis = *this;
	Polinom p = pol;

	pthis.Plist.Reset();
	p.Plist.Reset();

	while (pthis.Plist.IsNotOver())
	{
		double pthis_coeff = pthis.Plist.Getcurrent()->data.coeff;
		int pthis_abc = pthis.Plist.Getcurrent()->data.abc;
		Polinom temp(pol);
		temp.Plist.Reset();
		while (temp.Plist.IsNotOver())
		{
			int temp_abc = temp.Plist.Getcurrent()->data.abc;
			if ((temp_abc % 10 + pthis_abc % 10) < 10 && (temp_abc / 10 % 10 + pthis_abc / 10 % 10) < 10 && (temp_abc / 100 + pthis_abc / 100) < 10)
			{
				temp.Plist.Getcurrent()->data.abc += pthis_abc;
				temp.Plist.Getcurrent()->data.coeff *= pthis_coeff;
			}
			else
				throw "Too big degree";
			temp.Plist.Step();
		}
		res = res + temp;
		pthis.Plist.Step();
	}
	return res;
}

//Оператор вывода
ostream& operator<<(ostream& ostr, const Polinom& pol)
{
	Polinom p = pol;
	p.Plist.Reset();
	Polinom zero("");
	if (pol == zero)
		ostr << "0";
	while (p.Plist.IsNotOver())
	{
		monom temp = p.Plist.Getcurrent()->data;

		if (temp.coeff > 0)
		{
			ostr << "+";
			if (temp.coeff == 1 && temp.abc == 0)
				ostr << "1";
			else
				if (temp.coeff != 1)
					ostr << temp.coeff;
		}
		else
			ostr << temp.coeff;

		int a = temp.abc / 100;
		if (a > 1)
			ostr << "x^" << a;
		else
			if (a == 1)
				ostr << "x";
		a = temp.abc / 10 % 10;
		if (a > 1)
			ostr << "y^" << a;
		else
			if (a == 1)
				ostr << "y";
		a = temp.abc % 10;
		if (a > 1)
			ostr << "z^" << a;
		else
			if (a == 1)
				ostr << "z";
		p.Plist.Step();
	}

	return ostr;
}