CXX 		= g++
CXXFLAGS 	= -Wall -pedantic -Wextra -std=c++1y

SRC 		= src/main.cpp \
               src/AbstractEntity.cpp \
               src/Game.cpp \
               src/Piece.cpp \
               src/PieceFactory.cpp \
               src/form/ITetro.cpp \
               src/form/JTetro.cpp \
               src/form/LTetro.cpp \
               src/form/OTetro.cpp \
               src/form/STetro.cpp \
               src/form/TTetro.cpp \
               src/form/ZTetro.cpp


all : tetris

main.o :
	$(CXX) -std=c++1y -c src/main.cpp

tetris : main.o
	$(CXX) $(CXXFLAGS) $(SRC) -o $@ -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

clean :
	$(RM) tetris
	$(RM) main.o