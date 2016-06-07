#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QDockWidget>

namespace Ui {
class calculator;
}

class calculator : public QDockWidget
{
    Q_OBJECT

public:
    explicit calculator(QWidget *parent = 0);
    ~calculator();

private slots:

    void on_pushButton_clicked();

    void on_comboBox_activated(const QString &arg1);
    void on_comboBox_wpn_type_activated(const QString &arg1);

    void on_tabWidget_currentChanged(int index);

    void on_checkBox_multipleshot_toggled(bool checked);

private:
    Ui::calculator *ui;
    void InitializeComboBoxLists();
    void GenerateHittingChanceCode();
    void GenerateDmgDoneCode();
    void GenerateCustomCode();
    void GenerateLimitCode();
    void setCodeHeader(QString playername, QString actionName, QString PAcost);
    void setCodeSuccesChance(int base);
    void setCodeDmgDone();
    void setCodeCustom();
    void setCodeLimit();
    void setDice(QString dice);


    QString code, preview_code;

    };

#endif // CALCULATOR_H
