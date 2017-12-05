#pragma once

#include "chr/cross/Context.h"
#include "chr/gl/Batch.h"
#include "chr/gl/shaders/LambertShader.h"
#include "chr/gl/shaders/TextureAlphaShader.h"

class Sketch : public chr::CrossSketch
{
public:
  Sketch();
  virtual ~Sketch() {}

  void setup() final;
  void draw() final;

protected:
  chr::gl::State state;

  chr::gl::IndexedVertexBatch<chr::gl::XYZ.N.UV> lightenBatch;
  chr::gl::shaders::LambertShader lambertShader;
  chr::gl::shaders::TextureAlphaShader textureAlphaShader;
  chr::gl::Texture texture;

  GLuint fboId;
  chr::gl::Texture fboColorTexture;
  chr::gl::Texture fboDepthTexture;

  void initTextures();
};
