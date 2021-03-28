#include <algorithm>
#include <string>
#include <vector>
#include <utility>

#include "test_runner.h"

// Объявляем Group<String> для произвольного типа String
// синонимом vector<String>.
// Благодаря этому в качестве возвращаемого значения
// функции можно указать не малопонятный вектор векторов,
// а вектор групп — vector<Group<String>>.
template <typename String>
using Group = std::vector<String>;

// Ещё один шаблонный синоним типа
// позволяет вместо громоздкого typename String::value_type
// использовать Char<String>
template <typename String>
using Char = typename String::value_type;
//Готовое решение, что не прошло грейдер
//template <typename String>
//bool Check_Strings(const String& rhs, const String& lhs)
//{
//	String copy_of_rhs = rhs;
//	String copy_of_lhs = lhs;
//	sort(begin(copy_of_rhs), end(copy_of_rhs));
//	copy_of_rhs.erase(unique(begin(copy_of_rhs), end(copy_of_rhs)), end(copy_of_rhs));
//
//	sort(begin(copy_of_lhs), end(copy_of_lhs));
//	copy_of_lhs.erase(std::unique(begin(copy_of_lhs), end(copy_of_lhs)), end(copy_of_lhs));
//
//	return (copy_of_rhs == copy_of_lhs) ? true : false;
//}
//
//template <typename String>
//std::vector<Group<String>> GroupHeavyStrings(std::vector<String> strings) 
//{
//	std::vector<Group<String>> result;
//
//	for (String& el : strings)
//	{
//		auto it = std::find_if(result.begin(), result.end(), 
//			[&el](const Group<String>& el_of_result) {
//				return Check_Strings(el, el_of_result[0]); 
//					}
//		);
//		if (it != result.end())
//		{
//			it->push_back(std::move(el));
//		}
//		else
//		{
//			result.push_back(Group<String>{ std::move(el) });
//		}
//	}
//
//	return result;
//}

template <typename String>
String ComputeStringKey(const String& srt) 
{
	String chars = srt;
	sort(begin(chars), end(chars));
	chars.erase(unique(begin(chars), end(chars)), end(chars));
	return chars;
}


template <typename String>
std::vector<Group<String>> GroupHeavyStrings(std::vector<String> strings)
{
	std::map<String, Group<String>> groups_map;
	for (String& string : strings) 
	{
		groups_map[ComputeStringKey(string)].push_back(move(string));
	}

	std::vector<Group<String>> groups;
	for (auto& el : groups_map)
	{
		groups.push_back(move(el.second));
	}
	return groups;
}
void TestGroupingABC() 
{
	std::vector<std::string> strings = { "caab", "abc", "cccc", "bacc", "c" };
	auto groups = GroupHeavyStrings(strings);
	ASSERT_EQUAL(groups.size(), 2);
	sort(begin(groups), end(groups));  // Порядок групп не имеет значения
	ASSERT_EQUAL(groups[0], std::vector<std::string>({ "caab", "abc", "bacc" }));
	ASSERT_EQUAL(groups[1], std::vector<std::string>({ "cccc", "c" }));
}

void TestGroupingReal() 
{
	std::vector<std::string> strings = { "law", "port", "top", "laptop", "pot", "paloalto", "wall", "awl" };
	auto groups = GroupHeavyStrings(strings);
	ASSERT_EQUAL(groups.size(), 4);
	sort(begin(groups), end(groups));  // Порядок групп не имеет значения
	ASSERT_EQUAL(groups[0], std::vector<std::string>({ "laptop", "paloalto" }));
	ASSERT_EQUAL(groups[1], std::vector<std::string>({ "law", "wall", "awl" }));
	ASSERT_EQUAL(groups[2], std::vector<std::string>({ "port" }));
	ASSERT_EQUAL(groups[3], std::vector<std::string>({ "top", "pot" }));
}

int main() 
{
	TestRunner tr;
	RUN_TEST(tr, TestGroupingABC);
	RUN_TEST(tr, TestGroupingReal);
	return 0;
}
