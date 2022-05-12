#pragma once

#include <glad/glad.h>
#include <string>

namespace Renderer {

	class ShaderProgram {
		bool isCompiled_{};
		GLuint program_id_{};
	private:
		ShaderProgram(const ShaderProgram&) = delete;
		ShaderProgram& operator =(const ShaderProgram&) = delete;
		std::pair<GLuint, bool> CreateShader(std::string_view source, const GLenum shaderType);
	public:
		ShaderProgram() = delete;
		ShaderProgram(std::string_view vertexShader, std::string_view fragmentShader);
		ShaderProgram& operator = (ShaderProgram&& shaderProgram) noexcept;
		ShaderProgram(ShaderProgram&& shaderProgram) noexcept;
		~ShaderProgram();
		bool isCompiled() const;
		void use() const;

	};
}