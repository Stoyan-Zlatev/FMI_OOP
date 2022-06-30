#pragma once

class Time
{
	size_t seconds;
	size_t mins;
	size_t hours;

	size_t convertToSeconds() const
	{
		return 3600 * hours + 60 * mins + seconds;
	}

public:
	Time();
	Time(size_t hours, size_t mins, size_t seconds);
	Time(size_t seconds);

	size_t getSeconds() const;
	size_t getMinutes() const;
	size_t getHours() const;

	void setSeconds(size_t seconds);
	void setMins(size_t mins);
	void setHours(size_t hours);

	void tick();

	int compare(const Time& other) const;
	Time getDiff(const Time& other) const;

	Time getToMidnight() const;
	bool isPartyTime() const;
	bool isDinnerTime() const;

	void print(bool is12hoursclock) const;
};

void timeBubbleSort(Time* arr, size_t arrLen);
