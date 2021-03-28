#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <exception>
#include <queue>
#include <set>


template <typename T>
class ObjectPool
{
public:
	T* Allocate()
	{
		if (freed_objects.empty())
		{
			T* temp = new T;
			auto iter = selected_objects.insert(temp);
			return *iter.first;
		}
		else
		{
			auto iter = selected_objects.insert(freed_objects.front());
			freed_objects.pop();
			return *iter.first;
		}
	}

	T* TryAllocate()
	{
		if (freed_objects.empty())
		{
			return nullptr;
		}
		else
		{
			auto iter = selected_objects.insert(freed_objects.front());
			freed_objects.pop();
			return *iter.first;
		}
	}

	void Deallocate(T* object)
	{
		auto temp = selected_objects.find(object);
		if (temp == selected_objects.end())
		{
			throw std::invalid_argument("");
		}
		else
		{
			freed_objects.push(*temp);
			selected_objects.erase(temp);
		}
	}

	~ObjectPool()
	{
		for (auto el : selected_objects)
		{
			delete el;
		}
		while (freed_objects.size() != 0)
		{
			delete freed_objects.front();
			freed_objects.pop();
		}
	}

private:
	std::set<T*> selected_objects; // выделенные объекты
	std::queue<T*> freed_objects; // освобождённые объекты
};

void TestObjectPool()
{
	ObjectPool<std::string> pool;

	auto p1 = pool.Allocate();
	auto p2 = pool.Allocate();
	auto p3 = pool.Allocate();

	*p1 = "first";
	*p2 = "second";
	*p3 = "third";

	pool.Deallocate(p2);
	ASSERT_EQUAL(*pool.Allocate(), "second");

	pool.Deallocate(p3);
	pool.Deallocate(p1);
	ASSERT_EQUAL(*pool.Allocate(), "third");
	ASSERT_EQUAL(*pool.Allocate(), "first");

	pool.Deallocate(p1);
}

int main()
{
	TestRunner tr;
	RUN_TEST(tr, TestObjectPool);
	return 0;
}
