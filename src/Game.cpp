#include "Game.hh"

Game::Game() {
    initGameState();
}

Game::~Game() {
    //dtor
}

static float MOVE_TIME = .5; // 0.5 seconds

void Game::initGameState() {
    this->gameOver = false;
    this->paused = false;
    this->quit = false;
    this->score = 0;

    // set size play field
    this->nFieldWidth = 12;
    this->nFieldHeight = 22;

    // create play field
    this->pField = new unsigned char[this->nFieldWidth * this->nFieldHeight]; // Create play field buffer
    for (int x = 0; x < this->nFieldWidth; x++) { // Board Boundary
        for (int y = 0; y < this->nFieldHeight; y++) {
            // set to 0 unless it's on the sides or the bottom
            if (x == 0 || x == this->nFieldWidth - 1 || y == this->nFieldHeight - 1) {
                this->pField[y * this->nFieldWidth + x] = 9;
            } else {
                this->pField[y * this->nFieldWidth + x] = 0;
            }

        }
    }

    getNewPiece();
}

const string Game::getScore() {
    const string s = to_string(this->score);
    return s;
}

void Game::getNewPiece() {
    // init piece
    this->currentPieceNum = rand() % 7; // rand() % 7
    this->currentPiece = PieceFactory::Create(this->Tetromino[this->currentPieceNum]);
    std::cout << "currentPieceNum: " << std::endl;
    std::cout << this->currentPieceNum << std::endl;
}

bool Game::getPaused() const {
    return this->paused;
}

void Game::render(RenderWindow &window) {
    // draw frame
    if (!this->loaded) {
        this->texturePit.loadFromFile("images/pit.png");
        this->spritePit.setTexture(this->texturePit);
        this->spritePit.setPosition(17, 13);
        cout << "background loaded only once" << endl;
        this->loaded = true;
    }

    window.draw(this->spritePit);

    // draw current piece
    this->currentPiece->Draw(window);

    // draw blocked pieces in play field
    Texture texture;
    Sprite sprite;
    for (int x = 0; x < this->nFieldWidth; x++) { // Board Boundary
        for (int y = 0; y < this->nFieldHeight; y++) {
            switch (this->pField[y * this->nFieldWidth + x]) {
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                case 7: {
                    int tetroPlace = this->pField[y * this->nFieldWidth + x] - 1;
                    texture.loadFromFile("images/" + this->Tetromino[tetroPlace] + ".png");
                    sprite.setTexture(texture);
                    sprite.setPosition(x * sprite.getTexture()->getSize().x, y * sprite.getTexture()->getSize().y);
                    window.draw(sprite);
                    break;
                }
                case 8:
                    cout << 8 << "\n" << endl;
                    break;
                case 9:

                    break;
                default:
                    break;
            }
        }
    }

    // draw collision
    if (!this->vLines.empty()) {
        for (auto &v : vLines)
            for (int px = 1; px < this->nFieldWidth - 1; px++) {
                for (int py = v; py > 0; py--) {
                    this->pField[py * this->nFieldWidth + px] = this->pField[(py - 1) * this->nFieldWidth + px];
                }
                this->pField[px] = 0;
            }
        vLines.clear();
    }
}

bool Game::isRunning() const {
    return !this->gameOver;
}

void Game::handleEvent(Event &event) {
    switch (event.type) {
        case Event::Closed:
            this->gameOver = true;
            break;
        case Event::KeyPressed:
            //case Event::KeyReleased:
            handleKeyEvent(event);
        default:
            break;
    }
}

void Game::handleKeyEvent(Event &event) {
    switch (event.key.code) {
        case Keyboard::Escape: {
            this->gameOver = true;
            this->quit = true;
            break;
        }

        case Keyboard::Right: {
            const int currentPos = this->currentPiece->GetPosX() + 1;
            this->currentPiece->Update(this->currentPiece->GetRotation(), currentPos, this->currentPiece->GetPosY(),
                                       this->pField, this->nFieldWidth, this->nFieldHeight);
            break;
        }

        case Keyboard::Left: {
            const int currentPos = this->currentPiece->GetPosX() - 1;
            this->currentPiece->Update(this->currentPiece->GetRotation(), currentPos, this->currentPiece->GetPosY(),
                                       this->pField, this->nFieldWidth, this->nFieldHeight);
            break;
        }

        case Keyboard::Down: {
            const int currentPos = this->currentPiece->GetPosY() + 1;
            this->currentPiece->Update(this->currentPiece->GetRotation(), this->currentPiece->GetPosX(), currentPos,
                                       this->pField, this->nFieldWidth, this->nFieldHeight);
            break;
        }

        case Keyboard::Up: {
            if(this->paused)
            {
                this->gameOver=false;
                this->paused=false;
                this->initGameState();
            }

            const int currentPos = this->currentPiece->GetRotation() + 1;
            this->currentPiece->Update(currentPos, this->currentPiece->GetPosX(), this->currentPiece->GetPosY(),
                                       this->pField, this->nFieldWidth, this->nFieldHeight);
            break;
        }
        case Keyboard::Space: {
            std::cout << "space " << std::endl;
            this->paused = !this->paused;
            break;
        }

        default:
            break;
    }
}

void Game::update(const Time &delta) {
    static float secondsSinceLastPieceMove = 0;
    secondsSinceLastPieceMove += delta.asSeconds();

    if (secondsSinceLastPieceMove > MOVE_TIME) {
        secondsSinceLastPieceMove = 0;

        const int nRotation = this->currentPiece->GetRotation();
        const int nPosX = this->currentPiece->GetPosX();
        const int nPosY = this->currentPiece->GetPosY() + 1;

        if (this->currentPiece->DoesPieceFit(nRotation, nPosX, nPosY, this->pField, this->nFieldWidth,
                                             this->nFieldHeight)) {
            this->currentPiece->Update(nRotation, nPosX, nPosY, this->pField, this->nFieldWidth, this->nFieldHeight);

        } else {
            // Lock the piece in place
            lockPieceInPlace();

            // Check collision
            checkCollision();

            getNewPiece();

        }
    }
}

void Game::lockPieceInPlace() {

    for (int px = 0; px < 4; px++) {
        for (int py = 0; py < 4; py++) {


            if (this->currentPiece->GetShape()[this->currentPiece->Rotate(px, py, this->currentPiece->GetRotation())] !=
                '.') {
                this->pField[(this->currentPiece->GetPosY() + py) * this->nFieldWidth +
                             (this->currentPiece->GetPosX() + px)] = this->currentPieceNum + 1;
            }
        }
    }
}

void Game::checkCollision() {
    for (int py = 0; py < 4; py++) {
        if (this->currentPiece->GetPosY() == 0) {
            this->gameOver = true;
            break;
        }
        if (this->currentPiece->GetPosY() + py < this->nFieldHeight - 1) {

            bool bLine = true;
            for (int px = 1; px < this->nFieldWidth - 1; px++) {
                if (bLine) {
                    bLine = (this->pField[(this->currentPiece->GetPosY() + py) * this->nFieldWidth + px]) != 0;
                }
            }

            if (bLine) {
                // Remove Line by setting to 8
                for (int px = 1; px < this->nFieldWidth - 1; px++) {
                    this->pField[(this->currentPiece->GetPosY() + py) * this->nFieldWidth + px] = 8;
                }
                this->vLines.push_back(this->currentPiece->GetPosY() + py);
                this->score += 25;
            }
        }


    }
}

bool Game::getQuit() const {
    return this->quit;
}

void Game::popMenu(sf::RenderWindow &window, sf::Font &font) {
    if (this->paused) {
        sf::RectangleShape menu(sf::Vector2f(250, 300));
        menu.setPosition(35, 80);
        menu.setFillColor(sf::Color(227, 102, 119));
        menu.setOutlineThickness(10);
        menu.setOutlineColor(sf::Color(219, 136, 196));

        window.clear();
        window.draw(menu);

        Text Text;
        Text.setFont(font);
        Text.setCharacterSize(30);
        Text.setStyle(Text::Bold);
        Text.setFillColor(Color::White);
        Text.setPosition(60, 110);
        string s = "score: " + this->getScore();
        Text.setString(s);
        window.draw(Text);
        
        if (!this->gameOver)
        {
            Text.setCharacterSize(20);
            Text.setFillColor(Color::White);
            Text.setPosition(60, 170);
            Text.setString("press space to \nunpause");
            window.draw(Text);
        }

        Text.setCharacterSize(20);
        Text.setFillColor(Color::White);
        Text.setPosition(60, 260);
        Text.setString("press escape to quit");
        window.draw(Text);

        Text.setCharacterSize(20);
        Text.setFillColor(Color::White);
        Text.setPosition(60, 300);
        Text.setString("press Up for a\n new game");
        window.draw(Text);


        window.display();
    }
    return;
}

void Game::setPaused(bool x) {
    this->paused = x;
}


