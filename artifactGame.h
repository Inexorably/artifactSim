#ifndef ARTIFACTGAME_H
#define ARTIFACTGAME_H

#include "artifactplayer.h"
#include "artifactposition.h"
#include "globals.h"
#include "utilities.h"

#include <memory>
#include <vector>


//Contains the artifact board, and by extension the players which are subclasses of the board.

struct artifactGame{
    artifactGame();
    std::vector<artifactPlayer> players;


    /******************Debug / Testing*****************************************/
    void createDebugDecks();
    void debugOutputdecks();


    /**************************Utility********************************************/

    //We need to overload the assignment operator so we can deepy copy the unique_ptr members.
    //11/21: Not needed due to removal of ptr vectors.
    //void deepCopy(const std::vector<std::shared_ptr<artifactCard>> from, std::vector<std::shared_ptr<artifactCard>> &to);
    //void operator = (const artifactGame &game);
    //artifactGame(const artifactGame &game);

    /***************************Game setup and nonevent turn functions***********************************************************/
    void assignIds();
    int nextId; //The next id to be assigned.  For example, if we spawn a card, we must give it an id number.
    void roundStart();
    void gameStart();  //A top level function that is called at the start of each game.  Calls functions such as assignIds.
    void executeRound();    //Play out the round.
    int radiantPlayerNum;   //0 or 1.  Other player is dire.  Used for determining who goes first.
    int activeLane; //The lane that is currently active.  0, 1, or 2.
    int activePlayer;   //0 or 1.
    int initiativePlayer; //Who has initiative?  0 or 1.

    /************************Base Mechanics (Spawning / Buffing, Destroying -- Events that could trigger effects*********/

    //When a base mechanic function is called (such as a card being destroyed, drawn, or buffed), that mechanic function will at resolution
    //check these vectors for cards that have been waiting for said event to trigger.
    //When a card is deployed / waiting to trigger, it is pushed onto these vectors.
    //When it can no longer trigger (ie dies or effect is negated) it is removed from these vectors.
    std::vector<artifactCard> cardsDrawn;
    std::vector<artifactCard> cardsDeploymentPhase;
    std::vector<artifactCard> cardsArmorIncreased;

    //Would be nice to have event class and do signals / slots but that can cause incorrect order executions (ie signal sent, inconsistent amount of code executed, function emitted).
    void eventActionPhase();

    void eventDeploymentPhase();
    //A card is spawned from nothing (not played or resurrected) ie Barracks.
    void eventSpawnCard(artifactCard card, const artifactPosition spawnLocation);

    /***************************Top Level Effect Functions***************************/

    //The effect functions are on a game level so that we can use the board variables which are on the player level.
    //Hierarchy: cards | towers -> players -> game
    //We want a vector of vectors because there can be different possibilities or numbers of targets.
    std::vector<std::vector<artifactPosition>> getPossibleEffectTargets(const artifactCard card);

    //Some choosing should happen to choose one vector of possible targets for calling effect.

    //TODO: Some effects do not need a target (input argument), while others do.
    //Can do this on artifactGame level, or by overloading the effect function and passing
    //by players/lanes by reference.
    //Should have effectRequirements function, which returns possible targets and costs like mana.
    void effect(const artifactCard card, const std::vector<artifactPosition> targets);

    //This function returns the resultant possible board states from different choices in the form of vector<artifactGame>.
    std::vector<artifactGame> getPossibleBoardStates(const artifactCard card);

};



#endif // ARTIFACTGAME_H
