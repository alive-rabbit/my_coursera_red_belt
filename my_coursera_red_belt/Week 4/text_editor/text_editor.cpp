#include <iostream>
#include <string>
#include <list>
#include "test_runner.h"

class Editor 
{
public:
    Editor():cursor_(data_.begin()){}
    void Left()                     // сдвинуть курсор влево
    {
        if (cursor_ != data_.begin())
        {
            cursor_--;
        }
    }
    void Right()                    // сдвинуть курсор вправо
    {
        if (cursor_ != data_.end())
        {
            cursor_++;
        }
    }
    void Insert(const char& token)  // вставить символ token
    {
        data_.insert(cursor_, token);
    }
    void Copy(const size_t& tokens) // cкопировать не более tokens символов,
    {                               // начиная с текущей позиции курсора
        buffer_.clear();
        if (tokens != 0)
        {
            buffer_.assign(cursor_, next_to_iterator(tokens));
        }
    }
    void Cut(const size_t& tokens)  // вырезать не более tokens символов,
    {                               // начиная с текущей позиции курсора
        if (tokens != 0)
        {
            buffer_.clear();
            auto it = next_to_iterator(tokens);
            buffer_.splice(buffer_.begin(), data_, cursor_, it);
            cursor_ = it;
        }
    }
    void Paste()                    // вставить содержимое буфера
    {                               // в текущую позицию курсора
        if (!buffer_.empty()) { data_.insert(cursor_, buffer_.begin(), buffer_.end()); }
    }
    std::string GetText() const     // получить текущее содержимое
    {                               // текстового редактора
        std::string result_str_;
        for (auto ch : data_)
        {
            result_str_ += ch;
        }
        return result_str_;
    }
private:
    std::list<char> data_;
    std::list<char> buffer_;
    std::list<char>::iterator cursor_;
    std::list<char>::iterator next_to_iterator(const size_t& quantity)
    {
        std::list<char>::iterator it = cursor_;
        for (size_t i = 0; i < quantity; i++)
        {
            if (it != data_.end())
            {
                it++;
            }
        }
        return it;
    }
};

void TypeText(Editor& editor, const std::string& text) 
{
    for (char c : text) 
    {
        editor.Insert(c);
    }
}

void TestEditing() 
{
    {
        Editor editor;

        const size_t text_len = 12;
        const size_t first_part_len = 7;
        TypeText(editor, "hello, world");
        for (size_t i = 0; i < text_len; ++i) 
        {
            editor.Left();
        }
        editor.Cut(first_part_len);
        for (size_t i = 0; i < text_len - first_part_len; ++i) 
        {
            editor.Right();
        }
        TypeText(editor, ", ");
        editor.Paste();
        editor.Left();
        editor.Left();
        editor.Cut(3);

        ASSERT_EQUAL(editor.GetText(), "world, hello");
    }
    {
        Editor editor;

        TypeText(editor, "misprnit");
        editor.Left();
        editor.Left();
        editor.Left();
        editor.Cut(1);
        editor.Right();
        editor.Paste();

        ASSERT_EQUAL(editor.GetText(), "misprint");
    }
}

void TestReverse() 
{
    Editor editor;

    const std::string text = "esreveR";
    for (char c : text) 
    {
        editor.Insert(c);
        editor.Left();
    }

    ASSERT_EQUAL(editor.GetText(), "Reverse");
}

void TestNoText() 
{
    Editor editor;
    ASSERT_EQUAL(editor.GetText(), "");

    editor.Left();
    editor.Left();
    editor.Right();
    editor.Right();
    editor.Copy(0);
    editor.Cut(0);
    editor.Paste();

    ASSERT_EQUAL(editor.GetText(), "");
}

void TestEmptyBuffer() 
{
    Editor editor;

    editor.Paste();
    TypeText(editor, "example");
    editor.Left();
    editor.Left();
    editor.Paste();
    editor.Right();
    editor.Paste();
    editor.Copy(0);
    editor.Paste();
    editor.Left();
    editor.Cut(0);
    editor.Paste();

    ASSERT_EQUAL(editor.GetText(), "example");
}

int main() 
{
    TestRunner tr;
    RUN_TEST(tr, TestEditing);
    RUN_TEST(tr, TestReverse);
    RUN_TEST(tr, TestNoText);
    RUN_TEST(tr, TestEmptyBuffer);
    return 0;
}
