#include <algorithm>

#include "profile.h"
#include "student.h"
#include "test_runner.h"

//Оптимизируйте эту функцию
bool Compare(const Student& first, const Student& second) 
{
    return first.Less(second);
}

void TestComparison() 
{
    Student newbie
    {
      "Ivan", "Ivanov",
        {
            {"c++", 1.0},
            {"algorithms", 3.0}
        },
        2.0
    };

    Student cpp_expert
    {
      "Petr", "Petrov", 
        {
            {"c++", 9.5},
            {"algorithms", 6.0}
        },
        7.75
    };

    Student guru
    {
      "Sidor", "Sidorov", 
        {
            {"c++", 10.0},
            {"algorithms", 10.0}
        },
        10.0
    };
    ASSERT(Compare(guru, newbie));
    ASSERT(Compare(guru, cpp_expert));
    ASSERT(!Compare(newbie, cpp_expert));
}

void TestSorting() {
    std::vector<Student> students
    {
      {"Sidor", "Sidorov", {{"maths", 2.}}, 2.},
      {"Semen", "Semenov", {{"maths", 4.}}, 4.},
      {"Ivan", "Ivanov", {{"maths", 5.}}, 5.},
      {"Petr", "Petrov", {{"maths", 3.}}, 3.},
      {"Alexander", "Alexandrov", {{"maths", 1.}}, 1.}
    };
    sort(students.begin(), students.end(), Compare);
    ASSERT(is_sorted(students.begin(), students.end(),
        [](Student first, Student second) { return first.Less(second); }));
}
void TEST_1() {
    LOG_DURATION("TEST_1");
    int count_of_students = 1000;
    std::vector<Student> students; {
        LOG_DURATION("TEST_1, (for()) : ");
        for (int i = 0; i < count_of_students; ++i)
        {
            students.push_back({ std::to_string(i), std::to_string(i + 1), {{std::to_string(i), i}}, double(i + 1) });
        }
    }
    sort(students.begin(), students.end(), Compare);
    ASSERT(is_sorted(students.begin(), students.end(),
        [](Student first, Student second) { return first.Less(second); }));
}


int main() 
{
    LOG_DURATION("Compare: ");

    TestRunner tr;
    RUN_TEST(tr, TestComparison);
    RUN_TEST(tr, TestSorting);
    RUN_TEST(tr, TEST_1);
    return 0;
}