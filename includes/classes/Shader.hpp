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

        template <typename T>
        void    setUniform(const GLuint &shaderID, const string &name, T value) {
            use(shaderID);

            if (is_same<T, bool>())
                glUniform1i(glGetUniformLocation(shaderID, name.c_str()), (int)value);
            else if (is_same<T, int>())
                glUniform1i(glGetUniformLocation(shaderID, name.c_str()), value);
            else if (is_same<T, float>())
                glUniform1f(glGetUniformLocation(shaderID, name.c_str()), value);
            else if (is_same<T, vec2>())
                glUniform2f(glGetUniformLocation(shaderID, name.c_str()), value[0], value[1]);
            else if (is_same<T, vec3>())
                glUniform3f(glGetUniformLocation(shaderID, name.c_str()), value[0], value[1], value[2]);
            else if (is_same<T, vec4>())
                glUniform4f(glGetUniformLocation(shaderID, name.c_str()), value[0], value[1], value[2], value[3]);
            else if (is_same<T, mat4>())
                glUniformMatrix4fv(glGetUniformLocation(shaderID, name.c_str()), 1, GL_FALSE, &value[0]);
            else
                throw runtime_error("Invalid uniform type");
            
            use(0);
        };

        /// Getters

        const GLuint &getCurrentShaderID() const;
};