#pragma once

#include <string>
#include <SFML/Graphics.hpp>

class VisibleGameObject {
public:
	VisibleGameObject();
	virtual ~VisibleGameObject();

	virtual void Load(std::string filename);
	virtual void Draw(sf::RenderWindow& window);
	virtual void Update(float elapsedTime);

	virtual void SetPosition(float x, float y);
	virtual sf::Vector2f GetPosition() const;
	virtual bool IsLoaded() const;

	virtual float GetWidth() const;
	virtual float GetHeight() const;
	virtual sf::FloatRect GetBoundingRect() const;

protected:
	sf::Sprite& GetSprite();

private:
	sf::Sprite _sprite;
	sf::Texture _texture;
	sf::String _filename;
	bool _isLoaded;
};