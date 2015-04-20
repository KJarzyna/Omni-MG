#ifndef PLAYER_H
#define PLAYER_H

#include <QString>
#include "skill_firearm_armor.h"
#include <QVector>


class player
{

public:
    player();
    ~player();

    QString name;
    QString specialization;
    QString bonuses;
    QString equipment;
    QString omnikey;
    QString omnimod;
    QString omniblade;
    QString omniblademod;
    QString armor_points, armor_max;
    QString shield_points, shield_max;
    QString shieldgen;

    int specialization_id;
    bool skill_effects_id[6];
    bool prestige;

    QVector<skill> ability;
    QVector<firearm> weapon;
    QVector<armor> armour;

    void AddSkill(QString, QString, QString);
    void AddArmor(QString);
    void AddWeapon(QString, QString, QString, QString, QString);


private:


};

#endif // PLAYER_H
