#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
#include <cstdlib>
#include <ctime>

class Utils
{
public:

	std::string AskStr(const std::string& msg, const std::vector<std::string>& validChoices);

	int AskInt(const std::string& msg, int min, int max);

	static int getTerminalWidth();
	static int getTerminalHeight();

	// Méthode statique d'initialisation du seed
	static void InitRandom();

	// Méthode statique pour générer un nombre aléatoire
	static int GenerateRandomNumber(int min, int max);

};


