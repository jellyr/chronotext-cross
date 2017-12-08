#include "Sketch.h"

#include "chr/gl/draw/Cube.h"
#include "chr/gl/draw/Rect.h"

using namespace std;
using namespace chr;
using namespace gl;

Sketch::Sketch()
{}

void Sketch::setup()
{
  setupFramebuffer();

  texture = Texture(Texture::ImageRequest("lys_32.png")
    .setFlags(image::FLAGS_TRANSLUCENT_INVERSE)
    .setMipmap(true)
    .setAnisotropy(true)
    .setWrap(GL_REPEAT, GL_REPEAT));

  textureBatch
    .setShader(textureShader)
    .setShaderColor(1, 1, 1, 1)
    .setTexture(fboColorTexture);

  lightenBatch.setTexture(texture);

  // ---

  draw::Rect()
    .setBounds(-200, -200, 400, 400)
    .setTextureScale(400.0f / fboColorTexture.width)
    .append(textureBatch, Matrix());

  //

  draw::Cube()
    .setSize(150)
    .append(lightenBatch, Matrix());

  // ---

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Sketch::draw()
{
  GLint defaultFBOId = 0;
  if (CHR_PLATFORM == PLATFORM_IOS) glGetIntegerv(GL_FRAMEBUFFER_BINDING, &defaultFBOId);

  glBindFramebuffer(GL_FRAMEBUFFER, fboId);
  drawScene2(fboColorTexture.size);
  glBindFramebuffer(GL_FRAMEBUFFER, defaultFBOId);

//  fboColorTexture.bind();
//  glGenerateMipmap(GL_TEXTURE_2D);
//  fboColorTexture.unbind();

  drawScene1();
}

void Sketch::setupFramebuffer()
{
  fboColorTexture = Texture(
    Texture::EmptyRequest(512, 512));

  glGenRenderbuffers(1, &rboId);
  glBindRenderbuffer(GL_RENDERBUFFER, rboId);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, 512, 512);
  glBindRenderbuffer(GL_RENDERBUFFER, 0);

  glGenFramebuffers(1, &fboId);
  glBindFramebuffer(GL_FRAMEBUFFER, fboId);

  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fboColorTexture.textureId, 0);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboId);

  switch (glCheckFramebufferStatus(GL_FRAMEBUFFER))
  {
    case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT :
      printf("FBO Incomplete Attachment\n");
      break;
    case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT :
      printf("FBO Missing Attachment\n");
      break;
    case GL_FRAMEBUFFER_UNSUPPORTED :
      printf("FBO Unsupported\n");
      break;
    case GL_FRAMEBUFFER_COMPLETE:
      printf("FBO OK\n");
      break;
    default:
      printf("FBO Problem?\n");
  }

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Sketch::drawScene1()
{
  glViewport(0, 0, windowInfo.width, windowInfo.height);

  glDisable(GL_CULL_FACE);
  glDisable(GL_DEPTH_TEST);
  glDepthMask(GL_FALSE);

  glClearColor(1, 0.75f, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT);

  // ---

  auto projectionMatrix = glm::perspective(60 * D2R, windowInfo.width / windowInfo.height, 0.1f, 1000.0f);

  Matrix mvMatrix;
  mvMatrix
    .scale(1, 1, 1)
    .translate(0, 0, -400)
    .rotateY(clock()->getTime() * 0.25f);

  auto mvpMatrix = mvMatrix * projectionMatrix;

  // ---

  State()
    .setShaderMatrix<MVP>(mvpMatrix)
    .apply();

  textureBatch.flush();
}

void Sketch::drawScene2(const glm::ivec2 &size)
{
  glViewport(0, 0, size.x, size.y);

  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  glDepthMask(GL_TRUE);

  glClearColor(0.5f, 0.5f, 0.5f, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // ---

  auto projectionMatrix = glm::perspective(60 * D2R, size.x / (float)size.y, 0.1f, 1000.0f);

  Matrix mvMatrix;
  mvMatrix
    .scale(1, -1, 1)
    .translate(0, 0, -300)
    .rotateY(clock()->getTime())
    .rotateZ(clock()->getTime() * 0.25f);

  auto mvpMatrix = mvMatrix * projectionMatrix;

  // ---

  State()
    .setShaderMatrix<MVP>(mvpMatrix)
    .setShaderMatrix<NORMAL>(mvMatrix.getNormalMatrix())
    .apply();

  glEnable(GL_POLYGON_OFFSET_FILL);
  glPolygonOffset(2, 1);

  lightenBatch
    .setShader(lambertShader)
    .setShaderColor(0.25f, 0.25f, 0.25f, 1)
    .flush();

  glDepthMask(GL_FALSE);
  glDisable(GL_POLYGON_OFFSET_FILL);

  lightenBatch
    .setShader(textureAlphaShader)
    .setShaderColor(1, 1, 1, 0.5f)
    .flush();
}