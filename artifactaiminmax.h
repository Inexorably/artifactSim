#ifndef ARTIFACTAIMINMAX_H
#define ARTIFACTAIMINMAX_H

#include "artifactGame.h"

//A basic, game-state based min max ai for doing initial prototyping of engine and structure.
//This should take a vector of board states which represent the branches in which a decision will result in game states.
//Type is vector<artifactGame>.
class artifactAIMinMax{
public:
    artifactAIMinMax();

    double evaluateGameState(const artifactGame game);
    artifactGame getBestGameState(const std::vector<artifactGame> tree);
};

#endif // ARTIFACTAIMINMAX_H
