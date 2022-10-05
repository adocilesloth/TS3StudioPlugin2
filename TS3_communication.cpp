/*******************************************
A Docile Sloth 2017 (adocilesloth@gmail.com)
*******************************************/
#include "TS3_communication.hpp"
#include "TS3_callout_exports.hpp"
#include "utility.hpp"
extern "C"
{
	#include <obs-module.h>
}

int connect(slothSock& sock, bool &discon)
{
	char* adrs = get_address();
	if(!sock.connectToHost(25639, adrs))
	{
		if(!discon)
		{
			blog(LOG_WARNING, "TS3: connect: Check TS3 is running and ClientQuery Plugin is enabled");
			discon = true;
		}
		return 1;
	}
	//discon = false;
	int iResult;
	char reci[260];
	iResult = sock.recvAll(reci, 260, 0);	//get TS3 Client... 181
	if(!iResult)
	{
		blog(LOG_WARNING, "TS3: connect: First Recieve Failure");
		return 2;
	}
	//blog(LOG_WARNING, reci);//--------------------------------------------
	return 0;
}

int authorise(slothSock& sock, bool &discon)
{
	int iResult;

	char* apikey = get_API_key();
	std::string auth = "auth apikey=";
	auth.append(apikey);
	auth.append("\n");
	//blog(LOG_WARNING, "AUTH");
	//blog(LOG_WARNING, auth.c_str());//--------------------------------------------
	iResult = sock.sendAll(auth.c_str(), (int)strlen(auth.c_str()), 0);
	if(!iResult)
	{
		blog(LOG_WARNING, "TS3: authorise: auth Send Failure");
		return 1;
	}
	//char reci[64];
	std::vector<char> reci;
	iResult = sock.recvAll(reci, 64, 0, "msg=");
	if(!iResult)
	{
		blog(LOG_WARNING, "TS3: authorise: auth Recieve Failure");
		return 2;
	}
	//blog(LOG_WARNING, reci);//--------------------------------------------

	//Check the API key was accepted
	std::string tempstr = std::string(reci.data(), reci.size());
	std::string identstart = "id=";
	size_t startpos = tempstr.find(identstart);
	if(startpos == -1)
	{
		if(!discon)	//if initial disconnection
		{
			blog(LOG_WARNING, "TS3: authorise: Invalid API Key Return");
			discon = true;
		}
		return 3;
	}
	else if(tempstr.substr(startpos, 7) == "id=1538")
	{
		if(!discon)	//if initial disconnection
		{
			blog(LOG_WARNING, "TS3: authorise: Invalid API Key");
			discon = true;
		}
		return 4;
	}
	//discon = false;
	return 0;
}

int get_schandlerid(slothSock &sock, std::vector<std::string> &schandlerid)
{
	int iResult;
	const char* schandlerlist = "serverconnectionhandlerlist\n";
	//blog(LOG_WARNING, "SCHANDLERID");
	//blog(LOG_WARNING, schandlerlist);//-----------------------------------
	iResult = sock.sendAll(schandlerlist, (int)strlen(schandlerlist), 0);	//send serverconnectionhandlerlist
	if(!iResult)
	{
		blog(LOG_WARNING, "TS3: get_schandlerid: schandlerlist Send Failure");
		return 1;
	}
	//char reci[256];
	std::vector<char> reci;
	iResult = sock.recvAll(reci, 256, 0, "msg=");	//get serverconnectionhandlerlist
	if(!iResult)
	{
		blog(LOG_WARNING, "TS3: get_schandlerid: schandlerlist Recieve Failure");
		return 2;
	}
	//blog(LOG_WARNING, std::string(reci.data(), reci.size()).c_str());//--------------------------------------------
	schandlerid.clear();
	//Get all schandlerid
	std::string tempstr = std::string(reci.data(), reci.size());
	while(tempstr.size() > 12)
	{
		std::string identstart = "sch";
		size_t startpos = tempstr.find(identstart);
		if(startpos >= 0 && startpos < tempstr.size())
		{
			schandlerid.push_back(tempstr.substr(startpos, 13));
		}
		else
		{
			break;
		}
		tempstr = tempstr.substr(startpos + 13, tempstr.size() - (startpos + 13));
	}

	return 0;
}

int get_cid(slothSock &sock, std::string &cid)
{
	int iResult;
	const char* whoami = "whoami\n";
	//blog(LOG_WARNING, "WHOAMI");
	//blog(LOG_WARNING, whoami);//------------------------------------------
	iResult = sock.sendAll(whoami, (int)strlen(whoami), 0);	//send whoami
	if(!iResult)
	{
		blog(LOG_WARNING, "TS3: get_cid: whoami Send Failure");
		return 1;
	}
	//char reci[64];
	std::vector<char> reci;
	iResult = sock.recvAll(reci, 64, 0, "msg=");	//get whoami
	if(!iResult)
	{
		blog(LOG_WARNING, "TS3: get_cid: whoami Recieve Failure");
		return 2;
	}
	//blog(LOG_WARNING, reci);//-------------------------------------------

	std::string identstart = "cid=";
	std::string identend = "\n";
	cid = std::string(reci.data(), reci.size());
	size_t startpos = cid.find(identstart);
	if(startpos == -1)
	{
		blog(LOG_WARNING, "TS3: get_cid: cid startpos == -1");
		return 3;
	}
	size_t endpos = cid.find(identend);
	if(endpos < 0)
	{
		blog(LOG_WARNING, "TS3: get_cid: cid endpos < 0");
		return 4;
	}
	cid = cid.substr(startpos, endpos - startpos);

	return 0;
}

int get_channelclientlist(slothSock &sock, std::string cid, std::vector<std::wstring> &names, std::vector<bool> &talking)
{
	std::string cllist = "channelclientlist ";
	cllist.append(cid);
	cllist.append(" -voice\n");

	int iResult;
	//blog(LOG_WARNING, "CHANNELCLIENTLIST");
	//blog(LOG_WARNING, cllist.c_str());//-------------------------------------------
	//get channelclientlist
	iResult = sock.sendAll(cllist.c_str(), (int)strlen(cllist.c_str()), 0);	//send channelcli...
	if(!iResult)
	{
		blog(LOG_WARNING, "TS3: get_channelclientlist: channelclientlist Send Failure");
		return 1;
	}
	std::vector<char> reci;
	iResult = sock.recvAll(reci, 22354, 0, "msg=");					//recieve channelcli...
	if(!iResult)
	{
		blog(LOG_WARNING, "TS3: get_channelclientlist: channelclientlist Recieve Failure");
		return 2;
	}

	std::wstring widentstart = L"name=";
	std::wstring widentend = L"client_type";
	std::wstring talkstart = L"client_flag_talking=";
	std::string list = std::string(reci.begin(), reci.end());
	std::wstring wlist = s2ws(list);
	//blog(LOG_WARNING, list.c_str());//------------------------------------

	size_t startpos = 1;
	size_t endpos;
	std::wstring wtempstr;

	names.clear();
	talking.clear();
	while(startpos > 0)
	{
		//get names
		startpos = wlist.find(widentstart);
		if(startpos == -1)
		{
			break;
		}
		endpos = wlist.find(widentend);
		if(endpos < 0)
		{

			break;
		}

		wtempstr = wlist.substr(startpos + 5, endpos - startpos - 6);
		wReplaceAll(wtempstr, L"\\s", L" ");
		names.push_back(wtempstr);

		//get talking
		startpos = wlist.find(talkstart);
		if(startpos == -1)
		{
			talking.push_back(false);
			break;
		}
		else if(wlist.substr(startpos + 20, 1) == L"0")
		{
			talking.push_back(false);
		}
		else if(wlist.substr(startpos + 20, 1) == L"1")
		{
			talking.push_back(true);
		}
		wlist = wlist.substr(startpos + 25);
	}
	return 0;
}

int set_schandlerid(slothSock &sock, std::string schandlerid)
{
	int iResult;
	std::string sendschandlerid = "use " + schandlerid + "\n";
	//blog(LOG_WARNING, "SENDSCHANDLERID");
	//blog(LOG_WARNING, sendschandlerid.c_str());//--------------------------
	iResult = sock.sendAll(sendschandlerid.c_str(), sendschandlerid.size(), 0);	//use schandlerid=i
	if(!iResult)
	{
		blog(LOG_WARNING, "TS3: set_schandlerid: useschandlerid=i Send Failure");
		return 1;
	}
	//char reci[256];
	std::vector<char> reci;
	iResult = sock.recvAll(reci, 256, 0, "msg=");	//recieve result: error id=0...
	if(!iResult)
	{
		blog(LOG_WARNING, "TS3: set_schandlerid: useschandlerid=i Recieve Failure");
		return 2;
	}
	//blog(LOG_WARNING, reci);//--------------------------------------------
	return 0;
}

int notifyregister(slothSock &sock, std::string schandlerid)
{
	int iResult;
	std::string notify = "clientnotifyregister " + schandlerid + " event=notifyclientnamefromuid\n";
	//blog(LOG_WARNING, "NOTIFYREGISTER");
	//blog(LOG_WARNING, notify.c_str());//-------------------------------------
	iResult = sock.sendAll(notify.c_str(), (int)strlen(notify.c_str()), 0);	//request notifyregister...
	if(!iResult)
	{
		blog(LOG_WARNING, "TS3: notifyregister: notifyregister Send Failure");
		return 1;
	}
	//char reci[256];
	std::vector<char> reci;
	iResult = sock.recvAll(reci, 256, 0, "msg=");	//recieve result: error id=0...
	if(!iResult)
	{
		blog(LOG_WARNING, "TS3: notifyregister: notifyregister Recieve Failure");
		return 2;
	}
	//blog(LOG_WARNING, reci);//--------------------------------------------
	return 0;
}

int clientname_from_uid(slothSock &sock, std::wstring &clientname)
{
	int iResult;
	std::string cluid = get_cluid();
	std::string getname = "clientgetnamefromuid cluid=";
	getname.append(cluid);
	getname.append("\n");
	//blog(LOG_WARNING, "NAMEFROMUID");
	//blog(LOG_WARNING, getname.c_str());//--------------------------------------------
	iResult = sock.sendAll(getname.c_str(), (int)strlen(getname.c_str()), 0);	//request clientnamefromuid...
	if(!iResult)
	{
		blog(LOG_WARNING, "TS3: clientname_from_uid: clientnamefromuid Send Failure");
		return 1;
	}
	//char reci[256];
	std::vector<char> reci;
	iResult = sock.recvAll(reci, 256, 0, "msg=");	//recieve name
	if(!iResult)
	{
		blog(LOG_WARNING, "TS3: clientname_from_uid: clientnamefromuid Recieve Failure");
		return 2;
	}
	//blog(LOG_WARNING, reci);//--------------------------------------------
	//get name
	std::wstring identstart = L"name=";
	std::wstring identend = L"\n";
	std::string name = std::string(reci.data(), reci.size());
	std::wstring wname = s2ws(name);

	size_t startpos = wname.find(identstart);	//start of name
	if(startpos == -1)
	{
		blog(LOG_WARNING, "TS3: clientname_from_uid: startpos == -1");
		blog(LOG_WARNING, name.c_str());
		//goto endofif;
		return 3;
	}
	size_t endpos = wname.find(identend);
	if(endpos < startpos)
	{
		blog(LOG_WARNING, "TS3: clientname_from_uid: endpos < startpos");
		blog(LOG_WARNING, name.c_str());
		//goto endofif;
		return 4;
	}
	clientname = wname.substr(startpos + 5, endpos - startpos - 5);
	return 0;
}

int set_clientname(slothSock &sock, std::wstring wname)
{
	std::wstring wnewname = L"clientupdate client_nickname=" + wname + L"\n";
	std::string name = ws2s(wnewname);	//set name to string
	//blog(LOG_WARNING, "UPDATENAME");
	//blog(LOG_WARNING, name.c_str());//--------------------------------------------
	int iResult;
	iResult = sock.sendAll(name.c_str(), (int)strlen(name.c_str()), 0);
	if(!iResult)
	{
		blog(LOG_WARNING, "TS3: set_clientname: clientupdate Send Failure");
		return 1;
	}
	//char reci[256];
	std::vector<char> reci;
	iResult = sock.recvAll(reci, 256, 0, "msg=");
	if(!iResult)
	{
		blog(LOG_WARNING, "TS3: set_clientname: clientupdate Recieve Failure");
		return 2;
	}
	//blog(LOG_WARNING, reci);//--------------------------------------------
	return 0;
}

int set_client_input_muted(slothSock &sock, bool state)
{

	int iResult;
	std::string mute = "clientupdate client_input_muted=";
	if(state)
	{
		mute.append("1\n");
	}
	else
	{
		mute.append("0\n");
	}

	iResult = sock.sendAll(mute.c_str(), (int)strlen(mute.c_str()), 0);	//set mute
	if(!iResult)
	{
		blog(LOG_WARNING, "TS3: set_client_input_muted: Mute Send Failure");
		return 1;
	}
	//psleep(1000);
	//char reci[256];
	std::vector<char> reci;
	iResult = sock.recvAll(reci, 256, 0, "msg=");	//recieve result: error id=0...
	if(!iResult)
	{
		blog(LOG_WARNING, "TS3: set_client_input_muted: Mute Recieve Failure");
		return 2;
	}
	return 0;
}

int set_client_output_muted(slothSock &sock, bool state)
{

	int iResult;
	std::string mute = "clientupdate client_output_muted=";
	if(state)
	{
		mute.append("1\n");
	}
	else
	{
		mute.append("0\n");
	}

	iResult = sock.sendAll(mute.c_str(), (int)strlen(mute.c_str()), 0);	//set mute
	if(!iResult)
	{
		blog(LOG_WARNING, "TS3: set_client_output_muted: Deaf Send Failure");
		return 1;
	}
	//char reci[256];
	std::vector<char> reci;
	iResult = sock.recvAll(reci, 256, 0, "msg=");	//recieve result: error id=0...
	if(!iResult)
	{
		blog(LOG_WARNING, "TS3: set_client_output_muted: Deaf Recieve Failure");
		return 2;
	}
	return 0;
}