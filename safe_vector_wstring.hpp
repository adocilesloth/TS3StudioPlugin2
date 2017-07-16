/*******************************************
A Docile Sloth 2017 (adocilesloth@gmail.com)
*******************************************/
#pragma once
#include <mutex>
#include <vector>
#include <string>

class safe_vector_wstring
{
private:
	std::vector<std::wstring> vector_wstring;
	std::mutex mutex;

public:
	safe_vector_wstring();

	void operator=(std::vector<std::wstring>);
	std::wstring operator[](int index);
	size_t size();
	void push_back(std::wstring);
	void clear();
	std::vector<std::wstring> vector();
};
