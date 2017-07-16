/*******************************************
A Docile Sloth 2017 (adocilesloth@gmail.com)
*******************************************/
#pragma once
#include <string>

int countSubstring(const std::string& str, const std::string& sub);
int wcountSubstring(const std::wstring& str, const std::wstring& sub);
void ReplaceAll(std::string &str, const std::string& from, const std::string& to);
void wReplaceAll(std::wstring &str, const std::wstring& from, const std::wstring& to);
std::wstring s2ws(const std::string& str);
std::string ws2s(const std::wstring& wstr);
void psleep(unsigned milliseconds);
