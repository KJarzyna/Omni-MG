#ifndef SKILL_FIREARM_ARMOR_H
#define SKILL_FIREARM_ARMOR_H
#include <QString>


class skill
{
public:
    skill();
    ~skill();
    QString name;
    QString type;
    QString level;
};

class firearm
{
public:
    firearm();
    ~firearm();
    QString name;
    QString Acc;
    QString Recoil;
    QString PA;
    QString DMG;
};

class armor
{
public:
    armor();
    ~armor();
    QString name;
};

#endif // SKILL_FIREARM_ARMOR
