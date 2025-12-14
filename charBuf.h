#pragma once

#include <array>
#include <stdio.h>
#include <map>

#include "openglHandles.h"

#include <ft2build.h>
#include FT_FREETYPE_H

#define MAX_STR_BUFFER 20

///////////////////////
///      SHADERS
///////////////////////
struct s_FTLib {
   FT_Library ft;
   FT_Face face;
};

struct s_ShaderBuf {
   unsigned int VBO_f;
   unsigned int VAO_f;
};

struct s_Character {
   unsigned int TextureID;  // ID handle of the glyph texture
   glm::ivec2   Size;       // Size of glyph
   glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
   unsigned int Advance;    // Offset to advance to next glyph
};

///////////////////////
///////////////////////
///////////////////////

// keep track of current line begin & end
struct s_Line {
   int begin;  // start of current array
   int end;    // end of current array
};

struct s_LineArr {
   s_Line line;
   size_t count;
   size_t capacity;
};

struct s_Cursor {
   glm::vec3 Color;  // cursor color
   uint pos;         // position isn't negative
};

struct s_StringBuf {
   size_t count;
   size_t capacity;
   std::array<char*, MAX_STR_BUFFER> strbuf;
};

// NOTE every line that you enter goes into historyBlock
struct s_MemLine {
   s_Cursor *cursor;
   s_LineArr *linearr;
   s_StringBuf buf;
};

// the memory block class used for each array of strings
//
// allow the class to activate freetype since it's also
// constructing the characters
class MemBlock {
   public:
      MemBlock() = default;

      void insertChar(s_MemLine *buf_t, char ch, s_Line line);
      void insertBuffer(s_MemLine *buf_t, char *buf, s_Line line, size_t bufLen);
      void updateBufferLines(s_MemLine *buf_t);
};

class FontManager {
   public:
      s_FTLib ftlib;
      s_ShaderBuf shaderBuf;

      std::map<char, s_Character> Characters;

      FontManager() = default;
      ~FontManager();

      void initFreetype(const std::string& fontPath);
      void initCharTextures();

      void ShaderBuffers();
      void RenderText(uint id, std::string text, float x, float y,
            float scale, glm::vec3 color);
};

// insert a single char into the buffer
#define CHAR_INSERT(buf, item)                                 \
   do {                                                        \
      if ((buf)->count >= (buf)->capacity) {                   \
         (buf)->capacity =                                     \
            (buf)->capacity == 0 ? MAX_STR_BUFFER : (buf)->capacity * 2;\
         (buf)->strbuf =                                       \
            reallocarray((buf->strbuf), 2 * (buf)->capacity, sizeof(char*));\
         ASSERT((buf)->strbuf != nullptr && "Reallocation failed");\
      }                                                        \
      (buf)->strbuf[(buf)->count++] = (item);                  \
   } while(0)

