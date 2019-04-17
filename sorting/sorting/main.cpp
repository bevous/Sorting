
#include <iostream>
#include <chrono>
#include <vector>
#include <fstream>
#include <string>
#include "sort.h"



void log_run_times(std::string times)
{
	std::ofstream data_log;
	data_log.open("time_log.csv", std::ofstream::app);

	data_log << times;
	data_log << std::endl;

	data_log.close();
}


int main()
{
	int start_time = 0;
	int end_time = 0;
	std::vector<int> data_set;
	const int increment[] = { 50000,100000};
	const int change_at = 1000000;
	const int stop_at = 2000000;
	int index = 0;
	std::string sizes = ",";
	std::string Insertion_Sort = "Insertion_Sort,";
	std::string Shell_Sort = "Shell_Sort,";
	std::string Median_Of_Three="Quick_Sort_Median_Of_Three,";
	std::string First_element = "First_element";
	std::string Middle_element = "Middle_element";
	std::string Random_element = "Random_element";
	std::string Median_of_five = "Median_of_five";

	std::string Merge_Sort="Merge_Sort,";
	std::string Radix_Sort="Radix_Sort,";

	//nwacc::fill_vector(data_set,50000);
	//nwacc::quick_sort_first(data_set);
	////nwacc::print(data_set);

	for (auto number_or_elements = increment[0]; number_or_elements <= stop_at; number_or_elements += increment[index])
	{
		if(number_or_elements == change_at)
		{
			index++;
		}
		else
		{
			std::cout << number_or_elements << std::endl;
			sizes += std::to_string(number_or_elements);
			//  a. Insertion Sort
			if (number_or_elements <= 300000) {
				std::cout << "insertion sort time = ";
				data_set.clear();
				nwacc::fill_vector(data_set, number_or_elements);
				start_time = std::chrono::system_clock::now().time_since_epoch().count();
				nwacc::insertion_sort(data_set);
				end_time = std::chrono::system_clock::now().time_since_epoch().count();
				Insertion_Sort += std::to_string((end_time - start_time)) + ",";
				std::cout << (end_time - start_time) << std::endl;
			}else
			{
				Insertion_Sort += ",";
			}

			//	b. Shell Sort
			if (number_or_elements <= 600000) {
				std::cout << "shell sort time = ";
				data_set.clear();
				nwacc::fill_vector(data_set, number_or_elements);
				start_time = std::chrono::system_clock::now().time_since_epoch().count();
				nwacc::shell_sort(data_set);
				end_time = std::chrono::system_clock::now().time_since_epoch().count();
				Shell_Sort += std::to_string((end_time - start_time)) + ",";
				std::cout << (end_time - start_time) << std::endl;
			}else
			{
				Shell_Sort += ",";
			}

			//quick sort middle
			std::cout << "middle quick sort time = ";
			data_set.clear();
			nwacc::fill_vector(data_set, number_or_elements);
			start_time = std::chrono::system_clock::now().time_since_epoch().count();
			nwacc::quick_sort_middle(data_set);
			end_time = std::chrono::system_clock::now().time_since_epoch().count();
			Middle_element += std::to_string((end_time - start_time)) + ",";
			std::cout << (end_time - start_time) << std::endl;

			//quick sort first
			std::cout << "first quick sort time = "<<std::endl;
			data_set.clear();
			nwacc::fill_vector(data_set, number_or_elements);
			start_time = std::chrono::system_clock::now().time_since_epoch().count();
			nwacc::quick_sort_first(data_set);
			end_time = std::chrono::system_clock::now().time_since_epoch().count();
			First_element += std::to_string((end_time - start_time)) + ",";
			std::cout << (end_time - start_time) << std::endl;

			//quick sort random
			std::cout << "random quick sort time = ";
			data_set.clear();
			nwacc::fill_vector(data_set, number_or_elements);
			start_time = std::chrono::system_clock::now().time_since_epoch().count();
			nwacc::quick_sort_random(data_set);
			end_time = std::chrono::system_clock::now().time_since_epoch().count();
			Random_element += std::to_string((end_time - start_time)) + ",";
			std::cout << (end_time - start_time) << std::endl;

			//	c. Quick Sort median of 3 (all 5 versions)
			std::cout << "median of three quick sort time = ";
			data_set.clear();
			nwacc::fill_vector(data_set, number_or_elements);
			start_time = std::chrono::system_clock::now().time_since_epoch().count();
			nwacc::quick_sort_median_of_three(data_set);
			end_time = std::chrono::system_clock::now().time_since_epoch().count();
			Median_Of_Three += std::to_string((end_time - start_time)) + ",";
			std::cout << (end_time - start_time) << std::endl;

			// quick sort median of 5
			std::cout << "median of five quick sort time = ";
			data_set.clear();
			nwacc::fill_vector(data_set, number_or_elements);
			start_time = std::chrono::system_clock::now().time_since_epoch().count();
			nwacc::quick_sort_median_of_five(data_set);
			end_time = std::chrono::system_clock::now().time_since_epoch().count();
			Median_of_five += std::to_string((end_time - start_time)) + ",";
			 std::cout << (end_time - start_time) << std::endl;


			//	d. Merge Sort
			std::cout << "merge sort time = ";
			data_set.clear();
			nwacc::fill_vector(data_set, number_or_elements);
			start_time = std::chrono::system_clock::now().time_since_epoch().count();
			nwacc::merge_sort(data_set);
			end_time = std::chrono::system_clock::now().time_since_epoch().count();
			Merge_Sort += std::to_string((end_time - start_time)) + ",";
			std::cout << (end_time - start_time) << std::endl;

			//	e. Radix Sort
			std::cout << "merge sort time = ";
			data_set.clear();
			nwacc::fill_vector(data_set, number_or_elements);
			start_time = std::chrono::system_clock::now().time_since_epoch().count();
			auto max = nwacc::max(data_set);
			auto max_size = nwacc::size(max);
			nwacc::radix_sort(data_set, max_size);
			end_time = std::chrono::system_clock::now().time_since_epoch().count();
			Radix_Sort += std::to_string((end_time - start_time)) + ",";
			std::cout << (end_time - start_time) << std::endl;
		}
	}
	log_run_times(Insertion_Sort);
	log_run_times(Shell_Sort);
	log_run_times(Median_Of_Three);
	log_run_times(Median_of_five);
	log_run_times(First_element);
	log_run_times(Middle_element);
	log_run_times(Random_element);
	log_run_times(Merge_Sort);
	//log_run_times(Radix_Sort);
	return 0;
}