/*
 * CourseReq.cpp
 *
 *  Created on: Oct 14, 2022
 *      Author: corydoak_snhu
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

	// Course structure definition
		struct Course{

		string courseId;
		string name;
		vector<string> prereqs;

		};

	// Function that splits string into list of strings
	vector<string> tokenize(string s, string del = " "){

		vector<string> stringArray;
		int start = 0;
		int end = s.find(del);
		while (end != -1) {

			stringArray.push_back(s.substr(start, end - start));
			start = end + del.size();
			end = s.find(del, start);
		}

		stringArray.push_back(s.substr(start, end - start));

		return stringArray;

		}

	// Function that loads file and stores details into list of courses
	vector<Course> LoadDataStructure(){

		// Creating iftsream class object to open file
		ifstream fin("abcu.txt",ios::in);

		vector<Course> courses;

		string line;

		// Infinite loop
		while(1){
			getline(fin,line);

			// break the loop if end of file is reached
			if(line=="-1")
				break;

			Course course;

			// getting tokenized information and storing on structure course
			vector<string> tokenizedInformation = tokenize(line,",");

			course.courseId = tokenizedInformation[0];
			course.name = tokenizedInformation[1];

			// store prereqs (if there are any)
			for(int i = 2; i < tokenizedInformation.size(); i++){

				course.prereqs.push_back(tokenizedInformation[i]);
			}

			// appending the course into list of courses
			courses.push_back(course);

			}

		// closing file and return list of courses
		fin.close();

		return courses;

		}

	// printing course info of course in correct format
	void printCourse(Course course){

		string courseId = course.courseId;
		string name = course.name;
		vector<string> prereqs = course.prereqs;

		cout << "Course Number: " << courseId << endl;
		cout << "Course Name: " << name << endl;
		cout << "Prerequisites: ";

		for(int i=0;i<prereqs.size();i++){
			cout << prereqs[i] << " ";
		}

		cout << "\n\n";

	}

	// printing course info of all courses
	void printCourseList(vector<Course> courses){

		int n = courses.size();

		// sorting the list
		for(int i = 0; i < n - 1; i++){

			for(int j = 0; j < n - i - 1; j++){

				if(courses[j].courseId > courses[j + 1].courseId){
					swap(courses[j + 1],courses[j]);
				}
			}
		}

		// print all courses and info by traversing list
		for(int i = 0; i < n; i++){

			printCourse(courses[i]);
		}
	}

	// search for user input for course number
	void searchCourse(vector<Course> courses){

		int n = courses.size();
		string courseId;
		int f = 0;

		cout << "Enter courseNumber: ";
		cin >> courseId;

		for(int i = 0; i < n; i++){

			// print course if found
			if(courses[i].courseId == courseId){
				f = 1;
				printCourse(courses[i]);

				break;
			}
		}

		// print error message if course name not found
		if(f == 0){

			cout << "Course not found\n";
		}
	}

	int main(int argc, char **argv){
		vector<Course> courses;

		// Printing menu
		cout << "1.Load Data Structure\n";
		cout << "2.Print Course List\n";
		cout << "3.Print Course\n";
		cout << "9.Exit\n";

		int Userchoice;

		do{

			// Prompt user to enter choice
			cout << "\nEnter your choice: ";
			cin >> Userchoice;

			switch(Userchoice){

				case 1: courses = LoadDataStructure(); break;
				case 2: printCourseList(courses); break;
				case 3: searchCourse(courses); break;
				case 9: cout << "Exit\n"; break;

				default: cout<<"Invalid Choice\n";
			}
		}

		while(Userchoice != 4);

		return 0;
	}



