/*-----------------------------------------------------------------------------
Author: Bîrzu George
Email:	b.gxg7@yahoo.com
Date:	08-11-2015
-----------------------------------------------------------------------------*/

#pragma once

#include <vector>

#include "IModel.h"
#include "CollisionManager.h"


namespace rendering
{
	namespace models
	{
		class Model : virtual public interfaces::IModel
		{
			public:
				Model();
				virtual ~Model();

				virtual void create()			override;
				virtual void draw()             override;
				virtual void update()           override;
				virtual void setProgram(GLuint shaderName) override final;
				virtual const GLuint getProgram() override final;
				virtual void destroy()          override final;

				virtual GLuint generateVBO() override = 0;
				virtual GLuint generateIBO() override = 0;
				virtual GLuint generateVAO() override = 0;

				virtual const GLuint getVao()               const override final;
				virtual const std::vector<GLuint> getIbos() const override final;
				virtual const std::vector<GLuint> getVbos() const override final;

				virtual void setModelMatrix() override = 0;

				virtual void bindShaderInputData() override = 0;

			protected:
				GLuint vao;
				std::vector<GLuint> ibos;
				GLuint program;
				std::vector<GLuint> vbos;
		};
	}
}
