#pragma once

#include "gl/gl.h"

#include <map>
#include <experimental/string_view>

namespace chr
{
  namespace gl
  {
    namespace shader
    {
      struct Element
      {
        std::string vertexShaderSource;
        std::string fragmentShaderSource;

        int useCount;
        GLuint programId;
        GLuint vertexShaderId;
        GLuint fragmentShaderId;

        GLuint matrixLocation;
        GLuint positionLocation;
        GLuint colorLocation;
        GLuint normalLocation;
        GLuint coordLocation;
        GLuint samplerLocation;

        std::map<std::string, GLuint> map_uniform;
      };
    }

    class ShaderProgram
    {
    public:
      int id;
      shader::Element *element;

      ShaderProgram();
      ShaderProgram(const std::string &vertexShaderResourcePath, const std::string &fragmentShaderResourcePath);
      ShaderProgram(const ShaderProgram &other);
      ShaderProgram& operator=(const ShaderProgram &other);

      ~ShaderProgram();

      bool bind();
      void unbind();
      void unload();

      GLuint getUniformLocation(const std::string &name);

      void applyMatrix(const glm::mat4 &matrix);
      void applyColor(float r, float g, float b, float a);
      void applyColor(const glm::vec4 &color);

      inline void applyUniform(const std::string &name, int v0) { glUniform1i(getUniformLocation(name), v0); }
      inline void applyUniform(const std::string &name, int v0, int v1) { glUniform2i(getUniformLocation(name), v0, v1); }
      inline void applyUniform(const std::string &name, int v0, int v1, int v2) { glUniform3i(getUniformLocation(name), v0, v1, v2); }
      inline void applyUniform(const std::string &name, int v0, int v1, int v2, int v3) { glUniform4i(getUniformLocation(name), v0, v1, v2, v3); }
      inline void applyUniform(const std::string &name, float v0) { glUniform1f(getUniformLocation(name), v0); }
      inline void applyUniform(const std::string &name, float v0, float v1) { glUniform2f(getUniformLocation(name), v0, v1); }
      inline void applyUniform(const std::string &name, float v0, float v1, float v2) { glUniform3f(getUniformLocation(name), v0, v1, v2); }
      inline void applyUniform(const std::string &name, float v0, float v1, float v2, float v3) { glUniform4f(getUniformLocation(name), v0, v1, v2, v3); }
      inline void applyUniform(const std::string &name, const std::vector<int> &v) { glUniform1iv(getUniformLocation(name), v.size(), v.data()); }
      inline void applyUniform(const std::string &name, const glm::ivec2 &v) { glUniform2iv(getUniformLocation(name), 1, &v[0]); }
      inline void applyUniform(const std::string &name, const glm::ivec3 &v) { glUniform3iv(getUniformLocation(name), 1, &v[0]); }
      inline void applyUniform(const std::string &name, const glm::ivec4 &v) { glUniform4iv(getUniformLocation(name), 1, &v[0]); }
      inline void applyUniform(const std::string &name, const std::vector<float> &v) { glUniform1fv(getUniformLocation(name), v.size(), v.data()); }
      inline void applyUniform(const std::string &name, const glm::vec2 &v) { glUniform2fv(getUniformLocation(name), 1, &v[0]); }
      inline void applyUniform(const std::string &name, const glm::vec3 &v) { glUniform3fv(getUniformLocation(name), 1, &v[0]); }
      inline void applyUniform(const std::string &name, const glm::vec4 &v) { glUniform4fv(getUniformLocation(name), 1, &v[0]); }

    protected:
      static int usageCounter;

      bool load();
    };
  }
}
