/*******************************************
A Docile Sloth 2017 (adocilesloth@gmail.com)
*******************************************/
#include "TS3_communication.hpp"
#include "TS3_callout_exports.hpp"
#include "utility.hpp"
extern "C"
{
	#include <obs-frontend-api.h>
}

bool update_ts3_name(bool add_fix)
{
	std::string fix = get_fix();
	if(fix == "" || !get_TS3_enabled())
	{
		return true;
	}

	slothSock sock;
	bool discon;

	//connect
	if(connect(sock, discon) != 0)
	{
		return false;
	}
	//authorise
	if(authorise(sock, discon) != 0)
	{
		sock.closeConnection();
		return false;
	}
	//get schandlerid
	std::vector<std::string> schandlerid;
	if(get_schandlerid(sock, schandlerid) != 0)
	{
		sock.closeConnection();
		return false;
	}

	int num_server;
	bool every_server = get_change_every_server();
	std::wstring wfix = s2ws(fix);
	bool fix_as_prefix = get_fix_as_prefix();
	std::wstring clientname;
	std::wstring newname;
	if(every_server)
	{
		num_server = schandlerid.size();
	}
	else
	{
		num_server = 1;
	}
	for(int i = 0; i < num_server; i++)
	{
		if(set_schandlerid(sock, schandlerid[i]) == 0)
		{
			if(notifyregister(sock, schandlerid[i]) == 0)
			{
				if(clientname_from_uid(sock, clientname) == 0)
				{
					if(add_fix)
					{
						if(fix_as_prefix)
						{
							if(clientname.substr(0, wfix.size()) != wfix)
							{
								newname = wfix + clientname;
							}
							else
							{
								newname = clientname;
							}
						}
						else
						{
							if(clientname.substr(clientname.size() - wfix.size(), wfix.size()) != wfix)
							{
								newname = clientname + wfix;
							}
							else
							{
								newname = clientname;
							}
						}
					}
					else
					{
						if(fix_as_prefix)
						{
							if(clientname.substr(0, wfix.size()) == wfix)
							{
								newname = clientname.substr(wfix.size(), clientname.size() - wfix.size());
							}
							else
							{
								newname = clientname;
							}
						}
						else
						{
							if(clientname.substr(clientname.size() - wfix.size(), wfix.size()) == wfix)
							{
								newname = clientname.substr(0, clientname.size() - wfix.size());
							}
							else
							{
								newname = clientname;
							}
						}
					}
					set_clientname(sock, newname);
				}
			}
		}
	}
	set_schandlerid(sock, schandlerid[0]);
	sock.closeConnection();

	return true;
}

bool set_mutedeaf_state(bool state)
{
	bool do_mute = get_do_mute();
	bool do_deaf = get_do_deaf();
	if((!do_mute && !do_deaf) || !get_TS3_enabled())
	{
		return true;
	}

	slothSock sock;
	bool discon;

	//connect
	if(connect(sock, discon) != 0)
	{
		return false;
	}
	//authorise
	if(authorise(sock, discon) != 0)
	{
		sock.closeConnection();
		return false;
	}
	//get schandlerid
	std::vector<std::string> schandlerid;
	if(get_schandlerid(sock, schandlerid) != 0)
	{
		sock.closeConnection();
		return false;
	}

	int num_server;
	bool every_server = get_change_every_server();
	if(every_server)
	{
		num_server = schandlerid.size();
	}
	else
	{
		num_server = 1;
	}
	for(int i = 0; i < num_server; i++)
	{
		if(set_schandlerid(sock, schandlerid[i]) == 0)
		{
			if(do_mute)
			{
				set_client_input_muted(sock, state);
			}
			if(do_deaf)
			{
				set_client_output_muted(sock, state);
			}
		}
	}
	set_schandlerid(sock, schandlerid[0]);
	sock.closeConnection();

	return true;
}

void ts3_callback(enum obs_frontend_event event, void *data)
{
	UNUSED_PARAMETER(data);

	if(event == OBS_FRONTEND_EVENT_STREAMING_STARTED || event == OBS_FRONTEND_EVENT_RECORDING_STARTED)
	{
		update_ts3_name(true);
		set_mutedeaf_state(true);
	}
	else if(event == OBS_FRONTEND_EVENT_STREAMING_STOPPED || event == OBS_FRONTEND_EVENT_RECORDING_STOPPED)
	{
		update_ts3_name(false);
		set_mutedeaf_state(false);
	}
}