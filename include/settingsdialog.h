#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr);
    ~SettingsDialog();
protected:
    void changeEvent(QEvent * event) override;
private:
    Ui::SettingsDialog *ui;
    void initLangs();
    void saveSettings();
};

#endif // SETTINGSDIALOG_H
