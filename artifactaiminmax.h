#ifndef ARTIFACTAIMINMAX_H
#define ARTIFACTAIMINMAX_H

#include "artifactGame.h"

#include <random>
#include <cmath>

//Performance testing
#include <QElapsedTimer>

//A basic, game-state based min max ai for doing initial prototyping of engine and structure.
//This should take a vector of board states which represent the branches in which a decision will result in game states.
//Type is vector<artifactGame>.

//TODO: Check board state assuming end of turn to simulate combat changes.
class artifactAIMinMax{
public:
    artifactAIMinMax();

    double evaluateCard(const artifactCard card);
    double evaluateGameState(const artifactGame game, const int playerIndex);
    artifactGame getBestGameState(const std::vector<artifactGame> tree, const int playerIndex);

private:
    //TODO: Do we need C? is it worth performance hit?
    //Ax^2 + bx
    //Variables for individual card evaluations in evaluateCard.
    double coefArmorA;
    double coefHealthA;
    double coefAttackA;
    double coefArmorB;
    double coefHealthB;
    double coefAttackB;

    //evaluateGameState variables.
    //Abs is absolute, delta is difference.
    double coefLaneWidth;
    double coefLaneMana;    //TODO: Confirm no ramp cards affecting base mana.  Otherwise might want abs and delta.
    double coefLaneHealthAbs;
    double coefLaneHealthDelta;
    double coefLaneImprovements;
    double coefHandAbs;    //Simple hand coef right now, can improve with mana costs etc if needed.  This just checks hand size.
    double coefHandDelta;
};

#endif // ARTIFACTAIMINMAX_H
