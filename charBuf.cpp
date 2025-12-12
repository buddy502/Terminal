#include "charBuf.h"

void FontManager::initFreetype(const std::string& fontPath) {
   if (FT_Init_FreeType(&ftlib.ft)) {
      throw std::runtime_error("ERROR::FREETYPE: Could not init FreeType Library");
   }

   if (FT_New_Face(ftlib.ft, fontPath.c_str(), 0, &ftlib.face)) {
      throw std::runtime_error("ERROR::FREETYPE: Failed to load font");
   }
}

void FontManager::initCharTextures(){
   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

   FT_Set_Pixel_Sizes(ftlib.face, 0, 48);

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

void FontManager::ShaderBuffers() {
   // generate buffers
   glGenVertexArrays(1, &shaderBuf.VAO_f);
   glGenBuffers(1, &shaderBuf.VBO_f);
   // bind 
   glBindVertexArray(shaderBuf.VAO_f);
   glBindBuffer(GL_ARRAY_BUFFER, shaderBuf.VBO_f);
   // create data
   glBufferData(GL_ARRAY_BUFFER, 6 * 4 * sizeof(float), NULL, GL_DYNAMIC_DRAW);
   // required enable
   glEnableVertexAttribArray(0);
   // create pointer data for vertex attribute
   glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
   // unbind
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glBindVertexArray(0);
}

void FontManager::RenderText(uint id, std::string text, float x, float y,
      float scale, glm::vec3 color) {

   glUniform3f(glGetUniformLocation(id, "textColor"), color.x, color.y, color.z);
   glActiveTexture(GL_TEXTURE0);
   glBindVertexArray(shaderBuf.VAO_f);

   // iterate through all characters
   std::string::const_iterator c;
   for (c = text.begin(); c != text.end(); c++) 
   {
      s_Character ch = Characters[*c];

      float xpos = x + ch.Bearing.x * scale;
      float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

      float w = ch.Size.x * scale;
      float h = ch.Size.y * scale;
      // update VBO for each character
      float vertices[6][4] = {
         { xpos,     ypos + h,   0.0f, 0.0f },            
         { xpos,     ypos,       0.0f, 1.0f },
         { xpos + w, ypos,       1.0f, 1.0f },

         { xpos,     ypos + h,   0.0f, 0.0f },
         { xpos + w, ypos,       1.0f, 1.0f },
         { xpos + w, ypos + h,   1.0f, 0.0f }           
      };
      // render glyph texture over quad
      glBindTexture(GL_TEXTURE_2D, ch.TextureID);
      // update content of VBO memory
      glBindBuffer(GL_ARRAY_BUFFER, shaderBuf.VBO_f);
      glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData
                                                                       // updates a portion of an existing buffer

      glBindBuffer(GL_ARRAY_BUFFER, 0);
      // render quad
      glDrawArrays(GL_TRIANGLES, 0, 6);
      // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
      x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
   }
   glBindVertexArray(0);
   glBindTexture(GL_TEXTURE_2D, 0);
}

FontManager::~FontManager() {
    if (ftlib.face) FT_Done_Face(ftlib.face);
    if (ftlib.ft)   FT_Done_FreeType(ftlib.ft);
}
