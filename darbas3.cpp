// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>

#include "03v.h"
#include "03v1.h"


using namespace std;



int main()
{
	srand(time(0));

	vector <StudentData> studentsData;

	string howToGetType;
	cout << "Ivesti duomenis: 'ivesti', jei skaityti is failo: 'skaityti'" << endl;
	cin >> howToGetType;

	if (howToGetType == "ivesti")
	{
		ReadDataFromFile(studentsData);
	}
	else if (howToGetType == "skaityti")
	{
		ReadDataFromFile(studentsData);
	}
	else
	{
		cout << "Pasirinktas budas neegzistuoja" << endl;
		return -1;
	}

	if (studentsData.size() > 0)
	{
		string howToCalculate;
		cout << "Skaiciuoti galutini bala naudojant vidurki: 'vidurkis', naudojant mediana: 'mediana'" << endl;
		cin >> howToCalculate;

		if (howToCalculate != "vidurkis" && howToCalculate != "mediana")
		{
			cout << "Pasirinktas neegzistuojantis budas, naudojamas vidurkis " << endl;
		}

		for (int i = 0; i < studentsData.size(); i++)
		{
			studentsData.at(i).finalResult = finalGrade(studentsData.at(i), howToCalculate);
		}


		cout << "Isvesti i konsole: 'konsole', ar i faila: 'failas'?\n";
		cin >> howToGetType;
		if (howToGetType == "konsole")
			WriteData(studentsData);
		else if (howToGetType == "failas")
			WriteDataToFile(studentsData);
		else {
			cout << "Pasirinktas budas neegzistuoja, isvedama i konsole\n";
			WriteData(studentsData);
		}
	}
	else
	{
		cout << "Nera duomenu" << endl;
	}

	return 0;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
