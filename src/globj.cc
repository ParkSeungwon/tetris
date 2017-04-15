#include<fstream>
#include<GL/glew.h>
#include"globj.h"
using namespace std;

GLObject::GLObject(unsigned prog) 
{
	shader_program_ = prog;
}

void GLObject::mode(GLenum md) 
{
	mode_ = md;
}

unsigned GLObject::vertexes(const vector<Matrix<float>>& v, const char* n, unsigned vbo) 
{
	return transfer_data(v, n, vbo);
}

unsigned GLObject::colors(const vector<Matrix<float>>& v, const char* n, unsigned vbo) 
{
	return transfer_data(v, n, vbo);
}

GLObject::operator Matrix<float>()
{
	Matrix<float> m{4,4};
	m.E();
	for(auto& a : matrixes_) m *= a;
	return m;
}

unsigned GLObject::indices(const vector<unsigned>& v, unsigned vbo)
{
	if(!vbo) glGenBuffers(1, &vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned) * v.size(), 
			v.data(), GL_STATIC_DRAW);
	index_size_ = v.size();
	return vbo;
}

void GLObject::operator()()
{
	glDrawElements(mode_, index_size_, GL_UNSIGNED_INT, 0);
}

unsigned GLObject::read_obj_file(string file, const char* var_name)
{
	vector<Matrix<float>> ver;
	vector<unsigned> ind;
	string s;
	ifstream f(file);
	while(getline(f, s)) {
		stringstream ss;
		ss << s;
		ss >> s;
		if(s == "v") {
			float x,  y, z;
			ss >> x >> y >> z;
			ver.push_back(Matrix<float>{x,y,z});
		} else if(s == "f") {
			unsigned a, b; 
			char c;
			while(ss >> a >> c >> c >> b) ind.push_back(a-1);
		}
	}
	vertexes(ver, var_name);
	indices(ind);
	return ver.size();
}	

unsigned GLObject::transfer_data(const vector<Matrix<float>>& v, const char* var,
		unsigned vbo) 
{
	int sz = v.size();
	if(!vbo) glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	float ar[sz * 3];
	for(int i=0; i<sz; i++) memcpy(ar + 3*i, v[i].data(), 3 * sizeof(float));
	glBufferData(GL_ARRAY_BUFFER, sizeof(ar), ar, GL_STATIC_DRAW);

	unsigned loc = glGetAttribLocation(shader_program_, var);
	glEnableVertexAttribArray(loc);
	cout << var << " : " << loc << endl;
	glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	return vbo;
}
