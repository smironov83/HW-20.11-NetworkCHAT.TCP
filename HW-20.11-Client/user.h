#pragma once
#include <string>
#include <vector>
#include <time.h>
#include <iostream>

#define DEFAULT_BUFLEN 1024

struct User
{
	std::string name_;
	std::vector<std::string> history_;

	User() = default;
	~User() = default;

	//Конструирует сообщение из текущей даты и времени, введенного текста и 
	//имени пользователя
	auto MessageConstructor(std::string text) -> std::string const
	{
		std::string message = TimeStamp() + " " + name_ + " : " + (text);
		return message;
	}

	//Получает текущее системное время, переформатирует в понятный обычному 
	//пользователю вид и возвращает полученное значение в формате строки.
	auto TimeStamp(void) -> std::string const
	{
		const size_t range = 26;
		time_t timeLong = 0;
		char timebuf[range] {};
		time(&timeLong);
#if OS_WIND_COMPATIBLE
		ctime_s(timebuf, range, &timeLong);
#else
		ctime_r(&timeLong, timebuf);
#endif
		std::string timeNow = "[";
		for (auto &user : timebuf)
			timeNow.push_back(user);
		timeNow.resize(25);
		timeNow.push_back(']');
		return timeNow;
	}
#if OS_WIND_COMPATIBLE
	//Конвертирует строку из string в кодировке UTF-8 в string в кодировке 
	//CHCP1251
	auto ConvertUTF8toCHCP1251(std::string const &strUTF8) -> std::string
	{
		std::string str1251;
		for (auto i = 0; i < strUTF8.size(); ++i)
		{
			switch (strUTF8[i])
			{
			case -48:
				if (strUTF8[i + 1] == -127)
					str1251.push_back(-88);
				else if (strUTF8[i + 1] >= -112 && strUTF8[i + 1] <= -65)
					str1251.push_back(strUTF8[i + 1] + 48);
				++i;
				break;
			case -47:
				if (strUTF8[i + 1] == -111)
					str1251.push_back(-72);
				else if (strUTF8[i + 1] >= -128 && strUTF8[i + 1] <= -113)
					str1251.push_back(strUTF8[i + 1] + 112);
				++i;
				break;
			default:
				str1251.push_back(strUTF8[i]);
				break;
			}
		}
		return str1251;
	}

	//Конвертирует строку из string в кодировке CHCP1251 в string в кодировке 
	//UTF-8
	auto ConvertCHCP1251toUTF8(std::string const &str1251) -> std::string
	{
		std::string strUTF8;
		for (auto i = 0; i < str1251.size(); ++i)
		{
			switch (str1251[i])
			{
			case -88:
				strUTF8.push_back(-48);
				strUTF8.push_back(-127);
				break;
			case -72:
				strUTF8.push_back(-47);
				strUTF8.push_back(-111);
				break;
			default:
				if (str1251[i] >= -64 && str1251[i] <= -17)
				{
					strUTF8.push_back(-48);
					strUTF8.push_back(str1251[i] - 48);
				}
				if (str1251[i] >= -16 && str1251[i] <= -1)
				{
					strUTF8.push_back(-47);
					strUTF8.push_back(str1251[i] - 112);
				}
				if (!(str1251[i] >= -64 && str1251[i] <= -1))
					strUTF8.push_back(str1251[i] + 0);
				break;
			}
		}
		return strUTF8;
	}
#endif
};