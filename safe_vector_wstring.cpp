/*******************************************
A Docile Sloth 2017 (adocilesloth@gmail.com)
*******************************************/
#include "safe_vector_wstring.hpp"

safe_vector_wstring::safe_vector_wstring()
{
	return;
}

void safe_vector_wstring::operator=(std::vector<std::wstring> new_vector)
{
	mutex.lock();
	vector_wstring = new_vector;
	mutex.unlock();
	return;
}

std::wstring safe_vector_wstring::operator[](int index)
{
	mutex.lock();
	std::wstring send_wstring = vector_wstring[index];
	mutex.unlock();
	return send_wstring;
}

size_t safe_vector_wstring::size()
{
	mutex.lock();
	size_t vector_size = vector_wstring.size();
	mutex.unlock();
	return vector_size;
}

void safe_vector_wstring::push_back(std::wstring wstring)
{
	mutex.lock();
	vector_wstring.push_back(wstring);
	mutex.unlock();
	return;
}

void safe_vector_wstring::clear()
{
	mutex.lock();
	vector_wstring.clear();
	mutex.unlock();
	return;
}

std::vector<std::wstring> safe_vector_wstring::vector()
{
	mutex.lock();
	std::vector<std::wstring> send_vector = vector_wstring;
	mutex.unlock();
	return send_vector;
}