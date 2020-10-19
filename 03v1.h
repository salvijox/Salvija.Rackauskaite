#pragma once
#include "03v.h"
#include <vector>
using namespace std;

void ReadGradesFromConsole(StudentData& studentsData);
void ReadDataFromFile(vector <StudentData>& studentsData);
void ReadDataFromConsole(vector <StudentData>& data);
void WriteData(vector <StudentData> data);
void WriteDataToFile(vector <StudentData> data);
