#include <numeric>
#include <iostream>
#include <vector>
#include <string>

#include "test_runner.h"

template <typename Iterator>
class IteratorRange
{
private:
    const Iterator first, last;
public:
    IteratorRange(const Iterator& f, const Iterator& l) :first(f), last(l) {}
    const size_t size() const { return last - first; }

    auto begin() const { return first; }
    auto begin() { return first; }

    auto end() const { return last; }
    auto end() { return last; }
};

template <typename Iterator>
class Paginator
{
private:
    std::vector<IteratorRange<Iterator>> pages;
public:
    Paginator(const Iterator& first, const Iterator& last, const size_t& p_s)
    {
        auto f = first, l = last;
        while (f < l)
        {
            auto temp_last_of_page = next(f, std::min(p_s, size_t(std::distance(f, l))));
            pages.push_back(IteratorRange<Iterator>{ f, temp_last_of_page });
            f = temp_last_of_page;
        }
    }
    // size() возвращает количество страниц, на которые был разбит переданный контейнер
    const size_t size() const { return pages.size(); }

    auto begin() const { return pages.begin(); }
    auto begin() { return pages.begin(); }

    auto end() const { return pages.end(); }
    auto end() { return pages.end(); }
};

// шаблон функции Paginate, которая принимает ссылку на контейнер и размер страницы, и возвращает объект класса Paginator<It>
template <typename C>
auto Paginate(C& c, const size_t& count_of_pages)
{
    return Paginator(c.begin(), c.end(), count_of_pages);
}

void TestPageCounts()
{
    std::vector<int> v(15);

    ASSERT_EQUAL(Paginate(v, 1).size(), v.size());
    ASSERT_EQUAL(Paginate(v, 3).size(), 5u);
    ASSERT_EQUAL(Paginate(v, 5).size(), 3u);
    ASSERT_EQUAL(Paginate(v, 4).size(), 4u);
    ASSERT_EQUAL(Paginate(v, 15).size(), 1u);
    ASSERT_EQUAL(Paginate(v, 150).size(), 1u);
    ASSERT_EQUAL(Paginate(v, 14).size(), 2u);
}

void TestModification()
{
    std::vector<std::string> vs = { "one", "two", "three", "four", "five" };
    for (auto page : Paginate(vs, 2))
    {
        for (auto& word : page)
        {
            word[0] = toupper(word[0]);
        }
    }

    const std::vector<std::string> expected = { "One", "Two", "Three", "Four", "Five" };
    ASSERT_EQUAL(vs, expected);
}

void TestPageSizes()
{
    std::string letters(26, ' ');

    Paginator<std::string::iterator> letters_pagination(letters.begin(), letters.end(), 11);
    std::vector<size_t> page_sizes;
    for (const auto& page : letters_pagination)
    {
        page_sizes.push_back(page.size());
    }

    const std::vector<size_t> expected = { 11, 11, 4 };
    ASSERT_EQUAL(page_sizes, expected);
}

void TestConstContainer()
{
    const std::string letters = "abcdefghijklmnopqrstuvwxyz";

    std::vector<std::string> pages;
    for (const auto& page : Paginate(letters, 10))
    {
        pages.push_back(std::string(page.begin(), page.end()));
    }

    const std::vector<std::string> expected = { "abcdefghij", "klmnopqrst", "uvwxyz" };
    ASSERT_EQUAL(pages, expected);
}

void TestPagePagination()
{
    std::vector<int> v(22);
    std::iota(begin(v), end(v), 1);

    std::vector<std::vector<int>> lines;
    for (const auto& split_by_9 : Paginate(v, 9))
    {
        for (const auto& split_by_4 : Paginate(split_by_9, 4))
        {
            lines.push_back({});
            for (int item : split_by_4)
            {
                lines.back().push_back(item);
            }
        }
    }

    const std::vector<std::vector<int>> expected = 
    {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9},
        {10, 11, 12, 13},
        {14, 15, 16, 17},
        {18},
        {19, 20, 21, 22}
    };
    ASSERT_EQUAL(lines, expected);
}

int main() 
{
    TestRunner tr;
    RUN_TEST(tr, TestPageCounts);
    RUN_TEST(tr, TestModification);
    RUN_TEST(tr, TestPageSizes);
    RUN_TEST(tr, TestConstContainer);
    RUN_TEST(tr, TestPagePagination);
}

