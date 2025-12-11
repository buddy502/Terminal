#include "charBuf.h"

void MemBlock::initCharTextures(){
   s_FTLib ftlib;
   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

   for (uint c = 0; c < 128; c++)
   {
      // load character glyph 
      if (FT_Load_Char(ftlib.face, c, FT_LOAD_RENDER))
      {
         std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
         continue;
      }
      // generate texture
      uint texture;
      glGenTextures(1, &texture);
      glBindTexture(GL_TEXTURE_2D, texture);
      glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            ftlib.face->glyph->bitmap.width,
            ftlib.face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            ftlib.face->glyph->bitmap.buffer
            );
      // set texture options
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      // now store character for later use
      s_Character character = {
         texture, 
         glm::ivec2(ftlib.face->glyph->bitmap.width, ftlib.face->glyph->bitmap.rows),
         glm::ivec2(ftlib.face->glyph->bitmap_left, ftlib.face->glyph->bitmap_top),
         ftlib.face->glyph->advance.x
      };

      Characters.insert(std::pair<char, s_Character>(c, character));
   }
}
