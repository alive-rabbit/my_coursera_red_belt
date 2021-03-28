#include <string>
#include <vector>
#include <list>
#include <forward_list>
#include <numeric>
#include <iterator>

#include "test_runner.h"

template<typename ForwardIterator, typename UnaryPredicate>
ForwardIterator max_element_if(ForwardIterator first, ForwardIterator last, UnaryPredicate pred)
{
    if (first == last) { return first; }

    auto max_element = *first;

    while (first != last)
    {
        if (pred(*first))
        {
            max_element = *first;
            break;
        }
        first++;
    }
    auto iter_of_max_element = first;
    while (first != last)
    {
        if (pred(*first) && *first > max_element)
        {
            max_element = *first;
            iter_of_max_element = first;
            ++first;
        }
        else
        {
            ++first;
        }
    }
    return iter_of_max_element;

}

void TestUniqueMax()
{
    auto IsEven = [](int x)
    {
        return x % 2 == 0;
    };

    const std::list<int> hill{ 2, 4, 8, 9, 6, 4, 2 };
    auto max_iterator = hill.begin();
    advance(max_iterator, 2);

    std::vector<int> numbers(10);
    std::iota(numbers.begin(), numbers.end(), 1);
    //____________________________________________________________________________________\\

    Assert(
        max_element_if(hill.begin(), hill.end(), IsEven) == max_iterator,
        "Expect the maximal even number"
    );

    Assert(
        max_element_if(numbers.begin(), numbers.end(), IsEven) == --numbers.end(),
        "Expect the last element"
    );
}

void TestSeveralMax()
{
    struct IsCapitalized
    {
        bool operator()(const std::string& s)
        {
            return !s.empty() && isupper(s.front());
        }
    };

    const std::forward_list<std::string> text{ "One", "two", "Three", "One", "Two",
      "Three", "one", "Two", "three" };
    auto max_iterator = text.begin();
    advance(max_iterator, 4);

    Assert(
        max_element_if(text.begin(), text.end(), IsCapitalized()) == max_iterator,
        "Expect the first \"Two\""
    );
}

void TestNoMax()
{
    const std::vector<int> empty;
    const std::string str = "Non-empty string";

    auto AlwaysTrue = [](int)
    {
        return true;
    };
    Assert(
        max_element_if(empty.begin(), empty.end(), AlwaysTrue) == empty.end(),
        "Expect end for empty container"
    );

    auto AlwaysFalse = [](char)
    {
        return false;
    };
    Assert(
        max_element_if(str.begin(), str.end(), AlwaysFalse) == str.end(),
        "Expect end for AlwaysFalse predicate"
    );
}

int main()
{
    TestRunner tr;
    tr.RunTest(TestUniqueMax, "TestUniqueMax");
    tr.RunTest(TestSeveralMax, "TestSeveralMax");
    tr.RunTest(TestNoMax, "TestNoMax");
    return 0;
}