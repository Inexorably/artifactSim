#ifndef ARTIFACTCARD_H
#define ARTIFACTCARD_H


#include "artifactposition.h"

#include <memory>

#include <QString>
#include <QDebug>


//TODO: Have "effect" class which does things which modify the boardstate (i.e discard, res, change values).
//This class should be part of artifactCard.

class artifactCard{
    public:
        artifactCard();
        artifactCard(QString name, int health, int armor, int attack, QString type, QString colourQString, QString rare);

        QString getCurrentName() const;
        QString getBaseName() const;
        void changeName(const QString name);
        void modifyArmor(const int num);
        void modifyHealth(const int num);
        void modifyAttack(const int num);
        QString getType() const;
        QString getColour() const;
        QString getRarity() const;
        artifactPosition position;

    private:
        QString currentName;
        QString baseName;
        int currentHealth;
        int currentArmor;
        int currentAttack;
        int baseHealth;
        int baseArmor;
        int baseAttack;
        QString cardType;
        QString colour;
        QString rarity;
};


#endif // ARTIFACTCARD_H
