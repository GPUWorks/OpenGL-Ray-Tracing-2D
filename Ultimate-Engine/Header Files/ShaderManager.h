/*-----------------------------------------------------------------------------
Author: Bîrzu George
Email:	b.gxg7@yahoo.com
Date:	08-11-2015
-----------------------------------------------------------------------------*/

#pragma once

#include <fstream>
#include <iostream>
#include <map>
#include <vector>

#include <glew\glew.h>
#include <freeglut\freeglut.h>


namespace managers
{
	class ShaderManager
	{
		public:
			ShaderManager(void);
			~ShaderManager(void);

			void createProgram(const std::string& shaderName,
				const std::string& vertexShaderFilename,
				const std::string& fragmentShaderFilename);

			const GLuint getProgram(const std::string& shaderName);

			std::string readShader(const std::string& filename);

			GLuint createShader(GLenum shaderType,
				const std::string& source,
				const std::string& shaderName);

	private:
			std::map<std::string, GLuint> programs;
	};
}
