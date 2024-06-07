#include <iostream>
#include <vector>
#include <GL/glut.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

// Estructura para almacenar datos del modelo
struct Mesh {
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;
};

std::vector<Mesh> meshes;

// Variable para controlar la rotación del objeto
GLfloat rotationAngle = 0.0;

// Función para cargar un modelo OBJ utilizando Assimp
void loadOBJ(const std::string& filePath) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "Error al cargar el modelo: " << importer.GetErrorString() << std::endl;
        return;
    }

    // Recorrer todos los nodos de la escena y extraer los datos del modelo
    for (unsigned int i = 0; i < scene->mNumMeshes; ++i) {
        Mesh mesh;
        const aiMesh* aiMesh = scene->mMeshes[i];

        for (unsigned int j = 0; j < aiMesh->mNumVertices; ++j) {
            mesh.vertices.push_back(aiMesh->mVertices[j].x);
            mesh.vertices.push_back(aiMesh->mVertices[j].y);
            mesh.vertices.push_back(aiMesh->mVertices[j].z);
        }

        for (unsigned int j = 0; j < aiMesh->mNumFaces; ++j) {
            const aiFace& face = aiMesh->mFaces[j];
            for (unsigned int k = 0; k < face.mNumIndices; ++k) {
                mesh.indices.push_back(face.mIndices[k]);
            }
        }

        meshes.push_back(mesh);
    }
}

// Función de inicialización de OpenGL
void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Cargar modelo OBJ
    loadOBJ("TreeColor.obj");
}

// Función de renderizado
void render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    // Rotar el objeto alrededor del eje Y
    glRotatef(rotationAngle, 0.0, 1.0, 0.0);

    // Renderizar cada malla del modelo
    for (const auto& mesh : meshes) {
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, mesh.vertices.data());

        glDrawElements(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_INT, mesh.indices.data());

        glDisableClientState(GL_VERTEX_ARRAY);
    }

    glutSwapBuffers();
}

void inicio3d(int argc, char** argv) {
    glutInit(&argc, argv);

   init();

    glutDisplayFunc(render);

    // Registrar funciones de manejo de eventos del ratón
    glutMotionFunc(nullptr);

    glutMainLoop();
    
}
