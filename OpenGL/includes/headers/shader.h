#ifndef SHADER_H
#define SHADER_H

#include "fstream"
#include "glad/glad.h"
#include "iostream"
#include "string"
#include <sstream>

std::string readFile(const char *path) {
    std::string code;
    std::ifstream fileStream;

    fileStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    fileStream.open(path);

    std::stringstream stringStream;

    stringStream << fileStream.rdbuf();

    fileStream.close();
    code = stringStream.str();
    return code;
};

class Shader {
  public:
    unsigned int ID; // program ID
    Shader(const char *vertexPath, const char *fragmentPath) {
        std::string vertexCode, fragmentCode;

        try {
            vertexCode = readFile(vertexPath);
            fragmentCode = readFile(fragmentPath);
        } catch (std::ifstream::failure e) {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ\n";
        }

        const char *vShaderCode = vertexCode.c_str();
        const char *fShaderCode = fragmentCode.c_str();

        unsigned int vertex, fragment;
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        checkErrors(vertex, "VERTEX");

        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        checkErrors(fragment, "FRAGMENT");

        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);
        checkErrors(ID, "LINK");

        glDeleteShader(vertex);
        glDeleteShader(fragment);
    };

    // activate the Shader
    void use() { glUseProgram(ID); }

    // utility uniform setters
    void setBool(const std::string &name, bool value) const {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
    }
    void setInt(const std::string &name, int value) const {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }
    void setFloat(const std::string &name, float value) const {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }

  private:
    void checkErrors(unsigned int shader, std::string type) {
        int success;
        char infoLog[512];

        if (type != "LINK") {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(shader, 512, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR in: " << type
                          << "\n"
                          << infoLog << "\n";
            }
        } else {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success) {
                glGetProgramInfoLog(shader, 512, NULL, infoLog);
                std::cout << "ERROR::SHADER_LINKING_ERROR\n" << infoLog << "\n";
            }
        }
    }
};

#endif /* ifndef SHADER_H                                                      \
                                                                               \
#include "fstream"                                                             \
#include "glad/glad.h"                                                         \
#include "iostream"                                                            \
#include "string"                                                              \
                                                                               \
class Shader {                                                                 \
  public:                                                                      \
    unsigned int ID; // program ID                                             \
    Shader(const char* vertexPath, const char* fragmentPath) {                 \
                                                                               \
      std::string vertexCode;                                                  \
      std::string fragmentCode;                                                \
      std::ifstream vShaderFileStream;                                         \
      std::ifstream fShaderFileStream;                                         \
                                                                               \
      vShaderFileStream.exceptions(std::ifstream::fail)                        \
    }                                                                          \
                                                                               \
    // activate the Shader                                                     \
    void use();                                                                \
                                                                               \
    // utility uniform setters                                                 \
    void setBool(const std::string &name, bool value) const;                   \
    void setInt(const std::string &name, int value) const;                     \
    void setFloat(const std::string &name, float value) const;                 \
};                                                                             \
 */
