/*******************************************
A Docile Sloth 2017 (adocilesloth@gmail.com)
*******************************************/
#pragma once

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QRadioButton>

QT_BEGIN_NAMESPACE

class Ui_TS3Callout
{
public:
	QGridLayout *ts3Layout;
	QLabel *enableLabel;
	QCheckBox *enableCheck;
	QLabel *ipadrsLabel;
	QLineEdit *ipadrsLineEdit;
	QLabel *apikeyLabel;
	QLineEdit *apikeyLineEdit;
	QPushButton *apikeyButton;
	QLabel *cluidLabel;
	QLineEdit *cluidLineEdit;
	QPushButton *cluidButton;
	QLabel *fixLabel;
	QLineEdit *fixLineEdit;
	QLabel *prefixLabel;
	QRadioButton *prefixRadio;
	QLabel *suffixLabel;
	QRadioButton *suffixRadio;
	QLabel *muteLabel;
	QCheckBox *muteCheck;
	QLabel *deafLabel;
	QCheckBox *deafCheck;
	QLabel *serversLabel;
	QCheckBox *serversCheck;

	QDialogButtonBox *closeButton;

	void setupUi(QDialog *TS3Callout)
	{
		if(TS3Callout->objectName().isEmpty())
		{
			TS3Callout->setObjectName(QStringLiteral("TS3Callout"));
		}
		TS3Callout->resize(600, 200);
		ts3Layout = new QGridLayout(TS3Callout);
		ts3Layout->setObjectName(QStringLiteral("ts3Layout"));

		int lineEditWidth = 5;

		//enable/disable
		enableLabel = new QLabel(TS3Callout);
		enableLabel->setObjectName(QStringLiteral("enableLabel"));
		ts3Layout->addWidget(enableLabel, 0, 1, 1, 1); //row, column, rowspan, columnspan

		enableCheck = new QCheckBox(TS3Callout);
		enableCheck->setObjectName(QStringLiteral("enableCheck"));
		enableCheck->setChecked(false);
		ts3Layout->addWidget(enableCheck, 0, 2, 1, 1);
		//IP Address
		ipadrsLabel = new QLabel(TS3Callout);
		ipadrsLabel->setObjectName(QStringLiteral("ipadrsLabel"));
		ts3Layout->addWidget(ipadrsLabel, 1, 1, 1, 1);

		ipadrsLineEdit = new QLineEdit(TS3Callout);
		ipadrsLineEdit->setObjectName(QStringLiteral("ipadrsLineEdit"));
		ipadrsLineEdit->setText("127.0.0.1");
		ts3Layout->addWidget(ipadrsLineEdit, 1, 2, 1, lineEditWidth);
		//API Key
		apikeyLabel = new QLabel(TS3Callout);
		apikeyLabel->setObjectName(QStringLiteral("apikeyLabel"));
		ts3Layout->addWidget(apikeyLabel, 2, 1, 1, 1);

		apikeyLineEdit = new QLineEdit(TS3Callout);
		apikeyLineEdit->setObjectName(QStringLiteral("apikeyLineEdit"));
		apikeyLineEdit->setEchoMode(QLineEdit::Password);
		apikeyLineEdit->setText("");
		ts3Layout->addWidget(apikeyLineEdit, 2, 2, 1, lineEditWidth);

		apikeyButton = new QPushButton(TS3Callout);
		apikeyButton->setObjectName(QStringLiteral("apikeyButton"));
		ts3Layout->addWidget(apikeyButton, 2, lineEditWidth+2, 1, 1);

		//cluid
		cluidLabel = new QLabel(TS3Callout);
		cluidLabel->setObjectName(QStringLiteral("cluidLabel"));
		ts3Layout->addWidget(cluidLabel, 3, 1, 1, 1);

		cluidLineEdit = new QLineEdit(TS3Callout);
		cluidLineEdit->setObjectName(QStringLiteral("cluidLineEdit"));
		cluidLineEdit->setEchoMode(QLineEdit::Password);
		cluidLineEdit->setText("");
		ts3Layout->addWidget(cluidLineEdit, 3, 2, 1, lineEditWidth);

		cluidButton = new QPushButton(TS3Callout);
		cluidButton->setObjectName(QStringLiteral("cluidButton"));
		ts3Layout->addWidget(cluidButton, 3, lineEditWidth + 2, 1, 1);
		
		//Fix
		fixLabel = new QLabel(TS3Callout);
		fixLabel->setObjectName(QStringLiteral("fixLabel"));
		ts3Layout->addWidget(fixLabel, 5, 1, 1, 1);

		fixLineEdit = new QLineEdit(TS3Callout);
		fixLineEdit->setObjectName(QStringLiteral("fixLineEdit"));
		fixLineEdit->setText("*R*");
		ts3Layout->addWidget(fixLineEdit, 5, 2, 1, lineEditWidth);
		//Prefix
		prefixLabel = new QLabel(TS3Callout);
		prefixLabel->setObjectName(QStringLiteral("prefixLabel"));
		ts3Layout->addWidget(prefixLabel, 6, 1, 1, 1);

		prefixRadio = new QRadioButton(TS3Callout);
		prefixRadio->setObjectName(QStringLiteral("prefixradio"));
		prefixRadio->setChecked(true);
		ts3Layout->addWidget(prefixRadio, 6, 2, 1, 1);
		//Suffix
		suffixLabel = new QLabel(TS3Callout);
		suffixLabel->setObjectName(QStringLiteral("suffixLabel"));
		ts3Layout->addWidget(suffixLabel, 6, 3, 1, 1);

		suffixRadio = new QRadioButton(TS3Callout);
		suffixRadio->setObjectName(QStringLiteral("suffixradio"));
		suffixRadio->setChecked(false);
		ts3Layout->addWidget(suffixRadio, 6, 4, 1, 1);
		//Mute
		muteLabel = new QLabel(TS3Callout);
		muteLabel->setObjectName(QStringLiteral("muteLabel"));
		ts3Layout->addWidget(muteLabel, 7, 1, 1, 1);

		muteCheck = new QCheckBox(TS3Callout);
		muteCheck->setObjectName(QStringLiteral("muteCheck"));
		muteCheck->setChecked(false);
		ts3Layout->addWidget(muteCheck, 7, 2, 1, 1);
		//Deaf
		deafLabel = new QLabel(TS3Callout);
		deafLabel->setObjectName(QStringLiteral("deafLabel"));
		ts3Layout->addWidget(deafLabel, 7, 3, 1, 1);

		deafCheck = new QCheckBox(TS3Callout);
		deafCheck->setObjectName(QStringLiteral("deafCheck"));
		deafCheck->setChecked(false);
		ts3Layout->addWidget(deafCheck, 7, 4, 1, 1);
		//Servers
		serversLabel = new QLabel(TS3Callout);
		serversLabel->setObjectName(QStringLiteral("serversLabel"));
		ts3Layout->addWidget(serversLabel, 8, 1, 1, 1);

		serversCheck = new QCheckBox(TS3Callout);
		serversCheck->setObjectName(QStringLiteral("serversCheck"));
		serversCheck->setChecked(false);
		ts3Layout->addWidget(serversCheck, 8, 2, 1, 1);

		closeButton = new QDialogButtonBox(TS3Callout);
		closeButton->setObjectName(QStringLiteral("buttonBox"));
		closeButton->setStandardButtons(QDialogButtonBox::Close);
		ts3Layout->addWidget(closeButton, 9, lineEditWidth+1, 1, 1);


		retranslateUi(TS3Callout);

		QMetaObject::connectSlotsByName(TS3Callout);
	} // setupUi

	void retranslateUi(QDialog *TS3Callout)
	{
		TS3Callout->setWindowTitle(QApplication::translate("TS3Callout", "TS3Callout", Q_NULLPTR));
		enableLabel->setText(QApplication::translate("TS3Callout", "Enable", Q_NULLPTR));
		ipadrsLabel->setText(QApplication::translate("TS3Callout", "IPV4", Q_NULLPTR));
		apikeyLabel->setText(QApplication::translate("TS3Callout", "APIKey", Q_NULLPTR));
		if(apikeyLineEdit->echoMode() == QLineEdit::Password)
		{
			apikeyButton->setText(QApplication::translate("TS3Callout", "Show", Q_NULLPTR));
		}
		else
		{
			apikeyButton->setText(QApplication::translate("TS3Callout", "Hide", Q_NULLPTR));
		}
		cluidLabel->setText(QApplication::translate("TS3Callout", "UniqueID", Q_NULLPTR));
		if(cluidLineEdit->echoMode() == QLineEdit::Password)
		{
			cluidButton->setText(QApplication::translate("TS3Callout", "Show", Q_NULLPTR));
		}
		else
		{
			cluidButton->setText(QApplication::translate("TS3Callout", "Hide", Q_NULLPTR));
		}
		fixLabel->setText(QApplication::translate("TS3Callout", "Modifier", Q_NULLPTR));
		prefixLabel->setText(QApplication::translate("TS3Callout", "Prefix", Q_NULLPTR));
		suffixLabel->setText(QApplication::translate("TS3Callout", "Suffix", Q_NULLPTR));
		muteLabel->setText(QApplication::translate("TS3Callout", "MuteTS3", Q_NULLPTR));
		deafLabel->setText(QApplication::translate("TS3Callout", "DeafenTS3", Q_NULLPTR));
		serversLabel->setText(QApplication::translate("TS3Callout", "ChangeAllServers", Q_NULLPTR));
	} // retranslateUi

};

namespace Ui {
	class TS3Callout : public Ui_TS3Callout {};
} // namespace Ui

QT_END_NAMESPACE


