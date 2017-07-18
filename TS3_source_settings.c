/*******************************************
A Docile Sloth 2017 (adocilesloth@gmail.com)
*******************************************/
#include <obs-module.h>
#include <obs-internal.h>
#include "TS3_source_settings.h"
#include "TS3_settings.hpp"

int number_of_names;
bool hide_self;
bool only_show_speaker;
int hide_name_after;
char* quiet_symbol;
char* talk_symbol;
bool symbol_right_of_speaker;

int frame_counter = 0;

static const char *ts3_plugin_get_name(void *unused)
{
	UNUSED_PARAMETER(unused);
	return obs_module_text("TeamSpeak 3 Overlay");
}

static void *ts3_plugin_create(obs_data_t *settings, obs_source_t *source)
{
	struct ts3_overlay *overlay = bzalloc(sizeof(struct ts3_overlay));
	overlay->source = source;

	const char *text_source_id = "text_ft2_source\0";
	overlay->textSource = obs_source_create(text_source_id, text_source_id, settings, NULL);

	obs_source_add_active_child(overlay->source, overlay->textSource);

	obs_properties_t *props = obs_source_properties(overlay->textSource);

	//TS3 Overlay
	obs_properties_add_int(props, "num_name",
		obs_module_text("NamesToShow"), 0, 100, 1);
	obs_data_set_default_int(overlay->textSource, "num_name", 10);

	obs_properties_add_bool(props, "speaking_only",
		obs_module_text("OnlyShowSpeakers"));

	obs_properties_add_int(props, "hide_after",
		obs_module_text("HideAfter"), 0, 2000, 1);

	obs_properties_add_bool(props, "no_self",
		obs_module_text("HideOwnName"));

	obs_properties_add_text(props, "quiet_symbol",
		obs_module_text("QuietSymbol"), OBS_TEXT_DEFAULT);
	obs_data_set_default_string(overlay->textSource, "quiet_symbol", "\xE2\x97\x8B"); //\u25CB ○ \xE2\x97\x8B

	obs_properties_add_text(props, "talk_symbol",
		obs_module_text("TalkSymbol"), OBS_TEXT_DEFAULT);
	obs_data_set_default_string(overlay->textSource, "talk_symbol", "\xE2\x97\x8F");	//\u25CF ● \xE2\x97\x8F

	obs_properties_add_bool(props, "right_of_name",
		obs_module_text("SymbolRightOfNames"));

	return overlay;
}

static void ts3_plugin_destroy(void *data)
{
	struct ts3_overlay *overlay = data;

	obs_source_remove(overlay->textSource);
	obs_source_release(overlay->textSource);
	overlay->textSource = NULL;
	bfree(overlay->textSource);
	overlay = NULL;
	bfree(overlay);
}

static void ts3_plugin_update(void *data, obs_data_t *settings)
{
	struct ts3_overlay *overlay = data;
	obs_source_update(overlay->textSource, settings);

	obs_data_set_bool(overlay->textSource, "from_file", false);
}

static uint32_t ts3_plugin_get_width(void *data)
{
	struct ts3_overlay *overlay = data;
	return obs_source_get_width(overlay->textSource);
}

static uint32_t ts3_plugin_get_height(void *data)
{
	struct ts3_overlay *overlay = data;
	return obs_source_get_height(overlay->textSource);
}

static void ts3_plugin_render(void *data, gs_effect_t *effect)
{
	//blog(LOG_WARNING, "ts3_plugin_render");
	struct ts3_overlay *overlay = data;

	obs_source_video_render(overlay->textSource);
}

static void ts3_plugin_video_tick(void *data, float seconds)
{
	struct ts3_overlay *overlay = data;

	if(!obs_source_showing(overlay->source))
	{
		return;
	}
	frame_counter += 1;

	if(frame_counter == 3)	//update every three frames
	{
		//Create namelist
		number_of_names = obs_data_get_int(overlay->textSource, "num_name");
		hide_self = obs_data_get_bool(overlay->textSource, "no_self");
		only_show_speaker = obs_data_get_bool(overlay->textSource, "speaking_only");
		hide_name_after = obs_data_get_int(overlay->textSource, "hide_after");
		quiet_symbol = obs_data_get_string(overlay->textSource, "quiet_symbol");
		talk_symbol = obs_data_get_string(overlay->textSource, "talk_symbol");
		symbol_right_of_speaker = obs_data_get_bool(overlay->textSource, "right_of_name");
		
		char* name_list = set_overlay(number_of_names, hide_self,
			only_show_speaker, hide_name_after, quiet_symbol,
			talk_symbol, symbol_right_of_speaker);
		
		//blog(LOG_WARNING, name_list);
		obs_data_set_string(overlay->textSource->context.settings, "text", name_list);
		frame_counter = 0;
	}

	obs_source_update(overlay->textSource, overlay->textSource->context.settings);
}

static obs_properties_t *ts3_plugin_properties(void *data)
{
	blog(LOG_WARNING, "ts3_plugin_properties");
	struct ts3_overlay *overlay = data;

	obs_properties_t *props = obs_source_properties(overlay->textSource);

	//TS3 Overlay
	obs_properties_add_int(props, "num_name",
		obs_module_text("NamesToShow"), 0, 100, 1);
	obs_data_set_default_int(overlay->textSource, "num_name", 10);

	obs_properties_add_bool(props, "speaking_only",
		obs_module_text("OnlyShowSpeakers"));

	obs_properties_add_int(props, "hide_after",
		obs_module_text("HideAfter"), 0, 2000, 1);

	obs_properties_add_bool(props, "no_self",
		obs_module_text("HideOwnName"));

	obs_properties_add_text(props, "quiet_symbol",
		obs_module_text("QuietSymbol"), OBS_TEXT_DEFAULT);
	obs_data_set_default_string(overlay->textSource, "quiet_symbol", "\xE2\x97\x8B");	//\u25CB ○ \xE2\x97\x8B

	obs_properties_add_text(props, "talk_symbol",
		obs_module_text("TalkSymbol"), OBS_TEXT_DEFAULT);
	obs_data_set_default_string(overlay->textSource, "talk_symbol", "\xE2\x97\x8F");	//\u25CF ● \xE2\x97\x8F

	obs_properties_add_bool(props, "right_of_name",
		obs_module_text("SymbolRightOfNames"));

	return props;
}

void enum_active_sources(void *data, obs_source_enum_proc_t enum_callback, void *param) {
	struct ts3_overlay *context = data;

	enum_callback(context->source, context->textSource, param);
}

struct obs_source_info getInfo()
{
	struct obs_source_info ts3_plugin_info = {
		.id = "ts3plugin",
		.type = OBS_SOURCE_TYPE_INPUT,
		.output_flags = OBS_SOURCE_VIDEO,
		.get_name = ts3_plugin_get_name,
		.create = ts3_plugin_create,
		.destroy = ts3_plugin_destroy,
		.update = ts3_plugin_update,
		.get_width = ts3_plugin_get_width,
		.get_height = ts3_plugin_get_height,
		.video_render = ts3_plugin_render,
		.video_tick = ts3_plugin_video_tick,
		.get_properties = ts3_plugin_properties,
		.enum_active_sources = enum_active_sources
	};
	return ts3_plugin_info;
}