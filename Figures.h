#pragma once
#include <glm/glm.hpp>
#include <array>

struct Vertex
{
	glm::vec2 position;
	glm::vec2 texCoord;
};



std::array<Vertex, 4> CreateSquare(float x, float y, float size , float rotation);
std::array<Vertex, 4> CreateRectangle(glm::vec3 position, glm::vec2 size, float rotation);
