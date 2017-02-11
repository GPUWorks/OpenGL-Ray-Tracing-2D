/*-----------------------------------------------------------------------------
Author: Bîrzu George
Email:	b.gxg7@yahoo.com
Date:	08-11-2015
-----------------------------------------------------------------------------*/

#pragma once

#include <glm\glm.hpp>


namespace rendering
{
	namespace formats
	{
		class VertexFormat
		{
			public:
				glm::vec4 position;
				glm::vec4 color;

				VertexFormat();
				VertexFormat(const glm::vec4 &iPos);
				VertexFormat(const glm::vec4 &iPos, const glm::vec4 &iColor);

				void setPosition(glm::vec4 position);
				void setColor(glm::vec4 color);

				glm::vec4 getPosition();
				glm::vec4 getColor();

				float get_X();
				float get_Y();
		};
	}
}
