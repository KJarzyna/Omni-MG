#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include "player.h"
#include "calculator.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QVector<player> Player;
    calculator calc;

    QVector<QWidget*> tab_copy;

private slots:

    //Buttons
    void on_pushButton_addSkill_clicked();
    void on_pushButton_removeSkill_clicked();
    void on_pushButton_calculate_clicked();
    void on_pushButton_addWeapon_clicked();
    void on_pushButton_removeWeapon_clicked();
    void on_pushButton_AddArmor_clicked();
    void on_pushButton_RemoveArmor_clicked();

    //CheckBoxes
    void on_checkBox_clicked(bool check);
    void on_checkBox_2_clicked(bool check);
    void on_checkBox_3_clicked(bool check);
    void on_checkBox_4_clicked(bool check);
    void on_checkBox_5_clicked(bool check);
    void on_checkBox_6_clicked(bool check);
    void on_checkBox_7_clicked(bool check);

    //LineEdits
    void on_lineEdit_miano1_textEdited(const QString &arg1);
    void on_lineEdit_p1_textEdited(const QString &arg1);
    void on_lineEdit_p2_textEdited(const QString &arg1);
    void on_lineEdit_t1_textEdited(const QString &arg1);
    void on_lineEdit_t2_textEdited(const QString &arg1);

    //ComboBoxes
    void on_comboBox_specialization_highlighted(const QString &arg1);
    void on_comboBox_selectplayer_currentIndexChanged(int index);
    void on_comboBox_specialization_activated(const QString &arg1);
    void on_comboBox_omni_activated(const QString &arg1);
    void on_comboBox_omni_mods_activated(const QString &arg1);
    void on_comboBox_omniblade_activated(const QString &arg1);
    void on_comboBox_omniblade_mods_activated(const QString &arg1);
    void on_comboBox_shield_activated(const QString &arg1);

    //Menu
    void on_actionWczytaj_zestaw_triggered();
    void on_actionZapisz_zestaw_jako_triggered();
    void on_actionZapisz_zestaw_triggered();
    void on_actionNowy_zestaw_triggered();
    void on_actionZamknij_triggered();
    void on_actionInformacje_o_produkcie_triggered();
    void on_actionPodziekowania_triggered();

    //PlainText
    void on_plainTextEdit_bonuses_textChanged();
    void on_plainTextEdit_equipment_textChanged();


    void on_actionOmni_Kalkulator_triggered();

private:
    Ui::MainWindow *ui;
    QStandardItemModel* model[8];
    QStandardItemModel* model_spec[8];
    QStandardItemModel* model_weap[8];

    void InitializePlayers();
    void setModels();
    void setStartingValues();
    void setTableParams();
    void setPlayerName(QString name);
    void setPrestigeClass(bool check);
    void ChangeSpecializationLabel(QString specializationname);
    void New();
    void Save();
    void Load();
    void ClearAllPlayerElements();
    void RemoveSkill();
    void RemoveArmor();
    void AddSkill();
    void AddWeapon();
    void RemoveWeapon();
    void AddSpecialization(QString specializationname);
    void AddPlayerBonuses();
    void AddArmor();
    void InitializeArmorsList();
    void InitializeOmniList();
    void InitializeShieldGenList();
    void UpdateView();
    void ChangePlayer(int index);
    void AddToolTip(QString ItemName, int PlayerIndex);
    void AddOmniKey(QString name);
    void AddOmniMods(QString name);
    void AddOmniBlade(QString name);
    void AddOmniBladeMod(QString name);
    void AddShieldGen(QString name);
    void CalculateMasteryChance();

    int NumOfPlayers;
    int NumOfAbilities;
    int NumOfWeapons;
    int NumOfArmors;
    int NumOfInfoItems;
    int InfoIndex[10];

    QString SaveName;
    QString PrestigeSkillsCopy[20];



};

#endif // MAINWINDOW_H
