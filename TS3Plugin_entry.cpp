/*******************************************
A Docile Sloth 2017 (adocilesloth@gmail.com)
*******************************************/
extern "C"
{
	#include <obs-frontend-api.h>
	#include <obs-module.h>
	#include <obs.h>
	#include "TS3_source_settings.h"
};
#include "TS3_overlay_loop.hpp"
#include "TS3_start-stop.hpp"
#include "TS3_callout_exports.hpp"

OBS_DECLARE_MODULE()
OBS_MODULE_USE_DEFAULT_LOCALE("TS3Plugin", "en-US")

static struct obs_source_info ts3_plugin_info = getInfo();

bool obs_module_load(void)
{
	obs_frontend_add_event_callback(ts3_callback, NULL);
	TS3_callout_init();
	start_overlay();
	obs_register_source(&ts3_plugin_info);
	return true;
}

void obs_module_unload(void)
{
	TS3_callout_free();
	return;
}

const char *obs_module_author(void)
{
	return "A Docile Sloth";
}

const char *obs_module_name(void)
{
	return "TeamSpeak 3 Plugin";
}

const char *obs_module_description(void)
{
	return "Adds an overlay for TeamSpeak 3";
}