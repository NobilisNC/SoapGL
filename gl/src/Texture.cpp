#include "Texture.hpp"
using namespace soap;

Texture::Texture(std::string path, Type type) : _type(type){

    int width, height;
    unsigned char* image = SOIL_load_image(path.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);

    if(!image)
        std::cerr << "[TEXTURE] - Error loading : " << path << std::endl;

    gl::GenTextures(1, &_id);
    gl::BindTexture(gl::TEXTURE_2D, _id);

    gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_WRAP_S, gl::REPEAT);
    gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_WRAP_T, gl::REPEAT);

    gl::TexImage2D(gl::TEXTURE_2D, 0, gl::RGB, width, height, 0,gl::RGBA, gl::UNSIGNED_BYTE, image);
    gl::GenerateMipmap(gl::TEXTURE_2D);
    SOIL_free_image_data(image);
    gl::BindTexture(gl::TEXTURE_2D, 0);
}

void Texture::bind(GLuint unit) {
    gl::ActiveTexture(gl::TEXTURE0 + unit);
    gl::BindTexture(gl::TEXTURE_2D, _id);
}

void Texture::unbind() {
    gl::BindTexture(gl::TEXTURE_2D, 0);

}
