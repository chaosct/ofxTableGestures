#include "GenericManager.hpp"

// Gestures //////
#include "InputGestureTuio1.12D.hpp"
#include "InputGestureTuio1.12.5D.hpp"
#include "InputGestureTuio1.13D.hpp"
#include "InputGestureBasicFingers.hpp"
#include "InputGestureBasicObjects.hpp"
#include "InputGestureDirectFingers.hpp"
#include "InputGestureDirectObjects.hpp"
#include "InputGestureTap.hpp"
#include "InputGestureLongPush.hpp"

// Feedback //////
#include "ObjectFeedback.hpp"
#include "CursorFeedback.hpp"
#include "TapFeedback.hpp"

// Graphics //////
#include "GraphicDispatcher.hpp"

GenericManager::~GenericManager(){
    // Delete gestures
    delete get<InputGestureTuio112D>();
    // delete get<InputGestureTuio1125D>();
    // delete get<InputGestureTuio113D>();
    delete get<InputGestureBasicFingers>();
    delete get<InputGestureDirectFingers>();
    delete get<InputGestureBasicObjects>();
    delete get<InputGestureDirectObjects>();
    delete get<InputGestureTap>();

    // Delete feedback
    delete get<ObjectFeedback>();
    delete get<CursorFeedback>();
    delete get<TapFeedback>();

    // Delete GraphicDispatcher
    delete get<GraphicDispatcher>();
}

void GenericManager::initAll(){
    // Init gestures
    get<InputGestureTuio112D>();
    // get<InputGestureTuio1125D>();
    // get<InputGestureTuio113D>();
    get<InputGestureBasicFingers>();
    get<InputGestureDirectFingers>();
    get<InputGestureBasicObjects>();
    get<InputGestureDirectObjects>();
    get<InputGestureTap>();

    // Init feedback
    get<ObjectFeedback>();
    get<CursorFeedback>();
    get<TapFeedback>();

    // Init GraphicDispatcher
    get<GraphicDispatcher>();
}

