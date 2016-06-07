#include "calculator.h"
#include "ui_calculator.h"
#include <QtMath>

calculator::calculator(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::calculator)
{
    ui->setupUi(this);
    InitializeComboBoxLists();
    ui->tabWidget->setCurrentIndex(0);
}

calculator::~calculator()
{
    delete ui;
}

void calculator::InitializeComboBoxLists()
{
    ui->comboBox->addItem("Broń samoczynna");
    ui->comboBox->addItem("Broń samopowtarzalna");
    ui->comboBox->addItem("Strzelba");
    ui->comboBox->addItem("Atak omni-ostrzem (normalny)");
    ui->comboBox->addItem("Atak omni-ostrzem (ciężki)");
    ui->comboBox->addItem("Atak omni-ostrzem (obszarowy)");
    ui->comboBox->addItem("Użycie zdolności");

    ui->comboBox_wpn_type->addItem("Broń samoczynna");
    ui->comboBox_wpn_type->addItem("Broń samopowtarzalna");
    ui->comboBox_wpn_type->addItem("Strzelba");
    ui->comboBox_wpn_type->addItem("Atak omni-ostrzem");
    ui->comboBox_wpn_type->addItem("Użycie zdolności");
    ui->comboBox_wpn_type->addItem("Kombinacja");
}

void calculator::GenerateHittingChanceCode()
{
    QString actionName = ui->comboBox->currentText();
    QString playername;
    QString PA_cost;
    int baseAcc = 50;

    if(actionName.endsWith("samoczynna"))
    {
        playername = ui->lineEdit->text();
        actionName = "SERIA Z: " + ui->lineEdit_wpnName->text().toUpper();
        PA_cost = ui->spinBox_PA->text();

        setCodeHeader(playername,actionName,PA_cost);
        setCodeSuccesChance(baseAcc);
        setDice("4d100");
    }

    else if(actionName.endsWith("samopowtarzalna"))
    {
        playername = ui->lineEdit->text();
        actionName = "STRZAŁ Z: " + ui->lineEdit_wpnName->text().toUpper();
        PA_cost = ui->spinBox_PA->text();

        setCodeHeader(playername,actionName,PA_cost);
        setCodeSuccesChance(baseAcc);
        setDice("1d100");
    }

    else if(actionName.endsWith("Strzelba"))
    {
        playername = ui->lineEdit->text();
        actionName = "STRZAŁ Z: " + ui->lineEdit_wpnName->text().toUpper();
        PA_cost = ui->spinBox_PA->text();

        setCodeHeader(playername,actionName,PA_cost);
        setCodeSuccesChance(baseAcc);
    }

    else if(actionName.endsWith("(ciężki)"))
    {
        playername = ui->lineEdit->text();
        actionName = "CIĘŻKI ATAK:  " + ui->lineEdit_wpnName->text().toUpper();
        PA_cost = ui->spinBox_PA->text();
        baseAcc = ui->spinBox_baseAcc->value();

        setCodeHeader(playername,actionName,PA_cost);
        setCodeSuccesChance(baseAcc);
        setDice("1d100");
    }
    else if(actionName.endsWith("(normalny)"))
    {
        playername = ui->lineEdit->text();
        actionName = "NORMALNY ATAK:  " + ui->lineEdit_wpnName->text().toUpper();
        PA_cost = ui->spinBox_PA->text();
        baseAcc = ui->spinBox_baseAcc->value();

        setCodeHeader(playername,actionName,PA_cost);
        setCodeSuccesChance(baseAcc);
        setDice("1d100");
    }
    else if(actionName.endsWith("(obszarowy)"))
    {
        playername = ui->lineEdit->text();
        actionName = "OBSZAROWY ATAK:  " + ui->lineEdit_wpnName->text().toUpper();
        PA_cost = ui->spinBox_PA->text();
        baseAcc = ui->spinBox_baseAcc->value();

        setCodeHeader(playername,actionName,PA_cost);
        setCodeSuccesChance(baseAcc);
        setDice("1d100");
    }

    else if(actionName.endsWith("zdolności"))
    {
        playername = ui->lineEdit->text();
        actionName = ui->lineEdit_wpnName->text().toUpper();
        PA_cost = ui->spinBox_PA->text();
        baseAcc = ui->spinBox_baseAcc->value();

        setCodeHeader(playername,actionName,PA_cost);
        setCodeSuccesChance(baseAcc);
        setDice("1d100");
    }

    ui->plainTextEdit_code->setPlainText(code);
    ui->textEdit_preview->setText(preview_code);
}

void calculator::GenerateDmgDoneCode()
{
    QString actionName;
    actionName = ui->lineEdit_wpnName_2->text();
    setCodeHeader("0",actionName,"0");
    setCodeDmgDone();
    ui->plainTextEdit_code->setPlainText(code);
    ui->textEdit_preview->setText(preview_code);
}

void calculator::GenerateCustomCode()
{
    QString actionName,playername, custom_dice, num_of_dice;
    actionName = ui->lineEdit_action->text();
    playername = ui->lineEdit->text();
    custom_dice = ui->spinBox_DICE->text();
    num_of_dice = ui->spinBox_DICE_2->text();
    custom_dice = num_of_dice + "d" + custom_dice;
    setCodeHeader(playername,actionName,"0");
    setCodeCustom();
    setDice(custom_dice);
    ui->plainTextEdit_code->setPlainText(code);
    ui->textEdit_preview->setText(preview_code);
}

void calculator::GenerateLimitCode()
{
    QString playername;
    playername = ui->lineEdit->text();
    setCodeHeader(playername,"0","0");
    setCodeLimit();
    ui->plainTextEdit_code->setPlainText(code);
    ui->textEdit_preview->setText(preview_code);
}

void calculator::on_pushButton_clicked()
{
    //Run when "Generuj Kod" button clicked
    code.clear();
    preview_code.clear();

    if(ui->tabWidget->currentIndex() == 0)
    {
       GenerateHittingChanceCode();
    }
    else if(ui->tabWidget->currentIndex() == 1)
    {
        GenerateDmgDoneCode();
    }
    else if(ui->tabWidget->currentIndex() == 2)
    {
        GenerateLimitCode();

    }
    else if(ui->tabWidget->currentIndex() == 3)
    {
        GenerateCustomCode();

    }
    else
    {

    }
}

void calculator::setCodeHeader(QString playername, QString actionName, QString PAcost)
{
    if(playername != "0" && PAcost != "0")
    {
        code = "1. ";
        preview_code = "1.";

        actionName = actionName.toUpper();
        PAcost =  " [" + PAcost + " PA]";

        preview_code += "<font color='#FF8000'>" + playername + "</font>" + "<font color='#4080FF'> [" + actionName + "]" + PAcost + "</font><br>";
        code += "[color=#FF8000]" + playername + "[/color]" + "[color=#4080FF] [" + actionName + "]" + PAcost + "[/color]\n";
    }
    else if(playername == "0" && PAcost == "0")
    {
        preview_code = "<u><font color='#FFBF00'>OBRAŻENIA (";
        code = "[color=#FFBF00][u]OBRAŻENIA (";

        actionName = actionName.toUpper();

        preview_code += actionName + ")</font></u><br>";
        code += actionName + ")[/u][/color]\n";
    }
    else if(playername != "0" && PAcost == "0" && actionName != "0")
    {
        actionName = actionName.toUpper();

        preview_code = "<font color='#FF8000'>" + playername + "</font>" + "<font color='#4080FF'> [" + actionName + "]</font><br>";
        code = "[color=#FF8000]" + playername + "[/color]" + "[color=#4080FF] [" + actionName + "][/color]\n";

    }
    else if(playername != "0" && PAcost == "0" && actionName == "0")
    {

        preview_code = "<u><font color='#008000'> LIMIT BONUSÓW [" + playername + "]</font></u><br>";
        code = "[color=#008000][u] LIMIT BONUSÓW [" + playername + "][/u][/color]\n";

    }
    else
    {

    }
}

void calculator::setCodeDmgDone()
{
    double full_dmg = 0;
    double full_dmgf = 0;
    double final_shield, final_armor;
    int dmg, seria, success_nmb, spread, ini_lvl, det_lvl;
    int shield, armor;
    double mod[4];
    bool nomods = true;

    mod[0] = ui->spinBox_mod1->value();
    mod[1] = ui->spinBox_mod2->value();
    mod[2] = ui->spinBox_mod3->value();
    mod[3] = ui->spinBox_mod4->value();

    QString mod_desc[4];
    QString playername = ui->lineEdit->text();

    //BEGINNIG
    if(ui->comboBox_wpn_type->currentText().endsWith("samoczynna"))
    {
        dmg = ui->spinBox_DMG->value();
        seria = ui->spinBox_SERIA->value();
        success_nmb = ui->spinBox_SUCCESSNMB->value();

        full_dmg = dmg*seria*(success_nmb*25*0.01);
        full_dmgf = qFloor(full_dmg);

        preview_code += "(" + QString::number(dmg) + "*" + QString::number(seria) + ")";
        code += "(" + QString::number(dmg) + "*" + QString::number(seria) + ")";
    }
    else if(ui->comboBox_wpn_type->currentText().endsWith("Strzelba"))
    {
        dmg = ui->spinBox_DMG->value();
        spread = ui->spinBox_SHOTGUN->value();

        full_dmg = dmg*(spread*0.01);
        full_dmgf = qFloor(full_dmg);

        preview_code += QString::number(dmg);
        code += QString::number(dmg);
    }
    else if(ui->comboBox_wpn_type->currentText().endsWith("Kombinacja"))
    {
        ini_lvl = ui->spinBox_INIC->value();
        det_lvl = ui->spinBox_DET->value();

        full_dmg = 100 + 25*(ini_lvl + det_lvl);
        full_dmgf = qFloor(full_dmg);

        preview_code += "[100 + 25 * (" + QString::number(ini_lvl) + " [Poziom Inicjatora] + " + QString::number(det_lvl) + " [Poziom Detonatora])]";
        code += "[100 + 25 * (" + QString::number(ini_lvl) + " [Poziom Inicjatora] + " + QString::number(det_lvl) + " [Poziom Detonatora])]";
    }
    else
    {
        dmg = ui->spinBox_DMG->value();

        full_dmg = dmg;
        full_dmgf = qFloor(full_dmg);

        preview_code += QString::number(dmg);
        code += QString::number(dmg);
    }

    //MODIFICATORS
    for (int n=0;n<4;n++)
    {
        if(mod[n]!= 0)
        {
            if(n==0) mod_desc[n] += ui->lineEdit_mod1->text();
            else if(n==1) mod_desc[n] += ui->lineEdit_mod2->text();
            else if(n==2) mod_desc[n] += ui->lineEdit_mod3->text();
            else if(n==3) mod_desc[n] += ui->lineEdit_mod4->text();

            mod[n] = 1 + mod[n]*0.01;
            full_dmg = full_dmg*mod[n];
            full_dmgf = qFloor(full_dmg);

            nomods = false;

            preview_code += " * " + QString::number(mod[n]) + " [" + mod_desc[n] + "]";
            code += " * " + QString::number(mod[n]) + " [" + mod_desc[n] + "]";
        }
    }

    //ENDING
    if(ui->comboBox_wpn_type->currentText().endsWith("samoczynna"))
    {
        if(full_dmg-full_dmgf != 0 )
        {
            preview_code += " * " + QString::number(success_nmb*25*0.01) + " [LICZBA SUKCESÓW] = " + QString::number(full_dmg) + " = " + QString::number(full_dmgf) + "<br><br>";
            code += " * " +  QString::number(success_nmb*25*0.01) + " [LICZBA SUKCESÓW] = " + QString::number(full_dmg) + " = " + QString::number(full_dmgf) +  "\n\n";
        }
        else
        {
            preview_code += " * " + QString::number(success_nmb*25*0.01) + " [LICZBA SUKCESÓW] = " + QString::number(full_dmg) + "<br><br>";
            code += " * " +  QString::number(success_nmb*25*0.01) + " [LICZBA SUKCESÓW] = " + QString::number(full_dmg) + "\n\n";
        }
    }
    else if(ui->comboBox_wpn_type->currentText().endsWith("Strzelba"))
    {
        if(full_dmg-full_dmgf != 0 )
        {
            preview_code += " * " +  QString::number(spread*0.01) + " [ROZRZUT STRZELBY] = " + QString::number(full_dmg)  + " = " + QString::number(full_dmgf) +  "<br><br>";
            code += " * " +  QString::number(spread*0.01) + " [ROZRZUT STRZELBY] = " + QString::number(full_dmg)  + " = " + QString::number(full_dmgf) +  "\n\n";
        }
        else
        {
            preview_code += " * " +  QString::number(spread*0.01) + " [ROZRZUT STRZELBY] = " + QString::number(full_dmg) + "<br><br>";
            code += " * " +  QString::number(spread*0.01) + " [ROZRZUT STRZELBY] = " + QString::number(full_dmg) + "\n\n";
        }
    }
    else
    {
        if(full_dmg-full_dmgf != 0)
        {
            preview_code += " = " + QString::number(full_dmg)  + " = " + QString::number(full_dmgf) +  "<br><br>";
            code += " = " + QString::number(full_dmg)  + " = " + QString::number(full_dmgf) +  "\n\n";
        }
        else if(full_dmg-full_dmgf == 0 && !nomods)
        {
            preview_code += " = " + QString::number(full_dmg) + "<br><br>";
            code += " = " + QString::number(full_dmg) + "\n\n";
        }
        else
        {
            preview_code += "<br><br>";
            code += "\n\n";
        }
    }


    //SHIELD AND ARMOR
    shield = ui->spinBox_SHIELD->value();
    armor = ui->spinBox_ARMOR->value();

    if(shield > 0 && !ui->comboBox_wpn_type->currentText().endsWith("ostrzem"))
    {
        final_shield = shield - full_dmgf;
        if(final_shield<0) final_shield = 0;
        preview_code += "<font color='#FF8000'>" + playername + "</font><br>";
        preview_code += "<font color='#0080FF'>Tarcze: " + QString::number(shield) + " - " + QString::number(full_dmgf) + " = " + QString::number(final_shield) +"</font><br>";
        preview_code += "<font color='#FF0000'>Pancerz: " + QString::number(armor) + "</font><br>";

        code += "[color=#FF8000]" + playername + "[/color]\n";
        code += "[color=#0080FF]Tarcze: " + QString::number(shield) + " - " + QString::number(full_dmgf) + " = " + QString::number(final_shield) +"[/color]\n";
        code += "[color=#FF0000]Pancerz: " + QString::number(armor) + "[/color]\n";

    }
    else
    {
        final_armor = armor - full_dmgf;
        if(final_armor<0) final_armor = 0;
        preview_code += "<font color='#FF8000'>" + playername + "</font><br>";
        preview_code += "<font color='#0080FF'>Tarcze: " + QString::number(shield) + "</font><br>";
        preview_code += "<font color='#FF0000'>Pancerz: " + QString::number(armor) + " - " + QString::number(full_dmgf) + " = " + QString::number(final_armor) + "</font><br>";

        code += "[color=#FF8000]" + playername + "[/color]\n";
        code += "[color=#0080FF]Tarcze: " + QString::number(shield) + "[/color]\n";
        code += "[color=#FF0000]Pancerz: " + QString::number(armor) +  " - " + QString::number(full_dmgf) + " = " + QString::number(final_armor) + "[/color]\n";
    }


    //DISPLAY
    ui->plainTextEdit_code->setPlainText(code);
    ui->textEdit_preview->setText(preview_code);
}

void calculator::setCodeSuccesChance(int base)
{
     QString chance_desc[5];
     int chance[5];
     int recoil;

     chance[0] = ui->spinBox_b1->value();
     chance[1] = ui->spinBox_b2->value();
     chance[2] = ui->spinBox_b3->value();
     chance[3] = ui->spinBox_b4->value();
     chance[4] = ui->spinBox_b5->value();

     recoil = ui->spinBox_REC->value();

     int full_chance = base;
     full_chance += ui->spinBox_ACC->value();
     full_chance -= recoil;

     for(int i=0;i<5;i++)
     {
         full_chance += chance[i];
     }

     if(full_chance>99) full_chance = 99;

     preview_code += QString::number(base);
     code += QString::number(base);

     if(ui->spinBox_ACC->isEnabled())
     {
         preview_code += " + " + ui->spinBox_ACC->text() + " [Celność]";
         code += " + " + ui->spinBox_ACC->text() + " [Celność]";
     }

     for(int n=0;n<5;n++)
     {
         if(chance[n] > 0)
         {
             if(n==0) chance_desc[n] += " [" + ui->lineEdit_acc_b1->text() + "]";
             else if(n==1) chance_desc[n] += " [" + ui->lineEdit_acc_b2->text() + "]";
             else if(n==2) chance_desc[n] += " [" + ui->lineEdit_acc_b3->text() + "]";
             else if(n==3) chance_desc[n] += " [" + ui->lineEdit_acc_b4->text() + "]";
             else if(n==4) chance_desc[n] += " [" + ui->lineEdit_acc_b5->text() + "]";

             preview_code += " + " + QString::number(chance[n]) + chance_desc[n];
             code += " + " + QString::number(chance[n]) + chance_desc[n];
         }
         else if(chance[n] < 0)
         {
             if(n==0) chance_desc[n] += " [" + ui->lineEdit_acc_b1->text() + "]";
             else if(n==1) chance_desc[n] += " [" + ui->lineEdit_acc_b2->text() + "]";
             else if(n==2) chance_desc[n] += " [" + ui->lineEdit_acc_b3->text() + "]";
             else if(n==3) chance_desc[n] += " [" + ui->lineEdit_acc_b4->text() + "]";
             else if(n==4) chance_desc[n] += " [" + ui->lineEdit_acc_b5->text() + "]";

             preview_code += " - " + QString::number(abs(chance[n])) + chance_desc[n];
             code += " - " + QString::number(abs(chance[n])) + chance_desc[n];
         }
     }

     if(recoil>0)
     {
         preview_code += " - " + QString::number(recoil) + " [Odrzut]";
         code += " - " + QString::number(recoil) + " [Odrzut]";
     }

     preview_code += " = " + QString::number(full_chance) + "%<br><br>";
     code += " = " + QString::number(full_chance) + "%\n";

     if(ui->comboBox->currentText() == "Strzelba")
     {
         preview_code += "Procent trafienia: " + QString::number(full_chance) + "%<br><br>";
         code += "\nProcent trafienia: " + QString::number(full_chance) + "%\n\n";
     }
     else
     {
         preview_code += "Szansa na trafienie: &lt; " + QString::number(full_chance) + "%<br><br>";
         code += "\nSzansa na trafienie: < " + QString::number(full_chance) + "%\n\n";
     }

     ui->plainTextEdit_code->setPlainText(code);
     ui->textEdit_preview->setText(preview_code);
}

void calculator::setCodeCustom()
{
     QString chance_desc[7];
     int chance[7];
     int base = ui->spinBox_SUCCESS->value();

     chance[0] = ui->spinBox_custom1->value();
     chance[1] = ui->spinBox_custom2->value();
     chance[2] = ui->spinBox_custom3->value();
     chance[3] = ui->spinBox_custom4->value();
     chance[4] = ui->spinBox_custom5->value();
     chance[5] = ui->spinBox_custom6->value();
     chance[6] = ui->spinBox_custom7->value();

     int full_chance = base;

     for(int i=0;i<7;i++)
     {
         full_chance += chance[i];
     }

     if(full_chance>99) full_chance = 99;

     preview_code += QString::number(base);
     code += QString::number(base);


     for(int n=0;n<7;n++)
     {
         if(chance[n] > 0)
         {
             if(n==0) chance_desc[n] += " [" + ui->lineEdit_custom1->text() + "]";
             else if(n==1) chance_desc[n] += " [" + ui->lineEdit_custom2->text() + "]";
             else if(n==2) chance_desc[n] += " [" + ui->lineEdit_custom3->text() + "]";
             else if(n==3) chance_desc[n] += " [" + ui->lineEdit_custom4->text() + "]";
             else if(n==4) chance_desc[n] += " [" + ui->lineEdit_custom5->text() + "]";
             else if(n==5) chance_desc[n] += " [" + ui->lineEdit_custom6->text() + "]";
             else if(n==6) chance_desc[n] += " [" + ui->lineEdit_custom7->text() + "]";

             preview_code += " + " + QString::number(chance[n]) + chance_desc[n];
             code += " + " + QString::number(chance[n]) + chance_desc[n];
         }
         else if(chance[n] < 0)
         {
             if(n==0) chance_desc[n] += " [" + ui->lineEdit_custom1->text() + "]";
             else if(n==1) chance_desc[n] += " [" + ui->lineEdit_custom2->text() + "]";
             else if(n==2) chance_desc[n] += " [" + ui->lineEdit_custom3->text() + "]";
             else if(n==3) chance_desc[n] += " [" + ui->lineEdit_custom4->text() + "]";
             else if(n==4) chance_desc[n] += " [" + ui->lineEdit_custom5->text() + "]";
             else if(n==5) chance_desc[n] += " [" + ui->lineEdit_custom6->text() + "]";
             else if(n==6) chance_desc[n] += " [" + ui->lineEdit_custom7->text() + "]";

             preview_code += " - " + QString::number(abs(chance[n])) + chance_desc[n];
             code += " - " + QString::number(abs(chance[n])) + chance_desc[n];
         }
     }

         preview_code += " = " + QString::number(full_chance) + "%<br><br>";
         code += " = " + QString::number(full_chance) + "%\n";

         preview_code += "Szansa na sukces: &lt; " + QString::number(full_chance) + "%<br><br>";
         code += "\nSzansa na sukces: < " + QString::number(full_chance) + "%\n\n";

         ui->plainTextEdit_code->setPlainText(code);
         ui->textEdit_preview->setText(preview_code);

}

void calculator::setCodeLimit()
{
     QString bonus_desc[8], bonus_line;
     int bonus[8];

     bonus[0] = ui->spinBox_bonus1->value();
     bonus[1] = ui->spinBox_bonus2->value();
     bonus[2] = ui->spinBox_bonus3->value();
     bonus[3] = ui->spinBox_bonus4->value();
     bonus[4] = ui->spinBox_bonus5->value();
     bonus[5] = ui->spinBox_bonus6->value();
     bonus[6] = ui->spinBox_bonus7->value();
     bonus[7] = ui->spinBox_bonus8->value();

     int full_bonus = 0;
     int n_bonus = 0;
     int limited_bonus50 = 0;
     int limited_bonus75 = 0;

     for(int i=0;i<8;i++)
     {
         full_bonus += bonus[i];
     }

     for(int n=0;n<8;n++)
     {
         if(bonus[n] > 0)
         {
             if(n==0) bonus_desc[n] += "% [" + ui->lineEdit_bonus1->text() + "]";
             else if(n==1) bonus_desc[n] += "% [" + ui->lineEdit_bonus2->text() + "]";
             else if(n==2) bonus_desc[n] += "% [" + ui->lineEdit_bonus3->text() + "]";
             else if(n==3) bonus_desc[n] += "% [" + ui->lineEdit_bonus4->text() + "]";
             else if(n==4) bonus_desc[n] += "% [" + ui->lineEdit_bonus5->text() + "]";
             else if(n==5) bonus_desc[n] += "% [" + ui->lineEdit_bonus6->text() + "]";
             else if(n==6) bonus_desc[n] += "% [" + ui->lineEdit_bonus7->text() + "]";
             else if(n==7) bonus_desc[n] += "% [" + ui->lineEdit_bonus8->text() + "]";

             if(n>0)
             {
                 bonus_line += " + ";
                 preview_code += " + ";
                 code += " + ";
             }

             bonus_line += QString::number(bonus[n]) + bonus_desc[n];
             preview_code += QString::number(bonus[n]) + bonus_desc[n];
             code += QString::number(bonus[n]) + bonus_desc[n];
         }
         else if(bonus[n] < 0)
         {
             if(n==0) bonus_desc[n] += "% [" + ui->lineEdit_bonus1->text() + "]";
             else if(n==1) bonus_desc[n] += "% [" + ui->lineEdit_bonus2->text() + "]";
             else if(n==2) bonus_desc[n] += "% [" + ui->lineEdit_bonus3->text() + "]";
             else if(n==3) bonus_desc[n] += "% [" + ui->lineEdit_bonus4->text() + "]";
             else if(n==4) bonus_desc[n] += "% [" + ui->lineEdit_bonus5->text() + "]";
             else if(n==5) bonus_desc[n] += "% [" + ui->lineEdit_bonus6->text() + "]";
             else if(n==6) bonus_desc[n] += "% [" + ui->lineEdit_bonus7->text() + "]";
             else if(n==7) bonus_desc[n] += "% [" + ui->lineEdit_bonus8->text() + "]";

             bonus_line += " - ";
             preview_code += " - ";
             code += " - ";

             bonus_line += QString::number(bonus[n]) + bonus_desc[n];
             preview_code += QString::number(abs(bonus[n])) + bonus_desc[n];
             code += QString::number(abs(bonus[n])) + bonus_desc[n];
         }
     }

     preview_code += " = " + QString::number(full_bonus) + "%<br><br>";
     code += " = " + QString::number(full_bonus) + "%\n\n";

     if(full_bonus>50)
     {
         preview_code += "Suma bonusów większa niż 50%. Liczę pierwszy próg. <br>";
         code += "Suma bonusów większa niż 50%. Liczę pierwszy próg.\n";

         n_bonus = full_bonus - 50;
         n_bonus = n_bonus*0.5;
         limited_bonus50 = 50 + n_bonus;

         preview_code += bonus_line + " - 50%";
         code += bonus_line + " - 50%";

         preview_code += " = " + QString::number(full_bonus - 50) + "%<br>";
         code += " = " + QString::number(full_bonus - 50) + "%\n";

         preview_code += QString::number(full_bonus - 50) + "% / 2 = " + QString::number(n_bonus) + "%<br>";
         code += QString::number(full_bonus - 50) + "% / 2 = " + QString::number(n_bonus) + "%\n";

         preview_code += "50% + " + QString::number(n_bonus) + "% = " + QString::number(limited_bonus50) +  "%<br><br>";
         code += "50% + " + QString::number(n_bonus) + "% = " + QString::number(limited_bonus50) +  "%\n\n";

         full_bonus = limited_bonus50;
     }

     if(full_bonus>75)
     {
         preview_code += "Suma bonusów większa niż 75%. Liczę drugi próg. <br>";
         code += "Suma bonusów większa niż 75%. Liczę drugi próg.\n";

         n_bonus = full_bonus - 75;
         n_bonus = n_bonus*0.5;
         limited_bonus75 = 75 + n_bonus;

         preview_code += QString::number(limited_bonus50) + "% - 75%";
         code += QString::number(limited_bonus50) + "% - 75%";

         preview_code += " = " + QString::number(limited_bonus50 - 75) + "%<br>";
         code += " = " + QString::number(limited_bonus50 - 75) + "%\n";

         preview_code += QString::number(limited_bonus50 - 75) + "% / 2 = " + QString::number(n_bonus) + "%<br>";
         code += QString::number(limited_bonus50 - 75) + "% / 2 = " + QString::number(n_bonus) + "%\n";

         preview_code += "75% + " + QString::number(n_bonus) + "% = " + QString::number(limited_bonus75) +  "%<br><br>";
         code += "75% + " + QString::number(n_bonus) + "% = " + QString::number(limited_bonus75) +  "%\n\n";

         full_bonus = limited_bonus75;
     }



     preview_code += "<font color='#008000'>Ostateczny bonus: " + QString::number(full_bonus) + "%</font><br><br>";
     code += "[color=#008000]Ostateczny bonus: " + QString::number(full_bonus) + "%[/color]\n\n";

     ui->plainTextEdit_code->setPlainText(code);
     ui->textEdit_preview->setText(preview_code);

}

void calculator::setDice(QString dice)
{
    preview_code += "[dice]" + dice + "[/dice]";
    code += "[dice]" + dice + "[/dice]";
}

void calculator::on_comboBox_activated(const QString &arg1)
{
    if(arg1.endsWith("samoczynna") || arg1.endsWith("samopowtarzalna") || arg1.endsWith("Strzelba"))
    {

//        ui->spinBox_REC->setEnabled(true);
//        ui->spinBox_REC->setValue(0);
//        ui->label_11->setEnabled(true);
        ui->spinBox_baseAcc->setDisabled(true);
        ui->spinBox_baseAcc->setValue(0);
        ui->label_7->setDisabled(true);
        ui->spinBox_ACC->setEnabled(true);
        ui->spinBox_ACC->setValue(0);
        ui->label_9->setEnabled(true);

        ui->label_5->setText("Broń:");
        ui->label_7->setText("Bazowa szansa na trafienie:");

        ui->label_29->setEnabled(true);
        ui->checkBox_multipleshot->setEnabled(true);
    }

    else if(arg1.endsWith("(ciężki)") || arg1.endsWith("(normalny)") || arg1.endsWith("(obszarowy)"))
    {

        ui->spinBox_REC->setDisabled(true);
        ui->spinBox_REC->setValue(0);
        ui->label_11->setDisabled(true);
        ui->spinBox_baseAcc->setEnabled(true);
        ui->spinBox_baseAcc->setValue(0);
        ui->label_7->setEnabled(true);
        ui->spinBox_ACC->setDisabled(true);
        ui->spinBox_ACC->setValue(0);
        ui->label_9->setDisabled(true);

        ui->label_5->setText("Broń:");
        ui->label_7->setText("Bazowa szansa na trafienie:");

        ui->label_29->setEnabled(false);
        ui->checkBox_multipleshot->setEnabled(false);
        ui->checkBox_multipleshot->setChecked(false);
    }

    else if(arg1.endsWith("zdolności"))
    {

        ui->spinBox_REC->setDisabled(true);
        ui->spinBox_REC->setValue(0);
        ui->label_11->setDisabled(true);
        ui->spinBox_baseAcc->setEnabled(true);
        ui->spinBox_baseAcc->setValue(0);
        ui->label_7->setEnabled(true);
        ui->spinBox_ACC->setDisabled(true);
        ui->spinBox_ACC->setValue(0);
        ui->label_9->setDisabled(true);

        ui->label_5->setText("Zdolność:");
        ui->label_7->setText("Szansa na trafienie:");

        ui->label_29->setEnabled(false);
        ui->checkBox_multipleshot->setEnabled(false);
        ui->checkBox_multipleshot->setChecked(false);
    }
}

void calculator::on_comboBox_wpn_type_activated(const QString &arg1)
{
    if(arg1.endsWith("samoczynna"))
    {
        ui->spinBox_DMG->setEnabled(true);
        ui->label_12->setEnabled(true);

        ui->spinBox_SERIA->setEnabled(true);
        ui->spinBox_SERIA->setValue(0);
        ui->label_13->setEnabled(true);

        ui->spinBox_SUCCESSNMB->setEnabled(true);
        ui->spinBox_SUCCESSNMB->setValue(0);
        ui->label_14->setEnabled(true);

        ui->spinBox_SHOTGUN->setEnabled(false);
        ui->spinBox_SHOTGUN->setValue(0);
        ui->label_15->setEnabled(false);

        ui->spinBox_INIC->setEnabled(false);
        ui->spinBox_DET->setEnabled(false);
        ui->label_24->setEnabled(false);
        ui->label_25->setEnabled(false);
        ui->label_26->setEnabled(false);
        ui->label_27->setEnabled(false);

    }

    else if(arg1.endsWith("samopowtarzalna") || arg1.endsWith("ostrzem") || arg1.endsWith("zdolności"))
    {
        ui->spinBox_DMG->setEnabled(true);
        ui->label_12->setEnabled(true);

        ui->spinBox_SERIA->setEnabled(false);
        ui->spinBox_SERIA->setValue(0);
        ui->label_13->setEnabled(false);

        ui->spinBox_SUCCESSNMB->setEnabled(false);
        ui->spinBox_SUCCESSNMB->setValue(0);
        ui->label_14->setEnabled(false);

        ui->spinBox_SHOTGUN->setEnabled(false);
        ui->spinBox_SHOTGUN->setValue(0);
        ui->label_15->setEnabled(false);

        ui->spinBox_INIC->setEnabled(false);
        ui->spinBox_DET->setEnabled(false);
        ui->label_24->setEnabled(false);
        ui->label_25->setEnabled(false);
        ui->label_26->setEnabled(false);
        ui->label_27->setEnabled(false);
    }

    else if(arg1.endsWith("Strzelba"))
    {
        ui->spinBox_DMG->setEnabled(true);
        ui->label_12->setEnabled(true);

        ui->spinBox_SERIA->setEnabled(false);
        ui->spinBox_SERIA->setValue(0);
        ui->label_13->setEnabled(false);

        ui->spinBox_SUCCESSNMB->setEnabled(false);
        ui->spinBox_SUCCESSNMB->setValue(0);
        ui->label_14->setEnabled(false);

        ui->spinBox_SHOTGUN->setEnabled(true);
        ui->spinBox_SHOTGUN->setValue(0);
        ui->label_15->setEnabled(true);

        ui->spinBox_INIC->setEnabled(false);
        ui->spinBox_DET->setEnabled(false);
        ui->label_24->setEnabled(false);
        ui->label_25->setEnabled(false);
        ui->label_26->setEnabled(false);
        ui->label_27->setEnabled(false);
    }

    else if(arg1.endsWith("Kombinacja"))
    {
        ui->spinBox_DMG->setEnabled(false);
        ui->label_12->setEnabled(false);

        ui->spinBox_SERIA->setEnabled(false);
        ui->spinBox_SERIA->setValue(0);
        ui->label_13->setEnabled(false);

        ui->spinBox_SUCCESSNMB->setEnabled(false);
        ui->spinBox_SUCCESSNMB->setValue(0);
        ui->label_14->setEnabled(false);

        ui->spinBox_SHOTGUN->setEnabled(false);
        ui->spinBox_SHOTGUN->setValue(0);
        ui->label_15->setEnabled(false);

        ui->spinBox_INIC->setEnabled(true);
        ui->spinBox_DET->setEnabled(true);
        ui->label_24->setEnabled(true);
        ui->label_25->setEnabled(true);
        ui->label_26->setEnabled(true);
        ui->label_27->setEnabled(true);
    }
}

void calculator::on_tabWidget_currentChanged(int index)
{
    ui->plainTextEdit_code->clear();
    ui->textEdit_preview->clear();
    code.clear();
    preview_code.clear();
}



void calculator::on_checkBox_multipleshot_toggled(bool checked)
{
    ui->spinBox_REC->setValue(0);
}
