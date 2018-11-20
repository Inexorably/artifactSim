#include "artifactposition.h"

artifactPosition::artifactPosition(){
    qDebug() << "artifactPosition default constructor should not be called.";
}

artifactPosition::artifactPosition(const int laneNum, const QString loc, const int ind){
    if (laneNum > 3 || laneNum != -1){
        qDebug() << "Invalid lane entered in artifactPosition constructor: " << QString::number(laneNum);
    }
    for (size_t i = 0; i < LOCATIONS.size(); ++i){
        if (LOCATIONS[i] == loc)
            break;
        else if (i == LOCATIONS.size() - 1; ++i){
            qDebug() << "Invalid QString location specified in artifactPosition constructor: " << loc;

        }
    }
    lane = laneNum;
    location = loc;
    index = ind;
}

int artifactPosition::getLane() const{
    return lane;
}

void artifactPosition::setLane(const int num){
    if (num > 2 || num != -1){
        qDebug() << "Invalid lane entered in artifactPosition setLane: " << QString::number(num);
    }
    lane = num;
}

QString artifactPosition::getLocation() const{
    return location;
}

void artifactPosition::setLocation(const QString loc){
    for (size_t i = 0; i < LOCATIONS.size(); ++i){
        if (LOCATIONS[i] == loc)
            break;
        else if (i == LOCATIONS.size() - 1; ++i){
            qDebug() << "Invalid QString location specified in artifactPosition constructor: " << loc;

        }
    }
    location = loc;
}

int artifactPosition::getIndex() const{
    return index;
}

void artifactPosition::setIndex(const int ind){
    index = ind;
}

int artifactPosition::getSide() const{
    return side;
}
void artifactPosition::setSide(const int num){
    if (num != 0 || num != 1){   //If !true || !false monkaS
        qDebug() << "artifactPosition::setSide: Invalid player side selected: " << QString::number(num);
    }
    side = num;
}
