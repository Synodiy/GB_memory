/*
	��������� � ��������� � �������� �������, ������������ 32-��������� ����������� ����� �������� uint32_t
	�� ������� ���� ������. ���������� �� ��������� ����� ��� ���� ��� � ������� �������� �� 4 ��������� ���� unsigned char.

	��� ����:
	������������ ���������;
	��������� �������� ���������� ����� ������;
	����������� 32-��������� �������� ������ ���� ���������� �� �������.
*/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <time.h> 
#include <iomanip>

using namespace std;

uint32_t* ConvertTo32(unsigned char* bytes)
{
	uint32_t res = 0;

	for (int i = 0; i < 4; i++)
	{
		res += (uint8_t)bytes[i] << i * 8;
	}

	return &res;
}

int main(int argc, char** args)
{
	srand(time(NULL));

	unsigned char* bytes = new unsigned char[4];

	for (int i = 0; i < 4; i++)
	{
		bytes[i] = rand() % 255;
	}

	cout << "Bytes at start: ";
	for (int i = 0; i < 4; i++)
	{
		cout << "0x" << setw(2) << setfill('0') << uppercase << hex << (int)bytes[3 - i] << "\t";
	}
	cout << endl;

	uint32_t* Result = ConvertTo32(bytes);

	cout << "Result: 0x" << setw(8) << setfill('0') << uppercase << hex << *Result << endl;

	delete(bytes);

	system("Pause");
	return 1;
}