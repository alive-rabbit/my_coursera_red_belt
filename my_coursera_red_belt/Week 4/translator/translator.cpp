#include <string>
#include <string_view>
#include <vector>
#include <map>
#include <deque>

#include "test_runner.h"

class Translator 
{
public:
	Translator() {}
	void Add(std::string_view source, std::string_view target)
	{
		const std::string_view source_view = GetClonedView(source);
		const std::string_view target_view = GetClonedView(target);
		dictionary_source_target[source_view] = GetClonedView(target_view);
		dictionary_target_source[target_view] = GetClonedView(source_view);
	}
	std::string_view TranslateForward(std::string_view source) const
	{
		if (const auto it = dictionary_source_target.find(source); it != dictionary_source_target.end())
		{
			return it->second;
		}
		return {};
	}
	std::string_view TranslateBackward(std::string_view target) const
	{
		if (const auto it = dictionary_target_source.find(target); it != dictionary_target_source.end())
		{
			return it->second;
		}
		return {};
	}
private:
	std::string_view GetClonedView(std::string_view s) {
		for (const auto* map_ptr : { &dictionary_source_target, &dictionary_target_source }) {
			const auto it = map_ptr->find(s);
			if (it != map_ptr->end()) {
				return it->first;
			}
		}
		return data.emplace_back(s);
	}

	std::map< std::string_view, std::string_view > dictionary_source_target;
	std::map< std::string_view, std::string_view > dictionary_target_source;
	std::deque<std::string> data;
};

void TestSimple() 
{
	Translator translator;
	translator.Add(std::string("okno"), std::string("window"));
 	
	translator.Add(std::string("stol"), std::string("table"));

	ASSERT_EQUAL(translator.TranslateForward("okno"), "window");
	ASSERT_EQUAL(translator.TranslateBackward("table"), "stol");
	ASSERT_EQUAL(translator.TranslateBackward("stol"), "");
}

int main() 
{
	TestRunner tr;
	RUN_TEST(tr, TestSimple);
	return 0;
}


