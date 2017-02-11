/*-----------------------------------------------------------------------------
Author: Bîrzu George
Email:	b.gxg7@yahoo.com
Date:	08-11-2015
-----------------------------------------------------------------------------*/

#pragma once

#include <vector>
#include <string>
#include "LineFormat.h"
#include "VertexFormat.h"


namespace managers
{
	class CollisionManager
	{
	public:
		static std::vector<rendering::formats::LineFormat*> scene_object_lines;
		static std::vector<std::string> scene_object_rays_names;
		static rendering::formats::LineFormat* incident_line;
		static bool is_light_directly_from_source;
		static bool is_camera_hit;

		static bool is_radius_drawing;

		static bool space_key_pressed;


		static long double getLightSourceRayAngle();
		static void getLightSourceStartCoordinates();
		static void addSceneLine(rendering::formats::VertexFormat* vertex1, rendering::formats::VertexFormat* vertex2);
		static void addCamera(rendering::formats::VertexFormat* vertex1, rendering::formats::VertexFormat* vertex2);
		static void checkForRadiusCollision();
		static void drawRay();

		static void reset();


	public:
		static int light_source_point;
		static bool light_source_point_changed;
		static int max_no_of_rays;
	};
}