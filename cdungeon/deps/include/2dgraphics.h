
#ifndef TWODGRAPHICS_H
#define TWODGRAPHICS_H

// #include "util.h"
#include "glapi.h"
#include "linmath.h"

#include <ft2build.h>
#include FT_FREETYPE_H

typedef struct Char {
  // Place in texture
  u8 c;
  union vec place;
  union vec size;
  union vec bearing;
  u32 advance;
} Char;

typedef struct typeface {
  char* name;
  hashtable* chars;
  
  // Opengl stuffs
  u8* tex;
  union vec texsize;
  u32 gl;
  GLuint slot;
  u32 space_width;
} typeface;
typeface* loadfont(char* file);
void doneloadingfonts();
typeface* loadchars(FT_Face face, char* chars);

typedef struct imagedata {
  u32 id;
  GLuint slot;
  GLenum type;
  u16 uses;
  union vec size;
  bool typeface;
  char* name; // Heap string
} imagedata;

typedef enum {
  QUAD,
  TEXT
} drawprimitives;

typedef struct spritesheet {
  size_t img;
  int step_y;
  int step_x;
} spritesheet;

typedef u32 img;

// Init for opengl
void loadglgraphics();

// Text things(took so longgggggggg)
void tfont(char* name);
void tsiz(u16 size);
void text(char* text, int x, int y);

// Draw related commands
void draw(void);
void rect(int x, int y, int w, int h);
void fill(float c1, float c2, float c3, float c4);

// Advanced stuff
void skiprec(u16 n);
void shapecolor(vec4 col, u16 verts);

// Image things took even longer than text :((((((
img loadimage(char* path);
img loadpixelart(char* path);
imagedata *imgd(img index);
void image(img image, int x, int y, int w, int h);
void imagesub(img image, int ix, int iy, int iw, int ih, int itx, int ity, int itw, int ith);

spritesheet* createss(img img, int step_x, int step_y);
void sprite(spritesheet * s, int sx, int sy, int x, int y, int w, int h);

#endif

