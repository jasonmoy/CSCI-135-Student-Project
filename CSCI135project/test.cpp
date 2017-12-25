#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
ifstream hunterCourses;
ofstream hi;
hunterCourses.open("HunterCourses.tsv");
hi.open("hello.tsv");
string subjectCode, catalogCode, contactHours, designationCode;
while(hunterCourses>>subjectCode>>catalogCode>>contactHours>>designationCode)
{
hi<<subjectCode<<" "<<catalogCode<<endl;
}
hi.close();
hunterCourses.close();
}
