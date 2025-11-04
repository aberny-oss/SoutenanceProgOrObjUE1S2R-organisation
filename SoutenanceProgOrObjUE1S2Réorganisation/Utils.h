#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>

class Utils
{
public:

	std::string AskStr(const std::string& msg, const std::vector<std::string>& validChoices);

	int AskInt(const std::string& msg, int min, int max);

	static int getTerminalWidth();
	static int getTerminalHeight();

};


