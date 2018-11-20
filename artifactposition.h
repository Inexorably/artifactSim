#ifndef ARTIFACTPOSITION_H
#define ARTIFACTPOSITION_H

#include "globals.h"

#include <QDebug>
#include <QString>

//A card effect might require a position not defined by a card, but by a spot on the board or hand.
//Example: spawning a card requires a choice on where to spawn the card.
class artifactPosition{
public:
    artifactPosition();
    artifactPosition(const int laneNum, const QString loc, const int ind);
    int getLane() const;
    void setLane(const int num);
    QString getLocation() const;
    void setLocation(const QString loc);
    int getIndex() const;
    void setIndex(const int ind);
    int getSide() const;
    void setSide(const int num);


private:
    //0, 1, or 2.  -1 if not in a lane.
    int lane;
    //Can be DECK, HAND, LANE, FOUNTAIN etc.  These are constants defined in globals.h.
    QString location;
    //The index in the hand, lane, example.
    int index;
    //Which player's side is this card on? 0 or 1.
    int side;



};

#endif // ARTIFACTPOSITION_H
