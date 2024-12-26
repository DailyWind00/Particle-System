#pragma once

# include <iostream>
# include <algorithm>
# include <vector>
# include <array>
# include <map>
# include <sstream>
# include "config.hpp"

using namespace std;
typedef array<float, 2> vec2;
typedef array<float, 3> vec3;
typedef array<float, 4> vec4;
typedef array<float, 16> mat4;

typedef struct shaderData {
    GLuint  shaderID;
    string  vertexPath;
    string  fragmentpath;
    string  shaderName;
}   shaderData;

typedef     map<GLuint, shaderData>::iterator ShaderIterator;
typedef     pair<GLuint, shaderData> ShaderPair;

class Shader {
    private:
        map<GLuint, shaderData>     shaders;
        vector<GLuint>              shaderIDs;
        GLuint                      currentShaderID;

        GLuint  make_module(const string &filepath, GLuint module_type);
        GLuint  make_shader(const string &vertex_path, const string &fragment_path);

    public:
        Shader();
        ~Shader();


        /// public functions

        void    use(GLuint shaderID);
        GLuint  recompile(GLuint shaderID);
        GLuint  add_shader(const string &vertexPath, const string &fragmentPath, const string &shaderName);
        void    remove_shader(GLuint shaderID);
        GLuint	SetNextShader();
        GLuint	SetPreviousShader();


        /// Uniforms setters

        void    setUniform(const GLuint &shaderID, const string &name, bool value);
        void    setUniform(const GLuint &shaderID, const string &name, int value);
        void    setUniform(const GLuint &shaderID, const string &name, float value);
        void    setUniform(const GLuint &shaderID, const string &name, vec2 value);
        void    setUniform(const GLuint &shaderID, const string &name, vec3 value);
        void    setUniform(const GLuint &shaderID, const string &name, vec4 value);
        void    setUniform(const GLuint &shaderID, const string &name, mat4 value);

        /// Getters

        const GLuint &getCurrentShaderID() const;
};