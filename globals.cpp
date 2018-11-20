#include "globals.h"

unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

//Position strings
const QString DECK = "Deck";
const QString LANE = "Lane";
const QString HAND = "Hand";
const QString GRAVEYARD = "Graveyard";
const std::vector<QString> LOCATIONS = {DECK, LANE, HAND, GRAVEYARD};


//Card strings
const QString HERO = "Hero";
const QString SPELL = "Spell";
const QString ITEM = "Item";
const QString CREATURE = "Creature";
const QString IMPROVEMENT = "Improvement";
const QString RED = "Red";
const QString BLACK = "Black";
const QString BLUE = "Blue";
const QString NEUTRAL = "Neutral";
const QString GREEN = "Green";
const QString RARE = "Rare";
const QString UNCOMMON = "Uncommon";
const QString COMMON = "Common";
