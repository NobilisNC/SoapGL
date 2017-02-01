#ifndef MESH_H
#define MESH_H

#include "gl_core_3_3.hpp"
#include "Vertex.hpp"
#include "Texture.hpp"
#include "Material.hpp"
#include "Shader.hpp"
#include <iostream>

namespace soap {


class Mesh
{
private :
    GLuint _VAO, _VBO;
    VertexArray _vertices;
    Material* _material;

    void construct();
    void destroy();
public:
    Mesh();
    Mesh(const VertexArray& vertices);
    ~Mesh();

    inline void setMaterial(Material* material) noexcept {_material = material;}
    inline void setVertices(const VertexArray& vertices) {std::cerr << "test" << std::endl;_vertices = vertices; construct();}



    void draw(Shader& shader);


};

}

#endif // MESH_H
