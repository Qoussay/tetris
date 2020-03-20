#include "PieceFactory.hh"

PieceFactory::PieceFactory()
{
    //ctor
}

PieceFactory::~PieceFactory()
{
    //dtor
}

const string PieceFactory::I = "ITetro";
const string PieceFactory::J = "JTetro";
const string PieceFactory::L = "LTetro";
const string PieceFactory::O = "OTetro";
const string PieceFactory::S = "STetro";
const string PieceFactory::T = "TTetro";
const string PieceFactory::Z = "ZTetro";

Piece *PieceFactory::Create(const std::string& str)
{
    if (str == PieceFactory::I) {
        return new ITetro;
    } else if(str == PieceFactory::J) {
        return new JTetro;
    } else if(str == PieceFactory::L) {
        return new LTetro;
    } else if(str == PieceFactory::O) {
        return new OTetro;
    } else if(str == PieceFactory::S) {
        return new STetro;
    } else if(str == PieceFactory::T) {
        return new TTetro;
    } else if(str == PieceFactory::Z) {
        return new ZTetro;
    }else {
        return nullptr;
    }
}
