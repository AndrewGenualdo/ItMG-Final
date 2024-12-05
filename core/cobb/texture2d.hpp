//
// Created by cobble on 9/25/2024.
//

#ifndef EWRENDER_TEXTURE2D_HPP
#define EWRENDER_TEXTURE2D_HPP

#include "iostream"
#include <string>
#include "../ew/external/glad.h"
#include "../ew/external/stb_image.h"
#include "shader.hpp"

using namespace std;

namespace cobb {
    static unsigned int VAO = -1, VBO = -1, EBO = -1;
    const unsigned int indices[] = {  // note that we start from 0!
            0, 1, 3,   // first triangle
            1, 2, 3    // second triangle
    };


    class Texture2d
    {
    private:
        unsigned int m_id;

        int m_width, m_height;
        int m_filterMode, m_wrapMode;
        const char *m_path;




    public:
        //unsigned int VBO, EBO;
        float vertices[36];
        Texture2d();
        Texture2d(const string &path);
        Texture2d(const string &path, float positions[8]);
        Texture2d(const string &path, int filterMode, int wrapMode, float positions[8]);
        ~Texture2d();
        void bind();
        void draw();

        void loadVertices(float positions[]);

        int getWidth() const;
        int getHeight() const;

        unsigned int getId() const;

        static unsigned int* getVAO();
        static unsigned int* getEBO();
        static unsigned int* getVBO();
        //static unsigned int* getVAO();

        void load();
    };
}



#endif //EWRENDER_TEXTURE2D_HPP
