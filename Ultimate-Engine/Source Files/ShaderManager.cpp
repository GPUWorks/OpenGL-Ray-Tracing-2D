/*-----------------------------------------------------------------------------
Author: Bîrzu George
Email:	b.gxg7@yahoo.com
Date:	08-11-2015
-----------------------------------------------------------------------------*/

#include "ShaderManager.h"



managers::ShaderManager::ShaderManager(void) { }

managers::ShaderManager::~ShaderManager(void)
{
	std::map<std::string, GLuint>::iterator it;

	for (it = programs.begin(); it != programs.end(); ++it)
	{
		GLuint pr = it->second;
		glDeleteProgram(pr);
	}

	programs.clear();
}

std::string managers::ShaderManager::readShader(const std::string& filename)
{
	std::ifstream file(filename, std::ios::in);

	if (!file.good()) {
		std::cout << "Can't read file " << filename.c_str() << std::endl;
		std::terminate();
	}

	std::string shaderCode;

	file.seekg(0, std::ios::end);
	shaderCode.resize(static_cast<unsigned int> (file.tellg()));

	file.seekg(0, std::ios::beg);
	file.read(&shaderCode[0], shaderCode.size());

	file.close();

	return shaderCode;
}

GLuint managers::ShaderManager::createShader(GLenum shaderType,
	const std::string& source,
	const std::string& shaderName)
{
	GLint isCompiled = GL_FALSE;

	GLuint shader = glCreateShader(shaderType);

	if (shader == 0)
		std::cout << "Shader Loader : CREATE SHADER ERROR " << shaderName.c_str() << std::endl;

	const char *shader_code_ptr = source.c_str();
	const int   shader_code_size = source.size();

	glShaderSource(shader, 1, &shader_code_ptr, &shader_code_size);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_FALSE)
	{
		int info_log_length = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_length);

		std::vector<char> shader_log(info_log_length);
		glGetShaderInfoLog(shader, info_log_length, NULL, &shader_log[0]);

		std::cout << "Shader Loader : COMPILE ERROR " << shaderName.c_str() << std::endl << &shader_log[0] << std::endl;
		return 0;
	}

	return shader;
}

void managers::ShaderManager::createProgram(const std::string& shaderName,
	const std::string& vertexShaderFilename,
	const std::string& fragmentShaderFilename)
{
	std::string vertex_shader_code = readShader(vertexShaderFilename);
	std::string fragment_shader_code = readShader(fragmentShaderFilename);

	GLuint vertex_shader = createShader(GL_VERTEX_SHADER, vertex_shader_code, "vertex shader");
	GLuint fragment_shader = createShader(GL_FRAGMENT_SHADER, fragment_shader_code, "fragment shader");

	int  isLinked = GL_FALSE;

	GLuint program = glCreateProgram();

	if (program == 0)
		std::cout << "Shader Loader : CREATE SHADER PROGRAM ERROR " << shaderName.c_str() << std::endl;

	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);

	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &isLinked);

	if (isLinked == GL_FALSE)
	{
		int info_log_length = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_log_length);

		std::vector<char> program_log(info_log_length);
		glGetProgramInfoLog(program, info_log_length, NULL, &program_log[0]);

		std::cout << "Shader Loader : LINK ERROR" << std::endl << &program_log[0] << std::endl;
		return;
	}

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	programs[shaderName] = program;
}

const GLuint managers::ShaderManager::getProgram(const std::string& shaderName)
{
	return programs.at(shaderName);
}
