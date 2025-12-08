#pragma once

#include <array>
#include "openglHandles.h"

#define MAX_STR_BUFFER 256

// use a strBuf for text related buffers as char*
struct s_CharBuf {
   int count;
   int capacity;
   std::array<char*, MAX_STR_BUFFER> strbuf;
};

class CharsBuffer {
   private:
      s_CharBuf buf;
   public:
      CharsBuffer() = default;
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
