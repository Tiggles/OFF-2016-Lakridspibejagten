#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <string>
#include "game_state.hpp"
#include "assets.hpp"

class GameStateDescription : public GameState {
protected:
	sf::Text textLeft;
	sf::Sprite back;

public:
	GameStateDescription(Game *g) {
		game = g;

		textLeft.setString(L"Du skal til en stor børnefødselsdag, og de "+std::to_wstring(game->children)+L" børn mangler\nlakridspiber. Tilmed er der en, der fortjener en gave!\nEn lange rejse venter dig, så kom endelig afsted!\n\n[Tryk <Space> for at starte.]");
		textLeft.setPosition({10, 520});
		textLeft.setFont(assets::font_main);
		textLeft.setCharacterSize(13);

		back.setTexture(assets::story_start);
		back.setScale({2.f, 2.f});
	}

	void draw(const float dt);
	void update(const float dt);
	void handleInput();
};
