#include "Complex.h"

Complex::Complex()
{
	real = 0;
	im = 0;
}
Complex::Complex(double real, double im)
{
	this->real = real;
	this->im = im;
}
Complex& Complex::operator+=(const Complex& other)
{
	real += other.real;
	im += other.im;
	return *this;
}
Complex& Complex::operator-=(const Complex& other)
{
	real -= other.real;
	im -= other.im;
	return *this;
}
Complex& Complex::operator*=(const Complex& other)
{
	double oldReal = real;
	real = real * other.real - im * other.im;
	im = oldReal * other.im + im * other.real;
	return *this;
}
Complex& Complex::operator/=(const Complex& other) // a/=b
{
	Complex Conjugated = other.getConjugated(); //������� ���������� ����������� �� ������� ���� (b)

	Complex otherCopy(other);// �������� ������� (b), �� �� �� � ���������.

	//���������� ����� �� ���������� �����������.
	*this *= Conjugated;
	otherCopy *= Conjugated; //��� ������ �� ������ ���� ������ ����.

	if (otherCopy.real != 0)
	{
		real /= otherCopy.real;
		im /= otherCopy.real;
	}

	return *this;
}


//���� ������������ �� +=, -=, *= � /=, ����� ����� �� ���������� +, -, * � /, �������������� ���� ���������� ��������.
Complex operator+(const Complex& lhs, const Complex& rhs) { //a+b

	Complex result(lhs); // ��������� ��� �����, ����� � ����� �� a (���������� ����-������������)
	result += rhs; //��� ������� �� a, �������� b (���������� ���� ����������� �������� +=)

	return result;
}

//����������� -, *, / �� ���������� � +. 
Complex operator-(const Complex& lhs, const Complex& rhs) {
	Complex result(lhs);
	result -= rhs;

	return result;
}

Complex operator*(const Complex& lhs, const Complex& rhs) {

	Complex result(lhs);
	result *= rhs;

	return result;
}

Complex operator/(const Complex& lhs, const Complex& rhs) {

	Complex result(lhs);
	result /= rhs;

	return result;
}

Complex Complex::getConjugated() const
{
	Complex result(*this);
	result.im *= -1;

	return result;
}

// �� �� ����� �� ������  cout<<c1 ��� �� ��������� ��� ���� � ��. 
std::ostream& operator<<(std::ostream& ofs, const Complex& r) {

	return ofs << r.real << ' ' << r.im << 'i';
}

// �� �� ����� �� ������ cin>>c1 ��� �� ����� �� ���� � ��. 
std::istream& operator>>(std::istream& ifs, Complex& r) {

	return ifs >> r.real >> r.im;
}