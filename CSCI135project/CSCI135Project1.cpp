/*
Jason Moy
CSCI 135
Ali/Professor Sakas
Project 1
This program will read information from two files and create a new
file that contains all the information(emplid,semester code,
subject code, catalog code, hours and designation code)
The second half of the code will calculate the gpa of each student
One for compsci classes and the other for all classes. It will
also calculate the percent of hours taking non-liberal arts courses
*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
ifstream studentData, hunterCourses;
ofstream studentDataPlus;//naming funnels
studentData.open("StudentData.tsv");
hunterCourses.open("HunterCourses.tsv");
studentDataPlus.open("StudentDataPlus.tsv");
//opening files
ifstream studentDataPlus2;
ofstream studentSummary;
studentDataPlus2.open("StudentDataPlus.tsv");
studentSummary.open("StudentSummary.tsv");//for part two


string  semesterCode, subjectCode, catalogCode,letterGrade;
int emplID;
double numericGrade;//studentData variables
string subjectCodeHC, catalogCodeHC, designationCode;
double contactHours;//hunterCourses variables

if(studentData.is_open() && hunterCourses.is_open() && studentDataPlus.is_open() && studentSummary.is_open()&& studentDataPlus2.is_open())
//makes sure file exsists or will cout error
{
  while(studentData>>emplID>>semesterCode>>subjectCode>>catalogCode>>letterGrade>>numericGrade)//copies studentData file
  {
    while(hunterCourses>>subjectCodeHC>>catalogCodeHC>>contactHours>>designationCode)
    {
      if(subjectCode!=subjectCodeHC && catalogCode!=catalogCodeHC)
      {
        studentDataPlus<<emplID<<"  "<<semesterCode<<"  "<<subjectCode<<"  "<<catalogCode<<"  "<<letterGrade<<"  "<<numericGrade<<"  "<<contactHours<<"  "<<designationCode<<"  "<<endl;
        //outputs to studentDataPlus
      }
      else
      {
        studentDataPlus<<emplID<<"  "<<semesterCode<<"  "<<subjectCode<<"  "<<catalogCode<<"  "<<letterGrade<<"  "<<numericGrade<<" "<<"3.0  RNL"<<endl;
        //given that not all courses match with HunterCourses, those that dont match are already designated "3.0 RNL"
      }
      break;
      hunterCourses.clear();
      hunterCourses.seekg(ios::beg);//resets hunterCourses to the beginning
    }
  }
  //closing files
  studentData.close();
  hunterCourses.close();
  studentDataPlus.close();


/*part two summarizes the information of studentDataPlus.
It contains each students GPA, their CSCI GPA and a percentage
of time spent on taking a liberal arts class*/
    double sum=0, csciSum=0,nonLiberalHours=0;
    int  currentEmplID=0, hours=0, csciHours=0;
    while(studentDataPlus2>>emplID>>semesterCode>>subjectCode>>catalogCode>>letterGrade>>numericGrade>>contactHours>>designationCode)
    {
      if(currentEmplID==0)//if grade less than zero it will be ignored
      {
      currentEmplID=emplID;
      }
      if(currentEmplID==emplID)//does this match temporary ID?
      {
        if(subjectCode=="CSCI")//compsci gpa calculation
        {
          csciSum+=numericGrade*contactHours;
          csciHours+=contactHours;
        }
        if(designationCode=="RNL" || designationCode=="MNL"|| designationCode=="GNL")// gathering for nonliberal arts hours
        {
          nonLiberalHours+=contactHours;
        }
        if(numericGrade==-1)//if the grade is -1 do not include it
        {
          numericGrade=0;
          contactHours=0;
        }
        sum+=numericGrade*contactHours;//calculate sum for gpa
        hours+=contactHours;//gather hours
      }
      if(currentEmplID!=emplID)//if the two id's do not match
      {
        double gpa=sum/hours;  //calculate gpa
        double csciGpa=csciSum/hours;  //cscigpa
        double percentHour=((nonLiberalHours)/(hours))*100;//calculate the percent of hours spent taking nonLiberalarts courses
        if(hours==0)//since you cannot divide by zero this helps prevents errors by automatically setting them to 0
        {
          gpa=0;
          percentHour=0;
        }
        if(csciHours==0)
        {
          csciGpa=0;
        }
        studentSummary<<currentEmplID<<" "<<gpa<<" "<<csciGpa<<" "<<percentHour<<"%"<<endl;//output data to student summary file

        //resets data to zero for next student
        currentEmplID=emplID;
        hours=0;
        csciHours=0;
        nonLiberalHours=0;
        sum=0;
        csciSum=0;
        //starts collecting data for the next student after values reset to zero
        if(subjectCode=="CSCI")
        {
          csciSum+=numericGrade*contactHours;
          csciHours+=contactHours;
        }
        if(designationCode=="RNL" || designationCode=="MNL"|| designationCode=="GNL")
        {
          nonLiberalHours+=contactHours;
        }
        if(numericGrade==-1)
        {
          numericGrade=0;
          contactHours=0;
        }
        sum+=numericGrade*contactHours;
        hours+=contactHours;
      }
    }
    studentSummary<<currentEmplID<<"  "<<sum/hours<<" "<<csciSum/csciHours<<" "<<(nonLiberalHours/hours)*100<<"%"<<endl;
  studentDataPlus2.close();
  studentSummary.close();
  }
else
  cout<<"Error! Unable to open file!"<<endl;
  exit(1);
}
