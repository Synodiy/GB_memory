#ifndef CATEGORIZER_HPP
#define CATEGORIZER_HPP

#include <iostream>
#include <fstream>
#include <iomanip>

bool CheckFile(std::fstream* f, char* fname);
void GetFileParameters(std::fstream* f, int* size);
void ParseFile(std::fstream* f, int* size, unsigned int* hist, int hist_size);
void SaveTXT(char* fname, int* size, unsigned int* hist, int hist_size);

#endif
