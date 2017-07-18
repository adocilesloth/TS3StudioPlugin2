/*******************************************
A Docile Sloth 2017 (adocilesloth@gmail.com)
*******************************************/
#include <obs-frontend-api.h>
#include "TS3_overlay_loop.hpp"
#include "TS3_communication.hpp"
#include "TS3_callout_exports.hpp"
#include "utility.hpp"
#include "safe_vector_wstring.hpp"
#include "safe_vector_bool.hpp"
#include "safe_wstring.hpp"
#include <atomic>
#include <thread>

safe_vector_wstring names;
safe_vector_bool talking;
safe_wstring own_name;
std::atomic<bool> pause(false);
std::thread overlay_thread;

std::vector<std::wstring> get_names()
{
	std::vector<std::wstring> sendnames;
	for(int i = 0; i < names.size(); i++)
	{
		sendnames.push_back(names[i]);
	}
	return sendnames;
}

std::vector<bool> get_talking()
{
	std::vector<bool> sendtalking;
	for(int i = 0; i < talking.size(); i++)
	{
		sendtalking.push_back(talking[i]);
	}
	return sendtalking;
}

std::wstring get_own_name()
{
	std::wstring local_name = own_name.string();
	wReplaceAll(local_name, L"\\s", L" ");
	return local_name;
}

void pause_overlay(bool do_pause)
{
	pause = do_pause;
}

void overlay_loop()
{
	slothSock sock;
	bool discon = false;

	std::string cid;
	std::wstring clientname;
	std::vector<std::wstring> name_list;
	std::vector<bool> talking_list;
	std::vector<std::string> schandlerid;

	while(true)
	{
		while(pause)
		{
			psleep(200);
		}
		//clear vectors
		name_list.clear();
		talking_list.clear();
		schandlerid.clear();

		if(get_TS3_enabled())
		{
			//blog(LOG_WARNING, "connect");
			if(connect(sock, discon) == 0)
			{
				//blog(LOG_WARNING, "authorise");
				if(authorise(sock, discon) == 0)
				{
					if(discon)
					{
						discon = false;
					}
					//Get Channel client list and talking state
					//blog(LOG_WARNING, "get_cid");
					if(get_cid(sock, cid) == 0)
					{
						//blog(LOG_WARNING, "get_channelclientlist");
						get_channelclientlist(sock, cid, name_list, talking_list);
						//names = name_list;
						//talking = talking_list;
					}
					//get own name
					//blog(LOG_WARNING, "get_schandlerid");
					if(get_schandlerid(sock, schandlerid) == 0)
					{
						//blog(LOG_WARNING, "notifyregister");
						if(notifyregister(sock, schandlerid[0]) == 0)
						{
							//blog(LOG_WARNING, "clientname_from_uid");
							clientname_from_uid(sock, clientname);
							own_name = clientname;
						}
					}
				}
				sock.closeConnection();
			}
		}
		names = name_list;
		talking = talking_list;
		psleep(200);
	}
	return;
}

void start_overlay()
{
	overlay_thread = std::thread(overlay_loop);
	return;
}
