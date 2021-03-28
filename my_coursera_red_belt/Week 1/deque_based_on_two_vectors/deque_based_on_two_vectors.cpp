#include <iostream>
#include <vector>
#include <exception>
#include <algorithm>

template <typename T>
class Deque
{
private:
    std::vector<T> vector_for_push_front, vector_for_push_back;
    T deq_front, deq_back;
public:
    Deque() {};
    bool Empty() const
    {
        return Size() == 0;
    }
    size_t Size() const
    {
        return vector_for_push_front.size() + vector_for_push_back.size();
    }
    //__________________________________________________________________________
    T& operator[](size_t index)
    {
        return At(index);
    }
    const T& operator[](size_t index) const
    {
        return At(index);
    }
    //__________________________________________________________________________
    T& At(size_t index) 
    { 
        if (index >= Size()) throw std::out_of_range("");
        if (index < vector_for_push_front.size()) return vector_for_push_front[vector_for_push_front.size() - 1 - index];
        index -= vector_for_push_front.size();
        return vector_for_push_back[index];
    }
    const T& At(size_t index) const
    {
        if (index >= Size()) throw std::out_of_range("");
        if (index < vector_for_push_front.size()) return vector_for_push_front[vector_for_push_front.size() - 1 - index];
        index -= vector_for_push_front.size();
        return vector_for_push_back[index];
    }
    //__________________________________________________________________________
    T& Front()
    {
        return At(0);
    }
    const T& Front()const //{ return deq_front; }
    {
        return At(0);
    }
    //__________________________________________________________________________
    T& Back()
    {
        if (Empty())
        {
            return Front();
        }
        return At(Size() - 1);
    }
    const T& Back()const //{ return deq_back; }
    {
        if (Empty())
        {
            return Front();
        }
        return At(Size() - 1);
    }
    //__________________________________________________________________________
    void PushFront(T element) 
    {
        //deq.insert(deq.begin(), element);
        vector_for_push_front.push_back(element);
        deq_front = element;
    }
    void PushBack(T element) 
    {
        //deq.push_back(element);
        vector_for_push_back.push_back(element);
        deq_back = element;
        //vector_for_push_back.push_back(element);
    } 
};
int main()
{
    Deque<int> d;
    if (d.Empty()) std::cout << "+" << std::endl;
    //
    d.PushFront(2);
    d.PushBack(1);
    d.PushBack(1);
    d.PushBack(1);
    d.PushBack(1);
    d.PushBack(1);
    d.PushBack(1);
    d.PushBack(1);
    d.PushBack(1);
    d.PushBack(1);
    d.PushBack(1);
    d.PushBack(1);
    d.PushFront(3);
    d.PushBack(5);
    std::cout << d.Front() << ' ' << d.Back() << std::endl;
    for (int i = 0; i < d.Size(); i++)
    {
        std::cout << d[i] << ' ';
    }
    std::cout << std::endl;
    //
    if (d.Empty()) std::cout << "+" << std::endl;
    //
    d.Front() = 3;
    d.Back() = 4;
    std::cout << d.Front() << ' ' << d.Back() << std::endl;
    for (int i = 0; i < d.Size(); i++)
    {
        std::cout << ++d[i] << ' ';
    }
    std::cout << std::endl;     // 4 3 2 5
    std::cout << d.At(3);
    return 0;
}
