/*-----------------------------------------------------------------------------
Author: Bîrzu George
Email:	b.gxg7@yahoo.com
Date:	08-11-2015
-----------------------------------------------------------------------------*/

#pragma once

#include "Model.h"
#include "CollisionManager.h"


namespace rendering
{
	namespace models
	{
		class RadiusDraw : public rendering::models::Model, managers::CollisionManager
		{
		public:
			RadiusDraw(rendering::formats::VertexFormat* vertex1, rendering::formats::VertexFormat* vertex2);
			~RadiusDraw();

			void create();
			virtual void draw()   override final;
			virtual void update() override final;

			virtual GLuint generateVBO()	override final;
			virtual GLuint generateIBO()	override final;
			virtual GLuint generateVAO()	override final;

			virtual void setModelMatrix() override final;

			virtual void bindShaderInputData() override final;

			rendering::formats::VertexFormat* vertex1;
			rendering::formats::VertexFormat* vertex2;

			long double rotate_Z;
			glm::vec3 translate;
			float length;
			float partial_length;
			bool is_draw_finished;

			static float draw_speed;
		};
	}
}
