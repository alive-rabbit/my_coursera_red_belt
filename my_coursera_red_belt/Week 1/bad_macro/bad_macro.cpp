#include <iostream>

#include "test_runner.h"

#define PRINT_VALUES(out, x, y) (out << (x) << std::endl << (y) << std::endl)

int main()
{
    int a = 2, b = 3;
    if (false) { PRINT_VALUES(std::cout, a, b); }
    else PRINT_VALUES(std::cout, b, a);

    if (true)
        PRINT_VALUES(std::cout, 5, "red belt");
    else
        PRINT_VALUES(std::cout, 5, "red belt");

    std::cout << "start" << std::endl;
    for (auto i = 0; i < 5; i += 2)
        PRINT_VALUES(std::cout, i + 1, i + 2);
    std::cout << "end" << std::endl;

    TestRunner tr;
    tr.RunTest([]
        {
            std::ostringstream output;
            PRINT_VALUES(output, 5, "red belt");
            ASSERT_EQUAL(output.str(), "5\nred belt\n");
        }, "PRINT_VALUES usage example");


    return 0;
}