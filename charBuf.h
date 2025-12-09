#pragma once

#include <array>
#include <stdio.h>

#include "openglHandles.h"
#include "types.h"

#define MAX_STR_BUFFER 20

// keep track of current line begin & end
struct s_MemLine {
   int begin;
   int end;
};

// NOTE every line that you enter goes into historyBlock
struct s_Line {
   int count;
   int capacity;
   std::array<uint, MAX_STR_BUFFER> strbuf;
};

struct s_Cursor {
   Vec3<float> Color;
};

class MemBlock {
   private:
      s_Line buf_t;
      s_Cursor cursor_t;
   public:

      MemBlock() = default;

      void insertChar(s_Line buf_t);
};

#define CHAR_INSERT(item, buf){                                \
   do {                                                        \
      if ((buf)->count >= (buf)->capacity) {                   \
         (buf)->capacity =                                     \
            (buf)->capacity == 0 ? MAX_STR_BUFFER : (buf)->capacity * 2;\
         (buf)->strbuf =                                       \
            reallocarray((buf->strbuf), 2 * (buf)->capacity, sizeof(char*));\
         ASSERT((buf)->strbuf != nullptr && "Reallocation failed");\
      }                                                        \
      (buf)->strbuf[(buf)->count++] = (item);                  \
   } while(0)                                                  \
}
