// ex3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

template<typename T> 
T Add(int& val, T arg){
    return arg;
}
template<typename T, typename... Args>
T Add(int& val, T first,  Args... _args) {
    val++;
    std::cout << val << std::endl;
    return (first + Add(val, _args...));
}
float findAvarage() {
    int num = 1;
    float Sum = Add(num, 5, 12, 3, 24, 5, 7, 9);
    return Sum / num;
}
int main()
{
 
    std::cout << findAvarage();
}

