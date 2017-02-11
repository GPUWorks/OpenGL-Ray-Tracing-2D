/*-----------------------------------------------------------------------------
Author: Bîrzu George
Email:	b.gxg7@yahoo.com
Date:	08-11-2015
-----------------------------------------------------------------------------*/

#pragma once

#include "Model.h"


namespace rendering
{
	namespace models
	{
		class Rectangle2 : public rendering::models::Model
		{
		public:
			Rectangle2();
			~Rectangle2();

			void create();
			virtual void draw()   override final;
			virtual void update() override final;

			virtual GLuint generateVBO()	override final;
			virtual GLuint generateIBO()	override final;
			virtual GLuint generateVAO()	override final;

			virtual void setModelMatrix() override final;

			virtual void bindShaderInputData() override final;
		};
	}
}
#pragma once
