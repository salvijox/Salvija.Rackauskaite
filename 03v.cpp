
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


bool IsNumber(string s)
{
	try {
		int number = stoi(s);
	}
	catch (exception e)
	{
		return false;
	}
	return true;
}

bool ComparisonFunction(const StudentData& data0, const StudentData& data1)
{
	if (data0.name != data1.name)
	{
		return data0.name < data1.name;
	}
	if (data0.name == data1.name)
	{
		return data0.surname < data1.surname;
	}
}



void GetData(vector <StudentData>& data)
{
	int numberOfStudents;
	cout << "Kiek studentu nuskaityti? " << endl;
	cin >> numberOfStudents;

	for (int i = 0; i < numberOfStudents; i++)
	{
		StudentData studentsData; // laikinas kintamasis vieno studento duomenims saugoti
		cout << "Vardas is pavarde: " << endl;
		cin >> studentsData.name >> studentsData.surname;

		string gradesType; // ar bus ivedami ranka, ar generuojami atsitiktinai
		cout << "Jei norite ivesti i konsole veskite 'konsole' - jei sugeneruoti, iveskite 'generuoti'" << endl;
		cin >> gradesType;

		if (gradesType == "konsole")
		{
			ReadGradesFromConsole(studentsData);
		}
		else if (gradesType == "generuoti")
		{
			RandomGradesGenerator(studentsData);
		}
		else
		{
			cout << "Pasirinktas budas neegzistuoja - skaitoma is konsoles" << endl;
			ReadGradesFromConsole(studentsData);
		}

		data.push_back(studentsData);
	}
}



float Average(vector <int> homeworksGrades)
{
	int sum = 0;

	if (homeworksGrades.size() < 1)
	{
		return 0;
	}

	for (unsigned int i = 0; i < homeworksGrades.size(); i++)
		sum += homeworksGrades[i];

	return sum * 1.0f / homeworksGrades.size();
}



float FindMedian(vector <int> homeworksGrades)
{
	if (homeworksGrades.size() < 1)
	{
		return 0;
	}
	// First we sort the array 
	sort(homeworksGrades.begin(), homeworksGrades.end());

	// check for even case 
	if (homeworksGrades.size() % 2 != 0)
		return (float)homeworksGrades[homeworksGrades.size() / 2];

	return (float)(homeworksGrades[(homeworksGrades.size() - 1) / 2] + homeworksGrades[homeworksGrades.size() / 2]) / 2.0f;
}



void RandomGradesGenerator(StudentData& studentsData)
{
	studentsData.egzamResult = rand() % 10 + 1;
	cout << "Egzamino pazimys: \n" << studentsData.egzamResult << endl;

	int numberOfGradesToGenerate;
	cout << "Kiek pazimiu sugeneruoti?" << endl;
	cin >> numberOfGradesToGenerate;

	if (numberOfGradesToGenerate < 1) numberOfGradesToGenerate = 1;

	cout << "Namu darbu pazymiai\n";
	for (int i = 0; i < numberOfGradesToGenerate; i++)
	{
		int random = rand() % 10 + 1;
		cout << random << " ";
		studentsData.homeworksGrades.push_back(random);
	}
	cout << endl;
}

float finalGrade(StudentData studentsData, string howToCalculate)
{
	float results;

	if (howToCalculate == "vid") // naudojamas vidurkis
	{
		results = Average(studentsData.homeworksGrades);
	}
	else if (howToCalculate == "med") // naudojama mediana
	{
		results = FindMedian(studentsData.homeworksGrades);
	}
	else
	{
		cout << "Pasirinktas skaiciavimo budas neegzistuoja, bus naudojamas vidurkis." << endl;
		results = Average(studentsData.homeworksGrades);
	}


	studentsData.finalResult = results * 0.4 + studentsData.egzamResult * 0.6;

	return studentsData.finalResult;
}
