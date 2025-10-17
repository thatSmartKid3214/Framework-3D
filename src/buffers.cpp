#include <gl_stuff/buffers.h>


VertexBuffer::VertexBuffer()
{
    glGenBuffers(1, &ID);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &ID);
}

void VertexBuffer::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VertexBuffer::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::addFloatData(float* data, int size, unsigned int drawMode)
{
    glBufferData(GL_ARRAY_BUFFER, size, data, drawMode);
}

void VertexBuffer::addIntData(int* data, int size, unsigned int drawMode)
{
    glBufferData(GL_ARRAY_BUFFER, size, data, drawMode);
}

void VertexBuffer::setAttribute(int index, int size, unsigned int dataType, int stride, void* offset)
{
    glVertexAttribPointer(index, size, dataType, GL_FALSE, stride, offset);
}

void VertexBuffer::enableAttribute(int index)
{
    glEnableVertexAttribArray(index);
}




//Index Buffer
IndexBuffer::IndexBuffer()
{
    glGenBuffers(1, &ID);
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &ID);
}

void IndexBuffer::bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void IndexBuffer::unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::addData(int* data, int size, unsigned int drawMode)
{
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, drawMode);
}


VertexArray::VertexArray()
{
    glGenVertexArrays(1, &ID);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &ID);
}

void VertexArray::bind()
{
    glBindVertexArray(ID);
}

void VertexArray::unbind()
{
    glBindVertexArray(0);
}