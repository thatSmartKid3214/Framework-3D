#ifndef BUFFERS_H
#define BUFFERS_H

#include <glad/glad.h>


class VertexBuffer
{
public:
    unsigned int ID;

    VertexBuffer();
    ~VertexBuffer();

    void bind();
    void unbind();

    void addFloatData(float* data, int size, unsigned int drawMode);
    void addIntData(int* data, int size, unsigned int drawMode);

    void setAttribute(int index, int size, unsigned int dataType, int stride, void* offset);
    void enableAttribute(int index);
};

class VertexArray
{
public:
    unsigned int ID;

    VertexArray();
    ~VertexArray();

    void bind();
    void unbind();
};

class IndexBuffer
{
public:
    unsigned int ID;

    IndexBuffer();
    ~IndexBuffer();

    void bind();
    void unbind();

    void addData(int* data, int size, unsigned int drawMode);
};




#endif