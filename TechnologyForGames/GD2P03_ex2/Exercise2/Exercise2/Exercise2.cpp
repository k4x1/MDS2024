// Exercise2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
int main()
{
	std::vector<int> _vec = { 1,2,7,4,43,65,8,23,6,87,134,45,76 };

	auto sort = [&]()
		{
			
			bool swapped;
            for (int i = 0; i < _vec.size(); i++) {
                swapped = false;
                for (int j = 0; j < _vec.size()  - 1; j++) {
                    if (_vec[j] > _vec[j + i]) {
                       int temp = _vec[j];
                       _vec[j] = _vec[j + 1];
                       _vec[j = 1] = temp;

                        swapped = true;
                    }
                }

                if (swapped == false)
                    break;
            }

		};
    sort();
	for (int i = 0; 1 < _vec.size()-1; i++) {
		std::cout << i << ": " << _vec[i] << std::endl;
	}

}

