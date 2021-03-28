#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>

// Реализуйте этот макрос так, чтобы функция main компилировалась

#define UNIQ_ID_IMPL_2(lineno) _a_local_var_##lineno
#define UNIQ_ID_IMPL(lineno) UNIQ_ID_IMPL_2(lineno)
#define UNIQ_ID UNIQ_ID_IMPL(__COUNTER__)

int main() 
{
	int UNIQ_ID = 0;
	std::string UNIQ_ID = "hello";
	std::vector<std::string> UNIQ_ID = { "hello", "world" };
	std::vector<int> UNIQ_ID = { 1, 2, 3, 4 };

	return 0;
}