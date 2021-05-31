#include "Figures.h"


std::array<Vertex,4> CreateSquare(float x, float y, float size , float rotation)
{
	Vertex v1;
	v1.position = { x , y };
	v1.texCoord = { 0.0f , 0.0f };

	Vertex v2;
	v2.position = { x + size , y };
	v2.texCoord = { 1.0f , 0.0f };

	Vertex v3;
	v3.position = { x + size , y + size };
	v3.texCoord = { 1.0f , 1.0f };

	Vertex v4;
	v4.position = { x , y + size };
	v4.texCoord = { 0.0f , 1.0f };

	return { v1,v2,v3,v4 };
}

std::array<Vertex, 4> CreateRectangle(glm::vec3 position, glm::vec2 size, float rotation)
{

	Vertex v1;
	v1.position = { position.x , position.y };
	v1.texCoord = { 0.0f , 0.0f };

	Vertex v2;
	v2.position = { position.x + size.x , position.y };
	v2.texCoord = { 1.0f , 0.0f };

	Vertex v3;
	v3.position = { position.x + size.x , position.y + size.y };
	v3.texCoord = { 1.0f , 1.0f };

	Vertex v4;
	v4.position = { position.x , position.y + size.y };
	v4.texCoord = { 0.0f , 1.0f };
	
	return { v1,v2,v3,v4 };
}
