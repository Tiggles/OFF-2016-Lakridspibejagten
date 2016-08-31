#ifndef SFML_LINESHAPE_HPP
#define SFML_LINESHAPE_HPP

#include <cmath>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

class sfLine : public sf::Drawable
{
private:
	sf::Vertex vertices[4];
	sf::Color color;
	float thickness;

public:
	sfLine(const sf::Vector2f& point1, const sf::Vector2f& point2):
		color(sf::Color::Yellow), thickness(5.f)
	{
		sf::Vector2f direction = point2 - point1;
		sf::Vector2f unitDirection =  direction / std::sqrt(direction.x * direction.x + direction.y * direction.y);
		sf::Vector2f unitPerpendicular(-unitDirection.y,unitDirection.x);

		sf::Vector2f offset = (thickness/2.f)*unitPerpendicular;

		vertices[0].position = point1 + offset;
		vertices[1].position = point2 + offset;
		vertices[2].position = point2 - offset;
		vertices[3].position = point1 - offset;

		for (int i=0; i<4; ++i)
				vertices[i].color = color;
	}

	void setColor(Color c) {
		color = c;
		for (int i=0; i<4; ++i)
			vertices[i].color = color;
	}

	void draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		// fjern advarsel om at states ikke bliver brugt
		while (false) states = states;

		target.draw(vertices, 4, sf::Quads);
	}


};

#endif // SFML_LINESHAPE_HPP