#include "artifactGame.h"

artifactGame::artifactGame(){
    //TODO: We need to generate decks in this default constructor.
    activeLane = 1;

    //Create players.
    artifactPlayer tempPlayer;
    for (int i = 0; i < 2; ++i){
        players.push_back(tempPlayer);
    }

}

/******************Debug / Testing*****************************************/
void artifactGame::createDebugDecks(){
    qDebug() << "artifactGame::createDebugDecks";
    for (size_t i = 0; i < players.size(); ++i){
        for (int j = 0; j < 40; ++j){
            players[i].deck.push_back(createCard("Axe"));
        }
    }
}

void artifactGame::debugOutputdecks(){
    qDebug() << "artifactGame::debugOutputdecks";
    for (size_t i = 0; i < players.size(); ++i){
        qDebug() << "\tPlayer: " << QString::number(i);
        for (size_t j = 0; j < players[i].deck.size(); ++j){
            qDebug() << "\t\t" << players[i].deck[j].getCurrentName();
        }
    }

}

/********************************Utility*******************************************************/
/*
//Copy constructor.
artifactGame::artifactGame(const artifactGame &game){
    players = game.players;
    activeLane = game.activeLane;

    //Deep copy unique ptr members.

    //std::vector<std::unique_ptr<artifactCard>> cardsDrawn;
    //std::vector<std::unique_ptr<artifactCard>> cardsDeploymentPhase;
    //std::vector<std::unique_ptr<artifactCard>> cardsArmorIncreased;

    deepCopy(game.cardsDrawn, cardsDrawn);
    deepCopy(game.cardsDeploymentPhase, cardsDeploymentPhase);
    deepCopy(game.cardsArmorIncreased, cardsArmorIncreased);
}

void artifactGame::deepCopy(const std::vector<std::shared_ptr<artifactCard> > from, std::vector<std::shared_ptr<artifactCard> > &to){
    //Adapted from: https://stackoverflow.com/questions/34797849/unique-copy-of-vectorunique-ptr
    //Don't have to dynamically allocate during push_back calls.
    to.reserve(from.size());
    for (const auto& e : from)
        to.push_back(std::make_unique<artifactCard>(*e));
}

void artifactGame::operator = (const artifactGame &game){
    players = game.players;
    activeLane = game.activeLane;

    //Deep copy unique ptr members.

    //std::vector<std::unique_ptr<artifactCard>> cardsDrawn;
    //std::vector<std::unique_ptr<artifactCard>> cardsDeploymentPhase;
    //std::vector<std::unique_ptr<artifactCard>> cardsArmorIncreased;

    deepCopy(game.cardsDrawn, cardsDrawn);
    deepCopy(game.cardsDeploymentPhase, cardsDeploymentPhase);
    deepCopy(game.cardsArmorIncreased, cardsArmorIncreased);
}
*/

/***************************Game setup and nonevent turn functions***********************************************************/
//Generate the initial ids when the decks are full.
void artifactGame::assignIds(){
    int nextId = 0;
    for (size_t i = 0; i < players.size(); ++i){
        if (!players[i].hand.empty()){
            qDebug() << "artifactGame::assignIds: Function called when hand drawn from deck.";
        }
        for (size_t j = 0; j < players[i].deck.size(); ++j){
            players[i].deck[j].modifyId(nextId);
        }
    }
}

//Call all functions here that need to be ran at game start.
void artifactGame::gameStart(){
    //Each card has unique id to help track for effects that trigger on events.  std ptrs are inferior for this due to need to
    //run multiple game instances and easily copy between.  While deep copy is easily overcome, updating ptrs as cards move between vectors
    //like hand deck and grave is really spooky.
    assignIds();

    //Player specific modifications.
    for (size_t i = 0; i < players.size(); ++i){
        //Start at 2 mana because we call the roundStart function on the first round which will incremement the maxMana.
        players[i].maxMana = 2;
        players[i].shuffleDeck();

        //Players start with 5 cards.
        players[i].draw(5);
    }

    //Determine player who goes first -- assign radiant.
    radiantPlayerNum = static_cast<int>(trueWithProbability(0.5));
    initiativePlayer = radiantPlayerNum;
    qDebug() << "Radiant Player: " << QString::number(radiantPlayerNum);
    //TODO

}


void artifactGame::roundStart(){
    for (size_t i = 0; i < players.size(); ++i){
        //Draw 2 cards at the beginning of each round.
        players[i].draw(2);
        //Increment mana.
        players[i].maxMana++;
    }

    //Begin in the first lane.
    activeLane = 0;

    //...........Turn start event?  Does anything trigger on this, or is it all phases.............TODO

}

void artifactGame::eventActionPhase(){
    //We determine the active player.  Note that this can change with initiative.  Can use initiativePlayer, then set active player to initiativePlayer, then switch activePlayer between 0 and 1 with !.
    activePlayer = initiativePlayer;

    //Check cards that we can play (have mana to).
    for (size_t i = 0; i < players[activePlayer].hand.size(); ++i){
        //If we can play the card:
        if (players[activePlayer].hand[i].getManaCost() <= players[activePlayer].lanes.currentMana){
            //CONTINUE here.
        }
    }
}

//Execute a complete round.  Phases: Action -> Combat -> Shopping -> Deployment -> End Phase.
void artifactGame::executeRound(){
    roundStart();
    eventActionPhase();

}

/***********************************************Base Game Mechanics / Event Functions*************/

//TODO: Finish this function.
void artifactGame::eventDeploymentPhase(){
    //Check the cards which would trigger at deployment, i.e barracks.
    for (size_t i = 0; i < cardsDeploymentPhase.size(); ++i){
        //TODO: Can improve by making lane specfic vectors of pointers for events so that this will not be needed.  However, unlikely needed.
        //More problems with this -- a can activate in graveyard for example, so it would not be a part of lane vectors, and additional vector would still be needed.
        //Minimal performance gains.
        if (activeLane == cardsDeploymentPhase[i].position.getLane()){
            //Activate the effect of the card.

            //When the possibleEffectTargets function is called, return possible targets, then check resulting board states
            //for minmax ai.  This check can occur in game level function.  Take as input ... continue TODO
            //tl;dr: generate a vector of board states and min max it.

            //std::vector<artifactGame> possibleBoardStates = getPossibleBoardStates();
            std::vector<std::vector<artifactPosition>> targets = getPossibleEffectTargets(cardsDeploymentPhase[i]);
            //
        }
    }

}

void artifactGame::eventSpawnCard(artifactCard card, const artifactPosition spawnLocation){
    qDebug() << "Entering artifactGame::eventSpawnCard";
    //Check if we are spawning the card in a valid position.
    if (spawnLocation.getLocation() != LANE){
        qDebug() << "artifactGame::eventSpawnCard: Attempt to spawn card in invalid location.";
        qDebug() << "Card: " << card.getCurrentName();
        qDebug() << "Location: " << spawnLocation.getLocation();
        return;
    }
    //Check if valid spawn index.
    if (spawnLocation.getIndex() >= players[spawnLocation.getSide()].lanes[spawnLocation.getLane()].cards.size() || spawnLocation.getIndex() < 0){
        qDebug() << "artifactGame::eventSpawnCard: Invalid index given: " << QString::number(spawnLocation.getIndex());
        return;
    }
    //Position should be valid.
    //TODO: Check that using .begin() with .insert is correct.
    card.position = spawnLocation;
    card.modifyId(nextId);
    players[spawnLocation.getSide()].lanes[spawnLocation.getLane()].cards.insert(players[spawnLocation.getSide()].lanes[spawnLocation.getLane()].cards.begin() + spawnLocation.getIndex(), card);

    //Loop through this lane and adjust the positions of the cards in the lane that changed position (all after spawned card).
    artifactPosition currentPosition = spawnLocation;
    for (size_t i = spawnLocation.getIndex() + 1; i < players[spawnLocation.getSide()].lanes[spawnLocation.getLane()].cards.size(); ++i){
        currentPosition.setIndex(i);
        players[spawnLocation.getSide()].lanes[spawnLocation.getLane()].cards[i].position = currentPosition;
    }
    return;
}




/**********************************************Top Level Effect Functions*************************/

//TODO: Some effects are mandatory.
//The target can be a location (ie spawning) or a current card (ie buffing).  Thus, we return positions instead of ptrs.
std::vector<std::vector<artifactPosition>> artifactGame::getPossibleEffectTargets(const artifactCard card){
    //The vector being returned.
    std::vector<std::vector<artifactPosition>> possibleTargets;

    //Use same string check structure as the createCard function in the utilities.cpp file.

    //Testing with Barracks.
    //Improvements will be retained as cards tied to the towers by unique_ptrs.
    if (card.getCurrentName() == "Barracks"){
        //Do nothing.  This way, empty vector is returned, meaning that no targets are required for the effect.
    }

    return possibleTargets;
}

//This function needs to tell the ai what targets it can take.  Should likely have getEffectTargets() function, which returns a vector of pointers
//to the possible targets.
//TODO: Does this function need to be on artifactGame level to do stuff like spawn?
void artifactGame::effect(const artifactCard card, const std::vector<artifactPosition> targets){
    //Same string check / switch structure as getTargetEffects and createCard.

    //Testing with Barracks.
    if (card.getCurrentName() == "Barracks"){
        //targets should have 1 member.
        //Spawn a melee creep card with 2/0/4 stat line in the row of Barracks.
        //artifactCard(QString name, int health, int armor, int attack, QString type, QString colourQString, QString rare);
        artifactCard meleeCreep("Melee Creep", 4, 0, 2, CREATURE, NEUTRAL, COMMON);
        //Targets should be one element for barracks.
        eventSpawnCard(meleeCreep, targets[0]);
    }
}

//For the AI to make decisions.
std::vector<artifactGame> artifactGame::getPossibleBoardStates(const artifactCard card) const{
    //Make a copy of the current boardState, we don't want to damage the board state in this.
    artifactGame startBoardState = *this;
    std::vector<artifactGame> possibleBoardStates;
    //An interim vector for how the tree branches both on body placement and effect.
    std::vector<artifactGame> interimBoardStates;

    //Creatures or heroes -- adding a body to the board from the hand.
    if (card.getType() == HERO || card.getType() == CREATURE){
        //Make sure the card is in the player's hand.
        bool inHand = false;
        for (size_t i = 0; i < players[activePlayer].hand.size(); ++i){
            if (players[activePlayer].hand[i].getId() == card.getId()){
                inHand = true;
                //It was played so we remove from the hand in startBoardState.
                startBoardState.players[activePlayer.hand.remove(startBoardState.players[activePlayer.hand.begin() + i)];
                break;
            }
        }

        //Card is in hand.
        if (inHand){
            //Play in possible positions.
            //Loop through the lanes, and the index of each lane.
            for (int i = 0; i < 3; i++){
                for (size_t j = 0; j < players[activePlayer].lanes[i].cards.size(); ++j){
                    artifactGame currentBoardState = startBoardState;
                    currentBoardState.players[activePlayer].lanes[i].cards.insert(currentBoardState.players[activePlayer].lanes[i].cards.begin() + j);
                    possibleBoardStates.push_back(currentBoardState);
                }
            }

            //Have vector of artifactGames now representing placement tree.
            //Now account for effects.
            //TODO: Improve performance by making above code act on interimBoardStates so we don't waste time copying.
            interimBoardStates = possibleBoardStates;
            possibleBoardStates.clear();
            for (size_t i = 0; i < interimBoardStates.size(); ++i){
                std::vector<std::vector<artifactPosition>> possibleTargets = interimBoardStates.getPossibleEffectTargets(card);
                for (size_t j = 0; j < possibleTargets.size(); ++j){
                    //TODO: Current board state created correctly?
                    artifactGame currentBoardState = interimBoardStates[i];
                    currentBoardState.effect(card, possibleTargets[j]);
                    possibleBoardStates.push_back(currentBoardState);
                }
            }
        }


    }

    //Spells or improvemnts -- things that do not add a body onto the board.  Also creatures / heros with effects that are already on board.

    if (!inHand){
        std::vector<std::vector<artifactPosition>> possibleTargets = getPossibleEffectTargets(card);
        for (size_t i = 0; i < possibleTargets.size(); ++i){
            //TODO: Current board state created correctly?
            artifactGame currentBoardState = startBoardState;
            currentBoardState.effect(card, possibleTargets[i]);
            possibleBoardStates.push_back(currentBoardState);
        }
    }






    return possibleBoardStates;
}
