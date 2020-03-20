#ifndef PIECEFACTORY_HH
#define PIECEFACTORY_HH

#include <string>

#include "form/ITetro.hh"
#include "form/JTetro.hh"
#include "form/LTetro.hh"
#include "form/OTetro.hh"
#include "form/STetro.hh"
#include "form/TTetro.hh"
#include "form/ZTetro.hh"

using namespace std;

class PieceFactory
{
    public:
        const static string I;
        const static string J;
        const static string L;
        const static string O;
        const static string S;
        const static string T;
        const static string Z;
    public:
        PieceFactory();
        virtual ~PieceFactory();

        static Piece *Create(const string& str);
};

#endif // PIECEFACTORY_HH
