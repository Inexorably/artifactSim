#include "artifactcard.h"

artifactCard::artifactCard(){
    qDebug() << "artifactCard created with default constructor.  Please pass valid arguments to prevent bugs.";
    baseName = "undefName";
    currentName = "undefName";
    baseHealth = -1;
    currentHealth = -1;
    baseArmor = -1;
    currentArmor = -1;
    baseAttack = -1;
    currentAttack = -1;
    cardType = "undefType";
    colour = "undefColour";
    rarity = "undefRarity";
}

artifactCard::artifactCard(QString name, int health, int armor, int attack, QString type, QString colourQString, QString rare){
    //qDebug() << "artifactCard::artifactCard(QString name, int health, int armor, int attack, QString type, QString colourQString, QString rare)";
    baseName = name;
    currentName = name;
    baseHealth = health;
    currentHealth = health;
    baseArmor = armor;
    currentArmor = armor;
    baseAttack = attack;
    currentAttack = attack;
    cardType = type;
    colour = colourQString;
    rarity = rare;
}

int artifactCard::getCurrentArmor() const{
    return currentArmor;
}

int artifactCard::getCurrentHealth() const{
    return currentHealth;
}

int artifactCard::getCurrentAttack() const{
    return currentAttack;
}

QString artifactCard::getColour() const{
    return colour;
}

QString artifactCard::getCurrentName() const{
    return currentName;
}

QString artifactCard::getBaseName() const{
    return baseName;
}

void artifactCard::changeName(const QString name){
    currentName = name;
}

void artifactCard::modifyArmor(const int num){
    currentArmor += num;
}

void artifactCard::modifyHealth(const int num){
    currentHealth += num;
    if (currentHealth > baseHealth)
        currentHealth = baseHealth;
}

void artifactCard::modifyAttack(const int num){
    currentAttack += num;
}

void artifactCard::modifyId(int &nextId){
    id = nextId;
    nextId++;
}

QString artifactCard::getType() const{
    return cardType;
}

QString artifactCard::getRarity() const{
    return rarity;
}

int artifactCard::getManaCost() const{
    return manaCost;
}

void artifactCard::modifyManaCost(const int num){
    manaCost = num;
}

