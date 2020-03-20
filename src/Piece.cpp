#include "Piece.hh"

Piece::Piece(string shape, string img)
{
    this->shape = shape;
    this->img = img;
    this->rotation = 0;
    this->posY = 0;
    this->posX = 5;
}

Piece::~Piece()
{
    //dtor
}

const string &Piece::GetShape() const
{
  return this->shape;
}

void Piece::SetShape(const string &shape)
{
  this->shape = shape;
}

const string &Piece::GetImg() const
{
  return this->img;
}

void Piece::SetImg(const string &img)
{
  this->img = img;
}

const int &Piece::GetRotation() const
{
  return this->rotation;
}

void Piece::SetRotation(const int &rotation)
{
  this->rotation = rotation;
}

const int &Piece::GetPosX() const
{
  return this->posX;
}

void Piece::SetPosX(const int &posX)
{
  this->posX = posX;
}

const int &Piece::GetPosY() const
{
  return this->posY;
}

void Piece::SetPosY(const int &posY)
{
  this->posY = posY;
}

void Piece::Update(const int &nRotation, const int &nPosX, const int &nPosY, unsigned char *pField, int nFieldWidth, int nFieldHeight)
{
    if (DoesPieceFit(nRotation, nPosX, nPosY, pField, nFieldWidth, nFieldHeight) == 1) {
        SetRotation(nRotation);
        SetPosX(nPosX);
        SetPosY(nPosY);
    }
}

void Piece::Draw(RenderWindow &window)
{
    static std::unordered_map<std::string, Texture> assoc;
    Sprite sprite;
    auto lookForTexture = assoc.find(this->img);
    if (lookForTexture == assoc.end()) {
        assoc.insert({this->img, Texture{}});
        assoc[this->img].loadFromFile("images/" + this->img);
    }
    sprite.setTexture(assoc[this->img]);

    // Texture texture;
    // texture.loadFromFile("images/" + this->img);


    for (int px = 0; px < 4; px++) {
        for (int py = 0; py < 4; py++) {
            int innerPos = this->Rotate(px, py, this->rotation);
            if (this->shape[innerPos] == 'X') {
                sprite.setPosition((px + this->posX) * sprite.getTexture()->getSize().x, (py + this->posY) * sprite.getTexture()->getSize().y);
                window.draw(sprite);
            }
        }
    }
}

int Piece::Rotate(int px, int py, int r)
{
	int pi = 0;
	switch (r % 4)
	{
	case 0: pi = py * 4 + px; // 0
        break;

	case 1: pi = 12 + py - (px * 4); // 90
		break;

	case 2: pi = 15 - (py * 4) - px; // 180
		break;

	case 3: pi = 3 - py + (px * 4); // 270
		break;
	}

	return pi;
}

bool Piece::DoesPieceFit(const int &nRotation, const int &nPosX, const int &nPosY, unsigned char *pField, int nFieldWidth, int nFieldHeight) {
    for (int px = 0; px < 4; px++)
    {
        for (int py = 0; py < 4; py++)
		{
			// Get index into piece
			int pi = this->Rotate(px, py, nRotation);

			// Get index into field
			int fi = (nPosY + py) * nFieldWidth + (nPosX + px);

			if (nPosX + px >= 0 && nPosX + px < nFieldWidth)
			{
				if (nPosY + py >= 0 && nPosY + py < nFieldHeight)
				{
					// Do collision check
					if (this->GetShape()[pi] != '.' && pField[fi] != 0)
                    {
                        return false; // fail on first hit
					}
				}
			}
		}
    }
	return true;
}
