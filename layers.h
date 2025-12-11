#pragma once

#include "openglHandles.h"

class Layers {
   public:
      void OnEvent();    // keystrokes in terminal
      void OnUpdate();   // unimplemented
      void OnRender();   // opengl rendering for text
};
