#include "player.h"
#include <QDebug>

player::player()
{
   //ability = new QVector<skill>();
}

player::~player()
{

}


void player::AddSkill(QString skillname, QString skilltype, QString skilllevel)
{


    skill ab;
    ab.name = skillname;
    ab.type = skilltype;
    ab.level = skilllevel;

     ability.append(ab);

}

void player::AddWeapon(QString weaponname, QString weaponAcc, QString weaponRec, QString weaponPA, QString weaponDMG)
{


    firearm fir;
    fir.name = weaponname;
    fir.Acc = weaponAcc;
    fir.Recoil = weaponRec;
    fir.PA = weaponPA;
    fir.DMG = weaponDMG;

     weapon.append(fir);

}

void player::AddArmor(QString armorname)
{


    armor arm;
    arm.name = armorname;

     armour.append(arm);

}


