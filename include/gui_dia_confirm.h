/*******************************************************************************************
*
*   DiaConfirm v1.0.0 - Tool Description
*
*   MODULE USAGE:
*       #define GUI_DIA_CONFIRM_IMPLEMENTATION
*       #include "gui_dia_confirm.h"
*
*       INIT: GuiDiaConfirmState state = InitGuiDiaConfirm();
*       DRAW: GuiDiaConfirm(&state);
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

#ifndef GUI_DIA_CONFIRM_H
#define GUI_DIA_CONFIRM_H

typedef struct {
    // Define anchors
    Vector2 anchor_dia_1;            // ANCHOR ID:1
    
    // Define controls variables
    bool messageWindowActive;            // WindowBox: messageWindow

    // Define rectangles
    Rectangle layoutRecs[4];

    // Custom state variables (depend on development software)
    // NOTE: This variables should be added manually if required

} GuiDiaConfirmState;

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
GuiDiaConfirmState InitGuiDiaConfirm(void);
void GuiDiaConfirm(GuiDiaConfirmState *state);

#ifdef __cplusplus
}
#endif

#endif // GUI_DIA_CONFIRM_H

/***********************************************************************************
*
*   GUI_DIA_CONFIRM IMPLEMENTATION
*
************************************************************************************/
#if defined(GUI_DIA_CONFIRM_IMPLEMENTATION)

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
GuiDiaConfirmState InitGuiDiaConfirm(void)
{
    GuiDiaConfirmState state = { 0 };

    // Init anchors
    state.anchor_dia_1 = (Vector2){ 216, 168 };            // ANCHOR ID:1
    
    // Initilize controls variables
    state.messageWindowActive = true;            // WindowBox: messageWindow

    // Init controls rectangles
    state.layoutRecs[0] = (Rectangle){ 216, 208, 352, 128 };// WindowBox: messageWindow
    state.layoutRecs[1] = (Rectangle){ state.anchor_dia_1.x + 16, state.anchor_dia_1.y + 40, 320, 32 };// Label: lblMessage
    state.layoutRecs[2] = (Rectangle){ state.anchor_dia_1.x + 48, state.anchor_dia_1.y + 80, 120, 32 };// Button: SureButton
    state.layoutRecs[3] = (Rectangle){ state.anchor_dia_1.x + 192, state.anchor_dia_1.y + 80, 120, 32 };// Button: ContinueButton

    // Custom variables initialization

    return state;
}

void GuiDiaConfirm(GuiDiaConfirmState *state)
{
    // Const text
    const char *messageWindowText = "rGuiLayout - GuiMessageBox";    // WINDOWBOX: messageWindow
    const char *lblMessageText = "Are you ready to create the most amazing tools?";    // LABEL: lblMessage
    const char *SureButtonText = "Sure!";    // BUTTON: SureButton
    const char *ContinueButtonText = "Continue!";    // BUTTON: ContinueButton
    
    // Draw controls
    if (state->messageWindowActive)
    {
        state->messageWindowActive = !GuiWindowBox(state->layoutRecs[0], messageWindowText);
    }
    GuiLabel(state->layoutRecs[1], lblMessageText);
    if (GuiButton(state->layoutRecs[2], SureButtonText)); // Sure button
    if (GuiButton(state->layoutRecs[3], ContinueButtonText)); // Continue button
}

#endif // GUI_DIA_CONFIRM_IMPLEMENTATION
