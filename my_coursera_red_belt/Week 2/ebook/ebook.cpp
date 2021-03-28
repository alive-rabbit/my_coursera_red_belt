#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <set>

class ReadingManager 
{
public:
    ReadingManager() :id_of_page_users(1001, 0), page_raiting(1001, 0) {}

    void Read(const int& user_id, const int& page_count) 
    {
        if (user_page[user_id] != 0) 
        {
            id_of_page_users[user_page[user_id]]--;
        }
        user_page[user_id] = page_count;
        id_of_page_users[page_count]++;

        int users_on_page = 0;
        if (user_page.size() == 1) 
        {
            page_raiting[page_count] = 1;
        }
        else 
        {
            for (size_t i = 0; i < 1000; i++) 
            {
                page_raiting[i + 1] = (users_on_page * 1.0) / (user_page.size() - 1);
                users_on_page += id_of_page_users[i + 1];
            }
        }
    }

    double Cheer(const int& user_id) const 
    {
        if (user_page.count(user_id) == 0) 
        {
            return 0;
        }
        return page_raiting.at(user_page.at(user_id));

        // По умолчанию деление целочисленное, поэтому
        // нужно привести числитель к типу double.
        // Простой способ сделать это — умножить его на 1.0.
    }

private:
    // Статическое поле не принадлежит какому-то конкретному
    // объекту класса. По сути это глобальная переменная,
    // в данном случае константная.
    // Будь она публичной, к ней можно было бы обратиться снаружи
    // следующим образом: ReadingManager::MAX_USER_COUNT.
    static const int MAX_USER_COUNT_ = 100'000;
    std::map<int, int> user_page;
    std::vector<double> page_raiting;
    std::vector<int> id_of_page_users;
    //map<int, double> user_raiting;
};


int main() 
{
    // Для ускорения чтения данных отключается синхронизация
    // cin и cout с stdio,
    // а также выполняется отвязка cin от cout
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    ReadingManager manager;

    int query_count;
    std::cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) 
    {
        std::string query_type;
        std::cin >> query_type;
        int user_id;
        std::cin >> user_id;

        if (query_type == "READ") 
        {
            int page_count;
            std::cin >> page_count;
            manager.Read(user_id, page_count);
        }
        else if (query_type == "CHEER") 
        {
            std::cout << std::setprecision(6) << manager.Cheer(user_id) << "\n";
        }
    }

    return 0;
}