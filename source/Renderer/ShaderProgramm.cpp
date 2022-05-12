#include "ShaderProgramm.h"
#include <iostream>


namespace Renderer {

	std::pair<GLuint, bool> ShaderProgram::CreateShader(std::string_view source, const GLenum shaderType)
	{
		GLuint typeShaders{ glCreateShader(shaderType) };

		const char* code{ source.data() };
		glShaderSource(typeShaders, 1, &code, nullptr);
		glCompileShader(typeShaders);

		GLint success{};
		glGetShaderiv(typeShaders, GL_COMPILE_STATUS, &success);
		if (!success) {
			GLchar log[1024]{};
			glGetShaderInfoLog(typeShaders, 1024, nullptr, log);
			std::cerr << log << std::endl;
			return { 0, false };
		}
		return { typeShaders , true};
	}

	ShaderProgram::ShaderProgram(std::string_view vertexShader, std::string_view fragmentShader)
	{
		auto [vertexShaderID, isCreateVertexShader] = CreateShader(vertexShader, GL_VERTEX_SHADER);
		if (!isCreateVertexShader) {
			std::cerr << "VERTEX SHADER compile-time error!" << std::endl;
			std::terminate();
		}
		auto [fragmentShaderID, isCreateFragmentShader] = CreateShader(fragmentShader, GL_FRAGMENT_SHADER);
		if (!isCreateFragmentShader) {
			std::cerr << "FRAGMENT SHADER compile-time error!" << std::endl;
			glDeleteShader(vertexShaderID);
			std::terminate();
		}
		program_id_ = glCreateProgram();
		glAttachShader(program_id_, vertexShaderID);
		glAttachShader(program_id_, fragmentShaderID);
		glLinkProgram(program_id_);

		GLint isSuccessLink{};
		glGetProgramiv(program_id_, GL_LINK_STATUS, &isSuccessLink);
		if (!isSuccessLink) {
			std::cerr << "ERROR::SHADER link-time error!" << std::endl;
			glDeleteShader(vertexShaderID);
			glDeleteShader(fragmentShaderID);
			std::terminate();
		}
		isCompiled_ = true;
		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);
	}

	ShaderProgram& ShaderProgram::operator=(ShaderProgram&& shaderProgram) noexcept
	{
		glDeleteProgram(program_id_);
		program_id_ = shaderProgram.program_id_;
		shaderProgram.program_id_ = 0;
		shaderProgram.isCompiled_ = false;
		return *this;
	}

	ShaderProgram::ShaderProgram(ShaderProgram&& shaderProgram) noexcept
	{
		program_id_ = shaderProgram.program_id_;
		shaderProgram.program_id_ = 0;
		shaderProgram.isCompiled_ = false;
	}

	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(program_id_);
	}

	bool ShaderProgram::isCompiled() const
	{
		return isCompiled_;
	}

	void ShaderProgram::use() const
	{
		glUseProgram(program_id_);
	}

}