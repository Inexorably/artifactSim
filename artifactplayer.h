#ifndef ARTIFACTPLAYER_H
#define ARTIFACTPLAYER_H

#include "artifactcard.h"
#include "globals.h"


#include <vector>

//From globals.h
extern unsigned seed;

//TODO: Need base health?  Ex: Fully heal cards.
struct artifactTower{
    artifactTower();
    int baseHealth;
    int currentHealth;
    bool isAncient;
    int baseAttack;
    int currentAttack;
    void modifyHealth(const int num);
};

struct artifactLane{
    artifactLane();
    std::vector<artifactCard> cards;
    std::vector<artifactCard> improvements;
    artifactTower tower;
    int currentMana;
    int baseMana;
};

//This is likely better as a struct than a class because publically accessible hand, board etc is useful for utility.
//Create type for lanes or towers (changes to ancient tower when base tower destroyed?)
struct artifactPlayer{
    std::vector<artifactCard> hand;
    std::vector<artifactCard> deck;
    std::vector<artifactCard> graveyard;
    std::vector<artifactCard> removedFromPlay;
    std::vector<artifactCard> baseDeck;
    std::vector<artifactCard> fountain;
    std::vector<artifactLane> lanes;


    void draw();
    void shuffleDeck();
    void reset();


};

#endif // ARTIFACTPLAYER_H
