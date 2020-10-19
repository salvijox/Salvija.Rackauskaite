
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


void WriteData(vector <StudentData> data)
{
	sort(data.begin(), data.end(), ComparisonFunction);

	cout << left << setw(15) << "Vardas\t" << setw(20) << "Pavarde\t" << "Galutinis (Vid.) / Galutinis(Med.)" << endl;
	cout << "--------------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < data.size(); i++)
	{
		cout << left << setw(15) << data.at(i).name << "\t" << setw(20) << data.at(i).surname << "\t" << fixed << setprecision(2) << data.at(i).finalResult << endl;
	}
}

void WriteDataToFile(vector <StudentData> data)
{
	ofstream outputStream("studentai.txt");
	sort(data.begin(), data.end(), ComparisonFunction);

	outputStream << left << setw(15) << "Vardas\t" << setw(20) << "Pavarde\t" << "Galutinis (Vid.) / Galutinis(Med.)" << endl;
	outputStream << "--------------------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < data.size(); i++)
	{
		outputStream << left << setw(15) << data.at(i).name << "\t" << setw(20) << data.at(i).surname << "\t" << fixed << setprecision(2) << data.at(i).finalResult << endl;
	}
	outputStream.close();
}



void ReadDataFromConsole(vector <StudentData>& data)
{
	int studentuSk;
	cout << "Kiek bus studentu? " << endl;
	cin >> studentuSk;

	for (int i = 0; i < studentuSk; i++)
	{
		StudentData studentData; // laikinas kintamasis vieno studento duomenims saugoti
		cout << "Iveskite studento varda, pavarde: " << endl;
		cin >> studentData.name >> studentData.surname;

		string howToGetGrades; // ar bus ivedami ranka, ar generuojami atsitiktinai
		cout << "Skaityti pazymius is konsoles:'konsole', generuoti: 'generuoti'" << endl;
		cin >> howToGetGrades;

		if (howToGetGrades == "konsole")
		{
			ReadGradesFromConsole(studentData);
		}
		else if (howToGetGrades == "generuoti")
		{
			RandomGradesGenerator(studentData);
		}
		else
		{
			cout << "Pasirinktas neegzistuojantis budas, bus naudojama konsole" << endl;
			ReadGradesFromConsole(studentData);
		}

		data.push_back(studentData);
	}
}
void ReadDataFromFile(vector <StudentData>& studentsData)
{

	// is pradziu suskaiciuojama, kiek bus is viso kintamuju
	ifstream inputStream("kursiokai.txt");

	if (inputStream.fail()) {
		cout << "Failas neegzistuoja" << endl;
	}
	else
	{
		string input;
		getline(inputStream, input);

		stringstream stringStr(input);
		string word;
		int kiekZodziu = 0;

		while (stringStr >> word) {
			++kiekZodziu;
		}

		// nuskaitomi duomenys
		while (!inputStream.eof())
		{
			StudentData studentData;

			inputStream >> studentData.name >> studentData.surname;
			string grade;

			// pazymiu skaicius randamas is visu stulpeliu skaiciaus atimant vardo, pavardes ir egzamino stulpelius
			for (int i = 0; i < kiekZodziu - 3; i++)
			{
				inputStream >> grade;
				int paz;
				if (IsNumber(grade) == true)
				{
					try {
						paz = std::stoi(grade);
					}
					catch (std::exception e) {
						cout << "įvyko nežinoma klaida\n";
					}

				}
				else
				{
					paz = 0;
				}
				studentData.homeworksGrades.push_back(paz);
			}

			string egzamString;
			inputStream >> egzamString;
			int egzam;

			if (IsNumber(egzamString) == true)
			{

				try {
					egzam = std::stoi(egzamString);
				}
				catch (std::exception e) {
					cout << "įvyko nežinoma klaida\n";
				}
			}
			else
			{
				egzam = 0;
			}

			studentData.egzamResult = egzam;
			studentsData.push_back(studentData);
		}
	}
}
void ReadGradesFromConsole(StudentData& studentsData)
{
	string egzamResultString;
	string invalidEgzamResultMessage = "Ivertinimas klaidingas, bus naudojamas 0";

	bool gradesExist = true; // ar ivestas dar vienas pazymys 
	string gradeString;
	bool isNull = true;

	cout << "Egzamino ivertinimas: " << endl;
	cin >> egzamResultString;

	bool number = IsNumber(egzamResultString);

	if (number == true)
	{
		int egzamResult = 0;
		try {
			egzamResult = stoi(egzamResultString);
		}
		catch (std::exception e) {
			cout << "įvyko nežinoma klaida\n";
		}

		if (egzamResult >= 0 && egzamResult <= 10)
		{
			studentsData.egzamResult = egzamResult;
		}
		else
		{
			cout << invalidEgzamResultMessage << endl;
			studentsData.egzamResult = 0;
		}
	}
	else
	{
		cout << invalidEgzamResultMessage << endl;
		studentsData.egzamResult = 0;
	}

	cout << "Iveskite pazymius atskirtus tarpais, baigus ivestite -1 ir paspauskite enter" << endl;
	while (gradesExist == true)
	{
		cin >> gradeString;

		int number = IsNumber(gradeString);

		if ((number == true) || (gradeString == "-1"))
		{
			int grade = 0;
			try {
				grade = std::stoi(gradeString);
			}
			catch (std::exception e) {
				cout << "įvyko nežinoma klaida\n";
			}

			if (grade >= 0 && grade <= 10)
			{
				studentsData.homeworksGrades.push_back(grade);
				isNull = false;
			}
			else if (grade == -1 && isNull == true)
			{
				cout << "Pazymiai neivesti" << endl;
				continue;
			}
			else if (grade == -1)
			{
				gradesExist = false; // ivestas jau ne pazymys, o ivedimo stabdymo zenklas
			}
			else
			{
				cout << "Pazymiai turi buti desimtbaleje sistemoje" << endl;
				continue;
			}
		}
		else
		{
			cout << "Ivestas ne skaicius" << endl;
			continue;
		}
	}
}