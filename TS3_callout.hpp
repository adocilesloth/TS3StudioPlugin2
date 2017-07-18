/*******************************************
A Docile Sloth 2017 (adocilesloth@gmail.com)
*******************************************/
#pragma once
#include <QDialog>
#include <memory>

#include "ui_TS3_callout.h"

class QCloseEvent;

class TS3Callout : public QDialog {
	Q_OBJECT

public:
	std::unique_ptr<Ui_TS3Callout> ui;
	TS3Callout(QWidget *parent);

	void closeEvent(QCloseEvent *event) override;

public slots:
	void toggle_APIKey();
	void toggle_cluid();
	void ShowHideDialog();

private:
	//Nothing here
};
