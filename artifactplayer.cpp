#include "artifactplayer.h"

/***********************************************/
//artifactPlayer functions
/***********************************************/

void artifactPlayer::draw(){
    if (deck.empty())
        return;
    hand.push_back(deck[0]);
    deck.erase(deck.begin());
}

void artifactPlayer::shuffleDeck(){
    std::shuffle(deck.begin(), deck.end(), std::default_random_engine(seed));
}

/*
    std::vector<artifactCard> hand;
    std::vector<artifactCard> deck;
    std::vector<artifactCard> graveyard;
    std::vector<artifactCard> removedFromPlay;
    std::vector<artifactCard> baseDeck;
    std::vector<artifactCard> fountain;
    std::vector<artifactLane> lanes;
*/

void artifactPlayer::reset(){
    deck = baseDeck;
    hand.clear();
    graveyard.clear();
    removedFromPlay.clear();
    fountain.clear();
    lanes.clear();

    //The artifactTower variable in the artifactLane initializes to a base tower (40 hp, not ancient)
    //so simply creating a temp variable works and pushing it back on to the vector.
    artifactLane tempLane;
    for (size_t i = 0; i < 3; ++i){
        lanes.push_back(tempLane);
    }
}

/***********************************************/
//artifactTower functions
/***********************************************/

artifactTower::artifactTower(){
    baseHealth = 40;
    currentHealth = 40;
    baseAttack = 0;
    currentAttack = 0;
    isAncient = false;
}

//TODO: Make tower emit signal that it becomes ancient when it is destroyed?
//Likely, this will be on artifactGame level.
void artifactTower::modifyHealth(const int num){
    currentHealth += num;
    if (currentHealth > baseHealth)
        currentHealth = baseHealth;
    else if (currentHealth <= 0 && !isAncient){
        isAncient = true;
        baseHealth = 80;
        currentHealth = 80;
    }
}

/***********************************************/
//artifactLane functions
/***********************************************/


artifactLane::artifactLane(){
    baseMana = 1;
    currentMana = 1;
}
