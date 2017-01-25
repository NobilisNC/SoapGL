#pragma once


#include "gl_core_3_3.hpp"
#include <string>
#include <iostream>
#include "SOIL/SOIL.h"



class Texture {
public :
    enum Type {
        SPECULAR, DIFFUSE
    };

    private :
        GLuint _id;
        Type _type;

    public :
        Texture(std::string path, Type type = DIFFUSE);
        void bind(GLuint unit = 0);
        void unbind();

        inline Type getType() const {return _type;}



};
