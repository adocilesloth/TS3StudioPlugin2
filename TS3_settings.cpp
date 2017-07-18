/*******************************************
A Docile Sloth 2017 (adocilesloth@gmail.com)
*******************************************/
#include "TS3_settings.hpp"
#include "TS3_overlay_loop.hpp"
#include "utility.hpp"
#include <vector>
#include <sstream>

#include <obs-module.h>

/*char* set_overlay()
{
	return "A Docile Sloth";
}*/

char* set_overlay(int number_of_names, bool hide_self, bool only_show_speaker,
	int hide_name_after, char* quiet_symbol, char* talk_symbol,
	bool symbol_right_of_speaker)
{
	std::vector<std::wstring> names = get_names();
	if(names.size() == 0)
	{
		blog(LOG_WARNING, "No names");
		return " ";
	}
	
	std::wstringstream overlay;
	std::string overlay_string;

	std::wstring wide_quiet_symbol = s2ws(quiet_symbol);
	std::wstring wide_talk_symbol = s2ws(talk_symbol);
	std::vector<bool> talking = get_talking();
	std::wstring own_name = get_own_name();

	if(names.size() < number_of_names)
	{
		number_of_names = names.size();
	}

	if(!only_show_speaker)
	{
		for(int i = 0; i < number_of_names; i++)
		{
			if(names[i].empty())
			{
				break;
			}
			wReplaceAll(names[i], L"\\s", L" ");
			if(hide_self && names[i] == own_name)
			{
				//do nothing
			}
			else
			{
				std::wstring wsTmp(names[i].begin(), names[i].end());
				if(!symbol_right_of_speaker)
				{
					if(talking[i])
					{
						overlay << wide_talk_symbol << wsTmp << L"\n";
					}
					else
					{
						overlay << wide_quiet_symbol << wsTmp << L"\n";
					}
				}
				else
				{
					if(talking[i])
					{
						overlay << wsTmp << wide_talk_symbol << L"\n";
					}
					else
					{
						overlay << wsTmp << wide_quiet_symbol << L"\n";
					}
				}
			}
		}//end for(int i...
	}
	//Only show talkers
	else
	{
		for(int i = 0; i < number_of_names; i++)
		{
			if(names[i].empty())
			{
				break;
			}
			wReplaceAll(names[i], L"\\s", L" ");
			if(hide_self && names[i] == own_name)
			{
				//do nothing
			}
			else
			{
				std::wstring wsTmp(names[i].begin(), names[i].end());
				if(talking[i])
				{
					overlay << wsTmp << L"\n";
				}//end if(talking[i])
			}
		}//end for(int i...
	}//end Only Show talkers

	if(overlay.str() == L"")
	{
		overlay_string = " ";
	}
	else
	{
		overlay_string = ws2s(overlay.str());
	}
	char *chr = new char[overlay_string.length() + 1];
	std::strcpy(chr, overlay_string.c_str());
	//blog(LOG_WARNING, chr);
	return chr;
}