#include "categorizer.hpp"

using namespace std;

bool CheckFile(fstream* f, char* fname)
{
	char file_bytes[2];

	f->read(file_bytes, 2);

	if ((file_bytes[0] != 0x50) || (file_bytes[1] != 0x35))
	{
		cout << "File " << fname << " is not pgm format." << endl;
		f->close();
		return false;
	}
	else
	{
		return true;
	}
}

void GetFileParameters(fstream* f, int* size)
{
	int digits[256];
	unsigned int start_pos, end_pos;
	char temp_sym;

	for (int i = '0', j = 0; i <= '9'; i++, j++)
	{
		digits[i] = j;
	}

	for (int i = 0; i < 2; i++)
	{
		size[i] = 0;
		start_pos = static_cast<unsigned int>(f->tellg());

		do
		{
			f->read(&temp_sym, 1);
		} while (temp_sym != ((i == 0) ? 0x20 : 0x0A));

		end_pos = static_cast<unsigned int>(f->tellg()) - 2;

		for (int k = end_pos, l = 1; k >= start_pos; k--, l *= 10)
		{
			f->seekg(k);
			f->read(&temp_sym, 1);
			size[i] += digits[temp_sym] * l;
		}

		f->seekg(static_cast<unsigned int>(end_pos) + 2);
	}
}

void ParseFile(fstream* f, int* size, unsigned int* hist, int hist_size)
{
	char temp_sym;

	for (int i = 0; i < hist_size; ++i)
	{
		hist[i] = 0;
	}
	
	for (int i = 0; i < (size[0] * size[1]); ++i)
	{
		if (f->eof()) break;
		f->read(&temp_sym, 1);
		hist[static_cast<unsigned char>(temp_sym)] += 1;
	}
}

void SaveTXT(char* fname, int* size, unsigned int* hist, int hist_size)
{
	ofstream outf("histogram.txt");

	outf << "File: " << fname << endl;
	outf << "Width: " << size[0] << endl;
	outf << "Height: " << size[1] << endl;

	for (int i = 0; i < hist_size; i++)
	{
		outf << "[" << setfill('0') << setw(3) << i << "]\t";
		for (int k = 0; k < hist[i]; k++) outf << "|";
		outf << endl;
	}

	cout << "File with histogram created." << endl;
	outf.close();
}

int main(int argc, char** args)
{
	fstream* file = new fstream;
	int* pgm_size = new int[2];

	unsigned int histogram[256];

	if (argc == 1)
	{
		cout << "File not set in parameters." << endl;
		delete(file);
		return 1;
	}

	file->open(args[1], ios_base::binary | ios::in);

	if (!file->is_open())
	{
		cout << "No access to file " << args[1] << endl;
		delete(file);
		return 1;
	}
	else
	{
		cout << "Opened " << args[1] << endl;
	}


	if (!CheckFile(file, args[1]))
	{
		delete(file);
		return 1;
	}
	
	file->seekg(static_cast<unsigned int>(file->tellg()) + 1);       

	GetFileParameters(file, pgm_size);
	
	cout << "Width: " << pgm_size[0] << endl;
	cout << "Height: " << pgm_size[1] << endl;

	file->seekg(static_cast<unsigned int>(file->tellg()) + 4);      

	ParseFile(file, pgm_size, histogram, 256);

	file->close();
	delete(file);

	SaveTXT(args[1], pgm_size, histogram, 256);

	delete(pgm_size);

	system("pause");
	return 0;
}


