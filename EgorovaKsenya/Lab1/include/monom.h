#pragma once

class monom
{
public:
	double coeff;//коэффициент монома			                                   
	unsigned int abc;//степень монома, x^a,y^b,z^c
	monom(double c = 0, unsigned int a = 0);
	monom& operator=(const monom& m);
	bool operator< (const monom& m) const;//перегрузка оператора меньше
	bool operator> (const monom& m) const;//перегрузка оператора больше
	//перегрузка операторов сравнения
	bool operator==(const monom& m) const;
	bool operator!=(const monom& m) const;
};