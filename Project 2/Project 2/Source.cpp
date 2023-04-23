#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <string>

using namespace std;

struct Course{
	string courseNumber;
	string name;
	vector<string> prerequisites; 
};
vector<string> tokenize(string s, string del = " "){
	vector<string> stringArray;


	int start = 0;
	int end = s.find(del);

	while (end != -1){
		stringArray.push_back(s.substr(start, end - start));
		start = end + del.size();
		end = s.find(del, start);
	}

	stringArray.push_back(s.substr(start, end - start));

	return stringArray;
}
vector<Course> LoadDataStructure(){
	ifstream fin("abcu.txt", ios::in);
	vector<Course> courses;
	string line;
	while (getline(fin, line)){
		Course course;
		vector<string> tokenizedInformation = tokenize(line, ",");
		if (tokenizedInformation.size() > 1){
			course.courseNumber = tokenizedInformation[0];
			course.name = tokenizedInformation[1];
			for (int i = 2; i < tokenizedInformation.size(); i++){
				course.prerequisites.push_back(tokenizedInformation[i]);
			}
			courses.push_back(course);
		}
	}

	fin.close();

	cout << "\n Courses Loaded Successfully \n";

	return courses;
}
void printCourse(Course course){
	string courseNumber = course.courseNumber;
	string name = course.name;
	vector<string> prerequisites = course.prerequisites;

	cout << "\n";
	cout << "Course Number: " << courseNumber << endl;
	cout << "Course Name: " << name << endl;
	cout << "Prerequisites: ";

	for (int i = 0; i < prerequisites.size(); i++){
		cout << prerequisites[i] << " ";
	}

	cout << "\n\n";
}
void printCourseList(vector<Course> courses){
	int n = courses.size();
	for (int i = 0; i < n - 1; i++){
		for (int j = 0; j < n - i - 1; j++){
			if (courses[j].courseNumber > courses[j + 1].courseNumber){
				swap(courses[j + 1], courses[j]);
			}
		}
	}
	cout << "\nHere is a sample schedule: \n";
	for (int i = 0; i < n; i++){
		cout << courses[i].courseNumber << ", " << courses[i].name << endl;
	}
}

void searchCourse(vector<Course> courses){
	int n = courses.size();
	string courseNumber;
	int f = 0;

	cout << "\nWhich course do you want to know about? ";
	cin >> courseNumber;

	cout << "\nCourse Details: \n";
	for (int i = 0; i < n; i++){

		if (strcmp(courses[i].courseNumber.c_str(), courseNumber.c_str()) == 0){
			f = 1;
			printCourse(courses[i]);
			break;
		}
	}

	if (f == 0){
		cout << "Invalid option\n";
	}
}

int main(int argc, char **argv){
	vector<Course> courses;
	cout << "WELCOME TO THE COURSE PLANNER" << endl;
	cout << "1.Load Data Structure\n";
	cout << "2.Print Course List\n";
	cout << "3.Print Course\n";
	cout << "4.Exit\n";

	int ch;

	do{

		cout << "\nWhat would you like to do? ";
		cin >> ch;

		switch (ch){
		case 1:
			courses = LoadDataStructure();
			break;
		case 2:
			printCourseList(courses);
			break;
		case 3:
			searchCourse(courses);
			break;
		case 4:
			cout << "\nThank you for using the course planner!\n";
			break;
		default:
			
			cout << ch << " is not a valid option\n";
		}
	} while (ch != 4);

	return 0;
}