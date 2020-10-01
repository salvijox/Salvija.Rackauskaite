// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <string>

using namespace std;

struct StudentData {
    string name;
    string surname;
    int egzamResult;
    vector<int> homeworksGrades;
    float finalResult = 0;
};

void GetData(vector <StudentData>& data);
float finalGrade(StudentData studentsData, string howToCalculate);
void RandomGradesGenerator(StudentData& studentsData);
void ReadGradesFromConsole(StudentData& studentsData);
bool IsNumber(string s);
float FindMedian(vector <int> homeworksGrades);
float Average(vector <int> homeworksGrades);

int main()
{
    srand(time(0));

    vector <StudentData> studentsData;

    GetData(studentsData);

    if (studentsData.size() > 0)
    {
        string howToCalculate;
        cout << "Skaiciouti naudojant vidurki 'vid' ar mediana 'med'" << endl;
        cin >> howToCalculate;

        for (int i = 0; i < studentsData.size(); i++)
        {
            studentsData.at(i).finalResult = finalGrade(studentsData.at(i), howToCalculate);
        }

        // duomenu isvedimas
        cout << left << setw(15) << "Vardas\t"<< setw(20) << "Pavarde\t" << "Galutinis (Vid.) / Galutinis(Med.)" << endl;
        cout << "----------------------------------------------------------------------------------" << endl;
        for (int i = 0; i < studentsData.size(); i++)
        {
            cout << left << setw(15) << studentsData.at(i).name << "\t" << setw(20) << studentsData.at(i).surname << "\t" << fixed << setprecision(2) << studentsData.at(i).finalResult << endl;
        }
    }
    else
    {
        cout << "Duomenys neivesti" << endl;
    }

    return 0;
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
        int egzamResult = stoi(egzamResultString);

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
            int grade = std::stoi(gradeString);
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

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
