#include <iostream>
#include <string>

using namespace std;

struct Sale
{
	string product;
	string town;
	double price;
	double quantity;
};

struct Profit
{
	string town;
	double totalIncome;
};

bool contains(const Profit* profits, int count, const string town)
{

}

int main()
{
	int n;
	cin >> n;

	Sale* sales = new Sale[n];
	Profit* profits = new Profit[n];

	for (unsigned i = 0; i < n; i++)
	{
		cin >> sales[i].town >> sales[i].product >> sales[i].price >> sales[i].quantity;
	}
}