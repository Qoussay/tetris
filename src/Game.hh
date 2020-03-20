#ifndef GAME_HH
#define GAME_HH

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Piece.hh"
#include "PieceFactory.hh"
#include "form/ITetro.hh"
#include "form/JTetro.hh"
#include "form/LTetro.hh"
#include "form/OTetro.hh"
#include "form/STetro.hh"
#include "form/TTetro.hh"
#include "form/ZTetro.hh"

using namespace sf;
using namespace std;

class Game {
private:
    Texture texturePit;
    Sprite spritePit;
    bool gameOver;
    bool quit;
    bool paused;
    bool loaded;
    Piece *currentPiece;
    const string Tetromino[7] = {"ITetro", "JTetro", "LTetro", "OTetro", "STetro", "TTetro", "ZTetro"};
    int currentPieceNum;
    int nFieldWidth;
    int nFieldHeight;
    unsigned char *pField = nullptr;
    vector<int> vLines;
    int score;
public:

    Game();

    void popMenu(sf::RenderWindow &window, Font &font);

    bool getPaused() const;

    bool getQuit() const;

    virtual ~Game();

    const string getScore();

    void handleEvent(Event &event);

    void render(RenderWindow &window);

    bool isRunning() const;

    void setPaused(bool x);

    void update(const Time &delta);

private:
    void initGameState();

    void handleKeyEvent(Event &event);

    void getNewPiece();

    void lockPieceInPlace();

    void checkCollision();
};

#endif // GAME_HH
