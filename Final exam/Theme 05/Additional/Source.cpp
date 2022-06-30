#include "Time.h"

int main()
{
	Time times[10] = { Time(11, 30, 0), Time(12, 44, 29), Time(), Time(17, 15, 23), 
					   Time(23, 60, 0), Time(3, 14, 15), Time(2, 71, 82),
					   Time(21, 22, 3), Time(17, 15, 23), Time(7, 31, 43) };
	timeBubbleSort(times, 10);
	for (int i = 0; i < 10; i++)
		times[i].print(false);
}