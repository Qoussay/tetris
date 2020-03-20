#ifndef ABSTRACTENTITY_HH
#define ABSTRACTENTITY_HH

#include <SFML/Graphics.hpp>
#include <string>

using namespace std;
using namespace sf;

class AbstractEntity
{
    public:
        virtual void Draw(RenderWindow &window);
        virtual void Update(const int &nRotation, const int &nPosX, const int &nPosY, unsigned char *pField, int nFieldWidth, int nFieldHeight);

    protected:
        AbstractEntity();
        virtual ~AbstractEntity();
};

#endif // ABSTRACTENTITY_HH
