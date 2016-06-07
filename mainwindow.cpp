#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>


//Autor: Krzysztof Jarzyna
//Wszelkie prawa zastrzeżone.

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    InitializeArmorsList();
    InitializeOmniList();
    InitializeShieldGenList();

    InitializePlayers();

    setStartingValues();
    setTableParams();
    setModels();

    SaveName = "nowa_sesja.ini";
}

MainWindow::~MainWindow()
{
    delete ui;
}

//PRIVATE SLOTS

//Buttons
void MainWindow::on_pushButton_addSkill_clicked()
{
    //Run when "Dodaj umiejętność" button is clicked
    AddSkill();
}


void MainWindow::on_pushButton_removeSkill_clicked()
{
    //Run when "Usuń umiejętność" button is clicked
    RemoveSkill();
}

void MainWindow::on_pushButton_calculate_clicked()
{
    //Calculate mastery chances when "Przelicz" button is clicked
    CalculateMasteryChance();

}

void MainWindow::on_pushButton_addWeapon_clicked()
{
    //Run when "Dodaj broń" button is clicked
    AddWeapon();
}

void MainWindow::on_pushButton_removeWeapon_clicked()
{
    //Run when "Usuń broń" button is clicked
    RemoveWeapon();

}

void MainWindow::on_pushButton_AddArmor_clicked()
{
    //Run when "Dodaj pancerz" button is clicked
    AddArmor();
}

void MainWindow::on_pushButton_RemoveArmor_clicked()
{
    //Run when "Usuń pancerz" button is clicked
    RemoveArmor();
}

//CheckBoxes
void MainWindow::on_checkBox_clicked(bool check)
{
    //Run when "Pancerz Technologiczny" is checked

    if(check) //if user checks Pancerz Technologiczny to be true
    {
       //Update player data
       Player[ui->comboBox_selectplayer->currentIndex()].skill_effects_id[0] = true;

       //Add information about "Pancerz Technologiczny" being active to the Info Widget
       QString InfoString;
       InfoString = Player[ui->comboBox_selectplayer->currentIndex()].name + " ma włączony Pancerz Technologiczny.";
       ui->listWidget_info->addItem(InfoString);
       InfoIndex[0] = ui->listWidget_info->count();
    }
    else //if user checks Pancerz Technologiczny to be false
    {
        QString ListItemText;
        ListItemText = Player[ui->comboBox_selectplayer->currentIndex()].name + " ma włączony Pancerz Technologiczny.";

        //Search which one item in the Info Widget is the right one
        for(int i=0;i<ui->listWidget_info->count();i++)
        {
         if(ui->listWidget_info->item(i)->text() == ListItemText) InfoIndex[0] = i;
        }

        //Delete information from Info Widget
        delete ui->listWidget_info->item(InfoIndex[0]);
        //Update player data
        Player[ui->comboBox_selectplayer->currentIndex()].skill_effects_id[0] = false;
    }

}

void MainWindow::on_checkBox_2_clicked(bool check)
{
    //Run when "Umocnienie" checkbox is checked

    //(same as Pancerz Technologiczny CheckBox)
    if(check)
    {
        Player[ui->comboBox_selectplayer->currentIndex()].skill_effects_id[1] = true;
        QString InfoString;
        InfoString = Player[ui->comboBox_selectplayer->currentIndex()].name + " ma włączone Umocnienie.";
        ui->listWidget_info->addItem(InfoString);
        InfoIndex[1] = ui->listWidget_info->count()-1;
    }
    else
    {
        QString ListItemText;
        ListItemText = Player[ui->comboBox_selectplayer->currentIndex()].name + " ma włączone Umocnienie.";
        for(int i=0;i<ui->listWidget_info->count();i++)
        {
         if(ui->listWidget_info->item(i)->text() == ListItemText) InfoIndex[1] = i;
        }
        delete ui->listWidget_info->item(InfoIndex[1]);
        Player[ui->comboBox_selectplayer->currentIndex()].skill_effects_id[1] = false;
    }

}

void MainWindow::on_checkBox_3_clicked(bool check)
{
    //Run when "Bariera" checkbox is checked

    //(same as Pancerz Technologiczny CheckBox)
    if(check)
    {
        Player[ui->comboBox_selectplayer->currentIndex()].skill_effects_id[2] = true;
        QString InfoString;
        InfoString = Player[ui->comboBox_selectplayer->currentIndex()].name + " ma włączoną Barierę.";
        ui->listWidget_info->addItem(InfoString);
        InfoIndex[2] = ui->listWidget_info->count()-1;
    }
    else
    {
        QString ListItemText;
        ListItemText = Player[ui->comboBox_selectplayer->currentIndex()].name + " ma włączoną Barierę.";
        for(int i=0;i<ui->listWidget_info->count();i++)
        {
         if(ui->listWidget_info->item(i)->text() == ListItemText) InfoIndex[2] = i;
        }
        delete ui->listWidget_info->item(InfoIndex[2]);
        Player[ui->comboBox_selectplayer->currentIndex()].skill_effects_id[2] = false;
    }

}

void MainWindow::on_checkBox_4_clicked(bool check)
{
    //Run when "Kula Biotyczna" checkbox is checked

    //(same as Pancerz Technologiczny CheckBox)
    if(check)
    {
        Player[ui->comboBox_selectplayer->currentIndex()].skill_effects_id[3] = true;
        QString InfoString;
        InfoString = Player[ui->comboBox_selectplayer->currentIndex()].name + " jest pod działaniem Kuli Biotycznej.";
        ui->listWidget_info->addItem(InfoString);
        InfoIndex[3] = ui->listWidget_info->count()-1;
    }
    else
    {
        QString ListItemText;
        ListItemText = Player[ui->comboBox_selectplayer->currentIndex()].name + " jest pod działaniem Kuli Biotycznej.";
        for(int i=0;i<ui->listWidget_info->count();i++)
        {
         if(ui->listWidget_info->item(i)->text() == ListItemText) InfoIndex[3] = i;
        }
        delete ui->listWidget_info->item(InfoIndex[3]);
        Player[ui->comboBox_selectplayer->currentIndex()].skill_effects_id[3] = false;
    }

}

void MainWindow::on_checkBox_5_clicked(bool check)
{
    //Run when "Tryb Pustoszyciela" CheckBox is checked

    //(same as Pancerz Technologiczny CheckBox)
    if(check)
    {
        Player[ui->comboBox_selectplayer->currentIndex()].skill_effects_id[4] = true;
        QString InfoString;
        InfoString = Player[ui->comboBox_selectplayer->currentIndex()].name + " ma włączony Tryb Pustoszyciela.";
        ui->listWidget_info->addItem(InfoString);
        InfoIndex[4] = ui->listWidget_info->count()-1;
    }
    else
    {
        QString ListItemText;
        ListItemText = Player[ui->comboBox_selectplayer->currentIndex()].name + " ma włączony Tryb Pustoszyciela.";
        for(int i=0;i<ui->listWidget_info->count();i++)
        {
         if(ui->listWidget_info->item(i)->text() == ListItemText) InfoIndex[4] = i;
        }
        delete ui->listWidget_info->item(InfoIndex[4]);
        Player[ui->comboBox_selectplayer->currentIndex()].skill_effects_id[4] = false;
    }

}

void MainWindow::on_checkBox_6_clicked(bool check)
{
    //Run when "Kule Biotyczne" is checked

    //(same as Pancerz Technologiczny CheckBox)
    if(check)
    {
        Player[ui->comboBox_selectplayer->currentIndex()].skill_effects_id[5] = true;
        QString InfoString;
        InfoString = Player[ui->comboBox_selectplayer->currentIndex()].name + " ma włączone Biotyczne Kule.";
        ui->listWidget_info->addItem(InfoString);
        InfoIndex[5] = ui->listWidget_info->count();
    }
    else
    {
        QString ListItemText;
        ListItemText = Player[ui->comboBox_selectplayer->currentIndex()].name + " ma włączone Biotyczne Kule.";
        for(int i=0;i<ui->listWidget_info->count();i++)
        {
         if(ui->listWidget_info->item(i)->text() == ListItemText) InfoIndex[5] = i;
        }
        delete ui->listWidget_info->item(InfoIndex[5]);
        Player[ui->comboBox_selectplayer->currentIndex()].skill_effects_id[5] = false;
    }
}

void MainWindow::on_checkBox_7_clicked(bool check)
{
    //Run when Player select "Klasa Prestiżowa" checkbox
    setPrestigeClass(check);
}

//LineEdits
void MainWindow::on_lineEdit_p1_textEdited(const QString &arg1)
{
    //Run when user edits players armor points (add to player's data)
    int index = ui->comboBox_selectplayer->currentIndex();
    Player[index].armor_points = arg1;
}

void MainWindow::on_lineEdit_p2_textEdited(const QString &arg1)
{
    //Run when user edits players max armor points (add to player's data)
    int index = ui->comboBox_selectplayer->currentIndex();
    Player[index].armor_max = arg1;
}

void MainWindow::on_lineEdit_t1_textEdited(const QString &arg1)
{
    //Run when user edits players shield points (add to player's data)
    int index = ui->comboBox_selectplayer->currentIndex();
    Player[index].shield_points = arg1;
}

void MainWindow::on_lineEdit_t2_textEdited(const QString &arg1)
{
    //Run when user edits players max shield points (add to player's data)
    int index = ui->comboBox_selectplayer->currentIndex();
    Player[index].shield_max = arg1;
}

void MainWindow::on_lineEdit_miano1_textEdited(const QString &arg1)
{
    //Run when user type new Player name
    setPlayerName(arg1);
}


//ComboBoxes
void MainWindow::on_comboBox_selectplayer_currentIndexChanged(int index)
{
    //Run when user change selected player in Select Player ComboBox
    ChangePlayer(index);
}


void MainWindow::on_comboBox_specialization_activated(const QString &arg1)
{
    //Run when user choose specialization skill
    AddSpecialization(arg1);
}


void MainWindow::on_comboBox_specialization_highlighted(const QString &arg1)
{
    //Run when specialization skill is highlited
    ChangeSpecializationLabel(arg1);
}

void MainWindow::on_comboBox_omni_activated(const QString &arg1)
{
    //Run when player select OmniTool in OmniTool ComboBox
    AddOmniKey(arg1);
}

void MainWindow::on_comboBox_omni_mods_activated(const QString &arg1)
{
    //Run when player select OmniTool mod in OmniTool Mods ComboBox
    AddOmniMods(arg1);
}

void MainWindow::on_comboBox_omniblade_activated(const QString &arg1)
{
    //Run when player select OmniBlade in OmniBlade ComboBox
    AddOmniBlade(arg1);
}

void MainWindow::on_comboBox_omniblade_mods_activated(const QString &arg1)
{
    //Run when player select OmniBlade mod in Omniblade mod ComboBox
    AddOmniBladeMod(arg1);
}

void MainWindow::on_comboBox_shield_activated(const QString &arg1)
{
    //Run when player selects Shield generator from Shield Generator ComboBox
    AddShieldGen(arg1);
}

//Menu
void MainWindow::on_actionWczytaj_zestaw_triggered()
{
    //Run when user select "Wczytaj zestaw" from menu
    Load();

}

void MainWindow::on_actionZapisz_zestaw_jako_triggered()
{
    //Run when user select "Zapisz jako" from menu

    SaveName = QFileDialog::getSaveFileName(this,"Zapisz plik","",tr("Plik INI (*.ini);;Wszystkie pliki (*.*)"));
    Save();
}

void MainWindow::on_actionZapisz_zestaw_triggered()
{
    //Run when user select "Zapisz zestaw" from menu
   Save();
}

void MainWindow::on_actionNowy_zestaw_triggered()
{
    //Run when user select "Nowy zestaw" from menu
    New();
}

void MainWindow::on_actionZamknij_triggered()
{
    //Close
    this->close();
}

void MainWindow::on_actionInformacje_o_produkcie_triggered()
{
    //Run when user select "Informacje o produkcie" from menu
    QMessageBox msgbox;
    msgbox.setIcon(QMessageBox::NoIcon);
    msgbox.setWindowTitle("Informacje o Omni-MG");
    msgbox.setText("<center><font size=14><b>Omni-MG v2.0</b></font><br> by Vex<br><br>"
                   " Omni-MG został stworzony na użytek userów forum Cytadela"
                   " PBF <br><br> Autor: Vex <br><br>Wszelkie prawa zastrzeżone.<br><br> Stylesheets by LoneWolf. Wszystkie elementy zostały stworzone w oparciu o informacje znajdujące się w leksykonie Mass Effect.</center>");

    msgbox.exec();
}

void MainWindow::on_actionPodziekowania_triggered()
{
    //Run when user select "Podziękowania" from menu
    QMessageBox msgbox;
    msgbox.setIcon(QMessageBox::NoIcon);
    msgbox.setWindowTitle("Podziękowania");
    msgbox.setText("<center>Bleysowi, za to, że dyktował mi przez skajpa statystyki broni (bo przepisywanie zajęłoby mi 2h). Masz, proszę. Twoje podziękowania. Całe okienko dostałeś na własność. :P</center>");

    msgbox.exec();
}

//PlainTexts
void MainWindow::on_plainTextEdit_bonuses_textChanged()
{
   //Run when Player write something in "Bonusy" area
    AddPlayerBonuses();
}

void MainWindow::on_plainTextEdit_equipment_textChanged()
{
    //Run when user write something in player's equipment area (and add to player's data)
    Player[ui->comboBox_selectplayer->currentIndex()].equipment = ui->plainTextEdit_equipment->toPlainText();
}


//PRIVATE FUNCTIONS

void MainWindow::AddSkill()
{
    //Add Skill

    //Set parameters of the skill
    QString skillName;  //Name of the skill
    QString skillLevel; //Level of the skill
    QString skillType;  //Type of the skill: Boj - Bojowy, Tech - Technologiczny, Bio - Biotyka,
                        //Kla - Klasowy, Amm - Amunicja specjalna, Gran - Granaty, Pres - Prestiżowe

    skillName = ui->comboBox->currentText();
    skillLevel = ui->comboBox_2->currentText();

    int currId = ui->comboBox->currentIndex(); //Index of the selected skill in the combobox list

    if(currId > 0 && currId < 6) skillType = "Boj";
    else if (currId > 6 && currId < 17) skillType = "Bio";
    else if (currId > 17 && currId < 30) skillType = "Tech";
    else if (currId > 30 && currId < 36) skillType = "Kla";
    else if (currId > 36 && currId < 41) skillType = "Amm";
    else if (currId > 41 && currId < 47) skillType = "Gran";
    else if (currId > 47) skillType = "Pres";


    //Warning about prestige skills. If skill's type is "Pres" and player isn't tagged as "Prestige class"
    //warn user that his player must be a "prestige class" and don't add skill to the list

    if(Player[ui->comboBox_selectplayer->currentIndex()].prestige == false && skillType == "Pres")
    {
        QMessageBox msgbox;
        msgbox.setIcon(QMessageBox::NoIcon);
        msgbox.setWindowTitle("Ostrzeżenie o klasie prestiżowej");
        msgbox.setText("<center>Zdolność dostępna tylko dla klasy prestiżowej!</center>");
        msgbox.exec();
    }
    else
    {

    //Add skill to the currently selected player data
    Player[ui->comboBox_selectplayer->currentIndex()].AddSkill(skillName, skillType, skillLevel);

    //Add skill to List Widget for display
    QString sSkill = skillName + " " + skillLevel;
    ui->listWidget->addItem(sSkill);


    //Enable CheckBoxes
    if(skillName == "Pancerz Technologiczny") ui->checkBox->setEnabled(true);
    else if(skillName == "Umocnienie") ui->checkBox_2->setEnabled(true);
    else if(skillName == "Bariera") ui->checkBox_3->setEnabled(true);
    else if(skillName == "Tryb Pustoszyciela" && Player[ui->comboBox_selectplayer->currentIndex()].prestige == true) ui->checkBox_5->setEnabled(true);
    else if(skillName == "Biotyczne Kule" && Player[ui->comboBox_selectplayer->currentIndex()].prestige == true) ui->checkBox_6->setEnabled(true);
    }

}

void MainWindow::RemoveSkill()
{
    //Remove Skill

    int currId = ui->listWidget->currentRow(); //currently selected skill

    if(currId!=-1) //if any skill is selected
    {
        //Check if selected skill is "special" skill.
        //If so, uncheck Checkbox connected with it, disable it and remove information about it from Info Widget

        if(Player[ui->comboBox_selectplayer->currentIndex()].ability[currId].name == "Pancerz Technologiczny")
        {
            ui->checkBox->setEnabled(false);
            ui->checkBox->setChecked(false);
            QString ListItemText;
            ListItemText = Player[ui->comboBox_selectplayer->currentIndex()].name + " ma włączony Pancerz Technologiczny.";

            //Check which item in Info Widget is the right one
            for(int i=0;i<ui->listWidget_info->count();i++)
            {
             if(ui->listWidget_info->item(i)->text() == ListItemText) InfoIndex[0] = i;
            }

            //delete item from Info Widget
            delete ui->listWidget_info->item(InfoIndex[0]);
            //update player data
            Player[ui->comboBox_selectplayer->currentIndex()].skill_effects_id[0] = false;
        }
        if(Player[ui->comboBox_selectplayer->currentIndex()].ability[currId].name == "Umocnienie")
        {
            ui->checkBox_2->setEnabled(false);
            ui->checkBox_2->setChecked(false);
            QString ListItemText;
            ListItemText = Player[ui->comboBox_selectplayer->currentIndex()].name + " ma włączone Umocnienie.";
            for(int i=0;i<ui->listWidget_info->count();i++)
            {
             if(ui->listWidget_info->item(i)->text() == ListItemText) InfoIndex[1] = i;
            }
            delete ui->listWidget_info->item(InfoIndex[1]);
            Player[ui->comboBox_selectplayer->currentIndex()].skill_effects_id[1] = false;
        }
        if(Player[ui->comboBox_selectplayer->currentIndex()].ability[currId].name == "Bariera")
        {
            ui->checkBox_3->setEnabled(false);
            ui->checkBox_3->setChecked(false);
            QString ListItemText;
            ListItemText = Player[ui->comboBox_selectplayer->currentIndex()].name + " ma włączoną Barierę.";
            for(int i=0;i<ui->listWidget_info->count();i++)
            {
             if(ui->listWidget_info->item(i)->text() == ListItemText) InfoIndex[2] = i;
            }
            delete ui->listWidget_info->item(InfoIndex[2]);
            Player[ui->comboBox_selectplayer->currentIndex()].skill_effects_id[2] = false;
        }
        if(Player[ui->comboBox_selectplayer->currentIndex()].ability[currId].name == "Tryb Pustoszyciela")
        {
            ui->checkBox_5->setEnabled(false);
            ui->checkBox_5->setChecked(false);
            QString ListItemText;
            ListItemText = Player[ui->comboBox_selectplayer->currentIndex()].name + " ma włączony Tryb Pustoszyciela.";
            for(int i=0;i<ui->listWidget_info->count();i++)
            {
             if(ui->listWidget_info->item(i)->text() == ListItemText) InfoIndex[4] = i;
            }
            delete ui->listWidget_info->item(InfoIndex[4]);
            Player[ui->comboBox_selectplayer->currentIndex()].skill_effects_id[3] = false;
        }
        if(Player[ui->comboBox_selectplayer->currentIndex()].ability[currId].name == "Biotyczne Kule")
        {
            ui->checkBox_3->setEnabled(false);
            ui->checkBox_3->setChecked(false);
            QString ListItemText;
            ListItemText = Player[ui->comboBox_selectplayer->currentIndex()].name + " ma włączone Biotyczne Kule.";
            for(int i=0;i<ui->listWidget_info->count();i++)
            {
             if(ui->listWidget_info->item(i)->text() == ListItemText) InfoIndex[5] = i;
            }
            delete ui->listWidget_info->item(InfoIndex[5]);
            Player[ui->comboBox_selectplayer->currentIndex()].skill_effects_id[4] = false;
        }

        //Remove skill from Player data
        Player[ui->comboBox_selectplayer->currentIndex()].ability.remove(currId);
        //Remove skill from List Widget
        delete ui->listWidget->currentItem();
    }
}

void MainWindow::AddWeapon()
{
    QString WeaponName, WeaponAcc, WeaponRec, WeaponPA, WeaponDMG;

    WeaponName = ui->comboBox_11->currentText(); //set name of the selected weapon

    //Add weapon statistics
    if(WeaponName == "M-3 Predator") {WeaponAcc = "20"; WeaponRec = "5"; WeaponPA = "4PA"; WeaponDMG = "75";}
    else if(WeaponName == "M-5 Falanga") {WeaponAcc = "20"; WeaponRec = "5"; WeaponPA = "4PA"; WeaponDMG = "115";}
    else if(WeaponName == "M-6 Kat") {WeaponAcc = "20"; WeaponRec = "5"; WeaponPA = "5PA"; WeaponDMG = "276";}
    else if(WeaponName == "Projektor Błyskawic") {WeaponAcc = "25"; WeaponRec = "10"; WeaponPA = "4PA/7PA"; WeaponDMG = "81/340";}
    else if(WeaponName == "Skorpion") {WeaponAcc = "25"; WeaponRec = "5"; WeaponPA = "4PA"; WeaponDMG = "115";}
    else if(WeaponName == "Akolita") {WeaponAcc = "25"; WeaponRec = "5"; WeaponPA = "6A"; WeaponDMG = "546";}
    else if(WeaponName == "M-11 Tłumiciel") {WeaponAcc = "27"; WeaponRec = "5"; WeaponPA = "4PA"; WeaponDMG = "220";}
    else if(WeaponName == "M-77 Paladyn") {WeaponAcc = "25"; WeaponRec = "10"; WeaponPA = "4PA"; WeaponDMG = "350";}
    else if(WeaponName == "M-358 Szpon") {WeaponAcc = "20"; WeaponRec = "15"; WeaponPA = "5PA"; WeaponDMG = "433";}
    else if(WeaponName == "Oprawca") {WeaponAcc = "25"; WeaponRec = "20"; WeaponPA = "6PA"; WeaponDMG = "872";}
    else if(WeaponName == "N7 Orzeł") {WeaponAcc = "15"; WeaponRec = "5"; WeaponPA = "4PA"; WeaponDMG = "84/6";}

    else if(WeaponName == "M-4 Shuriken") {WeaponAcc = "10"; WeaponRec = "10"; WeaponPA = "4PA"; WeaponDMG = "29/8";}
    else if(WeaponName == "M-9 Grom") {WeaponAcc = "15"; WeaponRec = "10"; WeaponPA = "5PA"; WeaponDMG = "41/10";}
    else if(WeaponName == "M-12 Szarańcza") {WeaponAcc = "25"; WeaponRec = "5"; WeaponPA = "5PA"; WeaponDMG = "39/10";}
    else if(WeaponName == "M-25 Szerszeń'") {WeaponAcc = "25"; WeaponRec = "15"; WeaponPA = "4PA"; WeaponDMG = "56/9";}
    else if(WeaponName == "Pistolet Maszynowy Gethów") {WeaponAcc = "30"; WeaponRec = "5"; WeaponPA = "5PA"; WeaponDMG = "26/20";}
    else if(WeaponName == "Karzyciel Krwawej Hordy") {WeaponAcc = "15"; WeaponRec = "15"; WeaponPA = "4PA"; WeaponDMG = "64/10";}
    else if(WeaponName == "Pistolet Maszynowy Zbieraczy") {WeaponAcc = "25"; WeaponRec = "5"; WeaponPA = "4PA"; WeaponDMG = "51/10";}
    else if(WeaponName == "N7 Huragan") {WeaponAcc = "15"; WeaponRec = "10"; WeaponPA = "4PA"; WeaponDMG = "60/10";}

    else if(WeaponName == "M-8 Mściciel") {WeaponAcc = "10"; WeaponRec = "10"; WeaponPA = "7PA"; WeaponDMG = "39/10";}
    else if(WeaponName == "M-15 Windykator") {WeaponAcc = "20"; WeaponRec = "10"; WeaponPA = "6PA"; WeaponDMG = "60/9";}
    else if(WeaponName == "M-37 Sokół") {WeaponAcc = "7"; WeaponRec = "20"; WeaponPA = "8PA"; WeaponDMG = "407";}
    else if(WeaponName == "M-55 Argus") {WeaponAcc = "10"; WeaponRec = "15"; WeaponPA = "7PA"; WeaponDMG = "100/6";}
    else if(WeaponName == "M-76 Zjawa") {WeaponAcc = "10"; WeaponRec = "10"; WeaponPA = "6PA"; WeaponDMG = "68/10";}
    else if(WeaponName == "M-96 Motyka") {WeaponAcc = "30"; WeaponRec = "10"; WeaponPA = "7PA"; WeaponDMG = "79/8";}
    else if(WeaponName == "M-99 Szabla") {WeaponAcc = "25"; WeaponRec = "20"; WeaponPA = "8PA"; WeaponDMG = "700";}
    else if(WeaponName == "Phaeston") {WeaponAcc = "20"; WeaponRec = "5"; WeaponPA = "6PA"; WeaponDMG = "46/10";}
    else if(WeaponName == "Wyrzutnia Chakram") {WeaponAcc = "37"; WeaponRec = "10"; WeaponPA = "6PA/8PA"; WeaponDMG = "554/831";}
    else if(WeaponName == "Karabin Pulsacyjny Gethów") {WeaponAcc = "25"; WeaponRec = "5"; WeaponPA = "6PA"; WeaponDMG = "25/20";}
    else if(WeaponName == "Karabin Szturmowy Zbieraczy") {WeaponAcc = "10"; WeaponRec = "5"; WeaponPA = "7PA"; WeaponDMG = "54/10";}
    else if(WeaponName == "Miotacz Cząsteczek") {WeaponAcc = "20"; WeaponRec = "0"; WeaponPA = "6PA"; WeaponDMG = "60/10";}
    else if(WeaponName == "Napastnik") {WeaponAcc = "15"; WeaponRec = "25"; WeaponPA = "8PA"; WeaponDMG = "164/4";}
    else if(WeaponName == "Błotniak") {WeaponAcc = "30"; WeaponRec = "10"; WeaponPA = "6PA"; WeaponDMG = "100/10";}
    else if(WeaponName == "Karabin Przeciw-Syn. Adas") {WeaponAcc = "10"; WeaponRec = "5"; WeaponPA = "7PA"; WeaponDMG = "129/6";}
    else if(WeaponName == "N7 Walkiria") {WeaponAcc = "20"; WeaponRec = "10"; WeaponPA = "7PA"; WeaponDMG = "150/4";}
    else if(WeaponName == "N7 Tajfun") {WeaponAcc = "20"; WeaponRec = "15"; WeaponPA = "6PA"; WeaponDMG = "72/10";}

    else if(WeaponName == "M-92 Modliszka") {WeaponAcc = "35"; WeaponRec = "10"; WeaponPA = "11PA"; WeaponDMG = "615";}
    else if(WeaponName == "M-97 Żmija") {WeaponAcc = "30"; WeaponRec = "10"; WeaponPA = "9PA"; WeaponDMG = "310";}
    else if(WeaponName == "M-29 Siekacz") {WeaponAcc = "25"; WeaponRec = "15"; WeaponPA = "11PA"; WeaponDMG = "168/3";}
    else if(WeaponName == "M-13 Raptor") {WeaponAcc = "30"; WeaponRec = "10"; WeaponPA = "9PA"; WeaponDMG = "105/5";}
    else if(WeaponName == "M-90 Indra") {WeaponAcc = "15"; WeaponRec = "10"; WeaponPA = "10PA"; WeaponDMG = "48/10";}
    else if(WeaponName == "M-98 Wdowa") {WeaponAcc = "35"; WeaponRec = "15"; WeaponPA = "11PA"; WeaponDMG = "867";}
    else if(WeaponName == "Czarna Wdowa") {WeaponAcc = "35"; WeaponRec = "20"; WeaponPA = "10PA"; WeaponDMG = "693";}
    else if(WeaponName == "Oszczep") {WeaponAcc = "35"; WeaponRec = "15"; WeaponPA = "11PA"; WeaponDMG = "795";}
    else if(WeaponName == "Wyrzutnia harpunów Kishock") {WeaponAcc = "25"; WeaponRec = "10"; WeaponPA = "9PA"; WeaponDMG = "656";}
    else if(WeaponName == "Krysae") {WeaponAcc = "30"; WeaponRec = "10"; WeaponPA = "10PA"; WeaponDMG = "601";}
    else if(WeaponName == "Karabin Snajperski Zbieraczy") {WeaponAcc = "10"; WeaponRec = "0"; WeaponPA = "10PA"; WeaponDMG = "20/10";}
    else if(WeaponName == "N7 Waleczny") {WeaponAcc = "35"; WeaponRec = "10"; WeaponPA = "10PA"; WeaponDMG = "697";}

    else if(WeaponName == "M-23 Katana") {WeaponAcc = "10"; WeaponRec = "20"; WeaponPA = "7PA"; WeaponDMG = "316";}
    else if(WeaponName == "M-27 Sejmitar") {WeaponAcc = "15"; WeaponRec = "15"; WeaponPA = "6PA"; WeaponDMG = "293";}
    else if(WeaponName == "M-22 Patroszyciel") {WeaponAcc = "15"; WeaponRec = "25"; WeaponPA = "8PA"; WeaponDMG = "500";}
    else if(WeaponName == "M-11 Upiór") {WeaponAcc = "15"; WeaponRec = "25"; WeaponPA = "8PA"; WeaponDMG = "765";}
    else if(WeaponName == "M-300 Claymore") {WeaponAcc = "10"; WeaponRec = "30"; WeaponPA = "8PA"; WeaponDMG = "1222";}
    else if(WeaponName == "AT-12 Najeźdźca") {WeaponAcc = "10"; WeaponRec = "25"; WeaponPA = "6PA"; WeaponDMG = "667";}
    else if(WeaponName == "Wyrzutnia Kolców Graal") {WeaponAcc = "10"; WeaponRec = "30"; WeaponPA = "7PA/9PA"; WeaponDMG = "700/960";}
    else if(WeaponName == "Adept") {WeaponAcc = "10"; WeaponRec = "20"; WeaponPA = "7PA"; WeaponDMG = "370";}
    else if(WeaponName == "Strzelba Plazmowa Gethów") {WeaponAcc = "20"; WeaponRec = "20"; WeaponPA = "7PA/9PA"; WeaponDMG = "893/1148";}
    else if(WeaponName == "Karabinek Reegar") {WeaponAcc = "10"; WeaponRec = "0"; WeaponPA = "4PA"; WeaponDMG = "533";}
    else if(WeaponName == "Strzelba Jad") {WeaponAcc = "25"; WeaponRec = "15"; WeaponPA = "7PA"; WeaponDMG = "950";}
    else if(WeaponName == "N7 Krzyżowiec") {WeaponAcc = "20"; WeaponRec = "25"; WeaponPA = "7PA"; WeaponDMG = "743";}
    else if(WeaponName == "N7 Pirania") {WeaponAcc = "10"; WeaponRec = "15"; WeaponPA = "5PA"; WeaponDMG = "508";};


    //Insert new Row to the Weapon Table and fill it with statistics of the selected weapon
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,new QTableWidgetItem(WeaponName));
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,new QTableWidgetItem(WeaponAcc));
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,2,new QTableWidgetItem(WeaponRec));
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,3,new QTableWidgetItem(WeaponPA));
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,4,new QTableWidgetItem(WeaponDMG));
    ui->tableWidget->item(ui->tableWidget->rowCount()-1,1)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget->item(ui->tableWidget->rowCount()-1,2)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget->item(ui->tableWidget->rowCount()-1,3)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget->item(ui->tableWidget->rowCount()-1,4)->setTextAlignment(Qt::AlignCenter);

    //Add weapon to the player data
    Player[ui->comboBox_selectplayer->currentIndex()].AddWeapon(WeaponName,WeaponAcc, WeaponRec, WeaponPA,WeaponDMG);
}

void MainWindow::RemoveWeapon()
{
    //Remove weapon from Player
    int currId = ui->tableWidget->currentRow(); //Index od the currently selected weapon in table
    if(currId!=-1) //if any weapon is selected
    {
        //delete weapon from player data
        Player[ui->comboBox_selectplayer->currentIndex()].weapon.remove(currId);
        //delete weapon from Table Widget
        ui->tableWidget->removeRow(ui->tableWidget->currentRow());
    }
}

void MainWindow::setPlayerName(QString name)
{
    int index = ui->comboBox_selectplayer->currentIndex(); //Index of the currently selected player
    ui->comboBox_selectplayer->setItemText(index,name); //set name of the player in the Select Player ComboBox
    Player[index].name = name; //add player name to player data
}

void MainWindow::setModels()
{
    //Set models for certain ComboBoxes. In new model certain positions are grayed out and disabled (for example, "===Technologiczne===" in skills ComboBox)
    QAbstractItemModel* CBAbstModel[1];
    QModelIndex CBRootMIndex[1];
    QModelIndex mIndex[1];
    QStandardItem* qsItem[1];

    int ComboBoxesColumn[1];

     //Skills ComboBox Model
    CBAbstModel[0] = ui->comboBox->model();
    CBRootMIndex[0] = ui->comboBox->rootModelIndex();
    ComboBoxesColumn[0] = ui->comboBox->modelColumn();

    for(int i=0;i<1;i++)
    {
        model_weap[i] = qobject_cast<QStandardItemModel*>(CBAbstModel[i]);
        mIndex[i] = model_weap[i]->index(0, ComboBoxesColumn[i], CBRootMIndex[i]); //Bojowe
        qsItem[i] = model_weap[i]->itemFromIndex(mIndex[i]);
        qsItem[i]->setEnabled(false);

        model_weap[i] = qobject_cast<QStandardItemModel*>(CBAbstModel[i]);
        mIndex[i] = model_weap[i]->index(6, ComboBoxesColumn[i], CBRootMIndex[i]); //Biotyczne
        qsItem[i] = model_weap[i]->itemFromIndex(mIndex[i]);
        qsItem[i]->setEnabled(false);

        model_weap[i] = qobject_cast<QStandardItemModel*>(CBAbstModel[i]);
        mIndex[i] = model_weap[i]->index(17, ComboBoxesColumn[i], CBRootMIndex[i]); //Technologiczne
        qsItem[i] = model_weap[i]->itemFromIndex(mIndex[i]);
        qsItem[i]->setEnabled(false);

        model_weap[i] = qobject_cast<QStandardItemModel*>(CBAbstModel[i]);
        mIndex[i] = model_weap[i]->index(30, ComboBoxesColumn[i], CBRootMIndex[i]); //Klasowe
        qsItem[i] = model_weap[i]->itemFromIndex(mIndex[i]);
        qsItem[i]->setEnabled(false);

        model_weap[i] = qobject_cast<QStandardItemModel*>(CBAbstModel[i]);
        mIndex[i] = model_weap[i]->index(36, ComboBoxesColumn[i], CBRootMIndex[i]); //Amunicja Specjalna
        qsItem[i] = model_weap[i]->itemFromIndex(mIndex[i]);
        qsItem[i]->setEnabled(false);

        model_weap[i] = qobject_cast<QStandardItemModel*>(CBAbstModel[i]);
        mIndex[i] = model_weap[i]->index(41, ComboBoxesColumn[i], CBRootMIndex[i]); //Granaty
        qsItem[i] = model_weap[i]->itemFromIndex(mIndex[i]);
        qsItem[i]->setEnabled(false);

        model_weap[i] = qobject_cast<QStandardItemModel*>(CBAbstModel[i]);
        mIndex[i] = model_weap[i]->index(47, ComboBoxesColumn[i], CBRootMIndex[i]); //Prestiżowe
        qsItem[i] = model_weap[i]->itemFromIndex(mIndex[i]);
        qsItem[i]->setEnabled(false);

    }

    //Specialization ComboBox Model
    CBAbstModel[0] = ui->comboBox_specialization->model();
    CBRootMIndex[0] = ui->comboBox_specialization->rootModelIndex();
    ComboBoxesColumn[0] = ui->comboBox_specialization->modelColumn();


    for(int i=0;i<1;i++)
    {
        model_weap[i] = qobject_cast<QStandardItemModel*>(CBAbstModel[i]);
        mIndex[i] = model_weap[i]->index(1, ComboBoxesColumn[i], CBRootMIndex[i]); //Bojowe
        qsItem[i] = model_weap[i]->itemFromIndex(mIndex[i]);
        qsItem[i]->setEnabled(false);

        model_weap[i] = qobject_cast<QStandardItemModel*>(CBAbstModel[i]);
        mIndex[i] = model_weap[i]->index(7, ComboBoxesColumn[i], CBRootMIndex[i]); //Biotyczne
        qsItem[i] = model_weap[i]->itemFromIndex(mIndex[i]);
        qsItem[i]->setEnabled(false);

        model_weap[i] = qobject_cast<QStandardItemModel*>(CBAbstModel[i]);
        mIndex[i] = model_weap[i]->index(18, ComboBoxesColumn[i], CBRootMIndex[i]); //Technologiczne
        qsItem[i] = model_weap[i]->itemFromIndex(mIndex[i]);
        qsItem[i]->setEnabled(false);

        model_weap[i] = qobject_cast<QStandardItemModel*>(CBAbstModel[i]);
        mIndex[i] = model_weap[i]->index(31, ComboBoxesColumn[i], CBRootMIndex[i]); //Klasowe
        qsItem[i] = model_weap[i]->itemFromIndex(mIndex[i]);
        qsItem[i]->setEnabled(false);

        model_weap[i] = qobject_cast<QStandardItemModel*>(CBAbstModel[i]);
        mIndex[i] = model_weap[i]->index(37, ComboBoxesColumn[i], CBRootMIndex[i]); //Amunicja Specjalna
        qsItem[i] = model_weap[i]->itemFromIndex(mIndex[i]);
        qsItem[i]->setEnabled(false);

        model_weap[i] = qobject_cast<QStandardItemModel*>(CBAbstModel[i]);
        mIndex[i] = model_weap[i]->index(42, ComboBoxesColumn[i], CBRootMIndex[i]); //Granaty
        qsItem[i] = model_weap[i]->itemFromIndex(mIndex[i]);
        qsItem[i]->setEnabled(false);

        model_weap[i] = qobject_cast<QStandardItemModel*>(CBAbstModel[i]);
        mIndex[i] = model_weap[i]->index(48, ComboBoxesColumn[i], CBRootMIndex[i]); //Prestiżowe
        qsItem[i] = model_weap[i]->itemFromIndex(mIndex[i]);
        qsItem[i]->setEnabled(false);

    }

    //Weapons ComboBox Model

    CBAbstModel[0] = ui->comboBox_11->model();
    CBRootMIndex[0] = ui->comboBox_11->rootModelIndex();
    ComboBoxesColumn[0] = ui->comboBox_11->modelColumn();

    for(int i=0;i<1;i++)
    {
        model_weap[i] = qobject_cast<QStandardItemModel*>(CBAbstModel[i]);
        mIndex[i] = model_weap[i]->index(0, ComboBoxesColumn[i], CBRootMIndex[i]); //Pistolety Ciężkie
        qsItem[i] = model_weap[i]->itemFromIndex(mIndex[i]);
        qsItem[i]->setEnabled(false);

        model_weap[i] = qobject_cast<QStandardItemModel*>(CBAbstModel[i]);
        mIndex[i] = model_weap[i]->index(11, ComboBoxesColumn[i], CBRootMIndex[i]); //Pistolety Maszynowe
        qsItem[i] = model_weap[i]->itemFromIndex(mIndex[i]);
        qsItem[i]->setEnabled(false);

        model_weap[i] = qobject_cast<QStandardItemModel*>(CBAbstModel[i]);
        mIndex[i] = model_weap[i]->index(19, ComboBoxesColumn[i], CBRootMIndex[i]); //Karabiny Szturmowe
        qsItem[i] = model_weap[i]->itemFromIndex(mIndex[i]);
        qsItem[i]->setEnabled(false);

        model_weap[i] = qobject_cast<QStandardItemModel*>(CBAbstModel[i]);
        mIndex[i] = model_weap[i]->index(35, ComboBoxesColumn[i], CBRootMIndex[i]); //Karabiny Snajperskie
        qsItem[i] = model_weap[i]->itemFromIndex(mIndex[i]);
        qsItem[i]->setEnabled(false);

        model_weap[i] = qobject_cast<QStandardItemModel*>(CBAbstModel[i]);
        mIndex[i] = model_weap[i]->index(47, ComboBoxesColumn[i], CBRootMIndex[i]); //Strzelby
        qsItem[i] = model_weap[i]->itemFromIndex(mIndex[i]);
        qsItem[i]->setEnabled(false);

        model_weap[i] = qobject_cast<QStandardItemModel*>(CBAbstModel[i]);
        mIndex[i] = model_weap[i]->index(59, ComboBoxesColumn[i], CBRootMIndex[i]); //Broń N7
        qsItem[i] = model_weap[i]->itemFromIndex(mIndex[i]);
        qsItem[i]->setEnabled(false);

    }

    //Armors ComboBox Model

    CBAbstModel[0] = ui->comboBox_armor->model();
    CBRootMIndex[0] = ui->comboBox_armor->rootModelIndex();
    ComboBoxesColumn[0] = ui->comboBox_armor->modelColumn();

    for(int i=0;i<1;i++)
    {
        model_weap[i] = qobject_cast<QStandardItemModel*>(CBAbstModel[i]);
        mIndex[i] = model_weap[i]->index(0, ComboBoxesColumn[i], CBRootMIndex[i]); //Hełmy
        qsItem[i] = model_weap[i]->itemFromIndex(mIndex[i]);
        qsItem[i]->setEnabled(false);

        model_weap[i] = qobject_cast<QStandardItemModel*>(CBAbstModel[i]);
        mIndex[i] = model_weap[i]->index(14, ComboBoxesColumn[i], CBRootMIndex[i]); //Napierśnik
        qsItem[i] = model_weap[i]->itemFromIndex(mIndex[i]);
        qsItem[i]->setEnabled(false);

        model_weap[i] = qobject_cast<QStandardItemModel*>(CBAbstModel[i]);
        mIndex[i] = model_weap[i]->index(22, ComboBoxesColumn[i], CBRootMIndex[i]); //Naramiennik
        qsItem[i] = model_weap[i]->itemFromIndex(mIndex[i]);
        qsItem[i]->setEnabled(false);

        model_weap[i] = qobject_cast<QStandardItemModel*>(CBAbstModel[i]);
        mIndex[i] = model_weap[i]->index(30, ComboBoxesColumn[i], CBRootMIndex[i]); //Rękawice
        qsItem[i] = model_weap[i]->itemFromIndex(mIndex[i]);
        qsItem[i]->setEnabled(false);

        model_weap[i] = qobject_cast<QStandardItemModel*>(CBAbstModel[i]);
        mIndex[i] = model_weap[i]->index(38, ComboBoxesColumn[i], CBRootMIndex[i]); //Nagolenniki
        qsItem[i] = model_weap[i]->itemFromIndex(mIndex[i]);
        qsItem[i]->setEnabled(false);

        model_weap[i] = qobject_cast<QStandardItemModel*>(CBAbstModel[i]);
        mIndex[i] = model_weap[i]->index(46, ComboBoxesColumn[i], CBRootMIndex[i]); //Pancerze Specjalne
        qsItem[i] = model_weap[i]->itemFromIndex(mIndex[i]);
        qsItem[i]->setEnabled(false);

    }

}

void MainWindow::ChangeSpecializationLabel(QString specializationname)
{
    //Change label of specialization, when current specialization skill is choosen
    QString text = specializationname + ":";
    ui->label_10->setText(text);
}

void MainWindow::setStartingValues()
{
    ui->comboBox->setCurrentIndex(1);
    ui->comboBox_11->setCurrentIndex(1);
    ui->comboBox_armor->setCurrentIndex(1);

    ui->tabWidget->setCurrentIndex(0);

    ui->checkBox->setEnabled(false);
    ui->checkBox_2->setEnabled(false);
    ui->checkBox_3->setEnabled(false);

    ui->checkBox_5->setVisible(false);
    ui->checkBox_6->setVisible(false);

}

void MainWindow::setTableParams()
{
    //set starting parameters of Weapons Table
    ui->tableWidget->setColumnWidth(0,130);
    ui->tableWidget->setColumnWidth(1,30);
    ui->tableWidget->setColumnWidth(2,30);
    ui->tableWidget->setColumnWidth(3,35);
    ui->tableWidget->setColumnWidth(4,50);
}

void MainWindow::AddSpecialization(QString specializationname)
{
    //Add Specialization skill to player data
    Player[ui->comboBox_selectplayer->currentIndex()].specialization = specializationname;
    Player[ui->comboBox_selectplayer->currentIndex()].specialization_id = ui->comboBox_specialization->currentIndex();
}

void MainWindow::Save()
{
    //Save player data to the config file

    QSettings settings(SaveName, QSettings::IniFormat);
    settings.clear();

    settings.beginGroup("GENERAL");
    settings.setValue("NumberOfPlayers", NumOfPlayers);
    NumOfInfoItems = ui->listWidget_info->count();
    settings.setValue("NumberOfInfoItems", NumOfInfoItems);
    settings.endGroup();
    QString GroupTitle;
    QString SkillKey;
    QString WeaponKey;
    QString ArmorKey;
    QString InfoWidget;

    for(int i=0;i<NumOfPlayers;i++)
    {
        GroupTitle = "PLAYER" + QString::number(i);

        //Save player general info
        settings.beginGroup(GroupTitle);
        settings.setValue("Name", Player[i].name);
        settings.setValue("Prestige", Player[i].prestige);
        settings.setValue("Specialization", Player[i].specialization);
        settings.setValue("Specialization ID", Player[i].specialization_id);
        settings.setValue("Active Effect[0]", Player[i].skill_effects_id[0]);
        settings.setValue("Active Effect[1]", Player[i].skill_effects_id[1]);
        settings.setValue("Active Effect[2]", Player[i].skill_effects_id[2]);
        settings.setValue("Active Effect[3]", Player[i].skill_effects_id[3]);
        settings.setValue("Active Effect[4]", Player[i].skill_effects_id[4]);
        settings.setValue("Active Effect[5]", Player[i].skill_effects_id[5]);
        NumOfAbilities = Player[i].ability.size();
        settings.setValue("NumberOfAbilities", NumOfAbilities);
        NumOfWeapons = Player[i].weapon.size();
        settings.setValue("NumberOfWeapons", NumOfWeapons);
        NumOfArmors = Player[i].armour.size();
        settings.setValue("NumberOfArmors", NumOfArmors);
        settings.endGroup();

        //Save player skills
        GroupTitle = "PLAYER" + QString::number(i) + "_SKILLS";

        settings.beginGroup(GroupTitle);
        for(int j=0;j<Player[i].ability.size();j++)
        {
            SkillKey = "Skill_" + QString::number(j) + "_name";
            settings.setValue(SkillKey, Player[i].ability[j].name);
            SkillKey = "Skill_" + QString::number(j) + "_type";
            settings.setValue(SkillKey, Player[i].ability[j].type);
            SkillKey = "Skill_" + QString::number(j) + "_level";
            settings.setValue(SkillKey, Player[i].ability[j].level);
        }
        settings.endGroup();

        //Save player weapons
        GroupTitle = "PLAYER" + QString::number(i) + "_WEAPONS";

        settings.beginGroup(GroupTitle);
        for(int j=0;j<Player[i].weapon.size();j++)
        {
            WeaponKey = "Weapon_" + QString::number(j) + "_name";
            settings.setValue(WeaponKey, Player[i].weapon[j].name);
            WeaponKey = "Weapon_" + QString::number(j) + "_Acc";
            settings.setValue(WeaponKey, Player[i].weapon[j].Acc);
            WeaponKey = "Weapon_" + QString::number(j) + "_Recoil";
            settings.setValue(WeaponKey, Player[i].weapon[j].Recoil);
            WeaponKey = "Weapon_" + QString::number(j) + "_PA";
            settings.setValue(WeaponKey, Player[i].weapon[j].PA);
            WeaponKey = "Weapon_" + QString::number(j) + "_DMG";
            settings.setValue(WeaponKey, Player[i].weapon[j].DMG);
        }
        settings.endGroup();

        //Save player armors
        GroupTitle = "PLAYER" + QString::number(i) + "_ARMORS";

        settings.beginGroup(GroupTitle);
        settings.setValue("ArmorPoints", Player[i].armor_points);
        settings.setValue("ArmorPointsMax", Player[i].armor_max);
        settings.setValue("ShieldPoints", Player[i].shield_points);
        settings.setValue("ShieldPointsMax", Player[i].shield_max);

        for(int j=0;j<Player[i].armour.size();j++)
        {
            ArmorKey = "Armor_" + QString::number(j) + "_name";
            settings.setValue(ArmorKey, Player[i].armour[j].name);
        }
        settings.endGroup();

        //Save player omni
        GroupTitle = "PLAYER" + QString::number(i) + "_OMNI";

        settings.beginGroup(GroupTitle);

        settings.setValue("Omnikey", Player[i].omnikey);
        settings.setValue("Omnimod", Player[i].omnimod);
        settings.setValue("Omniblade", Player[i].omniblade);
        settings.setValue("Omniblademod", Player[i].omniblademod);

        settings.endGroup();

        //Save player shield generator
        GroupTitle = "PLAYER" + QString::number(i) + "_SHIELDGEN";

        settings.beginGroup(GroupTitle);

        settings.setValue("Shieldgen", Player[i].shieldgen);

        settings.endGroup();


        //Save player bonuses
        GroupTitle = "PLAYER" + QString::number(i) + "_BONUSES";

        settings.beginGroup(GroupTitle);
        settings.setValue("Bonuses",Player[i].bonuses);
        settings.endGroup();

        //Save player equipment
        GroupTitle = "PLAYER" + QString::number(i) + "_EQ";

        settings.beginGroup(GroupTitle);
        settings.setValue("Equipment",Player[i].equipment);
        settings.endGroup();

    }

    settings.beginGroup("INFO");
    for(int j=0;j<ui->listWidget_info->count();j++)
    {
        InfoWidget = "ListWidget" + QString::number(j);
        settings.setValue(InfoWidget, ui->listWidget_info->item(j)->text());

    }
     settings.endGroup();

    settings.beginGroup("NOTES");
    settings.setValue("Personal_notes", ui->plainTextEdit->toPlainText());
    settings.endGroup();

    settings.sync();

}

void MainWindow::Load()
{
    New();
    SaveName = QFileDialog::getOpenFileName(this,"Otwórz plik","",tr("Plik INI (*.ini);;Wszystkie pliki (*.*)"));

    QSettings settings(SaveName, QSettings::IniFormat);
    settings.beginGroup("GENERAL");
    NumOfPlayers = settings.value("NumberOfPlayers").toInt();
    NumOfInfoItems = settings.value("NumberOfInfoItems").toInt();
    settings.endGroup();

    QString GroupTitle;
    QString SkillKey;
    QString WeaponKey;
    QString ArmorKey;
    QString InfoWidget;

    for(int i=0;i<NumOfPlayers;i++)
    {
        //Load Player settings from config file
        GroupTitle = "PLAYER" + QString::number(i);

        settings.beginGroup(GroupTitle);
        Player[i].name = settings.value("Name").toString();
        Player[i].prestige = settings.value("Prestige").toBool();
        Player[i].specialization = settings.value("Specialization").toString();
        Player[i].specialization_id = settings.value("Specialization ID").toInt();
        Player[i].skill_effects_id[0] = settings.value("Active Effect[0]").toBool();
        Player[i].skill_effects_id[1] = settings.value("Active Effect[1]").toBool();
        Player[i].skill_effects_id[2] = settings.value("Active Effect[2]").toBool();
        Player[i].skill_effects_id[3] = settings.value("Active Effect[3]").toBool();
        Player[i].skill_effects_id[4] = settings.value("Active Effect[4]").toBool();
        Player[i].skill_effects_id[5] = settings.value("Active Effect[5]").toBool();
        NumOfAbilities = settings.value("NumberOfAbilities").toInt();
        NumOfWeapons = settings.value("NumberOfWeapons").toInt();
        NumOfArmors = settings.value("NumberOfArmors").toInt();
        settings.endGroup();

        //Load Player Skills
        GroupTitle = "PLAYER" + QString::number(i) + "_SKILLS";

        settings.beginGroup(GroupTitle);
        for(int j=0;j<NumOfAbilities;j++)
        {
            QString SkillName, SkillType, SkillLevel;
            SkillKey = "Skill_" + QString::number(j) + "_name";
            SkillName = settings.value(SkillKey).toString();
            SkillKey = "Skill_" + QString::number(j) + "_type";
            SkillType = settings.value(SkillKey).toString();
            SkillKey = "Skill_" + QString::number(j) + "_level";
            SkillLevel = settings.value(SkillKey).toString();
            Player[i].AddSkill(SkillName, SkillType, SkillLevel);

        }
        settings.endGroup();

        //Load Player Weapons
        GroupTitle = "PLAYER" + QString::number(i) + "_WEAPONS";

        settings.beginGroup(GroupTitle);
        for(int j=0;j<NumOfWeapons;j++)
        {

            QString WeaponName, WeaponAcc, WeaponRec, WeaponPA, WeaponDMG;
            WeaponKey = "Weapon_" + QString::number(j) + "_name";
            WeaponName = settings.value(WeaponKey).toString();
            WeaponKey = "Weapon_" + QString::number(j) + "_Acc";
            WeaponAcc = settings.value(WeaponKey).toString();
            WeaponKey = "Weapon_" + QString::number(j) + "_Recoil";
            WeaponRec = settings.value(WeaponKey).toString();
            WeaponKey = "Weapon_" + QString::number(j) + "_PA";
            WeaponPA = settings.value(WeaponKey).toString();
            WeaponKey = "Weapon_" + QString::number(j) + "_DMG";
            WeaponDMG = settings.value(WeaponKey).toString();

            Player[i].AddWeapon(WeaponName, WeaponAcc, WeaponRec, WeaponPA, WeaponDMG);

        }
        settings.endGroup();

        //Load Player Armors
        GroupTitle = "PLAYER" + QString::number(i) + "_ARMORS";

        settings.beginGroup(GroupTitle);

        Player[i].armor_points = settings.value("ArmorPoints").toString();
        Player[i].armor_max = settings.value("ArmorPointsMax").toString();
        Player[i].shield_points = settings.value("ShieldPoints").toString();
        Player[i].shield_max = settings.value("ShieldPointsMax").toString();

        for(int j=0;j<NumOfArmors;j++)
        {

            QString ArmorName;
            ArmorKey = "Armor_" + QString::number(j) + "_name";
            ArmorName = settings.value(ArmorKey).toString();

            Player[i].AddArmor(ArmorName);

        }
        settings.endGroup();

        //Load Player Omni
        GroupTitle = "PLAYER" + QString::number(i) + "_OMNI";

        settings.beginGroup(GroupTitle);

        Player[i].omnikey = settings.value("Omnikey").toString();
        Player[i].omnimod = settings.value("Omnimod").toString();
        Player[i].omniblade = settings.value("Omniblade").toString();
        Player[i].omniblademod = settings.value("Omniblademod").toString();

        settings.endGroup();

        //Load Player Shield Generator
        GroupTitle = "PLAYER" + QString::number(i) + "_SHIELDGEN";

        settings.beginGroup(GroupTitle);

        Player[i].shieldgen = settings.value("Shieldgen").toString();

        settings.endGroup();

        //Load players names
        ui->comboBox_selectplayer->setItemText(i,Player[i].name);


        //Load Player Bonuses
        GroupTitle = "PLAYER" + QString::number(i) + "_BONUSES";
        settings.beginGroup(GroupTitle);
        Player[i].bonuses = settings.value("Bonuses").toString();
        settings.endGroup();

        //Load Player Equipment
        GroupTitle = "PLAYER" + QString::number(i) + "_EQ";
        settings.beginGroup(GroupTitle);
        Player[i].equipment = settings.value("Equipment").toString();
        settings.endGroup();
    }

    settings.beginGroup("INFO");
    for(int j=0;j<NumOfInfoItems;j++)
    {
        InfoWidget = "ListWidget" + QString::number(j);
        ui->listWidget_info->addItem(settings.value(InfoWidget).toString());

    }
     settings.endGroup();

    settings.beginGroup("NOTES");
    ui->plainTextEdit->setPlainText(settings.value("Personal_notes").toString());
    settings.endGroup();

    UpdateView();

}

void MainWindow::New()
{
    //Create New session
    ClearAllPlayerElements();
    InitializePlayers();

    SaveName = "nowa_sesja.ini";

    ui->listWidget_info->clear();
    ui->plainTextEdit->clear();
    ui->plainTextEdit_bonuses->clear();
    ui->plainTextEdit_equipment->clear();
}

void MainWindow::ClearAllPlayerElements()
{
    //Clear all elements
    ui->lineEdit_miano1->clear();
    ui->lineEdit_p1->clear();
    ui->lineEdit_p2->clear();
    ui->lineEdit_t1->clear();
    ui->lineEdit_t2->clear();
    ui->listWidget->clear();
    ui->listWidget_armor->clear();

    while(ui->tableWidget->rowCount()>0)
    {
        ui->tableWidget->removeRow(0);
    }
    ui->comboBox_specialization->setCurrentIndex(0);
    ui->comboBox_armor->setCurrentIndex(1);
    ui->comboBox_omni->setCurrentIndex(0);
    ui->comboBox_omni->setToolTip("");
    ui->comboBox_omni_mods->setCurrentIndex(0);
    ui->comboBox_omni_mods->setToolTip("");
    ui->comboBox_omniblade->setCurrentIndex(0);
    ui->comboBox_omniblade->setToolTip("");
    ui->comboBox_omniblade_mods->setCurrentIndex(0);
    ui->comboBox_omniblade_mods->setToolTip("");
    ui->comboBox_shield->setCurrentIndex(0);
    ui->comboBox_shield->setToolTip("");
    ui->tabWidget->setCurrentIndex(0);

    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();

    ui->checkBox->setChecked(false);
    ui->checkBox_2->setChecked(false);
    ui->checkBox_3->setChecked(false);
    ui->checkBox_4->setChecked(false);
    ui->checkBox_5->setChecked(false);
    ui->checkBox_6->setChecked(false);
    ui->checkBox_7->setChecked(false);

    ui->checkBox->setEnabled(false);
    ui->checkBox_2->setEnabled(false);
    ui->checkBox_3->setEnabled(false);
    ui->checkBox_5->setEnabled(false);
    ui->checkBox_6->setEnabled(false);

    ui->checkBox_5->setVisible(false);
    ui->checkBox_6->setVisible(false);

}

void MainWindow::AddPlayerBonuses()
{
    //Add Player bonuses to Player data
    Player[ui->comboBox_selectplayer->currentIndex()].bonuses = ui->plainTextEdit_bonuses->toPlainText();
}

void MainWindow::setPrestigeClass(bool check)
{
    //Set Prestige Class
    ui->checkBox_5->setVisible(check);
    ui->checkBox_6->setVisible(check);
    Player[ui->comboBox_selectplayer->currentIndex()].prestige = check;
}

void MainWindow::InitializeArmorsList()
{
    //Initialize list of Armors in Armor Combobox
    ui->comboBox_armor->addItem("=== Hełmy ===");
    ui->comboBox_armor->addItem("Hełm Standardowy (bez maski)");
    ui->comboBox_armor->addItem("Hełm Standardowy (z maską)");
    ui->comboBox_armor->addItem("Maska Pośmiertna");
    ui->comboBox_armor->addItem("Wizjer Kuwashii");
    ui->comboBox_armor->addItem("Interfejs Strażnika");
    ui->comboBox_armor->addItem("Hełm Pustułka");
    ui->comboBox_armor->addItem("Hełm Kondensatorowy");
    ui->comboBox_armor->addItem("Wizjer Archon");
    ui->comboBox_armor->addItem("Wizjer Umbra");
    ui->comboBox_armor->addItem("Kaptur Zwiadowczy");
    ui->comboBox_armor->addItem("Wizjer Pamięciowy");
    ui->comboBox_armor->addItem("Hełm Securitel");
    ui->comboBox_armor->addItem("Nakładka Delumcore");

    ui->comboBox_armor->addItem("=== Napierśniki ===");
    ui->comboBox_armor->addItem("Napierśnik N7");
    ui->comboBox_armor->addItem("Napierśnik Kassa Fabrication");
    ui->comboBox_armor->addItem("Napierśnik Serrice Council");
    ui->comboBox_armor->addItem("Napierśnik Rosenkov Materials");
    ui->comboBox_armor->addItem("Napierśnik Armax Arsenal");
    ui->comboBox_armor->addItem("Napierśnik Ariake Technologies");
    ui->comboBox_armor->addItem("Napierśnik Hahne-Kedar");

    ui->comboBox_armor->addItem("=== Naramienniki ===");
    ui->comboBox_armor->addItem("Naramienniki N7");
    ui->comboBox_armor->addItem("Naramienniki Kassa Fabrication");
    ui->comboBox_armor->addItem("Naramienniki Serrice Council");
    ui->comboBox_armor->addItem("Naramienniki Rosenkov Materials");
    ui->comboBox_armor->addItem("Naramienniki Armax Arsenal");
    ui->comboBox_armor->addItem("Naramienniki Ariake Technologies");
    ui->comboBox_armor->addItem("Naramienniki Hahne-Kedar");

    ui->comboBox_armor->addItem("=== Rękawice ===");
    ui->comboBox_armor->addItem("Rękawice N7");
    ui->comboBox_armor->addItem("Rękawice Kassa Fabrication");
    ui->comboBox_armor->addItem("Rękawice Serrice Council");
    ui->comboBox_armor->addItem("Rękawice Rosenkov Materials");
    ui->comboBox_armor->addItem("Rękawice Armax Arsenal");
    ui->comboBox_armor->addItem("Rękawice Ariake Technologies");
    ui->comboBox_armor->addItem("Rękawice Hahne-Kedar");

    ui->comboBox_armor->addItem("=== Nagolenniki ===");
    ui->comboBox_armor->addItem("Nagolenniki N7");
    ui->comboBox_armor->addItem("Nagolenniki Kassa Fabrication");
    ui->comboBox_armor->addItem("Nagolenniki Serrice Council");
    ui->comboBox_armor->addItem("Nagolenniki Rosenkov Materials");
    ui->comboBox_armor->addItem("Nagolenniki Armax Arsenal");
    ui->comboBox_armor->addItem("Nagolenniki Ariake Technologies");
    ui->comboBox_armor->addItem("Nagolenniki Hahne-Kedar");

    ui->comboBox_armor->addItem("=== Pancerze Specjalne ===");
    ui->comboBox_armor->addItem("Pancerz Cerberusa");
    ui->comboBox_armor->addItem("Pancerz Inferno");
    ui->comboBox_armor->addItem("Pancerz Terminusa");
    ui->comboBox_armor->addItem("Pancerz Zbieraczy");
    ui->comboBox_armor->addItem("Pancerz Krwawych Smoków");
    ui->comboBox_armor->addItem("Pancerz Rachmistrza");
    ui->comboBox_armor->addItem("Obrońca N7");
}

void MainWindow::UpdateView()
{
    ui->comboBox_selectplayer->setCurrentIndex(1);
    ui->comboBox_selectplayer->setCurrentIndex(0);
}

void MainWindow::ChangePlayer(int index)
{
    //Select Another Player

    //Clear All Player elements
    ClearAllPlayerElements();

    //Fill all elements with Selected Player Data

    //Set selected Player's name
    ui->lineEdit_miano1->setText(Player[index].name);

    //Set selected Player's skills
    QString skillWidget, armorWidget;
    for(int i=0; i<Player[index].ability.size();i++)
    {
        skillWidget = Player[index].ability[i].name + " " + Player[index].ability[i].level;
        ui->listWidget->addItem(skillWidget);
    }
    //Set selected Player's armors
    for(int i=0; i<Player[index].armour.size();i++)
    {
        armorWidget = Player[index].armour[i].name;
        ui->listWidget_armor->addItem(armorWidget);
    }
    //Set tooltips for armors
    for(int i=0;i<Player[index].armour.size();i++)
    {
      AddToolTip(Player[index].armour[i].name, index);
    }

    //Set selected Player's Omnikey
    for(int i=0; i<ui->comboBox_omni->count();i++)
    {
        if(ui->comboBox_omni->itemText(i) == Player[index].omnikey) ui->comboBox_omni->setCurrentIndex(i);
    }
    //Set selected Player's Omnimods
    for(int i=0; i<ui->comboBox_omni_mods->count();i++)
    {
        if(ui->comboBox_omni_mods->itemText(i) == Player[index].omnimod) ui->comboBox_omni_mods->setCurrentIndex(i);
    }
    //Set selected Player's Omniblade
    for(int i=0; i<ui->comboBox_omniblade->count();i++)
    {
        if(ui->comboBox_omniblade->itemText(i) == Player[index].omniblade) ui->comboBox_omniblade->setCurrentIndex(i);
    }
    //Set selected Player's Omniblade mod
    for(int i=0; i<ui->comboBox_omniblade_mods->count();i++)
    {
        if(ui->comboBox_omniblade_mods->itemText(i) == Player[index].omniblademod) ui->comboBox_omniblade_mods->setCurrentIndex(i);
    }

    //Set selected Player's Shield Generator
    for(int i=0; i<ui->comboBox_shield->count();i++)
    {
        if(ui->comboBox_shield->itemText(i) == Player[index].shieldgen) ui->comboBox_shield->setCurrentIndex(i);
    }

    //Set Tooltips for all above
    AddToolTip(Player[index].omnikey, index);
    AddToolTip(Player[index].omnimod, index);
    AddToolTip(Player[index].omniblade, index);
    AddToolTip(Player[index].omniblademod, index);
    AddToolTip(Player[index].shieldgen, index);

    //Set selected Player's weapons
    for(int i=0; i<Player[index].weapon.size();i++)
    {
        ui->tableWidget->insertRow(i);
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(Player[index].weapon[i].name));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(Player[index].weapon[i].Acc));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(Player[index].weapon[i].Recoil));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(Player[index].weapon[i].PA));
        ui->tableWidget->setItem(i,4,new QTableWidgetItem(Player[index].weapon[i].DMG));
        ui->tableWidget->item(i,1)->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->item(i,2)->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->item(i,3)->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->item(i,4)->setTextAlignment(Qt::AlignCenter);
    }

    //Set selected Player's specialization skill
    ui->comboBox_specialization->setCurrentIndex(Player[ui->comboBox_selectplayer->currentIndex()].specialization_id);
    ChangeSpecializationLabel(ui->comboBox_specialization->currentText());

    //Set status of Special Skill Effects CheckBoxes
    for(int i=0; i<Player[index].ability.size();i++)
    {
        if(Player[index].ability[i].name == "Pancerz Technologiczny") ui->checkBox->setEnabled(true);
        if(Player[index].ability[i].name == "Umocnienie") ui->checkBox_2->setEnabled(true);
        if(Player[index].ability[i].name == "Bariera") ui->checkBox_3->setEnabled(true);
        if(Player[index].ability[i].name == "Tryb Pustoszyciela") ui->checkBox_5->setEnabled(true);
        if(Player[index].ability[i].name == "Biotyczne Kule") ui->checkBox_6->setEnabled(true);
    }

    if(Player[index].skill_effects_id[0] == true) ui->checkBox->setChecked(true);
    if(Player[index].skill_effects_id[1] == true) ui->checkBox_2->setChecked(true);
    if(Player[index].skill_effects_id[2] == true) ui->checkBox_3->setChecked(true);
    if(Player[index].skill_effects_id[3] == true) ui->checkBox_4->setChecked(true);
    if(Player[index].skill_effects_id[4] == true) ui->checkBox_5->setChecked(true);
    if(Player[index].skill_effects_id[5] == true) ui->checkBox_6->setChecked(true);

    //Set Prestige Class
    if(Player[index].prestige == true){ ui->checkBox_7->setChecked(true); ui->checkBox_5->setVisible(true);ui->checkBox_6->setVisible(true);}

    //Set Player Bonuses
    ui->plainTextEdit_bonuses->setPlainText(Player[index].bonuses);

    //Set Player Equipment
    ui->plainTextEdit_equipment->setPlainText(Player[index].equipment);

    //Set Players armor and shield points
    ui->lineEdit_p1->setText(Player[index].armor_points);
    ui->lineEdit_p2->setText(Player[index].armor_max);
    ui->lineEdit_t1->setText(Player[index].shield_points);
    ui->lineEdit_t2->setText(Player[index].shield_max);
}

void MainWindow::AddToolTip(QString ItemName, int PlayerIndex)
{
    //Add ToolTip

    QString sToolTip = "";

    //Armors
    if(ItemName.startsWith("Hełm Standardowy")) sToolTip = "<center><b>Hełm Standardowy</b></center><br>+10% do pancerza (zdrowia)";
    else if(ItemName.startsWith("Maska Pośmiertna")) sToolTip = "<center><b>Maska Pośmiertna</b></center><br>+10% do walki wręcz";
    else if(ItemName.startsWith("Wizjer Kuwashii")) sToolTip = "<center><b>Wizjer Kuwashii</b></center><br>+5% do obrażeń od broni<br>+10% do strzałów w głowę";
    else if(ItemName.startsWith("Interfejs Strażnika")) sToolTip = "<center><b>Interfejs Strażnika</b></center><br>+10% do tarcz";
    else if(ItemName.startsWith("Hełm Pustułka")) sToolTip = "<center><b>Hełm Pustułka</b></center><br>+10% do zapasu amunicji";
    else if(ItemName.startsWith("Hełm Kondensatorowy")) sToolTip = "<center><b>Hełm Kondensatorowy</b></center><br>+10% do regeneracji tarcz";
    else if(ItemName.startsWith("Wizjer Archon")) sToolTip = "<center><b>Wizjer Archon</b></center><br>-10% zmniejszony koszt użycia mocy";
    else if(ItemName.startsWith("Wizjer Umbra")) sToolTip = "<center><b>Wizjer Umbra</b></center><br>+10% do obrażeń od mocy";
    else if(ItemName.startsWith("Kaptur Zwiadowczy")) sToolTip = "<center><b>Kaptur Zwiadowczy</b></center><br>+10% do obrażeń od broni";
    else if(ItemName.startsWith("Wizjer Pamięciowy")) sToolTip = "<center><b>Wizjer Pamięciowy</b></center><br>+5% do obrażeń od mocy<br>-5% zmniejszony koszt użycia mocy";
    else if(ItemName.startsWith("Hełm Securitel")) sToolTip = "<center><b>Hełm Securitel</b></center><br>+5% do tarcz<br>+5% do pancerza (życia)";
    else if(ItemName.startsWith("Nakładka Delumcore")) sToolTip = "<center><b>Nakładka Delumcore</b></center><br>+10% do obrażeń od broni<br>+5% do obrażeń od strzałów w głowę";

    else if(ItemName.startsWith("Napierśnik N7")) sToolTip = "<center><b>Napierśnik N7</b></center><br>+10% do pancerza (zdrowia)";
    else if(ItemName.startsWith("Napierśnik Kassa Fabrication")) sToolTip = "<center><b>Napierśnik Kassa Fabrication</b></center><br>-10% skrócony czas ładowania tarcz";
    else if(ItemName.startsWith("Napierśnik Serrice Council")) sToolTip = "<center><b>Napierśnik Serrice Council</b></center><br>+10% do obrażeń od mocy";
    else if(ItemName.startsWith("Napierśnik Rosenkov Materials")) sToolTip = "<center><b>Napierśnik Rosenkov Materials</b></center><br>-10% zmniejszony koszt użycia mocy";
    else if(ItemName.startsWith("Napierśnik Armax Arsenal")) sToolTip = "<center><b>Napierśnik Armax Arsenal</b></center><br>+10% do zapasu amunicji";
    else if(ItemName.startsWith("Napierśnik Ariake Technologies")) sToolTip = "<center><b>Napierśnik Ariake Technologies</b></center><br>+10% do obrażeń w walce wręcz";
    else if(ItemName.startsWith("Napierśnik Hahne-Kedar")) sToolTip = "<center><b>Napierśnik Hahne-Kedar</b></center><br>+10% do obrażeń od broni";

    else if(ItemName.startsWith("Naramienniki N7")) sToolTip = "<center><b>Naramienniki N7</b></center><br>+10% do pancerza (zdrowia)";
    else if(ItemName.startsWith("Naramienniki Kassa Fabrication")) sToolTip = "<center><b>Naramienniki Kassa Fabrication</b></center><br>-10% skrócony czas ładowania tarcz";
    else if(ItemName.startsWith("Naramienniki Serrice Council")) sToolTip = "<center><b>Naramienniki Serrice Council</b></center><br>+10% do obrażeń od mocy";
    else if(ItemName.startsWith("Naramienniki Rosenkov Materials")) sToolTip = "<center><b>Naramienniki Rosenkov Materials</b></center><br>-10% zmniejszony koszt użycia mocy";
    else if(ItemName.startsWith("Naramienniki Armax Arsenal")) sToolTip = "<center><b>Naramienniki Armax Arsenal</b></center><br>+5% do obrażeń od broni<br>+10% do obrażeń krytycznych";
    else if(ItemName.startsWith("Naramienniki Ariake Technologies")) sToolTip = "<center><b>Naramienniki Ariake Technologies</b></center><br>+10% do obrażeń w walce wręcz";
    else if(ItemName.startsWith("Naramienniki Hahne-Kedar")) sToolTip = "<center><b>Naramienniki Hahne-Kedar</b></center><br>+10% do obrażeń od broni";

    else if(ItemName.startsWith("Rękawice N7")) sToolTip = "<center><b>Rękawice N7</b></center><br>+10% do pancerza (zdrowia)";
    else if(ItemName.startsWith("Rękawice Kassa Fabrication")) sToolTip = "<center><b>Rękawice Kassa Fabrication</b></center><br>-10% skrócony czas ładowania tarcz";
    else if(ItemName.startsWith("Rękawice Serrice Council")) sToolTip = "<center><b>Rękawice Serrice Council</b></center><br>+10% do obrażeń od mocy";
    else if(ItemName.startsWith("Rękawice Rosenkov Materials")) sToolTip = "<center><b>Rękawice Rosenkov Materials</b></center><br>-10% zmniejszony koszt użycia mocy";
    else if(ItemName.startsWith("Rękawice Armax Arsenal")) sToolTip = "<center><b>Rękawice Armax Arsenal</b></center><br>+5% do obrażeń od broni<br>+10% do obrażeń krytycznych";
    else if(ItemName.startsWith("Rękawice Ariake Technologies")) sToolTip = "<center><b>Rękawice Ariake Technologies</b></center><br>+10% do obrażeń w walce wręcz";
    else if(ItemName.startsWith("Rękawice Hahne-Kedar")) sToolTip = "<center><b>Rękawice Hahne-Kedar</b></center><br>+10% do obrażeń od broni";

    else if(ItemName.startsWith("Nagolenniki N7")) sToolTip = "<center><b>Nagolenniki N7</b></center><br>+10% do pancerza (zdrowia)";
    else if(ItemName.startsWith("Nagolenniki Kassa Fabrication")) sToolTip = "<center><b>Nagolenniki Kassa Fabrication</b></center><br>-10% skrócony czas ładowania tarcz";
    else if(ItemName.startsWith("Nagolenniki Serrice Council")) sToolTip = "<center><b>Nagolenniki Serrice Council</b></center><br>+10% do obrażeń od mocy";
    else if(ItemName.startsWith("Nagolenniki Rosenkov Materials")) sToolTip = "<center><b>Nagolenniki Rosenkov Materials</b></center><br>-10% zmniejszony koszt użycia mocy";
    else if(ItemName.startsWith("Nagolenniki Armax Arsenal")) sToolTip = "<center><b>Nagolenniki Armax Arsenal</b></center><br>+10% do zapasu amunicji";
    else if(ItemName.startsWith("Nagolenniki Ariake Technologies")) sToolTip = "<center><b>Nagolenniki Ariake Technologies</b></center><br>+10% do obrażeń w walce wręcz";
    else if(ItemName.startsWith("Nagolenniki Hahne-Kedar")) sToolTip = "<center><b>Nagolenniki Hahne-Kedar</b></center><br>+10% do obrażeń od broni";

    else if(ItemName.startsWith("Pancerz Cerberusa")) sToolTip = "<center><b>Pancerz Cerberusa</b></center>"
                                                                  "<br>+10% do zapasu amunicji"
                                                                  "<br>+10% do tarcz<br>+20% do pancerza"
                                                                  "<br>+10% do obrażeń od broni";

    else if(ItemName.startsWith("Pancerz Inferno")) sToolTip = "<center><b>Pancerz Inferno</b></center>"
                                                                  "<br>+30% do obrażeń od mocy"
                                                                  "<br>-30% skrócony koszt ładowania mocy";

    else if(ItemName.startsWith("Pancerz Terminusa")) sToolTip = "<center><b>Pancerz Terminusa</b></center>"
                                                                  "<br>+15% do obrażeń w walce wręcz"
                                                                  "<br>+30% do tarcz<br>+15% do zapasu amunicji";

    else if(ItemName.startsWith("Pancerz Zbieraczy")) sToolTip = "<center><b>Pancerz Zbieraczy</b></center>"
                                                                  "<br>+20% do regeneracji tarcz"
                                                                  "<br>+20% do tarcz<br>+20% do pancerza";

    else if(ItemName.startsWith("Pancerz Krwawych Smoków")) sToolTip = "<center><b>Pancerz Krwawych Smoków</b></center>"
                                                                  "<br>-10% skrócony czas ładowania mocy"
                                                                  "<br>+20% do tarcz<br>+30% obrażeń od mocy";

    else if(ItemName.startsWith("Pancerz Rachmistrza")) sToolTip = "<center><b>Pancerz Rachmistrza</b></center>"
                                                                  "<br>+20% do obrażeń w walce wręcz"
                                                                  "<br>+10% do tarcz<br>+10% do pancerza"
                                                                  "<br>+10% do obrażeń od broni";

    else if(ItemName.startsWith("N7 Obrońca")) sToolTip = "<center><b>N7 Obrońca</b></center>"
                                                                  "<br>+20% do zapasu amunicji"
                                                                  "<br>+10% do tarcz<br>+10% do pancerza"
                                                                  "<br>+10% do obrażeń od broni";

    for(int i=0;i<Player[PlayerIndex].armour.size();i++)
    {
     if(ui->listWidget_armor->item(i)->text() == ItemName) ui->listWidget_armor->item(i)->setToolTip(sToolTip);
    }

    //Omnikeys
    if(ItemName.startsWith("Primo")) sToolTip = "<center><b>Omni-klucz Primo</b></center><br>Bonus tarcz: 0%<br>Premia technologiczna: 10% <br><br>";
    else if(ItemName.startsWith("Bluewire")) sToolTip = "<center><b>Omni-klucz Bluewire</b></center><br>Bonus tarcz: 10%<br>Premia technologiczna: 10% <br><br>";
    else if(ItemName.startsWith("Polaris")) sToolTip = "<center><b>Omni-klucz Polaris</b></center><br>Bonus tarcz: 20%<br>Premia technologiczna: 10% <br><br>";
    else if(ItemName.startsWith("Logic Arrest")) sToolTip = "<center><b>Omni-klucz Logic Arrest</b></center><br>Bonus tarcz: 15%<br>Premia technologiczna: 15% <br><br>";
    else if(ItemName.startsWith("Nexus")) sToolTip = "<center><b>Omni-klucz Nexus</b></center><br>Bonus tarcz: 15%<br>Premia technologiczna: 20% <br><br>";
    else if(ItemName.startsWith("Sawant")) sToolTip = "<center><b>Omni-klucz Rady Serrice</b></center><br>Bonus tarcz: 20%<br>Premia technologiczna: 15% <br><br>";
    else if(ItemName.startsWith("Kameleon")) sToolTip = "<center><b>Omni-klucz Primo</b></center><br>Bonus tarcz: 20%<br>Premia technologiczna: 20% <br><br>";
    else if(ItemName.startsWith("Cipher")) sToolTip = "<center><b>Omni-klucz Cipher</b></center><br>Bonus tarcz: 30%<br>Premia technologiczna: 20% <br><br>";
    else if(ItemName.startsWith("Evolva")) sToolTip = "<center><b>Omni-klucz Evolva</b></center><br>Bonus tarcz: 20%<br>Premia technologiczna: 30% <br><br>";
    else if(ItemName.startsWith("Alestire")) sToolTip = "<center><b>Omni-klucz Primo</b></center><br>Bonus tarcz: 30%<br>Premia technologiczna: 30% <br><br>";


    for(int i=0;i<Player[PlayerIndex].omnikey.size();i++)
    {
     if(ui->comboBox_omni->currentText() == ItemName) ui->comboBox_omni->setToolTip(sToolTip);
    }

    //Omnikey mods
    if(ItemName.startsWith("Osełka")) sToolTip = "<center><b>Mod Osełka</b></center><br>+20% do obrażeń od walki wręcz <br><br>";
    else if(ItemName.startsWith("Kompensator energetyczny")) sToolTip = "<center><b>Kompensator energetyczny</b></center><br>-30% do kosztu regeneracji tarcz <br><br>";
    else if(ItemName.startsWith("Precyzyjny")) sToolTip = "<center><b>Precyzyjny aplikator</b></center><br>+10 punktów procentowych do premii technologicznej <br><br>";
    else if(ItemName.startsWith("Zaawansowane sensory")) sToolTip = "<center><b>Zaawansowane sensory</b></center><br>Pozwala uzyskać od MG informacje na temat przeciwnika"
                                                                    " oraz okolicy. <br><br>";


    for(int i=0;i<Player[PlayerIndex].omnimod.size();i++)
    {
     if(ui->comboBox_omni_mods->currentText() == ItemName) ui->comboBox_omni_mods->setToolTip(sToolTip);
    }

    //Omni blades
    if(ItemName.startsWith("Krótkie")) sToolTip = "<center><b>Krótkie Omni-Ostrze</b></center><br>Obrażenia: podstawowe dla rasy<br>"
            "Koszt ataku: podstawowy<br>"
            "Szansa na trafienie: 50<br>"
            "Dodatkowe właściwości: Brak<br>"
            "Dostępne warianty: krio-mod, modyfikacja zapalająca, wzmacniacze kinetyczne, układ optymalizacyjny <br><br>";
    else if(ItemName.startsWith("Długie")) sToolTip = "<center><b>Długie Omni-Ostrze</b></center><br>Obrażenia: +20%<br>"
            "Koszt ataku: +1 PA<br>"
            "Szansa na trafienie: 50<br>"
            "Dodatkowe właściwości: Brak<br>"
            "Dostępne warianty: krio-mod, modyfikacja zapalająca, wzmacniacze kinetyczne, układ optymalizacyjny <br><br>";
    else if(ItemName.startsWith("Omni-Pięść")) sToolTip = "<center><b>Omni-Pięść</b></center><br>Obrażenia: -20%<br>"
            "Koszt ataku: -1 PA<br>"
            "Szansa na trafienie: 50<br>"
            "Dodatkowe właściwości: Przy każdym uderzeniu 30% szans na ogłuszenie wroga. Utrzymuje się przez turę, cel uodparnia się po pierwszej aktywacji efektu<br>"
            "Dostępne warianty: krio-mod, mod. zapalający, wzmacniacze kinetyczne, omni-kolce, układ optymalizacyjny <br><br>";
     else if(ItemName.startsWith("Omni-Pazury")) sToolTip = "<center><b>Omni-Pazury</b></center><br>Obrażenia: -10%<br>"
            "Koszt ataku: -2 PA<br>"
            "Szansa na trafienie: 50<br>"
            "Dodatkowe właściwości: Przy każdym ataku istnieje 20% szans, że nie zmniejszy się liczba PA i limit akcji w turze<br>"
            "Dostępne warianty: krio-mod, mod. zapalający, wzmacniacze kinetyczne, układ optymalizacyjny<br><br>";
    else if(ItemName.startsWith("Omni-Kusza")) sToolTip = "<center><b>Omni-Kusza</b></center><br>Obrażenia: 400<br>"
            "Koszt ataku: 6 PA<br>"
            "Szansa na trafienie: 30<br>"
            "Dodatkowe właściwości: Brak możliwości stosowania lekkich i ciężkich ataków w walce wręcz<br>"
            "Dostępne warianty: układ optymalizacyjny, strzały kierowane, przeciwpancerne i dysrupcyjne<br><br>";
      else if(ItemName.startsWith("Omni-Tonfa")) sToolTip = "<center><b>Omni-Tonfa</b></center><br>Obrażenia: podstawowe dla rasy<br>"
            "Koszt ataku: +1 PA<br>"
            "Szansa na trafienie: 30<br>"
            "Dodatkowe właściwości: Brak<br>"
            "Dostępne warianty: krio-mod, mod. zapalająca, wzmacniacze kinetyczne, układ optymalizacyjny<br><br>";
    else if(ItemName.startsWith("Omni-Kama")) sToolTip = "<center><b>Omni-Kama</b></center><br>Obrażenia: 400<br>"
            "Koszt ataku: -1 PA<br>"
            "Szansa na trafienie: 30<br>"
            "Dodatkowe właściwości: Brak<br>"
            "Dostępne warianty: krio-mod, mod. zapalająca, wzmacniacze kinetyczne, układ optymalizacyjny<br><br>";
    else if(ItemName.startsWith("Omni-Kilof")) sToolTip = "<center><b>Omni-Kilof</b></center><br>Szacun na górniczej dzielni<br><br>";



    for(int i=0;i<Player[PlayerIndex].omniblade.size();i++)
    {
     if(ui->comboBox_omniblade->currentText() == ItemName) ui->comboBox_omniblade->setToolTip(sToolTip);

    }

    //Omniblade mods
    if(ItemName.startsWith("Krio")) sToolTip = "<center><b>Krio-Mod</b></center><br>Trafiony przeciwnik zostaje poddany efektowi 3-poziomowego kriowybuchu. Ponieważ do aktywacji dochodzi za pośrednictwem omni-broni, aktywne osłony nie negują działania modyfikacji. Może stanowić inicjator kombinacji.<br><br>";
    else if(ItemName.startsWith("Modyfikacja")) sToolTip = "<center><b>Modyfikacja Zapalająca</b></center><br>Broń zadaje dodatkowe 20% obrażeń i zyskuje efekt obszarowy, który rani wrogów w bezpośrednim sąsiedztwie celu. Posiada 20% szans na podpalenie ofiary.<br><br>";
    else if(ItemName.startsWith("Wzmacniacze")) sToolTip = "<center><b>Wzmacniacze Kinetyczne</b></center><br>Dodatkowe 10% obrażeń i dodanie do każdego ataku szansy na odrzucenie z siłą 750N. Może stanowić detonator kombinacji. W przeciwieństwie do typowych ataków biotycznych - omija tarcze.<br><br>";
    else if(ItemName.startsWith("Omni-kolce")) sToolTip = "<center><b>Omni-Kolce</b></center><br>Niwelują podstawową karę do obrażeń omni-pięści.<br><br>";
    else if(ItemName.startsWith("Układ")) sToolTip = "<center><b>Układ Optymalizacyjny</b></center><br>Atak omni-bronią jest tańszy o 1PA.<br><br>";
    else if(ItemName.startsWith("Strzały kierowane")) sToolTip = "<center><b>Strzały Kierowane</b></center><br>Po aktywacji (3 PA), podczas pięciu kolejnych ataków, podstawowa celność omni-kuszy wzrasta do 60.<br><br>";
    else if(ItemName.startsWith("Strzały przeciwpancerne")) sToolTip = "<center><b>Strzały Przeciwpancerne</b></center><br>Po aktywacji (3 PA), podczas pięciu kolejnych wystrzałów, siła omni-kuszy jest zwiększona o 20%. Dodatkowo skuteczne trafienie nakłada jednorazowe 20% osłabienie pancerza.<br><br>";
    else if(ItemName.startsWith("Strzały dysrupcyjne")) sToolTip = "<center><b>Strzały Dysrupcyjne</b></center><br>Po aktywacji (3 PA), podczas pięciu kolejnych ataków, omni-kusza zadaje dodatkowe 10% obrażeń i uniemożliwia jakąkolwiek regenerację tarcz przez okres 2 tur (zatrzymuje również samoczynne odnawianie osłon).<br><br>";

    for(int i=0;i<Player[PlayerIndex].omniblademod.size();i++)
    {
     if(ui->comboBox_omniblade_mods->currentText() == ItemName) ui->comboBox_omniblade_mods->setToolTip(sToolTip);

    }

    //Shield generator
    if(ItemName.endsWith("Standardowy")) sToolTip = "<center><b>Standardowy</b></center><br>Pojemność: 650"
            "<br>Koszt odnowienia: 12 PA<br><br>";
    else if(ItemName.startsWith("Standardowy wzmocniony")) sToolTip = "<center><b>Standardowy wzmocniony</b></center><br>Pojemność: 750"
            "<br>Koszt odnowienia: 10,5 PA<br><br>";
    else if(ItemName.startsWith("Niezłomny")) sToolTip = "<center><b>Niezłomny</b></center><br>Pojemność: 860"
            "<br>Koszt odnowienia: 12 PA<br><br>";
    else if(ItemName.startsWith("Hyperion")) sToolTip = "<center><b>Hyperion</b></center><br>Pojemność: 650"
            "<br>Koszt odnowienia: 6 PA"
            "<br>Dodatkowe: Odnawia się samoczynnie po jednej turze bez otrzymania obrażeń<br><br>";
    else if(ItemName.startsWith("Bandyta")) sToolTip = "<center><b>Bandyta</b></center><br>Pojemność: 800"
            "<br>Koszt odnowienia: 9 PA<br><br>";
    else if(ItemName.startsWith("Bestia")) sToolTip = "<center><b>Bestia</b></center><br>Pojemność: 750"
            "<br>Koszt odnowienia: 10 PA"
            "<br>Dodatkowy: W momencie, gdy stan tarcz spada do zera, użytkownik otrzymuje jednorazowy bonus +15% do obrażeń w walce wręcz.<br><br>";
    else if(ItemName.startsWith("Wojownik")) sToolTip = "<center><b>Wojownik</b></center><br>Pojemność: 750"
            "<br>Koszt odnowienia: 10 PA"
            "<br>Dodatkowy: W momencie, gdy stan tarcz sięgnie zera, użytkownik otrzymuje jednorazowy bonus +15% do obrażeń od broni.<br><br>";
    else if(ItemName.startsWith("Strażnik")) sToolTip = "<center><b>Strażnik</b></center><br>Pojemność: 750"
            "<br>Koszt odnowienia: 10 PA"
            "<br>Dodatkowy: Po wyładowaniu tarcz użytkownik otrzymuje jednorazowy bonus +15% do obrażeń od mocy.<br><br>";
    else if(ItemName.startsWith("Tajfun")) sToolTip = "<center><b>Tajfun</b></center><br>Pojemność: 850"
            "<br>Koszt odnowienia: 8 PA"
            "<br>Dodatkowe: Odnawia się samoczynnie po jednej turze bez otrzymania obrażeń<br><br>";
    else if(ItemName.startsWith("Cierń")) sToolTip = "<center><b>Cierń</b></center><br>Pojemność: 870"
            "<br>Koszt odnowienia: 10 PA"
            "<br>Dodatkowy: Odpycha cele w promieniu 1 metra z siła 500N<br><br>";
    else if(ItemName.startsWith("Ostatnia Szansa")) sToolTip = "<center><b>Ostatnia szansa</b></center><br>Pojemność: 870"
            "<br>Koszt odnowienia: 8 PA"
            "<br>Dodatkowy: Ten generator pozwala na natychmiastowe przywrócenie stanu tarcz do 10% w momencie, gdy ten sięga zeru, jednakże jest to działanie jednorazowe, dostępne dopiero po 4 turach od ostatniego użycia.<br><br>";
    else if(ItemName.startsWith("Ares")) sToolTip = "<center><b>Ares</b></center><br>Pojemność: 870"
            "<br>Koszt odnowienia: 10 PA"
            "<br>Dodatkowy: Generator, którego tarcze mają zdolność do wybuchu - w momencie, w którym użytkownik traci tę barierę, generator, przy użyciu składowanych rezerw tarcz, wyzwala wybuch, rażący wszystkich przeciwników znajdujących się w promieniu 4 metrów. Eksplozja zadaje jednorazowo 500 obrażeń.<br><br>";
    else if(ItemName.startsWith("Elektrowstrząs")) sToolTip = "<center><b>Elektrowstrząs</b></center><br>Pojemność: 870"
            "<br>Koszt odnowienia: 10 PA"
            "<br>Dodatkowy: Grom to generator mający podobne właściwości do Aresa - pozwala na zdetonowanie zapasowych tarcz, które wcześniej przechowuje, a wybuch przeistacza się w falę przeciążeniową, zadającą 500 obrażeń syntetykom oraz uszkadzającą tarcze przeciwników znajdujących się w promieniu 4 metrów, obniżając ich poziom o 50%.<br><br>";
    else if(ItemName.startsWith("Feniks")) sToolTip = "<center><b>Feniks</b></center><br>Pojemność: 870"
            "<br>Koszt odnowienia: 10 PA"
            "<br>Dodatkowy: Feniks jest generatorem pozwalającym na podpalenie wrogów znajdujących się odpowiednio blisko za pomocą wytwarzanych przez siebie tarcz. Stanowi inicjator poziomu drugiego dla kombinacji ogniowych, jednocześnie wywołuje u przeciwników organicznych panikę. Jego zasięg wynosi 1m.<br><br>";
    else if(ItemName.startsWith("Grom")) sToolTip = "<center><b>Grom</b></center><br>Pojemność: 870"
            "<br>Koszt odnowienia: 10 PA"
            "<br>Dodatkowy: Generator tarcz swoim działaniem przypominający nieco Feniksa oraz Ciernia. Stanowi inicjator poziomu drugiego dla kombinacji technologicznych, jednocześnie ogłuszając przeciwników organicznych. Działa na cele znajdujące się w odległości 1m. <br><br>";
    else if(ItemName.startsWith("Ortos")) sToolTip = "<center><b>Ortos</b></center><br>Pojemność: 1250"
            "<br>Koszt odnowienia: 6 PA"
            "<br>Dodatkowy: Odnawia się samoczynnie po jednej turze bez otrzymanych obrażeń.<br><br>";
    else if(ItemName.startsWith("Hydra")) sToolTip = "<center><b>Hydra</b></center><br>Pojemność: 1500"
            "<br>Koszt odnowienia: 5 PA"
            "<br>Dodatkowy: Odnawia się samoczynnie po jednej turze bez otrzymanych obrażeń.<br><br>";

    for(int i=0;i<Player[PlayerIndex].shieldgen.size();i++)
    {
     if(ui->comboBox_shield->currentText() == ItemName) ui->comboBox_shield->setToolTip(sToolTip);

    }

}

void MainWindow::InitializeOmniList()
{
    //Initialize list of omnitools in Omni Tool Combobox

   ui->comboBox_omni->addItem("Brak");
   ui->comboBox_omni->addItem("Primo");
   ui->comboBox_omni->addItem("Bluewire");
   ui->comboBox_omni->addItem("Polaris");
   ui->comboBox_omni->addItem("Logic Arrest");
   ui->comboBox_omni->addItem("Nexus");
   ui->comboBox_omni->addItem("Sawant");
   ui->comboBox_omni->addItem("Kameleon");
   ui->comboBox_omni->addItem("Cipher");
   ui->comboBox_omni->addItem("Evolva");
   ui->comboBox_omni->addItem("Alestire");

   ui->comboBox_omni_mods->addItem("Brak");
   ui->comboBox_omni_mods->addItem("Kompensator energetyczny");
   ui->comboBox_omni_mods->addItem("Osełka");
   ui->comboBox_omni_mods->addItem("Precyzyjny aplikator");
   ui->comboBox_omni_mods->addItem("Zaawansowane sensory");

   ui->comboBox_omniblade->addItem("Brak");
   ui->comboBox_omniblade->addItem("Krótkie Omni-ostrze");
   ui->comboBox_omniblade->addItem("Długie Omni-ostrze");
   ui->comboBox_omniblade->addItem("Omni-Pięść");
   ui->comboBox_omniblade->addItem("Omni-Pazury");
   ui->comboBox_omniblade->addItem("Omni-Kusza");
   ui->comboBox_omniblade->addItem("Omni-Tonfa");
   ui->comboBox_omniblade->addItem("Omni-Kama");
   ui->comboBox_omniblade->addItem("Omni-Kilof");

   ui->comboBox_omniblade_mods->addItem("Brak");
   ui->comboBox_omniblade_mods->addItem("Krio-mod");
   ui->comboBox_omniblade_mods->addItem("Modyfikacja zapalająca");
   ui->comboBox_omniblade_mods->addItem("Wzmacniacze kinetyczne");
   ui->comboBox_omniblade_mods->addItem("Omni-kolce");
   ui->comboBox_omniblade_mods->addItem("Układ optymalizacyjny");
   ui->comboBox_omniblade_mods->addItem("Strzały kierowane");
   ui->comboBox_omniblade_mods->addItem("Strzały przeciwpancerne");
   ui->comboBox_omniblade_mods->addItem("Strzały dysrupcyjne");
}

void MainWindow::AddArmor()
{
    //Add armor

    //Add armor to Player
    QString armorName = ui->comboBox_armor->currentText();
    Player[ui->comboBox_selectplayer->currentIndex()].AddArmor(armorName);

    //Add armor to List Widget
    ui->listWidget_armor->addItem(armorName);

    //Add tool tip containing armor specyfication
    AddToolTip(armorName,ui->comboBox_selectplayer->currentIndex());
}

void MainWindow::RemoveArmor()
{
    //Remove Armor
    int currId = ui->listWidget_armor->currentRow(); //Index of currently selected armor
    if(currId!=-1) //if any selected
    {
        //Remove armor from player data
        Player[ui->comboBox_selectplayer->currentIndex()].armour.remove(currId);
        //Remove armor from List Widget
        delete ui->listWidget_armor->currentItem();
    }
}

void MainWindow::AddOmniKey(QString name)
{
    //Add omni key to player data
    int index = ui->comboBox_selectplayer->currentIndex();
    Player[index].omnikey = name;
    AddToolTip(name,index);
}

void MainWindow::AddOmniMods(QString name)
{
    //Add omni mod to player data
    int index = ui->comboBox_selectplayer->currentIndex();
    Player[index].omnimod = name;
    AddToolTip(name,index);
}

void MainWindow::AddOmniBlade(QString name)
{
    //Add omni blade to player data
    int index = ui->comboBox_selectplayer->currentIndex();
    Player[index].omniblade = name;
    AddToolTip(name,index);
}

void MainWindow::AddOmniBladeMod(QString name)
{
    //Add omni blade mod to player data
    int index = ui->comboBox_selectplayer->currentIndex();
    Player[index].omniblademod = name;
    AddToolTip(name,index);
}

void MainWindow::AddShieldGen(QString name)
{
    //Add shield generator to Player data
    int index = ui->comboBox_selectplayer->currentIndex();
    Player[index].shieldgen = name;
    AddToolTip(name,index);
}

void MainWindow::CalculateMasteryChance()
{
    //Calculate Mastery Chances

    //Calculate BojPoints, BioPoints, TechPoints etc
    int iBojPoints = 0, iBioPoints = 0, iTechPoints = 0, iKlaPoints = 0, iPresPoints = 0;
    for(int i=0;i<Player[ui->comboBox_selectplayer->currentIndex()].ability.size();i++)
    {
        if(Player[ui->comboBox_selectplayer->currentIndex()].ability[i].type == "Boj")
        {
            if(Player[ui->comboBox_selectplayer->currentIndex()].ability[i].level.startsWith("4")) iBojPoints += 4;
            else if(Player[ui->comboBox_selectplayer->currentIndex()].ability[i].level.startsWith("5")) iBojPoints += 5;
            else if(Player[ui->comboBox_selectplayer->currentIndex()].ability[i].level.startsWith("6")) iBojPoints += 6;
            else iBojPoints += Player[ui->comboBox_selectplayer->currentIndex()].ability[i].level.toInt();
        }
        if(Player[ui->comboBox_selectplayer->currentIndex()].ability[i].type == "Bio")
        {
            if(Player[ui->comboBox_selectplayer->currentIndex()].ability[i].level.startsWith("4")) iBioPoints += 4;
            else if(Player[ui->comboBox_selectplayer->currentIndex()].ability[i].level.startsWith("5")) iBioPoints += 5;
            else if(Player[ui->comboBox_selectplayer->currentIndex()].ability[i].level.startsWith("6")) iBioPoints += 6;
            else iBioPoints += Player[ui->comboBox_selectplayer->currentIndex()].ability[i].level.toInt();
        }
        if(Player[ui->comboBox_selectplayer->currentIndex()].ability[i].type == "Tech")
        {
            if(Player[ui->comboBox_selectplayer->currentIndex()].ability[i].level.startsWith("4")) iTechPoints += 4;
            else if(Player[ui->comboBox_selectplayer->currentIndex()].ability[i].level.startsWith("5")) iTechPoints += 5;
            else if(Player[ui->comboBox_selectplayer->currentIndex()].ability[i].level.startsWith("6")) iTechPoints += 6;
            else iTechPoints += Player[ui->comboBox_selectplayer->currentIndex()].ability[i].level.toInt();
        }
        if(Player[ui->comboBox_selectplayer->currentIndex()].ability[i].type == "Kla")
        {
            if(Player[ui->comboBox_selectplayer->currentIndex()].ability[i].level.startsWith("4")) iKlaPoints += 4;
            else if(Player[ui->comboBox_selectplayer->currentIndex()].ability[i].level.startsWith("5")) iKlaPoints += 5;
            else if(Player[ui->comboBox_selectplayer->currentIndex()].ability[i].level.startsWith("6")) iKlaPoints += 6;
            else iKlaPoints += Player[ui->comboBox_selectplayer->currentIndex()].ability[i].level.toInt();

            if(Player[ui->comboBox_selectplayer->currentIndex()].ability[i].name == "Pancerz Technologiczny") iTechPoints += iKlaPoints;
            else if(Player[ui->comboBox_selectplayer->currentIndex()].ability[i].name == "Nowa") iBioPoints += iKlaPoints;
            else if(Player[ui->comboBox_selectplayer->currentIndex()].ability[i].name == "Szarża Biotyczna") iBioPoints += iKlaPoints;
            else if(Player[ui->comboBox_selectplayer->currentIndex()].ability[i].name == "Amunicja Dysrupcyjna") iBojPoints += iKlaPoints;
            else if(Player[ui->comboBox_selectplayer->currentIndex()].ability[i].name == "Kamuflaż Taktyczny") iTechPoints += iKlaPoints;
        }
        if(Player[ui->comboBox_selectplayer->currentIndex()].ability[i].type == "Pres")
        {
            if(Player[ui->comboBox_selectplayer->currentIndex()].ability[i].level.startsWith("4")) iPresPoints += 4;
            else if(Player[ui->comboBox_selectplayer->currentIndex()].ability[i].level.startsWith("5")) iPresPoints += 5;
            else if(Player[ui->comboBox_selectplayer->currentIndex()].ability[i].level.startsWith("6")) iPresPoints += 6;
            else iPresPoints += Player[ui->comboBox_selectplayer->currentIndex()].ability[i].level.toInt();

            if(Player[ui->comboBox_selectplayer->currentIndex()].ability[i].name == "Tryb Pustoszyciela") iBojPoints += iPresPoints;
            else if(Player[ui->comboBox_selectplayer->currentIndex()].ability[i].name == "Pakiet Stymulantów") iBojPoints += iPresPoints;
            else if(Player[ui->comboBox_selectplayer->currentIndex()].ability[i].name == "Strzelec Wyborowy") iBojPoints += iPresPoints;
            else if(Player[ui->comboBox_selectplayer->currentIndex()].ability[i].name == "Ciemny Kanał") iBioPoints += iPresPoints;
            else if(Player[ui->comboBox_selectplayer->currentIndex()].ability[i].name == "Kula Ciemnej Energii") iBioPoints += iPresPoints;
            else if(Player[ui->comboBox_selectplayer->currentIndex()].ability[i].name == "Biotyczne Kule") iBioPoints += iPresPoints;
            else if(Player[ui->comboBox_selectplayer->currentIndex()].ability[i].name == "Skupienie Biotyczne") iBioPoints += iPresPoints;
            else if(Player[ui->comboBox_selectplayer->currentIndex()].ability[i].name == "Bicz") iBioPoints += iPresPoints;
            else if(Player[ui->comboBox_selectplayer->currentIndex()].ability[i].name == "Roztrzaskanie") iBioPoints += iPresPoints;
            else if(Player[ui->comboBox_selectplayer->currentIndex()].ability[i].name == "Pole Unicestwienia") iBioPoints += iPresPoints;
            else if(Player[ui->comboBox_selectplayer->currentIndex()].ability[i].name == "Ciśnięcie") iBioPoints += iPresPoints;
            else if(Player[ui->comboBox_selectplayer->currentIndex()].ability[i].name == "Wzmocnienie Tarcz") iTechPoints += iPresPoints;
            else if(Player[ui->comboBox_selectplayer->currentIndex()].ability[i].name == "Pylon Zaopatrzenia") iTechPoints += iPresPoints;
            else if(Player[ui->comboBox_selectplayer->currentIndex()].ability[i].name == "Płomiennik") iTechPoints += iPresPoints;
            else if(Player[ui->comboBox_selectplayer->currentIndex()].ability[i].name == "Atak z Ukrycia") iTechPoints += iPresPoints;
            else if(Player[ui->comboBox_selectplayer->currentIndex()].ability[i].name == "Elektryczne Cięcie") iTechPoints += iPresPoints;
            else if(Player[ui->comboBox_selectplayer->currentIndex()].ability[i].name == "Mina Zwiadowcza") iTechPoints += iPresPoints;
            else if(Player[ui->comboBox_selectplayer->currentIndex()].ability[i].name == "Przynęta") iTechPoints += iPresPoints;
            else if(Player[ui->comboBox_selectplayer->currentIndex()].ability[i].name == "Atak Dewastatora") iTechPoints += iPresPoints;
            else if(Player[ui->comboBox_selectplayer->currentIndex()].ability[i].name == "Granaty Łukowe") iTechPoints += iPresPoints;

            iPresPoints = 0;
        }
    }

    // CHECK IF SPECIALIZATION
    if(ui->comboBox_specialization->currentText()=="Brak specjalizacji")
    {
        int base = 30;
        int iBojChance,iBioChance,iTechChance;

        iBojChance = base + iBojPoints*5;
        iBioChance = base + iBioPoints*5;
        iTechChance = base + iTechPoints*5;

        if(iBojChance>90) iBojChance = 90;
        if(iBioChance>90) iBioChance = 90;
        if(iTechChance>90) iTechChance = 90;

        ui->lineEdit_2->setText(QString::number(iBojChance)+"%");
        ui->lineEdit_3->setText(QString::number(iBioChance)+"%");
        ui->lineEdit_4->setText(QString::number(iTechChance)+"%");
        ui->lineEdit_5->clear();

    }

    else
    {
        int base = 30;

        QString mastery;
        int iBojChance,iBioChance,iTechChance, iSpecChance;

        for(int i=0;i<Player[ui->comboBox_selectplayer->currentIndex()].ability.size();i++)
        {
            if(Player[ui->comboBox_selectplayer->currentIndex()].ability[i].name == ui->comboBox_specialization->currentText())
            {
                QString spec_type = Player[ui->comboBox_selectplayer->currentIndex()].ability[i].type;
                if(spec_type == "Boj") { iSpecChance = 50 + iBojPoints*5; mastery = "Boj";}
                else if(spec_type == "Bio") {iSpecChance = 50 + iBioPoints*5; mastery = "Bio";}
                else if(spec_type == "Tech") {iSpecChance = 50 + iTechPoints*5; mastery = "Tech";}
                else if(spec_type == "Kla")
                {
                    if(Player[ui->comboBox_selectplayer->currentIndex()].ability[i].name == "Pancerz Technologiczny") {iSpecChance = 50 + iTechPoints*5; mastery = "Tech";}
                    else if(Player[ui->comboBox_selectplayer->currentIndex()].ability[i].name == "Nowa") {iSpecChance = 50 + iBioPoints*5; mastery = "Bio";}
                    else if(Player[ui->comboBox_selectplayer->currentIndex()].ability[i].name == "Szarża Biotyczna") {iSpecChance = 50 + iBioPoints*5; mastery = "Bio";}
                    else if(Player[ui->comboBox_selectplayer->currentIndex()].ability[i].name == "Amunicja Dysrupcyjna") {iSpecChance = 50 + iBojPoints*5; mastery = "Boj";}
                    else if(Player[ui->comboBox_selectplayer->currentIndex()].ability[i].name == "Kamuflaż Taktyczny") {iSpecChance = 50 + iTechPoints*5;mastery = "Tech";}
                }
                else if(spec_type == "Pres")
                {
                    if(Player[ui->comboBox_selectplayer->currentIndex()].ability[i].name == "Tryb Pustoszyciela") {iSpecChance = 50 + iBojPoints*5; mastery = "Boj";}
                    else if(Player[ui->comboBox_selectplayer->currentIndex()].ability[i].name == "Pakiet Stymulantów") {iSpecChance = 50 + iBojPoints*5; mastery = "Boj";}
                    else if(Player[ui->comboBox_selectplayer->currentIndex()].ability[i].name == "Strzelec Wyborowy") {iSpecChance = 50 + iBojPoints*5; mastery = "Boj";}
                    else if(Player[ui->comboBox_selectplayer->currentIndex()].ability[i].name == "Ciemny Kanał") {iSpecChance = 50 + iBioPoints*5; mastery = "Bio";}
                    else if(Player[ui->comboBox_selectplayer->currentIndex()].ability[i].name == "Kula Ciemnej Energii") {iSpecChance = 50 + iBioPoints*5; mastery = "Bio";}
                    else if(Player[ui->comboBox_selectplayer->currentIndex()].ability[i].name == "Biotyczne Kule") {iSpecChance = 50 + iBioPoints*5; mastery = "Bio";}
                    else if(Player[ui->comboBox_selectplayer->currentIndex()].ability[i].name == "Skupienie Biotyczne") {iSpecChance = 50 + iBioPoints*5; mastery = "Bio";}
                    else if(Player[ui->comboBox_selectplayer->currentIndex()].ability[i].name == "Bicz") {iSpecChance = 50 + iBioPoints*5; mastery = "Bio";}
                    else if(Player[ui->comboBox_selectplayer->currentIndex()].ability[i].name == "Roztrzaskanie") {iSpecChance = 50 + iBioPoints*5; mastery = "Bio";}
                    else if(Player[ui->comboBox_selectplayer->currentIndex()].ability[i].name == "Pole Unicestwienia") {iSpecChance = 50 + iBioPoints*5; mastery = "Bio";}
                    else if(Player[ui->comboBox_selectplayer->currentIndex()].ability[i].name == "Ciśnięcie") {iSpecChance = 50 + iBioPoints*5; mastery = "Bio";}
                    else if(Player[ui->comboBox_selectplayer->currentIndex()].ability[i].name == "Wzmocnienie Tarcz") {iSpecChance = 50 + iTechPoints*5; mastery = "Tech";}
                    else if(Player[ui->comboBox_selectplayer->currentIndex()].ability[i].name == "Pylon Zaopatrzenia") {iSpecChance = 50 + iTechPoints*5; mastery = "Tech";}
                    else if(Player[ui->comboBox_selectplayer->currentIndex()].ability[i].name == "Płomiennik") {iSpecChance = 50 + iTechPoints*5; mastery = "Tech";}
                    else if(Player[ui->comboBox_selectplayer->currentIndex()].ability[i].name == "Atak z Ukrycia") {iSpecChance = 50 + iTechPoints*5; mastery = "Tech";}
                    else if(Player[ui->comboBox_selectplayer->currentIndex()].ability[i].name == "Elektryczne Cięcie") {iSpecChance = 50 + iTechPoints*5; mastery = "Tech";}
                    else if(Player[ui->comboBox_selectplayer->currentIndex()].ability[i].name == "Mina Zwiadowcza") {iSpecChance = 50 + iTechPoints*5; mastery = "Tech";}
                    else if(Player[ui->comboBox_selectplayer->currentIndex()].ability[i].name == "Przynęta") {iSpecChance = 50 + iTechPoints*5; mastery = "Tech";}
                    else if(Player[ui->comboBox_selectplayer->currentIndex()].ability[i].name == "Atak Dewastatora") {iSpecChance = 50 + iTechPoints*5; mastery = "Tech";}
                    else if(Player[ui->comboBox_selectplayer->currentIndex()].ability[i].name == "Granaty Łukowe") {iSpecChance = 50 + iTechPoints*5; mastery = "Tech";}
                }
            }

        }

        if(mastery == "Boj")
        {
        base = 20;
        iBojChance = base + iBojPoints*5;
        base = 30;
        iBioChance = base + iBioPoints*5;
        iTechChance = base + iTechPoints*5;
        }
        else if(mastery == "Bio")
        {
            base = 20;
            iBioChance = base + iBioPoints*5;
            base = 30;
            iBojChance = base + iBojPoints*5;
            iTechChance = base + iTechPoints*5;
        }
        else if(mastery == "Tech")
        {
            base = 20;
            iTechChance = base + iTechPoints*5;
            base = 30;
            iBioChance = base + iBioPoints*5;
            iBojChance = base + iBojPoints*5;
        }

        if(iBojChance>90) iBojChance = 90;
        if(iBioChance>90) iBioChance = 90;
        if(iTechChance>90) iTechChance = 90;
        if(iSpecChance>90) iSpecChance = 90;


        //PRINT CHANCES
        ui->lineEdit_2->setText(QString::number(iBojChance)+"%");
        ui->lineEdit_3->setText(QString::number(iBioChance)+"%");
        ui->lineEdit_4->setText(QString::number(iTechChance)+"%");
        ui->lineEdit_5->setText(QString::number(iSpecChance)+"%");

        }
}

void MainWindow::InitializeShieldGenList()
{
    //Initialize list of shield generators in Shield Generator ComboBox
    ui->comboBox_shield->addItem("Brak");
    ui->comboBox_shield->addItem("Standardowy");
    ui->comboBox_shield->addItem("Standardowy wzmocniony");
    ui->comboBox_shield->addItem("Niezłomny");
    ui->comboBox_shield->addItem("Hyperion");
    ui->comboBox_shield->addItem("Bandyta");
    ui->comboBox_shield->addItem("Bestia");
    ui->comboBox_shield->addItem("Wojownik");
    ui->comboBox_shield->addItem("Strażnik");
    ui->comboBox_shield->addItem("Tajfun");
    ui->comboBox_shield->addItem("Cierń");
    ui->comboBox_shield->addItem("Ostatnia Szansa");
    ui->comboBox_shield->addItem("Ares");
    ui->comboBox_shield->addItem("Elektrowstrząs");
    ui->comboBox_shield->addItem("Feniks");
    ui->comboBox_shield->addItem("Grom");
    ui->comboBox_shield->addItem("Ortos");
    ui->comboBox_shield->addItem("Hydra");

}

void MainWindow::InitializePlayers()
{
    //Initialize list of the players
    NumOfPlayers = 8;
    for(int i=0;i<NumOfPlayers;i++)
        {
         ui->comboBox_selectplayer->setItemText(i,"Gracz " + QString::number(i+1));
        }

    Player.clear();

    for(int i=0;i<NumOfPlayers;i++)
    {
        player plr;
        plr.specialization_id = 0;
        plr.prestige = false;
        plr.skill_effects_id[0] = 0;
        plr.skill_effects_id[1] = 0;
        plr.skill_effects_id[2] = 0;
        plr.skill_effects_id[3] = 0;
        plr.skill_effects_id[4] = 0;
        plr.skill_effects_id[5] = 0;
        Player.append(plr);
    }
}

void MainWindow::on_actionOmni_Kalkulator_triggered()
{
    calc.setVisible(true);
}
