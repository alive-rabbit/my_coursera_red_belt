#include <iostream>
#include <vector>

#include "test_runner.h"

template <class T>
class Table
{
private:
    size_t first, second;
    std::vector<std::vector<T>> vec;
public:
    Table(size_t f, size_t s)
    {
        Resize(f, s);
    }
    void Resize(size_t f, size_t s)
    {
        first = f;
        second = s;
        if (first == 0 || second == 0)
        {
            first == second == 0;
        }
        vec.resize(f);
        for (std::vector<T>& k : vec)
        {
            k.resize(s);
        }
    }
    std::pair<size_t, size_t> Size() const
    {
        if (first == 0 || second == 0)
        {
            return { 0,0 };
        }
        return { first, second };
    }
    std::vector<T>& operator[](const size_t& index) 
    {
        return vec[index];
    }
    const std::vector<T>& operator[](const size_t& index) const 
    {
        return vec.at(index);
    }
};

void TestTable() 
{
    Table<int> t(1, 1);
    ASSERT_EQUAL(t.Size().first, 1u);
    ASSERT_EQUAL(t.Size().second, 1u);
    std::cerr << t[0][0] << '\n';
    t[0][0] = 42;
    ASSERT_EQUAL(t[0][0], 42);
    t.Resize(3, 4);
    ASSERT_EQUAL(t.Size().first, 3u);
    ASSERT_EQUAL(t.Size().second, 4u);
}

int main() 
{
    TestRunner tr;
    RUN_TEST(tr, TestTable);

    return 0;
}
