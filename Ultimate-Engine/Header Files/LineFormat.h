/*-----------------------------------------------------------------------------
Author: Bîrzu George
Email:	b.gxg7@yahoo.com
Date:	08-11-2015
-----------------------------------------------------------------------------*/

#pragma once

#include <cmath>
#include <string>

#include "VertexFormat.h"

namespace rendering
{
	namespace formats
	{
		class LineFormat
		{
		public:
			LineFormat();
			LineFormat(rendering::formats::VertexFormat* vertex1, rendering::formats::VertexFormat* vertex2);
			~LineFormat();

			rendering::formats::VertexFormat* vertex1;
			rendering::formats::VertexFormat* vertex2;

			float slope;
			float y_intercept;
			std::string name;

			bool isLineContainingPoint(rendering::formats::VertexFormat vertex);
			bool isLineInteresectingLine(LineFormat line);

			float getLineIntersectionPoint_X(LineFormat line);
			float getLineIntersectionPoint_Y(LineFormat line);

			float getDistanceBetweenTwoPoints(rendering::formats::VertexFormat vertex1, rendering::formats::VertexFormat vertex2);
		
			rendering::formats::LineFormat* rendering::formats::LineFormat::getLineReflection(LineFormat incident_line,
				LineFormat surface_line, VertexFormat incident_surface_intersection_point);

			void computeLineReflection(LineFormat line);

			bool rendering::formats::LineFormat::isValidReflection(LineFormat incident_line, LineFormat surface_line,
				VertexFormat incident_surface_intersection_point, long double angle);

			void drawLineReflection(LineFormat incident_line, LineFormat surface_line, VertexFormat incident_surface_intersection_point, long double angle, glm::vec4 color);
		};
	}
}