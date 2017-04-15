#pragma once
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<vector>
#include<valarray>
#include<type_traits>
#include"matrix.h"

void glortho(float r);
void glcolor(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
bool glinit(GLFWwindow* window);
void bindNdraw(unsigned color, unsigned vertex, GLenum mode, int first, int count, unsigned indices = 0);
std::valarray<Matrix<float>> polygon(int points_count=100, float r=1);
unsigned make_shader_program(const char* v_file,const char* f_file);
void replace(char* str, std::string anchor, const Matrix<float>& mat);
void transfer_matrix(unsigned shader_program, const Matrix<float>& m, const char* var_name);
void gl_bind_data(unsigned fv, unsigned fc, unsigned fe);

template <typename T>
unsigned int gl_transfer_data(T* begin, T* end, GLenum mode = GL_ARRAY_BUFFER)
{
	int sz = end - begin;
	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(mode, vbo);
	
	T ar[sz];
	memcpy(ar, begin, sizeof(ar));
	glBufferData(mode, sizeof(ar), ar, GL_STATIC_DRAW);
	return vbo;
}

template<typename T> unsigned gl_transfer_index(const T& v, unsigned vbo = 0)
{
	if(!vbo) glGenBuffers(1, &vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, v.size() * sizeof(unsigned), 
			v.data(), GL_STATIC_DRAW);
	return vbo;
}

static void mcopy(float* p, const Matrix<float>& m) {
	memcpy(p, m.data(), 3 * sizeof(float));
}
static void mcopy(float* p, float m) {
	*p = m;
}
template <typename T> unsigned gl_transfer_data(const T& v, unsigned vbo = 0)
{//v should offer operator[], if vbo is not 0, then transfer using it
	int dim = 1;
	int sz = v.size();
	if(!vbo) glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	if(std::is_class<typename T::value_type>::value) dim = 3;//if Matrix
	float ar[sz * dim];
	for(int i=0; i<sz; i++) mcopy(ar+i*dim, v[i]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(ar), ar, GL_STATIC_DRAW);
	return vbo;
}
/*
class GLObject
{
public:
	template<typename C, typename V> GLObject(C c, V v) {
		color_vbo = gl_transfer_data(c);
		vertex_vbo = gl_transfer_data(v);
	}

	


protected:
	unsigned color_vbo = 0, vertex_vbo = 0;
	std::deque<Matrix<float>> matrixes;
*/
