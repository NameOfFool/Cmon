#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include <QPushButton>
#include <QSettings>
#include <QTranslator>

SettingsDialog::SettingsDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    connect(ui->saveButton, &QPushButton::clicked, this, &SettingsDialog::saveSettings);
    initLangs();
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::initLangs()
{
    QSettings settings;
    QString currentLang = settings.value("Language", "en_US").toString();
    ui->languageComboBox->addItem("English", "en_US");
    ui->languageComboBox->addItem("Русский", "ru_RU");
    int index = ui->languageComboBox->findData(currentLang);
    if(index >= 0)
        ui->languageComboBox->setCurrentIndex(index);
}
void SettingsDialog::saveSettings()
{
    QSettings settings;
    settings.setValue("Language", ui->languageComboBox->currentData());
    accept();
}
void SettingsDialog::changeEvent(QEvent * event)
{
    if (event->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
    }
}
