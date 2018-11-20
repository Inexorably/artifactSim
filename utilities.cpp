#include "utilities.h"

//Unlikely to ever need performance from std::map or enum switch.
artifactCard createCard(QString name){
    //artifactCard(QString name, int health, int armor, int attack, QString type, QString colour, QString rarity);
    //Divide into letter to increase speed at reaching later letters.




    if (name == "Axe")
        return artifactCard(name, 11, 2, 7, HERO, RED, RARE);
    if (name == "Beastmaster")
        return artifactCard(name, 12, 0, 5, HERO, RED, COMMON);
    if (name == "Bristleback")
        return artifactCard(name, 12, 0, 8, HERO, RED, COMMON);
    if (name == "Centaur Warrunner")
        return artifactCard(name, 14, 0, 4, HERO, RED, RARE);




    //Fall through / default case:
    qDebug() << "Fall through in createCard in utilities.  Card with name " << name << " does not exist.";
    return artifactCard();
}
