//============================================================================
// Name        : ABCU.cpp
// Author      : Christopher Frederick
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : 7-1 Project Two
//============================================================================

#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

// define a structure to hold course information
struct Course {
    string courseNumber;
    string courseName;
    vector<string> preReqs;
    Course() {
    }
};

//============================================================================
// Linked-List class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a linked-list.
 */
class CourseList {

private:
    //Internal structure for list entries, housekeeping variables
    struct Node {
        Course course;
        Node* next;

        // default constructor
        Node() {
            next = nullptr;
        }

        // initialize with a course
        Node(Course aCourse) {
            course = aCourse;
            next = nullptr;
        }
    };

    Node* head;
    Node* tail;
    int size = 0;

public:
    vector<Course> courseList;
    CourseList();
    virtual ~CourseList();
    void Append(Course course);
    void InsertionSort();
    void PrintCourses();
    Course Search(string courseNumber);
    int Size();
};

/**
 * Default constructor
 */
CourseList::CourseList() {
    // set head and tail equal to null
    head = nullptr;
    tail = nullptr;
}

/**
 * Destructor
 */
CourseList::~CourseList() {
    // start at the head
    Node* current = head;
    Node* temp;

    // loop over each node, detach from list then delete
    while (current != nullptr) {
        temp = current; // hang on to current node
        current = current->next; // make current the next node
        delete temp; // delete the orphan node
    }
}

/**
 * Append a new course to the end of the list
 */
void CourseList::Append(Course course) {
    //Create new node
    Node* newNode = new Node(course);

    // if there is nothing at the head...
    if (head == nullptr) {
        // new node becomes the head and the tail
        head = newNode;
        tail = newNode;
    }
    // else 
    else {
        // make current tail node point to the new node
        tail->next = newNode;
        // and tail becomes the new node
        tail = newNode;
    }
    // increase size count
    size++;
}

/**
 * Sort the list of courses
 */
void CourseList::InsertionSort() {
    // if the list is empty, return
    if (head == nullptr || head->next == nullptr) {
        return;
    }

    // start with head's next node
    struct Node* currNodeA = head->next;

    // while nullptr not reached
    while (currNodeA != nullptr) {
        // hold the course number of currNodeA
        string courseData = currNodeA->course.courseNumber;

        // to determine of correct spot has been found
        bool found = false;

        // start with head node
        struct Node* currNodeB = head;

        // iterate until currNodeB is equal to currNodeA
        while (currNodeB != currNodeA) {
            // if B's course # is greater than A's course # and the spot has not been found yet
            if (currNodeB->course.courseNumber > currNodeA->course.courseNumber && !found) {
                // set course data equal to B's course #
                courseData = currNodeB->course.courseNumber;

                // make B's course # equal to A's course #
                currNodeB->course.courseNumber = currNodeA->course.courseNumber;

                // spot has been found
                found = true;

                // move to B's next node
                currNodeB = currNodeB->next;
            }
            // else
            else {
                // if spot has been found
                if (found) {
                    // temporarily hold the course data
                    string temp = courseData;

                    // set the course data to B's course #
                    courseData = currNodeB->course.courseNumber;

                    // set B's course # to temp
                    currNodeB->course.courseNumber = temp;
                }

                // move to B's next node
                currNodeB = currNodeB->next;
            }
        }

        // set B's course # to the course data
        currNodeB->course.courseNumber = courseData;

        // move to A's next node
        currNodeA = currNodeA->next;
    }
}


/**
 * Simple output of all courses in the list
 */
void CourseList::PrintCourses() {
    // start at the head
    Node* currentNode = head;

    // while loop over each node looking for a match
    while (currentNode != nullptr) {
        // output course information
        cout << currentNode->course.courseNumber << ", " << currentNode->course.courseName;

        // if/else to hand # of prerequisites
        if (currentNode->course.preReqs.size() == 0) {
            cout << endl;
        }
        else if (currentNode->course.preReqs.size() == 1) {
            cout << ", " << currentNode->course.preReqs.at(0) << endl;
        }
        else {
            for (int i = 0; i < currentNode->course.preReqs.size() - 1; ++i) {
                cout << ", " << currentNode->course.preReqs.at(i) << ", ";
            }

            cout << currentNode->course.preReqs.at(currentNode->course.preReqs.size() - 1) << endl;
        }

        //set current equal to next
        currentNode = currentNode->next;
    }
}

/**
 * Search for the specified courseNumber and output its information
 *
 * @param courseNumber The course number to search for
 */
Course CourseList::Search(string courseNumber) {
    // start at the head of the list
    Node* currentNode = head;

    // keep searching until end reached with while loop
    while (currentNode != nullptr) {
        // if the current node matches, return it
        if (currentNode->course.courseNumber == courseNumber) {
            return currentNode->course;
        }
        // else current node is equal to next node
        currentNode = currentNode->next;
    }
}

/**
 * Returns the current size (number of elements) in the list
 */
int CourseList::Size() {
    return size;
}

/**
 * Display the course information
 *
 * @param course struct containing the course info
 */
void displayCourse(Course course) {
    cout << course.courseNumber << ", " << course.courseName << endl;
    cout << "Prerequisites: ";
    if (course.preReqs.size() == 0) {
        cout << "None" << endl;
        cout << endl;
    }
    else if (course.preReqs.size() == 1) {
        cout << course.preReqs.at(0) << endl;
        cout << endl;
    }
    else {
        for (int i = 0; i < course.preReqs.size() - 1; ++i) {
            cout << course.preReqs.at(i) << ", ";
        }

        cout << course.preReqs.at(course.preReqs.size() - 1) << endl;
        cout << endl;
    }
}

// check the file format
bool CheckFileFormat(string file_name) {
    vector<string> courseInfo;
    vector<string> courseNumbers;
    vector<string> preReqs;
    ifstream file;

    string lineData;

    file.open(file_name);

    if (!file.is_open()) {
        return false;
    }

    while (!file.eof()) {
        for (lineData; getline(file, lineData, ','); ) {
            courseInfo.push_back(lineData);
        }

        if (courseInfo.size() < 2) {
            return false;
        }

        courseNumbers.push_back(courseInfo.at(0));

        if (courseInfo.size() > 2) {
            for (int i = 2; i < courseInfo.size(); ++i) {
                preReqs.push_back(courseInfo.at(i));
            }
        }
    }

    for (int j = 0; j < courseNumbers.size(); ++j) {
        if (find(courseNumbers.begin(), courseNumbers.end(), preReqs.at(j)) != courseNumbers.end()) {
            return false;
        }
    }

    file.close();

    return true;
}

/**
 * Load a file containing courses into a LinkedList
 *
 * @return a LinkedList containing all the courses read
 */
vector<Course> loadCourses(string file_name, CourseList* list) {
    cout << "Loading course data file " << file_name << endl;

    vector<string> allCourseInfo;
    vector<string> courseInfo;
    vector<Course> courses;

    if (!CheckFileFormat(file_name)) {
        cout << endl;
        cout << "Unreliable course data." << endl;
        cout << endl;
        return courses;
    }

    ifstream file;

    string lineData;

    file.open(file_name);

    if (file.is_open()) {
        while (!file.eof()) {
            for (lineData; getline(file, lineData, '\n'); ) {
                allCourseInfo.push_back(lineData);
            }

            for (int i = 0; i < allCourseInfo.size(); ++i) {
                vector<string> courseInfo;
                string data;
                stringstream ss(allCourseInfo.at(i));

                for (data; getline(ss, data, ','); ) {
                    courseInfo.push_back(data);
                }

                Course course;
                course.courseNumber = courseInfo.at(0);
                course.courseName = courseInfo.at(1);
                if (courseInfo.size() > 2) {
                    for (int j = 2; j < courseInfo.size(); ++j) {
                        course.preReqs.push_back(courseInfo.at(j));
                    }
                }

                list->Append(course);
            }
        }
    }

    file.close();

    return courses;
}

/**
 * The one and only main() method
 */
int main() {

    // process command line arguments
    string courseInput;

    CourseList courseList;
    Course course;

    vector<Course> courses;

    int choice = 0;
    while (choice != 9) {
        cout << "Welcome to the course planner." << endl;
        cout << "   1. Load Data Structure." << endl;
        cout << "   2. Print Course List." << endl;
        cout << "   3. Print Course." << endl;
        cout << "   9. Exit" << endl;
        cout << endl;
        cout << "What would you like to do? ";
        cin >> choice;
        cout << endl;

        switch (choice) {
        case 1:
            loadCourses("CourseData.txt", &courseList);
            cout << endl;
            cout << courseList.Size() << " courses read successfully" << endl;
            cout << endl;
            break;

        case 2:
            cout << "Here are the available courses:" << endl;
            cout << endl;

            courseList.InsertionSort();
            courseList.PrintCourses();
            cout << endl;

            break;

        case 3:
            cout << "What course do you want to know about? " << endl;

            cin >> courseInput;
            
            cout << endl;

            course = courseList.Search(courseInput);

            if (!course.courseNumber.empty()) {
                displayCourse(course);
            }
            else {
                cout << "Course " << courseInput << " not found." << endl;
            }

            break;

        default:
            if (choice != 9) {
                cout << choice << " is not a valid option." << endl;
            }

            break;
        }
    }

    cout << "Thank you for using the course planner!" << endl;

    return 0;
}