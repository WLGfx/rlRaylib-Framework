/*******************************************************************************************
*
*   1280x800T v1.0.0 - Tool Description
*
*   MODULE USAGE:
*       #define GUI_1280X800T_IMPLEMENTATION
*       #include "gui_1280x800T.h"
*
*       INIT: Gui1280x800TState state = InitGui1280x800T();
*       DRAW: Gui1280x800T(&state);
*
*   LICENSE: Propietary License
*
*   Copyright (c) 2022 raylib technologies. All Rights Reserved.
*
*   Unauthorized copying of this file, via any medium is strictly prohibited
*   This project is proprietary and confidential unless the owner allows
*   usage in any other form by expresely written permission.
*
**********************************************************************************************/

#include "raylib.h"

// WARNING: raygui implementation is expected to be defined before including this header
#undef RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include <string.h>     // Required for: strcpy()

#ifndef GUI_1280X800T_H
#define GUI_1280X800T_H

typedef struct {
    // Define anchors
    Vector2 anchor01;            // ANCHOR ID:1

    // Define rectangles
    Rectangle layoutRecs[8];

    // Custom state variables (depend on development software)
    // NOTE: This variables should be added manually if required

} Gui1280x800TState;

#ifdef __cplusplus
extern "C" {            // Prevents name mangling of functions
#endif

//----------------------------------------------------------------------------------
// Defines and Macros
//----------------------------------------------------------------------------------
//...

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------
// ...

//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------
Gui1280x800TState InitGui1280x800T(void);
void Gui1280x800T(Gui1280x800TState *state);

#ifdef __cplusplus
}
#endif

#endif // GUI_1280X800T_H

/***********************************************************************************
*
*   GUI_1280X800T IMPLEMENTATION
*
************************************************************************************/
#if defined(GUI_1280X800T_IMPLEMENTATION)

#include "raygui.h"

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
//...

//----------------------------------------------------------------------------------
// Internal Module Functions Definition
//----------------------------------------------------------------------------------
//...

//----------------------------------------------------------------------------------
// Module Functions Definition
//----------------------------------------------------------------------------------
Gui1280x800TState InitGui1280x800T(void)
{
    Gui1280x800TState state = { 0 };

    // Init anchors
    state.anchor01 = (Vector2){ 16, 8 };            // ANCHOR ID:1
    
    // Init controls rectangles
    state.layoutRecs[0] = (Rectangle){ 0, 0, 1280, 800 };// Panel: rPanel_1
    state.layoutRecs[1] = (Rectangle){ 8, 72, 1264, 16 };// Line: rLine
    state.layoutRecs[2] = (Rectangle){ 8, 8, 1264, 64 };// Panel: rPanel_2
    state.layoutRecs[3] = (Rectangle){ 16, 32, 192, 24 };// Label: rLabel_title
    state.layoutRecs[4] = (Rectangle){ 200, 408, 880, 64 };// DummyRec: rDummy

    state.layoutRecs[7] = (Rectangle){ 8, 768, 1264, 24 };// StatusBar: rStatus

    // Custom variables initialization

    return state;
}

void Gui1280x800T(Gui1280x800TState *state)
{
    // Const text
    const char *rLabel_titleText = "WLGfx - Time is not the problem";    // LABEL: rLabel_title
    const char *rDummyText = "Space";    // DUMMYREC: rDummy
    const char *rStatusText = "SAMPLE TEXT";    // STATUSBAR: rStatus
    
    // Draw controls
    GuiDummyRec(state->layoutRecs[4], rDummyText);
    GuiStatusBar(state->layoutRecs[7], rStatusText);
}

#endif // GUI_1280X800T_IMPLEMENTATION
