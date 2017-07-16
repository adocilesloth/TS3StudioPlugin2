/*******************************************
A Docile Sloth 2017 (adocilesloth@gmail.com)
*******************************************/
#include "TS3_callout_exports.hpp"
#include "TS3_callout.hpp"
#include "TS3_overlay_loop.hpp"
#include <obs-frontend-api.h>
#include <QMainWindow>
#include <QMessageBox>
#include <QAction>

TS3Callout *co;

bool get_TS3_enabled()
{
	return co->ui->enableCheck->isChecked();
	//return true;
}

char* get_address()
{
	std::string str = co->ui->ipadrsLineEdit->text().toStdString();
	char *chr = new char[str.length() + 1];
	std::strcpy(chr, str.c_str());
	return chr;
	//return "127.0.0.1";
}

char* get_API_key()
{
	std::string str = co->ui->apikeyLineEdit->text().toStdString();
	char *chr = new char[str.length() + 1];
	std::strcpy(chr, str.c_str());
	return chr;
	//return "26HD-9MV0-BNTX-IX0D-0M7F-GMMJ";
}

char* get_cluid()
{
	std::string str = co->ui->cluidLineEdit->text().toStdString();
	char *chr = new char[str.length() + 1];
	std::strcpy(chr, str.c_str());
	return chr;
	//return "9KzgOxf/cQ7JiOgeGiMfnw7BWYM=";
}

char* get_fix()
{
	std::string str = co->ui->fixLineEdit->text().toStdString();
	char *chr = new char[str.length() + 1];
	std::strcpy(chr, str.c_str());
	return chr;
	//return "*R*";
}

bool get_fix_as_prefix()
{
	return co->ui->prefixRadio->isChecked();
	//return true;
}

bool get_do_mute()
{
	return co->ui->muteCheck->isChecked();
	//return false;
}

bool get_do_deaf()
{
	return co->ui->deafCheck->isChecked();
	//return false;
}

bool get_change_every_server()
{
	return co->ui->serversCheck->isChecked();
	//return false;
}

static void save_TS3_callout(obs_data_t *save_data, bool saving, void *)
{
	if(saving)
	{
		obs_data_t *obj = obs_data_create();
		QString qstr;
		std::string str;

		obs_data_set_bool(obj, "Enable", co->ui->enableCheck->isChecked());
		qstr = co->ui->ipadrsLineEdit->text();
		str = qstr.toStdString();
		obs_data_set_string(obj, "IPV4", str.c_str());
		qstr = co->ui->apikeyLineEdit->text();
		str = qstr.toStdString();
		obs_data_set_string(obj, "APIKey", str.c_str());
		qstr = co->ui->cluidLineEdit->text();
		str = qstr.toStdString();
		obs_data_set_string(obj, "UniqueID", str.c_str());
		
		qstr = co->ui->fixLineEdit->text();
		str = qstr.toStdString();
		obs_data_set_string(obj, "Modifier", str.c_str());
		obs_data_set_bool(obj, "Prefix", co->ui->prefixRadio->isChecked());
		obs_data_set_bool(obj, "Mute", co->ui->muteCheck->isChecked());
		obs_data_set_bool(obj, "Deaf", co->ui->deafCheck->isChecked());
		obs_data_set_bool(obj, "AllServers", co->ui->serversCheck->isChecked());

		obs_data_set_obj(save_data, "TS3Callout", obj);
		
		obs_data_release(obj);
	}
	else
	{
		obs_data_t *obj = obs_data_get_obj(save_data, "TS3Callout");
		QString qstr;
		if(!obj)
		{
			obj = obs_data_create();
		}
		co->ui->enableCheck->setChecked(obs_data_get_bool(obj, "Enable"));
		qstr = QString::fromLocal8Bit(obs_data_get_string(obj, "IPV4"));
		co->ui->ipadrsLineEdit->setText(qstr);
		qstr = QString::fromLocal8Bit(obs_data_get_string(obj, "APIKey"));
		co->ui->apikeyLineEdit->setText(qstr);
		qstr = QString::fromLocal8Bit(obs_data_get_string(obj, "UniqueID"));
		co->ui->cluidLineEdit->setText(qstr);
		
		qstr = QString::fromLocal8Bit(obs_data_get_string(obj, "Modifier"));
		co->ui->fixLineEdit->setText(qstr);
		co->ui->prefixRadio->setChecked(obs_data_get_bool(obj, "Prefix"));
		co->ui->suffixRadio->setChecked(!obs_data_get_bool(obj, "Prefix"));
		co->ui->muteCheck->setChecked(obs_data_get_bool(obj, "Mute"));
		co->ui->deafCheck->setChecked(obs_data_get_bool(obj, "Deaf"));
		co->ui->serversCheck->setChecked(obs_data_get_bool(obj, "AllServers"));
		
		obs_data_release(obj);
	}
}

TS3Callout::TS3Callout(QWidget *parent)
	: QDialog(parent),
	ui(new Ui_TS3Callout)
{
	ui->setupUi(this);

	QObject::connect(ui->apikeyButton, SIGNAL(clicked()),
		this, SLOT(toggle_APIKey()));
	QObject::connect(ui->cluidButton, SIGNAL(clicked()),
		this, SLOT(toggle_cluid()));
	QObject::connect(ui->closeButton->button(QDialogButtonBox::Close),
		SIGNAL(clicked()), this, SLOT(hide()));

}

void TS3Callout::toggle_APIKey()
{
	blog(LOG_WARNING, "toggle_APIKey()");
	if(co->ui->apikeyLineEdit->echoMode() == QLineEdit::Password)
	{
		co->ui->apikeyLineEdit->setEchoMode(QLineEdit::Normal);
		co->ui->apikeyButton->setText(QApplication::translate("TS3Callout", "Hide", Q_NULLPTR));
	}
	else
	{
		co->ui->apikeyLineEdit->setEchoMode(QLineEdit::Password);
		co->ui->apikeyButton->setText(QApplication::translate("TS3Callout", "Show", Q_NULLPTR));
	}
}

void TS3Callout::toggle_cluid()
{
	if(co->ui->cluidLineEdit->echoMode() == QLineEdit::Password)
	{
		co->ui->cluidLineEdit->setEchoMode(QLineEdit::Normal);
		co->ui->cluidButton->setText(QApplication::translate("TS3Callout", "Hide", Q_NULLPTR));
	}
	else
	{
		co->ui->cluidLineEdit->setEchoMode(QLineEdit::Password);
		co->ui->cluidButton->setText(QApplication::translate("TS3Callout", "Show", Q_NULLPTR));
	}
}

void TS3Callout::ShowHideDialog()
{
	if(!isVisible())
	{
		setVisible(true);
		pause_overlay(true);
		//QTimer::singleShot(250, this, SLOT(show()));
	}
	else
	{
		setVisible(false);
		pause_overlay(false);
		//QTimer::singleShot(250, this, SLOT(hide()));
	}
}

void TS3Callout::closeEvent(QCloseEvent* event)
{
	obs_frontend_save();
}

static void TS3_callout_event(enum obs_frontend_event event, void *)
{
	if(event == OBS_FRONTEND_EVENT_EXIT)
	{
		obs_frontend_save();
	}
}

void TS3_callout_init()
{
	blog(LOG_WARNING, "TS3_callout_init");
	QAction *action = (QAction*)obs_frontend_add_tools_menu_qaction(
		obs_module_text("TS3Callout"));
	blog(LOG_WARNING, "push translations");
	obs_frontend_push_ui_translation(obs_module_get_string);

	QMainWindow *window = (QMainWindow*)obs_frontend_get_main_window();

	co = new TS3Callout(window);

	auto cb = []()
	{
		co->ShowHideDialog();
	};

	obs_frontend_pop_ui_translation();

	obs_frontend_add_event_callback(TS3_callout_event, nullptr);
	obs_frontend_add_save_callback(save_TS3_callout, nullptr);

	action->connect(action, &QAction::triggered, cb);
}

void TS3_callout_free()
{
	//delete co;
	//co = nullptr;
}