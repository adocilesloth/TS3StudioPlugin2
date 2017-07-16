/*******************************************
A Docile Sloth 2017 (adocilesloth@gmail.com)
*******************************************/
#include "safe_vector_bool.hpp"

safe_vector_bool::safe_vector_bool()
{
	return;
}

void safe_vector_bool::operator=(std::vector<bool> new_vector)
{
	mutex.lock();
	vector_bool = new_vector;
	mutex.unlock();
	return;
}

bool safe_vector_bool::operator[](int index)
{
	mutex.lock();
	bool send_bool = vector_bool[index];
	mutex.unlock();
	return send_bool;
}

size_t safe_vector_bool::size()
{
	mutex.lock();
	size_t vector_size = vector_bool.size();
	mutex.unlock();
	return vector_size;
}

void safe_vector_bool::push_back(bool true_false)
{
	mutex.lock();
	vector_bool.push_back(true_false);
	mutex.unlock();
	return;
}

void safe_vector_bool::clear()
{
	mutex.lock();
	vector_bool.clear();
	mutex.unlock();
	return;
}

std::vector<bool> safe_vector_bool::vector()
{
	mutex.lock();
	std::vector<bool> send_vector = vector_bool;
	mutex.unlock();
	return send_vector;
}