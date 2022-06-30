#include <iostream>
#include <fstream>
#include "HexViewer.h"
using namespace std;

int main()
{
	std::ofstream file("MyNumber2.dat", std::ios::binary);
	int a = 12345;
	file.write((const char*)&a, sizeof(a));
	file.close();
	HexViewer h("MyNumber2.dat");

	h.print();
	h.addByte("FF");
	h.print();

	h.removeLastByte();
	h.print();

	h.change(3, "63");
	h.print();
}
