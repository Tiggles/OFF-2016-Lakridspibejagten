#include <SFML/Graphics.hpp>
#include <algorithm>
#include <string>
#include "assets.hpp"
#include <iostream>

using namespace sf;
using namespace std;

#include "end_state.hpp"

end_state::end_state(Game * g) : back_rect(0,0,400,300) {
	game = g;

	back.setScale({2.f,2.f});

	textTop.setFont(assets::font_main);
	textTop.setString(L"På rejsen har du samlet:");
	textTop.setPosition({30,100});
	textTop.setColor(sf::Color::Black);

	textBottom.setFont(assets::font_main);
	textBottom.setString("");
	textBottom.setPosition({30,400});
	textBottom.setColor(sf::Color::Black);
	textBottom.setCharacterSize(26);
}

void end_state::draw_summary(float const dt) {
	do_nothing(dt);

	game->window.draw(textTop);
	game->window.draw(textBottom);
}

void end_state::draw(float const dt) {
	sf::Color bluish(96, 185, 214);
	game->window.clear(bluish);

	if (show_texture) draw_texture(dt);
	else              draw_summary(dt);

}

bool end_state::has_won() {
	// Move icons and text to center
	game->icon_gave.setPosition({200,250});
	game->icon_gave.setScale({4.f,4.f});

	game->icon_pibe.setPosition({200,150});
	game->icon_pibe.setTexture(assets::pibe);
	game->icon_pibe.setScale({4.f,4.f});

	game->text_pibe.setPosition({450,200});
	game->text_pibe.setCharacterSize(50);

	std::wstring str = L"til " + std::to_string(game->children) + L" børn.";
	if (game->score_pibe >= game->children && game->score_gave) {
		// Won
		std::cerr << "won: piber = " << game->score_pibe << " / " << game->children << " = children" << std::endl;
		std::cerr << "won: gave?" << game->score_gave << std::endl;
		textBottom.setString(str + L"\nFedest, nu er alle glade!\n\n[Tryk en vilkårlig tast.]");
		return true;
	}
	// Lose 
	std::cerr << "lose: piber = " << game->score_pibe << " / " << game->children << " = children" << std::endl;
	std::cerr << "lose: gave?" << game->score_gave << std::endl;
	textBottom.setString(str + L"\nEj, det er ikke god stil!\n\n[Tryk en vilkårlig tast.]");
	return false;
}

void end_state::draw_texture(float const dt) {
	do_nothing(dt);
	
	game->window.draw(back);
	game->window.draw(textTop);
	if (state == 2) {
		time += dt;
		if (time > 0.2) {
			time = 0.0;
			frame = (frame+1) % 3;
			back_rect.left = frame * 400;
			back.setTextureRect(back_rect);
		}
	}
}

void end_state::update(float const dt) {
	do_nothing(dt);

	if (state == 0) {
		if (has_won()) {
			state = 1;
			back.setTexture(assets::story_win);
		} else {
			state = 2;
			back.setTexture(assets::story_lose);
		}
	}
}

void end_state::handleInput() {
	sf::Event event;
	while (game->window.pollEvent(event)) {
		switch(event.type ) {
			case Event::Closed:
				game->window.close();
				break;
			case Event::KeyPressed:
				if (show_texture) {
					game->window.close();
				} else {
					show_texture = true;
					game->icon_pibe.setPosition({-200,-200});
					game->icon_gave.setPosition({-200,-200});
					game->text_pibe.setPosition({-200,-200});

					Color grey(200,200,200);
					textTop.setCharacterSize(20);
					textTop.setColor(grey);
					if (state == 2) {
						textTop.setString(L"Tænk på alle de børn du har skuffet.");
						textTop.setPosition({50,200});
					} else if (state == 1) {
						textTop.setString(L"Dagen og børnefødselsdagen er reddet.\nSe engang hvor glade de er.");
						textTop.setPosition({40, 545});
					}
				}
			default:
				break;
		}
	};
}

