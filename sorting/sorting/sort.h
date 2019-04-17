#ifndef SORT_H_
#define SORT_H_

#include <cstdlib>
#include <ctime>
#include <functional>
#include <iostream>
#include <vector>

namespace nwacc
{
	
	void fill_vector(std::vector<int> & list, int size)
	{
		std::srand(static_cast<unsigned>(std::time(nullptr)));
		for (auto index = 0; index < size; index++)
		{
			list.push_back(std::rand());
		}
	}

	template <typename T>
	void print(std::vector<T> list, std::ostream & out = std::cout)
	{
		for (size_t index = 0; index < list.size(); index++)
		{
			out << list[index] << " ";
		}
		out << std::endl;
	}

	template <typename T>
	void shell_sort(std::vector<T> & list)
	{
		for (auto gap = list.size() / 2; gap > 0; gap /= 2)
		{
			for (auto index = gap; index < list.size(); index++)
			{
				T temp = std::move(list[index]);
				auto inner_index = index;
				for (; inner_index >= gap && temp < list[inner_index - gap]; inner_index -= gap)
				{
					list[inner_index] = std::move(list[inner_index - gap]);
				}
				list[inner_index] = std::move(temp);
			}
		}
	}

	template <typename T>
	void ciura_shell_sort(std::vector<T> & list)
	{
		int gaps[8]{ 1, 4, 10, 23, 57, 132, 301, 701 };

		for (auto gap_index = 7; gap_index >= 0; gap_index--)
		{
			auto gap = gaps[gap_index];
			for (auto index = gap; index < list.size(); index++)
			{
				T temp = std::move(list[index]);
				auto inner_index = index;
				for (; inner_index >= gap && temp < list[inner_index - gap]; inner_index -= gap)
				{
					list[inner_index] = std::move(list[inner_index - gap]);
				}
				list[inner_index] = std::move(temp);
			}
		}
	}

	template <typename T>
	void insertion_sort(std::vector<T> & list)
	{ // running time O(N^2)
		for (auto index = 1; index < list.size(); index++)
		{
			T temp = std::move(list[index]);
			auto inner_index = 0;
			for (inner_index = index; inner_index > 0 && temp < list[inner_index - 1]; inner_index--)
			{
				list[inner_index] = std::move(list[inner_index - 1]);
			}
			list[inner_index] = std::move(temp);
		}
	}

	template <typename T>
	void insertion_sort(std::vector<T> & list, int left, int right)
	{
		for (auto index = left + 1; index <= right; index++)
		{
			T temp = std::move(list[index]);
			auto inner_index = index;
			for (inner_index = index; inner_index > left && temp < list[inner_index - 1]; inner_index--)
			{
				list[inner_index] = std::move(list[inner_index - 1]);
			}
			list[inner_index] = std::move(temp);
		}
	}

	template <typename T>
	void radix_sort(std::vector<T> & list, int size)
	{
		std::vector<std::vector<int>> radix_buckets;
		for (auto index = 0; index < 10; index++)
		{
			radix_buckets.push_back(std::vector<int>());
		}

		auto radix = 1;
		for (auto index = 0; index < size; index++)
		{
			// populate the radix buckets. 
			for (size_t bucket_index = 0; bucket_index < list.size(); bucket_index++)
			{
				auto temp = list[bucket_index] / radix % 10;
				radix_buckets[temp].push_back(list[bucket_index]);
			}
			// copy the buckets back into the list. 
			auto postion = 0;
			for (auto buckets = 0; buckets < 10; buckets++)
			{
				for (auto value : radix_buckets[buckets])
				{
					list[postion] = value;
					postion++;
				}
				radix_buckets[buckets].clear();
			}
			radix *= 10;
		}
	}

	template <typename T>
	T max(std::vector<T> & list)
	{
		auto max = list[0];
		for (size_t index = 1; index < list.size(); index++)
		{
			if (max < list[index])
			{
				max = list[index];
			} // else, not a new max, do_nothing();
		}
		return max;
	}

	int size(int value)
	{
		auto count = 0;
		auto copy = value;
		while (copy > 0)
		{
			count++;
			copy /= 10;
		}
		return count;
	}

	template <typename T>
	void merge(
		std::vector<T> & lhs, 
		std::vector<T> & rhs, 
		int left_position, 
		int right_position, 
		int right_end)
	{
		auto left_end = right_position - 1;
		auto temp = left_position;
		auto number_of_elements = right_end - left_position + 1;

		while (left_position <= left_end && right_position <= right_end)
		{
			if (lhs[left_position] <= lhs[right_position])
			{
				rhs[temp++] = std::move(lhs[left_position++]);
			}
			else
			{
				rhs[temp++] = std::move(lhs[right_position++]);
			}
		}

		while (left_position <= left_end)
		{
			rhs[temp++] = std::move(lhs[left_position++]);
		}

		while (right_position <= right_end)
		{
			rhs[temp++] = std::move(lhs[right_position++]);
		}

		for (auto index = 0; index < number_of_elements; index++, --right_end)
		{
			lhs[right_end] = std::move(rhs[right_end]);
		}
	}

	template <typename T>
	void merge_sort(std::vector<T> & lhs, std::vector<T> & rhs, int left, int right)
	{
		if (left < right)
		{
			auto center = (left + right) / 2;
			merge_sort(lhs, rhs, left, center);
			merge_sort(lhs, rhs, center + 1, right);
			merge(lhs, rhs, left, center + 1, right);
		}
	}

	template <typename T>
	void merge_sort(std::vector<T> & list)
	{
		std::vector<T> temp(list.size());
		merge_sort(list, temp, 0, list.size() - 1);
	}

	//First element
	template <typename T>
	void quick_sort_first(std::vector<T> & list, int left, int right)
	{
		if (left + 5 <= right)
		{ // I still have enough elements in the list to quick sort
			const T & pivot = list[left];
			std::swap(list[left], list[right - 1]);
			auto left_index = left;
			auto right_index = right - 1;
			auto is_done = false;

			while (!is_done)
			{
				
				while (list[++left_index] < pivot) {}
				while (pivot < list[--right_index]) {}
				if (left_index < right_index)
				{
					//std::cout << left_index << "  " << right_index << std::endl;
					std::swap(list[left_index], list[right_index]);
				}
				else
				{
					is_done = true;
				}
			}

			// restore the pivot to the correct place.
			std::swap(list[left_index], list[right - 1]);
			quick_sort_first(list, left, left_index - 1);
			quick_sort_first(list, left_index + 1, right);
		}
		else
		{ // our list is too small to quick sort, call the insertion sort. 
			insertion_sort(list, left, right);
		}
	}

	template <typename T>
	void quick_sort_first(std::vector<T> & list)
	{
		quick_sort_first(list, 0, list.size() - 1);
	}
	//Middle element
	template <typename T>
	void quick_sort_middle(std::vector<T> & list, int left, int right)
	{
		if (left + 5 <= right)
		{ // I still have enough elements in the list to quick sort
			const T & pivot = list[(left + right) / 2];
			auto left_index = left;
			auto right_index = right - 1;
			auto is_done = false;
			while (!is_done)
			{
				while (list[++left_index] < pivot) {}
				while (pivot < list[--right_index]) {}
				if (left_index < right_index)
				{
					std::swap(list[left_index], list[right_index]);
				}
				else
				{
					is_done = true;
				}
			}

			// restore the pivot to the correct place.
			std::swap(list[left_index], list[right - 1]);
			quick_sort_middle(list, left, left_index - 1);
			quick_sort_middle(list, left_index + 1, right);
		}
		else
		{ // our list is too small to quick sort, call the insertion sort. 
			insertion_sort(list, left, right);
		}
	}

	template <typename T>
	void quick_sort_middle(std::vector<T> & list)
	{
		quick_sort_middle(list, 0, list.size() - 1);
	}
	//Random element
	template <typename T>
	void quick_sort_random(std::vector<T> & list, int left, int right)
	{
		if (left + 5 <= right)
		{ // I still have enough elements in the list to quick sort
			const T & pivot = list[std::rand() % (right-left) + left];
			auto left_index = left;
			auto right_index = right - 1;
			auto is_done = false;
			while (!is_done)
			{
				while (list[++left_index] < pivot) {}
				while (pivot < list[--right_index]) {}
				if (left_index < right_index)
				{
					std::swap(list[left_index], list[right_index]);
				}
				else
				{
					is_done = true;
				}
			}

			// restore the pivot to the correct place.
			std::swap(list[left_index], list[right - 1]);
			quick_sort_random(list, left, left_index - 1);
			quick_sort_random(list, left_index + 1, right);
		}
		else
		{ // our list is too small to quick sort, call the insertion sort. 
			insertion_sort(list, left, right);
		}
	}

	template <typename T>
	void quick_sort_random(std::vector<T> & list)
	{
		quick_sort_random(list, 0, list.size() - 1);
	}

	//Median of five
	template<typename T>
	const T & median_of_five(std::vector<T> & list, int left, int right)
	{
		auto center = (left + right) / 2;
		auto left_two = center - 1;
		auto right_two = center + 1;
		//if	a1 < a2, #1
		if(list[left]<list[left_two])
		{
			std::swap(list[left], list[left_two]);
		}
		//if	a3	<	a4, #2
		if (list[center] < list[right_two])
		{
			std::swap(list[center], list[right_two]);
		}
		//if	a1	<	a3, swap a1, a3 and swap a2, a4#3
		if (list[left] < list[center])
		{
			std::swap(list[left], list[center]);
			std::swap(list[left_two],list[right_two]);
		}
		//if	a2	<	a5	swap a2, a5#4
		if (list[left_two] < list[right])
		{
			std::swap(list[left_two], list[right]);
		}
		//if	a2	>	a3 //if	#5
		if (list[left_two] < list[center])
		{
			std::swap(list[left_two], list[center]);
		}
		//	if	a3	>	a5		return	a3		//if	#6
		if (list[right] < list[center])
		{
			std::swap(list[right], list[center]);
		}
		else
		{
			return list[right];
		}//	else	return	a5

		//else
		//	if	a2	>	a4		return		a2	//if	#6
		if(list[right_two]<list[left_two])
		{
			return list[left_two];
		}else
		{
			return list[right_two];
		}
		
	}


	template <typename T>
	void quick_sort_median_of_five(std::vector<T> & list, int left, int right)
	{
		if (left + 5 <= right)
		{ // I still have enough elements in the list to quick sort
			const T & pivot = median_of_five(list, left, right);
			auto left_index = left;
			auto right_index = right - 1;
			auto is_done = false;
			while (!is_done)
			{
				while (list[++left_index] < pivot) {}
				while (pivot < list[--right_index]) {}
				if (left_index < right_index)
				{
					std::swap(list[left_index], list[right_index]);
				}
				else
				{
					is_done = true;
				}
			}

			// restore the pivot to the correct place.
			std::swap(list[left_index], list[right - 1]);
			quick_sort_median_of_five(list, left, left_index - 1);
			quick_sort_median_of_five(list, left_index + 1, right);
		}
		else
		{ // our list is too small to quick sort, call the insertion sort. 
			insertion_sort(list, left, right);
		}
	}

	template <typename T>
	void quick_sort_median_of_five(std::vector<T> & list)
	{
		quick_sort_median_of_five(list, 0, list.size() - 1);
	}

	
	//Median of three
	template <typename T>
	const T & median_of_three(std::vector<T> & list, int left, int right)
	{
		auto center = (left + right) / 2;
		if (list[center] < list[left])
		{
			std::swap(list[left], list[center]);
		}

		if (list[right] < list[left])
		{
			std::swap(list[left], list[right]);
		}

		if (list[right] < list[center])
		{
			std::swap(list[center], list[right]);
		}

		// place the pivot at right - 1
		std::swap(list[center], list[right - 1]);
		return list[right - 1];
	}


	template <typename T>
	void quick_sort_median_of_three(std::vector<T> & list, int left, int right)
	{
		if (left + 5 <= right)
		{ // I still have enough elements in the list to quick sort
			const T & pivot = median_of_three(list, left, right);
			auto left_index = left;
			auto right_index = right - 1;
			auto is_done = false;
			while (!is_done)
			{
				while (list[++left_index] < pivot) {}
				while (pivot < list[--right_index]) {}
				if (left_index < right_index)
				{
					std::swap(list[left_index], list[right_index]);
				}
				else
				{
					is_done = true;
				}
			}

			// restore the pivot to the correct place.
			std::swap(list[left_index], list[right - 1]);
			quick_sort_median_of_three(list, left, left_index - 1);
			quick_sort_median_of_three(list, left_index + 1, right);
		}
		else
		{ // our list is too small to quick sort, call the insertion sort. 
			insertion_sort(list, left, right);
		}
	}

	template <typename T>
	void quick_sort_median_of_three(std::vector<T> & list)
	{
		quick_sort_median_of_three(list, 0, list.size() - 1);
	}


}



#endif