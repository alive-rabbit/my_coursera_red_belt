#pragma once

#include <cstdlib>
#include <iostream>
#include <exception>
#include <algorithm>

template <typename T>
class SimpleVector 
{
	public:
		SimpleVector() : data_(nullptr), size_(0), capacity_(0) {}
		explicit SimpleVector(size_t size)
		{
			data_ = new T[size];
			capacity_ = size;
			size_ = size;
		}
		~SimpleVector()
		{
			delete[] data_;
		}

		T& operator[](size_t index)
		{
			if (index >= 0 && index < size_) { return data_[index]; }
			else { throw std::out_of_range(""); }
		}

		T* begin()
		{
			return data_;
		}
		T* end()
		{
			if (size_ == 0) { return data_; }
			else { return data_ + size_; }
		}

		const T* begin() const
		{
			return data_;
		}
		const T* end() const
		{
			if (size_ == 0) { return data_; }
			else { return data_ + size_; }
		}

		size_t Size() const
		{
			return size_;
		}
		size_t Capacity() const
		{
			return capacity_;
		}
		//
		void PushBack(const T& value)
		{	// insert element at end
			if (size_ < capacity_)
			{
				data_[size_] = value;
				size_++;
			}
			else
			{
				if (capacity_ == 0) { capacity_ = 1; }
				else { capacity_ += capacity_; }

				T* temporary_data_ = new T[capacity_];
				std::copy(data_, data_ + size_, temporary_data_);
				temporary_data_[size_] = value;
				delete[] data_;
				data_ = temporary_data_;

				size_++;
			}
		}
		//
	private:
		T* data_;
		size_t size_;
		unsigned int capacity_;
		bool first_push_back = false;
};
