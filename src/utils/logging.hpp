#pragma once

#include <iostream>
#include <iomanip>

namespace bork 
{
	template<typename T>
	void print_2darray(T *arr, int m, int n)
	{
		std::cout.setf(std::ios::fixed | std::ios::showpos);

		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				std::cout << "| " << std::setw(4) << *(arr + (i * n) + j) << " | ";
			}
			std::cout << "\n";
		}
		std::cout << std::endl;
		std::cout.unsetf(std::ios::fixed | std::ios::showpos);
	}


}
