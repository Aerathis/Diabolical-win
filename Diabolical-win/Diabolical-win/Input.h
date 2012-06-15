#ifndef _INPUT_H
#define _INPUT_H

#include "keysym.h"

// The mouse handling is extremely simple at the moment since I don't even know what I want
// to do with it yet. 

namespace input
{
  enum e_dEventType
  {
    e_mouseEvent,
    e_keyEvent,
  };

  enum e_mEventType
  {
    e_mMotion,
    e_mButtonPress,
    e_mButtonRelease
  };

  enum e_mouseButton
  {
    e_lButton,
    e_rButton,
    e_mButton,
    e_noButton
  };

  struct s_mouseEvent
  {
    e_mEventType type;
    int xPos;
    int yPos;
    e_mouseButton button;
  };

  struct s_mouseState
  {
    int xPos;
    int yPos;
    bool buttonState; // True for down, false for up
  };

  struct s_DEvent
  {
    e_dEventType type;
    s_mouseEvent mouseEvent;
    DKeysym::e_DKeysym key;
  };

}

#endif //INPUT_H
