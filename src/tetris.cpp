#include<chrono>
#include<thread>
#include<iostream>
#include"glutil.h"
#include"tetris.h"
#include"game.h"
#include"globj.h"

using namespace std;
extern Matrix<float> KeyBindMatrix;
extern Game* PGAME;

int main()
{
	if (!glfwInit()) return -1;

	GLFWwindow* window = glfwCreateWindow(640, 1000, "Color Cube", NULL, NULL);
	if (!glinit(window)) return -1;

	Tetris tetris(15, 30);

	Game game{15,30};
	PGAME = &game;

	Matrix<float> m{4,4};
	///compile shaders
	unsigned shader_program = 
		make_shader_program("src/tetris.glsl", "src/fragment_shader.glsl");
	if(!shader_program) return 0;

	GLObject obj{shader_program};
	obj.vertexes(tetris.vertexes, "a_pos");
	obj.colors(tetris.colors, "a_color");
	unsigned fe = obj.indices(tetris.indices());
	obj.mode(GL_QUADS);

	extern int score;
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if(glfwGetTime() > 1.0 - float(score) / 100) {
			glfwSetTime(0);
			game.down();
		}
		glUseProgram(shader_program);
		auto tm = m.glscale(0.1,0.064,0.1) * KeyBindMatrix;
		transfer_matrix(shader_program, tm, "KeyBindMatrix");
		tetris.board = game.change();
		obj.indices(tetris.indices(), fe);
		obj();

		glfwSwapBuffers(window);
		glfwPollEvents();
		this_thread::sleep_for(chrono::milliseconds(50));
	}
	glfwTerminate();
}
