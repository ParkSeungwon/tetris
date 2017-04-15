#include<vector>
#include<iostream>
#include"tetris.h"
using namespace std;

Tetris::Tetris(int w, int h) : m0{w+1, h+1}, m1{w+1, h+1}, board{w, h}
{
	width = w; height =h;
	for(int i=0; i<=w; i++) for(int j=0; j<=h; j++) 
		m0[i+1][j+1] = Matrix<float>{i, j, 0};
	for(int i=0; i<=w; i++) for(int j=0; j<=h; j++) 
		m1[i+1][j+1] = Matrix<float>{i, j, 1};
	for(int k=0; k<6; k++) for(int i=0; i<=w; i++) for(int j=0; j<=h; j++) {
		vertexes.push_back(m0[i+1][j+1]);
		vertexes.push_back(m1[i+1][j+1]);
	}
	for(int k=0; k<6; k++) for(int i=0; i<(w+1)*(h+1)*2; i++) 
		colors.push_back(color[k]);
	board = 6;
}

array<unsigned, 24> Tetris::get_cube_element(int x, int y, int c)
{
	unsigned offset = c * (width + 1) * (height + 1);//color offset
	offset += (height + 1) * x + y;//vertex offset
	offset *= 2;//there was z axis appending
	unsigned cube[8];
	for(int i=0; i<4; i++) cube[i] = offset + i;
	for(int i=4; i<8; i++) cube[i] = cube[i-4] + 2 * (height + 1);
	unsigned idx[24] = {0,1,3,2, 4,5,7,6, 0,1,5,4, 1,3,7,5, 3,2,6,7, 0,2,6,4};
	array<unsigned, 24> r;
	int k = 0;
	for(auto a : idx) r[k++] = cube[a];
	return r;
}

const vector<unsigned>& Tetris::indices() 
{
	indices_.clear();
	for(int j=0; j<height; j++) for(int i=0; i<width; i++) {
		if(board[i+1][j+1] != 6) {
			auto array = get_cube_element(i, j, board[i+1][j+1]);
			for(auto a : array) indices_.push_back(a);
		}
	}
	return indices_;
}
	
unsigned Tetris::index_size() 
{
	return indices_.size();
}

