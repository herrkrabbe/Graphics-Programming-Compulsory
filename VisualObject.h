#ifndef VISUALOBJECT_H
#define VISUALOBJECT_H

#include <QVulkanWindow>
#include <vector>
#include "Vertex.h"
#include "Utilities.h"

class VisualObject
{
public:
    VisualObject();
    VisualObject(std::string filePath);

    virtual void move(float x, float y = 0.0f, float z = 0.0f);
    virtual void scale(float s);
    virtual void rotate(float t, float x, float y, float z);
    virtual void Tick(float deltaTime);
    virtual bool isVisible() {return bDisplay;}
    virtual void ToggleVisible() {bDisplay = !bDisplay;}

	//Setters and Getters
    inline std::vector<Vertex> getVertices() { return mVertices; }
    inline VkBuffer& getVBuffer() { return mVertexBuffer.mBuffer; }
    inline VkDeviceMemory& getVBufferMemory() { return mVertexBuffer.mBufferMemory; }
	inline VkDeviceMemory& getIBufferMemory() { return mIndexBuffer.mBufferMemory; }
    inline void setVBuffer(VkBuffer bufferIn) { mVertexBuffer.mBuffer = bufferIn; }
    inline void setVBufferMemory(VkDeviceMemory bufferMemoryIn) { mVertexBuffer.mBufferMemory = bufferMemoryIn; }
    inline VkBuffer& getIBuffer() { return mIndexBuffer.mBuffer; }
    inline void setIBuffer(VkBuffer bufferIn) { mIndexBuffer.mBuffer = bufferIn; }
    inline void setIBufferMemory(VkDeviceMemory bufferMemoryIn) { mIndexBuffer.mBufferMemory = bufferMemoryIn; }
    inline void setName(std::string name) { mName = name; }
    inline std::string getName() const { return mName; }
    inline int getDrawType() const { return drawType; }
    inline QMatrix4x4 getMatrix() const {return mMatrix;}
	inline std::vector<Vertex> getVertices() const { return mVertices; }
	inline std::vector<uint32_t> getIndices() const { return mIndices; }
    inline std::string GetTexture() const {return texture;}

protected:
    std::vector<Vertex> mVertices;
    std::vector<uint32_t> mIndices;
    QMatrix4x4 mMatrix;
    std::string mName;
    bool bDisplay{1};
    std::string texture{""};

	BufferHandle mVertexBuffer;
	BufferHandle mIndexBuffer;
    //VkPrimitiveTopology mTopology{ VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST }; //not used

    int drawType{ 0 }; // 0 = fill, 1 = line
    bool moveToGround{1};

private:
    void ReadFile(std::string fileName);
    void ReadLine(std::string& line, unsigned int &temp_index, std::vector<QVector3D>& positions, std::vector<QVector3D>& normals, std::vector<QVector2D>& uvs);

    void HandlePositionFromLine(std::stringstream& strStream, std::string &word, std::vector<QVector3D>& positions);
    void HandleNormalFromLine(std::stringstream& strStream, std::string &word, std::vector<QVector3D>& normals);
    void HandleUVFromLine(std::stringstream& strStream, std::string &word, std::vector<QVector2D>& uvs);
    void HandleNameFromLine(std::stringstream& strStream, std::string &word);
    void HandleScaleFromLine(std::stringstream& strStream, std::string &word, std::vector<QVector3D>& positions, std::vector<QVector3D>& normals, std::vector<QVector2D>& uvs);
    void HandleTriangleFromLine(std::stringstream& strStream, unsigned int &temp_index, std::string &word, std::vector<QVector3D>& positions, std::vector<QVector3D>& normals, std::vector<QVector2D>& uvs);
};

#endif // VISUALOBJECT_H

