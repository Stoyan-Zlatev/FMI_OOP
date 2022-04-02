#include <iostream>
#include <fstream>
#include <cstring>
#pragma warning(disable:4996)

const size_t maxActivitiesCount = 100;
const size_t BUFF = 1024;

bool isBetween(size_t number, size_t number1, size_t number2)
{
	return (number >= number1 && number <= number2) || (number >= number2 && number <= number1);
}

size_t convertCharToInt(const char element)
{
	return element - '0';
}

size_t convertStringToInt(const char* str)
{
	size_t strLength = strlen(str);
	size_t number = 0;
	for (size_t i = 0; i < strLength; i++)
	{
		number *= 10;
		number += convertCharToInt(str[i]);
	}
	return number;
}

bool isDigit(char element)
{
	return element >= '0' && element <= '9';
}

void getTimeFromString(const char* str, size_t& seconds, size_t& minutes, size_t& hours, char& sign)
{
	size_t currentIndex = 0;
	sign = str[currentIndex++];
	while (str[currentIndex] == ' ' && str[currentIndex] != '\0')
	{
		currentIndex++;
	}

	while (str[currentIndex] != ' ' && str[currentIndex] != '\0')
	{
		char element = str[currentIndex++];
		hours *= 10;
		hours += convertCharToInt(element);
	}
	currentIndex++;
	while (str[currentIndex] != ' ' && str[currentIndex] != '\0')
	{
		char element = str[currentIndex++];
		minutes *= 10;
		minutes += convertCharToInt(element);
	}
	currentIndex++;
	while (str[currentIndex] != ' ' && str[currentIndex] != '\0')
	{
		char element = str[currentIndex++];
		seconds *= 10;
		seconds += convertCharToInt(element);
	}
}

struct Time
{
	char sign;
	size_t hours;
	size_t minutes;
	size_t seconds;
};

class LogFile
{
	Time times[maxActivitiesCount];
	size_t activitiesCount;
	char filePath[BUFF];
	std::fstream sourceFile;
public:
	LogFile();
	LogFile(const char* filePath);
	void setFilePath(const char* filePath);
	void setTime(Time& time, size_t seconds, size_t minutes, size_t hours, char sign);
	void setActivitiesCount(size_t activitiesCount);
	void setSourceFile();
	void loadBuffer();
	const char* getFilePath() const;
	size_t logAfterHour(size_t hour) const;
	size_t logBetweenHours(size_t hour1, size_t hour2) const;
	size_t maxSecondsLogged() const;
	bool isLoggedInHour(size_t hour) const;
};

LogFile::LogFile() : LogFile("") {}

LogFile::LogFile(const char* filePath)
{
	setFilePath(filePath);
	setSourceFile();
}

void LogFile::setActivitiesCount(size_t activitiesCount)
{
	this->activitiesCount = activitiesCount;
}


void LogFile::loadBuffer()
{
	if (!sourceFile.is_open())
	{
		std::cout << "File is not opened" << std::endl;
		return;
	}
	char line[BUFF];
	sourceFile.getline(line, BUFF);
	setActivitiesCount(convertStringToInt(line));
	for (size_t i = 0; i < activitiesCount; i++)
	{
		sourceFile.getline(line, BUFF);
		char sign;
		size_t hours = 0;
		size_t minutes = 0;
		size_t seconds = 0;
		getTimeFromString(line, seconds, minutes, hours, sign);
		setTime(times[i], seconds, minutes, hours, sign);
	}
}


const char* LogFile::getFilePath() const
{
	return filePath;
}

void LogFile::setSourceFile()
{
	if (strcmp(filePath, "") == 0)
	{
		std::cout << "File path is empty";
		return;
	}
	sourceFile.open(filePath, std::ios::in);
	loadBuffer();
}

void LogFile::setFilePath(const char* filePath)
{
	strcpy(this->filePath, filePath);
}

void LogFile::setTime(Time& time, size_t seconds, size_t minutes, size_t hours, char sign)
{
	time.seconds = seconds;
	time.minutes = minutes;
	time.hours = hours;
	time.sign = sign;
}

size_t LogFile::logAfterHour(size_t hour) const
{
	size_t counter = 0;
	for (size_t i = 0; i < activitiesCount; i++)
	{
		if (times[i].hours > hour && times[i].sign == '+')
			counter++;
	}
	return counter;
}

size_t LogFile::logBetweenHours(size_t hour1, size_t hour2) const
{
	size_t counter = 0;
	for (size_t i = 0; i < activitiesCount; i++)
	{
		if (isBetween(times[i].hours,hour1,hour2) && times[i].sign == '+')
			counter++;
	}
	return counter;
}

size_t convertToSeconds(size_t hours, size_t minutes, size_t seconds)
{
	size_t total = 0;
	total += seconds;
	total += (minutes * 60);
	total += (hours * 60);
	return total;
}

size_t LogFile::maxSecondsLogged() const
{
	size_t logSeconds = 0;
	size_t outSeconds = 0;
	size_t maxTotalSeconds = 0;
	for (size_t i = 0; i < activitiesCount; i+=2)
	{
		if (times[i].sign == '-')
		{
			outSeconds = convertToSeconds(times[i].hours, times[i].minutes, times[i].seconds);
			logSeconds = convertToSeconds(times[i + 1].hours, times[i + 1].minutes, times[i + 1].seconds);
		}
		else
		{
			logSeconds = convertToSeconds(times[i].hours, times[i].minutes, times[i].seconds);
			outSeconds = convertToSeconds(times[i + 1].hours, times[i + 1].minutes, times[i + 1].seconds);
		}
		if ((logSeconds-outSeconds) > maxTotalSeconds)
			maxTotalSeconds = (logSeconds - outSeconds);
	}
	return maxTotalSeconds;
}

bool LogFile::isLoggedInHour(size_t hour) const
{
	for (size_t i = 0; i < activitiesCount; i++)
	{
		if (times[i].sign == '+' && times[i].hours == hour)
			return true;
	}
	return false;
}

int main()
{
	LogFile logFile("Time.txt");
	std::cout<<logFile.isLoggedInHour(16)<<std::endl;
	std::cout << logFile.logAfterHour(7)<<std::endl;
	std::cout << logFile.maxSecondsLogged()<<std::endl;
	std::cout << logFile.logBetweenHours(7, 23)<<std::endl;
}
