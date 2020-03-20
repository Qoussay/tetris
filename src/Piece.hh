#ifndef PIECE_HH
#define PIECE_HH

#include "AbstractEntity.hh"
#include <iostream>
#include <string>
#include <unordered_map>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Piece: public AbstractEntity
{
    private:
        string shape;
        string img;
        int rotation;
        int posX;
        int posY;
    public:
        Piece(string shape, string img);
        virtual ~Piece();

        void Update(const int &nRotation, const int &nPosX, const int &nPosY, unsigned char *pField, int nFieldWidth, int nFieldHeight);
        void Draw(RenderWindow &window) override;

        const string &GetShape() const;
        void SetShape(const string &shape);

        const string &GetImg() const;
        void SetImg(const string &img);

        const int &GetRotation() const;
        void SetRotation(const int &rotation);

        const int &GetPosX() const;
        void SetPosX(const int &posX);

        const int &GetPosY() const;
        void SetPosY(const int &posY);

        static int Rotate(int px, int py, int r);
        bool DoesPieceFit(const int &nRotation, const int &nPosX, const int &nPosY, unsigned char *pField, int nFieldWidth, int nFieldHeight);
};

#endif // PIECE_HH
