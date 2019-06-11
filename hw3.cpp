/*
	Составить программу, выводящую на экран текущую среду сборки (Windows/Linux),
	дату и время последней успешной сборки.
	Использовать константу TIME для вывода времени.
*/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using namespace std;

int main(int argc, char** args)
{
#ifdef _WIN64
	cout << "Windows x64 detected" << endl;
#endif

#ifdef _WIN32
	cout << "Windows x32 detected" << endl;
#endif

#ifdef __linux__
	cout << "Linux detected" << endl;
#endif

#ifdef __cplusplus
	cout << "C++ language" << endl;
#endif

#ifdef __STDC__
	cout << "C language" << endl;
#endif

	cout << "Program builded on " << __DATE__ << " at " << __TIME__ << endl;

	system("Pause");
	return 1;
}