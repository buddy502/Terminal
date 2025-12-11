#pragma once

#include <array>
#include <stdio.h>
#include <map>

#include "openglHandles.h"

#include <ft2build.h>
#include FT_FREETYPE_H

#define MAX_STR_BUFFER 20

struct s_FTLib {
   FT_Library ft;
   FT_Face face;
};

struct s_Character {
   unsigned int TextureID;  // ID handle of the glyph texture
   glm::ivec2   Size;       // Size of glyph
   glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
   unsigned int Advance;    // Offset to advance to next glyph
};

// keep track of current line begin & end
struct s_Line {
   int begin;  // start of current array
   int end;    // end of current array
};
// NOTE every line that you enter goes into historyBlock
struct s_MemLine {
   int count;
   int capacity;
   std::array<uint, MAX_STR_BUFFER> strbuf;
};
struct s_Cursor {
   glm::vec3 Color;  // cursor color
   uint position;    // position isn't negative
};

// the memory block class used for each array of strings
//
// allow the class to activate freetype since it's also
// constructing the characters
class MemBlock {
   private:
      s_MemLine buf_t;
      s_Cursor cursor_t;

      s_FTLib Ftlib_t;
   public:
      MemBlock() = default;

      void init(const std::string& fontPath) {
         if (FT_Init_FreeType(&Ftlib_t.ft)) {
            throw std::runtime_error("ERROR::FREETYPE: Could not init FreeType Library");
         }

         if (FT_New_Face(Ftlib_t.ft, fontPath.c_str(), 0, &Ftlib_t.face)) {
            throw std::runtime_error("ERROR::FREETYPE: Failed to load font");
         }
      }
      ~MemBlock() {
         FT_Done_FreeType(Ftlib_t.ft);
      }

      std::map<char, s_Character> Characters;

      void initCharTextures();
      void insertChar(s_Line buf_t);
};

// insert a single char into the buffer
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
