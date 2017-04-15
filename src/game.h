#include"matrix.h"

class Block
{
public:
	Block();
	bool rotate(), left(), right(), down(), up();
	Matrix<char> block;

protected:
};

class Game
{
public:
	Game(int w, int h);
	Matrix<char> board;
	Block block;
	void left(), right(), down(), rotate();
	void remove_block(), put_block();
	int x, y;
	int width, height;
	bool overlap(int x, int y, const Block& block);
	void game_over();
	Matrix<unsigned> change();
	void clear_line();
};

