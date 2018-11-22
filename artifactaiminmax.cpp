#include "artifactaiminmax.h"

//AI development: genetic minmax -> monte carlo -> machine learning.

//A basic, game-state based min max ai for doing initial prototyping of engine and structure.
//This should take a vector of board states which represent the branches in which a decision will result in game states.
//Type is vector<artifactGame>.
artifactAIMinMax::artifactAIMinMax(){
    //TODO: Improve.

    //Initialize as random values for base genetic popoulation.
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(1.0, 2.0);

    coefArmorA = dis(gen);
    coefHealthA = dis(gen);
    coefAttackA = dis(gen);
    coefArmorB = dis(gen);
    coefHealthB = dis(gen);
    coefAttackB = dis(gen);
}

//TODO: Include parameter that takes card name string and gives numeric strength of effect.
double artifactAIMinMax::evaluateCard(const artifactCard card){
    QElapsedTimer timer;
    timer.start();
    double result = 0;
    //Ax^2 + Bx
    result += coefArmorA*static_cast<double>(card.getCurrentArmor())*static_cast<double>(card.getCurrentArmor());
    result += coefArmorB*static_cast<double>(card.getCurrentArmor());
    result += coefHealthA*static_cast<double>(card.getCurrentHealth())*static_cast<double>(card.getCurrentHealth());
    result += coefHealthB*static_cast<double>(card.getCurrentHealth());
    result += coefAttackA*static_cast<double>(card.getCurrentAttack())*static_cast<double>(card.getCurrentAttack());
    result += coefAttackB*static_cast<double>(card.getCurrentAttack());

    qint64 ns = timer.nsecsElapsed();
    qDebug() << "artifactAIMinMax::evaluateCard: Elapsed time (nanoseconds): " << QString::number(ns);
    return result;
}

double artifactAIMinMax::evaluateGameState(const artifactGame game, const int playerIndex){
    double result = 0;
    const int opponentIndex = static_cast<int>(!static_cast<bool>(playerIndex));
    //We need to break the board state down into some numerical quantities.
    //For example, number of cards in hand, number of cards in each lane, life in each lane, etc.
    //Use doubles for var types.
    //For each comparison, do differential based (so we can squish both sides into a number), and include factor for total value of combined to prevent 10 - 10 == 2 - 2 cases.

    //Hand, Lanes + Improvements.
    //Cards in lanes should be first scored individually with variables for armor, health, and attack.
    //TODO: Account with value on artifactCard level for continually valued effects, such as buffing every turn which would not get counted in above calculation.

    //Lanes.  We evaluate both players side as all is known information.  We can use the fact that playerIndex is 0 or 1 to use ! to switch between (cast bool).
    for (size_t i = 0; i < game.players[playerIndex].lanes.size(); ++i){
        //When we evaluate the individual cards, we score card powers and then compare the results of player and opponent.
        //Thus, here we have a factor that averages the lane width and adds that to the weighting.
        double laneWidthFactor = coefLaneWidth*(static_cast<double>(game.players[playerIndex].lanes.size()) + static_cast<double>(game.players[opponentIndex].lanes.size()))/2;
        double playerLaneScore = 0;
        for (size_t j = 0; j < game.players[playerIndex].lanes[i].cards.size(); ++j){
            playerLaneScore += evaluateCard(game.players[playerIndex].lanes[i].cards[j]);
        }
        double opponentLaneScore = 0;
        for (size_t j = 0; j < game.players[opponentIndex].lanes[i].cards.size(); ++j){
            opponentLaneScore += evaluateCard(game.players[opponentIndex].lanes[i].cards[j]);
        }
        result += laneWidthFactor*(playerLaneScore - opponentLaneScore);
        result += coefLaneHealthAbs*game.players[playerIndex].lanes[i].tower.currentHealth;
        result += coefLaneHealthDelta*(game.players[playerIndex].lanes[i].tower.currentHealth - game.players[opponentIndex].lanes[i].tower.currentHealth);
        //Don't need to care about opponent's mana because these game states eval will always happen when it is player's turn to make decisions, meaning opponent has max mana.
        result += coefLaneMana*static_cast<double>(game.players[playerIndex].lanes[i].currentMana)/static_cast<double>(game.players[playerIndex].maxMana);

        //TODO: Evaluate improvements.  Can do simple eval with number and mana.
        double improvementDelta = 0;
        for (size_t j = 0; j < game.players[playerIndex].lanes[i].improvements.size(); ++j){
            improvementDelta += game.players[playerIndex].lanes[i].improvements[j].getManaCost();
        }
        for (size_t j = 0; j < game.players[opponentIndex].lanes[i].improvements.size(); ++j){
            improvementDelta -= game.players[opponentIndex].lanes[i].improvements[j].getManaCost();
        }
        result += coefLaneImprovements*improvementDelta;
    }
    result += coefHandDelta*(static_cast<double>(game.players[playerIndex].hand.size()) - static_cast<double>(game.players[opponentIndex].hand.size()));
    result += coefHandAbs*static_cast<double>(game.players[playerIndex].hand.size());

    return result;

}

//Note that playerIndex is needed of course, to decide perspective of good board state and to see what information the evaluateGameState function is allowed to have.
artifactGame artifactAIMinMax::getBestGameState(const std::vector<artifactGame> tree, const int playerIndex){
    qDebug() << "artifactAIMinMax::getBestGameState: ";
    if (tree.empty()){
        qDebug() << "artifactAIMinMax::getBestGameState: " << "Empty game state tree passed.";
    }
    double highestScore = 0;
    size_t index = 0; //The index of the highest scoring game state.
    for (size_t i = 0; i < tree.size(); ++i){
        double currentScore = evaluateGameState(tree[i], playerIndex);
        if (currentScore > highestScore){
            highestScore = currentScore;
            index = i;
        }
    }
    return tree[index];
}
