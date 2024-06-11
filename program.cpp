#include <cstdint>
#include <vector>
#include "splashkit.h"

using namespace std;

struct course
{
    string name;
    int courseID;
    int availableSeats;
};

struct student
{
    string name;
    int studentID;
    vector<course> registeredCourses;
};

struct university
{
    vector<course> Courses;
    vector<student> Students;
};

enum Menu_Options
{
    ADD_COURSE,
    ADD_STUDENT,
    REGISTER_COURSE,
    LIST_REGISTERED_COURSES,
    LIST_AVAILABLE_COURSES,
    EXIT
};

string read_string(string prompt)
{
    string result;
    write_line(prompt);
    result = read_line();
    return result;
}

int read_integer(string prompt)
{
    int result;
    write_line(prompt);
    result = convert_to_integer(read_line());
    return result;
}



course read_course_details()
{
    course Course;

    Course.name = read_string("\nEnter course name: ");
    Course.courseID = read_integer("Enter Course ID: ");
    Course.availableSeats = read_integer("Enter available seats: ");

    return Course;
}

student read_student_details()
{
    student Student;

    Student.name = read_string("\nEnter Student name: ");
    Student.studentID = read_integer("Enter Student ID: ");

    return Student;
}

void add_courses(university &university)
{
    int numCourses = read_integer("\nEnter the number of courses you want to add: ");
    for (int i = 0; i < numCourses; i++)
    {
        course Course = read_course_details();
        university.Courses.push_back(Course);
    }
}


void add_students(university &university)
{
    int numStudents = read_integer("\nEnter the number of students you want to add: ");
    for (int i = 0; i < numStudents; i++)
    {
        student Student = read_student_details();
        university.Students.push_back(Student);
    }
}


void register_course(university &University, int &studentID, const int &courseID)
{
    course Course;

    for (course &courses : University.Courses)
    {
        if (courses.courseID == courseID && courses.availableSeats > 0)
        {
            for (student &Student : University.Students)
            {
                if (Student.studentID == studentID)
                {
                    courses.availableSeats--;
                    Student.registeredCourses.push_back(courses);
                    write_line("\n--------------------------------------------------");
                    write_line("Student: " + Student.name + " registered for course: " + courses.name);
                    write_line("--------------------------------------------------");
                    return;
                }
            }
        }
    }
}


void list_registered_courses(const student &Student, const course &courses)
{
    write_line("\nCourses registered by: " + Student.name);
    for (const course &courses : Student.registeredCourses)
    {
        write_line("\n--------------------------------------------------");
        write_line("Course Name: " + courses.name);
        write_line("--------------------------------------------------");
    }
}


void list_available_courses(const university &university)
{
    write_line("\nAvailable Courses: ");
    for (const course &courses : university.Courses)
    {
        if (courses.availableSeats > 0)
        {
            write_line("\n--------------------------------------------------");
            write_line("Course Name: " + courses.name + " Course ID: " + to_string(courses.courseID) +
                       " Available Seats: " + to_string(courses.availableSeats));
            write_line("--------------------------------------------------");
        }
    }
}

void regiseter_for_course(university &University)
{
    int studentID;
    int courseID;
    studentID = read_integer("\n Eneter Student ID: ");
    courseID  = read_integer("\n Enter Course ID: ");
    register_course(University, studentID, courseID);
}

int read_interger_range(const string &prompt, int min, int max)
{
    int result;
    do
    {
        write_line(prompt);
        result = convert_to_integer(read_line());

        if (result < min || result > max)
        {
            write_line("\nPlease enter a value between " + to_string(min) + " to " + to_string(max));
        }
    } while (result < min || result > max);
    return result;
}


Menu_Options read_menu_options()
{
    int options;
    do
    {

        write_line("\nPLEASE CHOOSE AN OPTION:");
        write_line("1. Add course");
        write_line("2. Add student");
        write_line("3. Register course");
        write_line("4. List registered course");
        write_line("5. List available course");
        write_line("6. Exit ");
        options = read_interger_range("Enter your choice: ", 1, 6);
    } while (options < 1 || options > 6);

    return static_cast<Menu_Options>(options - 1);
}

int main()
{
    university University;
    course Courses;
    student Student;

    write_line("\nWELCOME TO UNIVERSITY COURSE REGISTRATION:");
    bool exit = false;
    while (!exit)
    {
        Menu_Options options = read_menu_options();

        switch (options)
        {
        case ADD_COURSE:
            add_courses(University);
            break;

        case ADD_STUDENT:
            add_students(University);
            break;

        case REGISTER_COURSE:
             regiseter_for_course(University);
            break;

        case LIST_REGISTERED_COURSES:
            list_registered_courses(Student, Courses);
            break;

        case LIST_AVAILABLE_COURSES:
            list_available_courses(University);
            break;

        case EXIT:
            exit = true;
            break;

        default:
            write_line("\nEnter a valid choice please: ");
            break;
        }
    }

    return 0;
}
