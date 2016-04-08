#pragma once

#include "gl/gl.h"
#include "gl/Quad.h"
#include "gl/Texture.h"
#include "gl/ShaderHelper.h"
#include "image/Utils.h"

namespace chr
{
  namespace gl
  {
    Texture loadTexture(const fs::path &relativePath, int flags = 0, bool useMipmap = true, GLenum wrapS = GL_CLAMP_TO_EDGE, GLenum wrapT = GL_CLAMP_TO_EDGE);
    Texture uploadMaskedTexture(const image::ImageBuffer &image, const image::ImageBuffer &mask, bool useMipmap = true, GLenum wrapS = GL_CLAMP_TO_EDGE, GLenum wrapT = GL_CLAMP_TO_EDGE);
    void uploadTexture(GLenum format, GLsizei width, GLsizei height, const GLvoid *data, bool useMipmap = true, GLenum wrapS = GL_CLAMP_TO_EDGE, GLenum wrapT = GL_CLAMP_TO_EDGE);

    const glm::mat4 getPerspectiveMatrix(float fovy, float zNear, float zFar, float width, float height, float panX, float panY, float zoom);

    glm::vec3 transformPoint(const glm::mat4 &matrix, const glm::vec2 &input);
    glm::vec3 transformPoint(const glm::mat4 &matrix, const glm::vec3 &input);

    template<int Primitive = GL_TRIANGLE_STRIP, int Orientation = GL_CCW, int Type>
    void addTransformedQuad(const glm::mat4 &matrix, const Quad<Type> &quad, std::vector<Vertex<Type>> &output);

    bool clip(Quad<UV> &quad, const math::Rectf &clipRect, const glm::vec2 &textureFactor);
  }
}
