#ifndef UTILITIES_H
#define UTILITIES_H

#include "artifactcard.h"
#include "globals.h"
#include <QDebug>
#include <random>

//Create an artifactCard given the name.
artifactCard createCard(QString name);

bool trueWithProbability(const double prob);



#endif // UTILITIES_H
