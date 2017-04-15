#include"matrix.h"

class Tetris
{
public:
	Tetris(int w, int h);
	std::vector<Matrix<float>> vertexes, colors;
	const std::vector<unsigned>& indices();//look at board->construct indices
	unsigned index_size();
	Matrix<unsigned> board;

protected:
	Matrix<Matrix<float>> m0, m1;//matrix ground floor, 1st floor
	Matrix<float> color[6] = {{1,0,0},{0,1,0},{0,0,1},{1,1,0},{1,0,1},{0,1,1}};
	int width, height;

private:
	std::vector<unsigned> indices_;
	std::array<unsigned, 24> get_cube_element(int x, int y, int c);
};

