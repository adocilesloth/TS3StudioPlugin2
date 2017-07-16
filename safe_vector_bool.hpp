/*******************************************
A Docile Sloth 2017 (adocilesloth@gmail.com)
*******************************************/
#pragma once
#include <mutex>
#include <vector>

class safe_vector_bool
{
private:
	std::mutex mutex;
	std::vector<bool> vector_bool;

public:
	safe_vector_bool();

	void operator=(std::vector<bool> new_vector);
	bool operator[](int index);
	size_t size();
	void push_back(bool);
	void clear();
	std::vector<bool> vector();
};
