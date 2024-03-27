/*constexpr std::string CheckName(std::string _name)
{
return _name;
}
int AddValues(int _var1, int _var2)
{
return _var1 + _var2;
}
int main()
{
constexpr int yearsToAdd;
yearsToAdd = 5;
constexpr int sumAge = AddValues(yearsToAdd, 17);
std::string checkedName = CheckName("John");
std::cout << checkedName << " is " << sumAge << " years old.";
}*/
//old code


#include <iostream>

constexpr const char* CheckName(const char* _name)
{
	return _name;
}
constexpr int AddValues(int _var1, int _var2)
{
	return _var1 + _var2;
}
int main()
{

	constexpr int yearsToAdd = 5;
	constexpr int sumAge = AddValues(yearsToAdd, 17);
	std::string checkedName = CheckName("John");
	std::cout << checkedName << " is " << sumAge << " years old.";
}