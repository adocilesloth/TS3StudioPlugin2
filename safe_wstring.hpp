/*******************************************
A Docile Sloth 2017 (adocilesloth@gmail.com)
*******************************************/
#pragma once
#include <string>
#include <mutex>

class safe_wstring
{
private:
	std::wstring wstring;
	std::mutex mutex;
public:
	safe_wstring();
	safe_wstring(std::wstring string);

	void operator=(std::wstring string);
	void append(std::wstring string);
	std::wstring string();
};
