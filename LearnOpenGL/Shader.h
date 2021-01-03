#ifndef SHADER_H
#define SHADER_H

#include<glad/glad.h>
#include<string>
#include<iostream>
#include<sstream>
#include<fstream>
#include<direct.h>

class Shader
{
	int vertexShader;
	int fragmentShader;
	int shaderProgram;
public:
	Shader(const char* vertexPath, const char* fragmentPath)
	{
		char* curDir;
		curDir = _getcwd(NULL, 0);

		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream vFragmentFile;
		vShaderFile.exceptions(std::ifstream::failbit || std::ifstream::badbit);
		vFragmentFile.exceptions(std::ifstream::failbit || std::ifstream::badbit);
		try
		{
			vShaderFile.open(vertexPath);
			vFragmentFile.open(fragmentPath);
			std::stringstream vShaderStream;
			std::stringstream vFragmentStream;
			vShaderStream << vShaderFile.rdbuf();
			vFragmentStream << vFragmentFile.rdbuf();
			vShaderFile.close();
			vFragmentFile.close();
			vertexCode = vShaderStream.str();
			fragmentCode = vFragmentStream.str();
		}
		catch (std::ifstream::failure e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		const char* shaderCode = vertexCode.c_str();
		glShaderSource(vertexShader, 1, &shaderCode, NULL);
		glCompileShader(vertexShader);
		int success;
		char infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		const char* code = fragmentCode.c_str();
		glShaderSource(fragmentShader, 1, &code, NULL);
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
		}
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	void use()
	{
		glUseProgram(shaderProgram);
	}

	void deleteShader()
	{
		glDeleteShader(shaderProgram);
	}

	void setInt(std::string name, float value)
	{
		glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), value);
	}
};
#endif