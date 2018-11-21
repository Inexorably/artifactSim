#include "artifactaiminmax.h"

//A basic, game-state based min max ai for doing initial prototyping of engine and structure.
//This should take a vector of board states which represent the branches in which a decision will result in game states.
//Type is vector<artifactGame>.
artifactAIMinMax::artifactAIMinMax(){
  //TODO
}

double artifactAIMinMax::evaluateGameState(const artifactGame game){
    //We need to break the board state down into some numerical quantities.
    //For example, number of cards in hand, number of cards in each lane, life in each lane, etc.
    //Use doubles for var types.

}

artifactGame artifactAIMinMax::getBestGameState(const std::vector<artifactGame> tree){
    qDebug() << "artifactAIMinMax::getBestGameState: ";
    if (tree.empty()){
        qDebug() << "artifactAIMinMax::getBestGameState: " << "Empty game state tree passed.";
    }
    double highestScore = 0;
    size_t index = 0; //The index of the highest scoring game state.
    for (size_t i = 0; i < tree.size(); ++i){
        double currentScore = evaluateGameState(tree[i]);
        if (currentScore > highestScore){
            highestScore = currentScore;
            index = i;
        }
    }
    return tree[index];
}
