/*******************************************
A Docile Sloth 2017 (adocilesloth@gmail.com)
*******************************************/
#pragma once
#include "slothSock.hpp"
#include <vector>
#include <string>

int connect(slothSock& sock, bool &discon);
int authorise(slothSock& sock, bool &discon);
int get_schandlerid(slothSock &sock, std::vector<std::string> &schandlerid);
int get_cid(slothSock &sock, std::string &cid);
int get_channelclientlist(slothSock &sock, std::string cid, std::vector<std::wstring> &names, std::vector<bool> &talking);
int set_schandlerid(slothSock &sock, std::string schandlerid);
int notifyregister(slothSock &sock, std::string schandlerid);
int clientname_from_uid(slothSock &sock, std::wstring &clientname);
int set_clientname(slothSock &sock, std::wstring wname);
int set_client_input_muted(slothSock &sock, bool state);
int set_client_output_muted(slothSock &sock, bool state);

