#pragma once

#include <array>
#include <stdio.h>
#include <map>

#include "openglHandles.h"
#include "history.h"

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

/* 
   We have a terminal filled with text that stays until the terminal
   erases it.
   Then we have a line of text that is forwarded to the history file
   and also able to change.
   The current line changes after every newline
   
   #  Body of terminal can be erased which removes all text shown
   apollo@repo/: Hello, World! 
   apollo@repo/: Hello, World!
   apollo@repo/: Hello, World!   # can change the current line

*/

/* 
   Mark a string with \0 and end current array   
   membuf = {"Hello\0"}
   membuf = {"World\0"}
*/

struct s_Cursor {
   glm::vec3 Color;  // cursor color
   uint pos;         // position isn't negative
};

struct s_StringBuf {
   size_t count;
   size_t capacity;
   char* strbuf;
};

// NOTE every line that you enter goes into historyBlock
struct s_MemLine {
   s_Cursor *cursor;
   s_StringBuf membuf;
};

// the memory block class used for each array of strings
//
// allow the class to activate freetype since it's also
// constructing the characters
class MemBlock {
   public:
      MemBlock() = default;

      void insertChar(s_MemLine *buf_t, char ch);
      void insertBuffer(s_MemLine *buf_t, char *buf, size_t bufLen);
      void updateBufferLine(s_MemLine *buf_t);
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
         (buf)->strbuf = static_cast<char*>(                   \
            reallocarray((buf)->strbuf, (buf)->capacity, sizeof(*(buf)->strbuf)));\
      }                                                        \
      (buf)->strbuf[(buf)->count++] = (item);                  \
   } while(0)

