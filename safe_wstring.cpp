/*******************************************
A Docile Sloth 2017 (adocilesloth@gmail.com)
*******************************************/
#include "safe_wstring.hpp"

safe_wstring::safe_wstring()
{
	return;
}

safe_wstring::safe_wstring(std::wstring string)
{
	mutex.lock();
	wstring = string;
	mutex.unlock();
	return;
}

void safe_wstring::operator=(std::wstring string)
{
	mutex.lock();
	wstring = string;
	mutex.unlock();
	return;
}

void safe_wstring::append(std::wstring string)
{
	mutex.lock();
	wstring.append(string);
	mutex.unlock();
}

std::wstring safe_wstring::string()
{
	mutex.lock();
	std::wstring send_wstring = wstring;
	mutex.unlock();
	return send_wstring;
}