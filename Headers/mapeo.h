#include<GLFW/glfw3.h>

//Coordenadas de Vertices
GLfloat suelo[] = {
	// COORDINATES            / COLORS             / TexCoord		/ NORMALS //

	//Cara Inferior
	-5.0f, 0.0f, -5.0f,	 0.0f, 0.70f, 0.44f,	 1.0f, 0.0f,	 0.0f, -1.0f, 0.0f,
	-5.0f, 0.0f, 5.0f,	 0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,	 0.0f, -1.0f, 0.0f,
	 5.0f, 0.0f, 5.0f,	 0.83f, 0.70f, 0.44f,	 0.0f, 1.0f,	 0.0f, -1.0f, 0.0f,
	 5.0f, 0.0f, -5.0f,  0.83f, 0.70f, 0.44f,	 1.0f, 1.0f,	 0.0f, -1.0f, 0.0f,
};

GLfloat lightVertices[] = {
	-0.1f, -0.1f,  0.1f,//0
	-0.1f, -0.1f, -0.1f,//1
	 0.1f, -0.1f, -0.1f,//2
	 0.1f, -0.1f,  0.1f,//3
	-0.1f,  0.1f,  0.1f,//4
	-0.1f,  0.1f, -0.1f,//5
	 0.1f,  0.1f, -0.1f,//6
	 0.1f,  0.1f,  0.1f//7
};

// Indices para obtener vertices
GLuint iSuelo[] = {
	0, 1, 2,
	0, 2, 3

};

GLuint lightIndices[] = {
	0, 1, 2,
	0, 2, 3,

	4, 5, 6,
	4, 6, 7,

	0, 1, 5,
	0, 5, 4,

	2, 3, 7,
	2, 7, 6,

	0, 3, 7,
	0, 6, 4,

	1, 2, 6,
	1, 6, 5
};
