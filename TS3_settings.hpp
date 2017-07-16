/*******************************************
A Docile Sloth 2017 (adocilesloth@gmail.com)
*******************************************/
#pragma once

#ifdef __cplusplus
	//extern "C" const char* set_overlay(void);
	extern "C" const char* set_overlay(int number_of_names, bool hide_self,
		bool only_show_speaker, int hide_name_after, char* quiet_symbol,
		char* talk_symbol, bool symbol_right_of_speaker);
#else
	//const char* set_overlay(void);
	const char* set_overlay(int number_of_names, bool hide_self,
		bool only_show_speaker, int hide_name_after, char* quiet_symbol,
		char* talk_symbol, bool symbol_right_of_speaker);
#endif
