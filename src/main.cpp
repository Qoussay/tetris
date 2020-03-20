#include <iostream>
#include <string>
#include <thread>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include "Game.hh"

using namespace sf;
using namespace std;

int main() {

    RenderWindow window(VideoMode(320, 480), "Welcome to Tetris");
    Game game;
    Clock clock;
    Text Text;
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("src/Tetris.ogg"))
        return -1;
    sf::Sound sound;
    sound.setBuffer(buffer);
    sound.play();

    sf::Font MyFont;

    if (!MyFont.loadFromFile("ttf/OpenSans-Regular.ttf")) {
        cout << "Error loading font\n";
    }
    Text.setFont(MyFont);
    Text.setCharacterSize(30);
    Text.setStyle(Text::Bold);
    Text.setFillColor(Color::White);
    Text.setPosition(230, 100);


    while (!game.getQuit() && window.isOpen()) {

        
        while (game.isRunning() && window.isOpen() && !game.getQuit()) {

            Event event;


            while (window.pollEvent(event)) {

                if (event.type == Event::Closed) {
                    window.close();
                }
                game.handleEvent(event);

                while (game.getPaused() && game.isRunning() && !game.getQuit()) {

                    //draw rectangle for menu
                    game.popMenu(window, MyFont);
                    window.pollEvent(event);
                    if (event.type == Event::Closed) {
                        window.close();
                    }
                    game.handleEvent(event);

                }

            }
            game.update(clock.restart());

            window.clear(Color::Black);
            game.render(window);
            Text.setString(game.getScore());
            window.draw(Text);
            window.display();
        }
        
        game.setPaused(true);
        game.popMenu(window, MyFont);
        Event event;
        while (window.pollEvent(event)) {

                if (event.type == Event::Closed) {
                    window.close();
                }
                game.handleEvent(event);
        }

    }

    return 0;
}
