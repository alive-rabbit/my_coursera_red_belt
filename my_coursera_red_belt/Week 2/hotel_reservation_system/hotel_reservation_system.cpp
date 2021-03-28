#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <deque>
#include <algorithm>

struct Hotel
{
	int64_t time; // time — целое число в диапазоне от −10^18 до 10^18 и не убывает от события к событию
	std::string hotel_name; // hotel_name — строка из латинских букв и цифр, имеющая длину не более 12 символов
	int client_id; // client_id — натуральное число, не превосходящее 10^9
	int room_count; // room_count — целое положительное число, не превосходящее 1000
};

class Hotels 
{
public:

	Hotels() : last_time(INT64_MIN) {}

	bool Func_Book(const int64_t& t = 0, const std::string& h_n = "",
		const int& c_i = 0, const int& r_c = 0) 
	{
		last_time = t;

		deq_of_hotels.push_back({ t, h_n, c_i, r_c });
		hotel_clients_this_day[h_n].insert(c_i);
		client_id_their_count[h_n][c_i]++;
		hotel_rooms_this_day[h_n] += r_c;

		while (deq_of_hotels.begin()->time <= last_time - 86400) {
			if (client_id_their_count[deq_of_hotels.begin()->hotel_name][deq_of_hotels.begin()->client_id] > 0) 
			{
				client_id_their_count[deq_of_hotels.begin()->hotel_name][deq_of_hotels.begin()->client_id]--;
			}

			if (client_id_their_count[deq_of_hotels.begin()->hotel_name][deq_of_hotels.begin()->client_id] == 0) 
			{ // проскакивает, если на два разных отеля 1 клиент id
				auto iter = hotel_clients_this_day[deq_of_hotels.begin()->hotel_name].find(deq_of_hotels.begin()->client_id);
				hotel_clients_this_day[deq_of_hotels.begin()->hotel_name].erase(iter);
			}
			hotel_rooms_this_day[deq_of_hotels.begin()->hotel_name] -= deq_of_hotels.begin()->room_count; // удаляем старые номера отелей
			deq_of_hotels.pop_front(); // тут чистить сразу свои мапы
		}
		return true;
	}

	int Func_Clients(const std::string& h_n) 
	{ // имена клиентов не должны совпадать
		return hotel_clients_this_day[h_n].size();
	}

	int Func_Rooms(const std::string& h_n) 
	{
		return hotel_rooms_this_day[h_n];
	}
private:
	int64_t last_time;

	std::map<std::string, std::set<int>> hotel_clients_this_day; // количество клиентов Hotel в этот день
	std::map < std::string, std::map<int, int>> client_id_their_count;
	std::map<std::string, int> hotel_rooms_this_day; // количество забронированных комнат в Hotel в этот день

	std::deque<Hotel> deq_of_hotels;
};



int main()
{
	std::cin.tie(nullptr);
	std::ios_base::sync_with_stdio(false);
	Hotels hotels;
	int time_started = 0;
	size_t quantity_of_requests = 0;
	std::cin >> quantity_of_requests;
	for (size_t i = 0; i < quantity_of_requests; i++) 
	{
		std::string request;
		std::cin >> request;
		if (request == "BOOK") 
		{
			int64_t time;
			std::string hotel_name;
			uint32_t client_id;
			uint16_t room_count;
			std::cin >> time >> hotel_name >> client_id >> room_count;

			if (hotels.Func_Book(time, hotel_name, client_id, room_count)) {}
			else return 0;
		}
		else if (request == "CLIENTS") 
		{
			std::string hotel_name;
			std::cin >> hotel_name;

			std::cout << hotels.Func_Clients(hotel_name) << '\n';
		}
		else if (request == "ROOMS") 
		{
			std::string hotel_name;
			std::cin >> hotel_name;

			std::cout << hotels.Func_Rooms(hotel_name) << '\n';
		}
		else 
		{
			exit(0);
		}
	}
	return 0;
}
