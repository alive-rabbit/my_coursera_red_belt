#pragma once

#include <stdexcept>
#include <array>

template <typename T, size_t N>
class StackVector 
{
private:
	std::array<T, N> data_;
	size_t size_ = 0;
	size_t capacity_ = N;
public:
	StackVector(size_t a_size = 0)
	{
		if (a_size > capacity_)
		{
			throw std::invalid_argument("");
		}
		else { size_ = a_size; }
	}

	T& operator[](size_t index) { return data_[index]; }
	const T& operator[](size_t index) const { return data_[index]; }

	typename std::array< T, N>::iterator begin() { return data_.begin(); }
	typename std::array< T, N>::iterator end() { return data_.begin() + size_; }
	const typename std::array< T, N>::const_iterator begin() const { return data_.begin(); }
	const typename std::array< T, N>::const_iterator end() const { return data_.begin() + size_; }

	size_t Size() const { return size_; }
	size_t Capacity() const { return capacity_; }

	void PushBack(const T& value)
	{
		if (size_ < capacity_)
		{
			data_[size_++] = value;
		}
		else { throw std::overflow_error(""); }
	}
	T PopBack()
	{
		if (size_ > 0)
		{
			return data_[--size_];
		}
		else { throw std::underflow_error(""); }
	}
};

