#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include "profile.h"

class Learner 
{
private:
    std::set<std::string> dict;

public:
    int Learn(const std::vector<std::string>& words)
    {
        int newWords = dict.size();
        for (const auto& word : words) 
        {
            dict.insert(word);
        }
        return dict.size() - newWords;
    }

    std::vector<std::string> KnownWords()
    {
        return { dict.begin(), dict.end() };
    }
};

int main() 
{
    Learner learner;
    std::string line;
    while (getline(std::cin, line)) 
    {
        LOG_DURATION("While");
        std::vector<std::string> words;
        std::stringstream ss(line);
        std::string word;
        while (ss >> word)
        {
            words.push_back(word);
        }
        std::cout << learner.Learn(words) << "\n";
    }
    std::cout << "=== known words ===\n";
    {
        LOG_DURATION("For");
        for (auto word : learner.KnownWords()) 
        {
            std::cout << word << ", ";
        }
        std::cout << std::endl;
    }
}