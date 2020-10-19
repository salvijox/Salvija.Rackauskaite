#pragma once
#include <string>
using namespace std;

struct StudentData {
	string name;
	string surname;
	int egzamResult;
	vector<int> homeworksGrades;
	float finalResult = 0;
};

bool IsNumber(string s);
void GetData(vector <StudentData>& data);
float finalGrade(StudentData studentsData, string howToCalculate);
void RandomGradesGenerator(StudentData& studentsData);
float FindMedian(vector <int> homeworksGrades);
float Average(vector <int> homeworksGrades);
bool ComparisonFunction(const StudentData& data0, const StudentData& data1); 

