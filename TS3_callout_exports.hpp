#pragma once
/*******************************************
A Docile Sloth 2017 (adocilesloth@gmail.com)
*******************************************/
#include <obs-module.h>

bool get_TS3_enabled();
char* get_address();
char* get_API_key();
char* get_cluid();
char* get_fix();
bool get_fix_as_prefix();
bool get_do_mute();
bool get_do_deaf();
bool get_change_every_server();
void TS3_callout_init();
void TS3_callout_free();