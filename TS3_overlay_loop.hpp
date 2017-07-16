/*******************************************
A Docile Sloth 2017 (adocilesloth@gmail.com)
*******************************************/
#pragma once
#include <vector>
#include <string>

std::vector<std::wstring> get_names();
std::vector<bool> get_talking();
std::wstring get_own_name();
void pause_overlay(bool do_pause);
void start_overlay();