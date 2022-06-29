#include <iostream>
class Complex
{
private:
	double real;
	double im;

public:
	Complex();
	Complex(double real, double im);

	Complex getConjugated() const;  //����� ���������� ����������� ����� �� ������� �����.

	//assignment operators 
	// a+=b ��� � �� ������ ���������� �� b. � �� ������� , b �� ��. ����������  �� ����� a �� �� ���� �� �� ������ ������� ������ (a+=b+=c)
	Complex& operator+=(const Complex&);
	Complex& operator-=(const Complex&);
	Complex& operator*=(const Complex&);
	Complex& operator/=(const Complex&);



	//stream opeartors   ( std::cout << c1)  (std::cin >> c1 )
	friend std::ostream& operator<<(std::ostream&, const Complex&);
	friend std::istream& operator>>(std::istream&, Complex&);

};
// a+b. ���������� ����� ���� ����������(Complex), ����� � ���������� �� ����������.
Complex operator+(const Complex&, const Complex&);
Complex operator-(const Complex&, const Complex&);
Complex operator*(const Complex&, const Complex&);
Complex operator/(const Complex&, const Complex&);