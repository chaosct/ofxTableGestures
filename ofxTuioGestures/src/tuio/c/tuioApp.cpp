#include "tuioApp.h"
#include "inputGestureManager.h"
namespace tuio
{

void registerMeToInputGestureManager(InputGesture * IG)
{
    inputGestureManager::addGesture(IG);
}

}
