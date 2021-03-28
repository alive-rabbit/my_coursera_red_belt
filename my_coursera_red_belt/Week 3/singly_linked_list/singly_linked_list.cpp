#include <vector>

#include "test_runner.h"

template <typename T>
class LinkedList
{
public:
    struct Node
    {
        T value;
        Node* next = nullptr;
    };

    ~LinkedList()
    {
        while (head) { PopFront(); }
    }

    void PushFront(const T& value)
    {
        Node* temporary_node = new Node;
        temporary_node->value = value;
        temporary_node->next = head;
        head = temporary_node;
    }
    void InsertAfter(Node* node, const T& value)
    {
        if (head == nullptr) { PushFront(value); }
        else
        {
            Node* temporary_node = new Node;
            temporary_node->next = node->next;
            temporary_node->value = value;
            node->next = temporary_node;

        }
    }
    void RemoveAfter(Node* node)
    {
        if (head == nullptr || node == nullptr)
        {
            PopFront();
        }
        else if (node->next == nullptr) { return; }
        else
        {
            Node* temporary_node = nullptr;
            temporary_node = node->next; // удалить

            node->next = temporary_node->next;
            delete temporary_node;
        }
    }
    void PopFront()
    {
        if (head == nullptr) { return; }
        else
        {
            Node* temporary_node = head;
            head = head->next;
            delete temporary_node;
        }
    }
    Node* GetHead() { return head; }
    const Node* GetHead() const { return head; }

private:
    Node* head = nullptr;
};

template <typename T>
std::vector<T> ToVector(const LinkedList<T>& list)
{
    std::vector<T> result;
    for (auto node = list.GetHead(); node; node = node->next)
    {
        result.push_back(node->value);
    }
    return result;
}

void TestPushFront()
{
    LinkedList<int> list;

    list.PushFront(1);
    ASSERT_EQUAL(list.GetHead()->value, 1);
    list.PushFront(2);
    ASSERT_EQUAL(list.GetHead()->value, 2);
    list.PushFront(3);
    ASSERT_EQUAL(list.GetHead()->value, 3);
    const std::vector<int> expected = { 3, 2, 1 };
    ASSERT_EQUAL(ToVector(list), expected);
}

void TestInsertAfter()
{
    LinkedList<std::string> list;

    list.PushFront("a");
    auto head = list.GetHead();
    ASSERT(head);
    ASSERT_EQUAL(head->value, "a");

    list.InsertAfter(head, "b");
    const std::vector<std::string> expected1 = { "a", "b" };
    ASSERT_EQUAL(ToVector(list), expected1);

    list.InsertAfter(head, "c");
    const std::vector<std::string> expected2 = { "a", "c", "b" };
    ASSERT_EQUAL(ToVector(list), expected2);
}

void TestRemoveAfter()
{
    LinkedList<int> list;
    for (int i = 1; i <= 5; ++i)
    {
        list.PushFront(i);
    }

    const std::vector<int> expected = { 5, 4, 3, 2, 1 };
    ASSERT_EQUAL(ToVector(list), expected);

    auto next_to_head = list.GetHead()->next;
    list.RemoveAfter(next_to_head); // удаляем 3
    list.RemoveAfter(next_to_head); // удаляем 2

    const std::vector<int> expected1 = { 5, 4, 1 };
    ASSERT_EQUAL(ToVector(list), expected1); //

    while (list.GetHead()->next)
    {
        list.RemoveAfter(list.GetHead());
    }
    ASSERT_EQUAL(list.GetHead()->value, 5);
}

void TestPopFront()
{
    LinkedList<int> list;

    for (int i = 1; i <= 5; ++i) 
    {
        list.PushFront(i);
    }
    for (int i = 1; i <= 5; ++i) 
    {
        list.PopFront();
    }
    ASSERT(list.GetHead() == nullptr);
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestPushFront);
    RUN_TEST(tr, TestInsertAfter);
    RUN_TEST(tr, TestRemoveAfter);
    RUN_TEST(tr, TestPopFront);
    return 0;
}
