#include "ServiceProvider.h"
#include "VisualObject.h"
#include <iostream>
#include <fstream>
#include <sstream>

VisualObject::VisualObject()
{
    mMatrix.setToIdentity();
}

VisualObject::VisualObject(std::string filePath)
{
    mMatrix.setToIdentity();
    ReadFile(filePath);
}

void VisualObject::move(float x, float y, float z)
{
    mMatrix.translate(x, y, z);
    if(!moveToGround) {
        return;
    }

    if(!ServiceProvider::HasGround()) {
        return;
    }

    float worldX = mMatrix.column(3).x();
    float worldY = mMatrix.column(3).y();
    float worldZ = mMatrix.column(3).z();
    Ground* ground = ServiceProvider::GetGround();

    float groundZ = ground->GetHeightFromWorldPos(worldX, worldY);
    float deltaZ = groundZ - worldZ;

    mMatrix.translate(0, 0, deltaZ);
    // mMatrix.translate(0, 0, groundZ);
}

void VisualObject::scale(float s)
{
    mMatrix.scale(s);
}

void VisualObject::rotate(float t, float x, float y, float z)
{
    mMatrix.rotate(t, x, y, z);
}

void VisualObject::Tick(float deltaTime)
{

}

void VisualObject::ReadFile(std::string fileName)
{
    std::string filePath;
    filePath = fileName;

    std::ifstream file;
    file.open(filePath, std::ifstream::in);

    if(!file) {
        qDebug() << "Failed to open file";
        return;
    }

    std::string line;
    std::vector<QVector3D> positions;
    std::vector<QVector3D> normals;
    std::vector<QVector2D> uvs;

    unsigned int temp_index = 0;

    while(std::getline(file, line)) {
        ReadLine(line, temp_index, positions, normals, uvs);
    }

    file.close();
}

void VisualObject::ReadLine(std::string &line, unsigned int &temp_index, std::vector<QVector3D> &positions, std::vector<QVector3D> &normals, std::vector<QVector2D> &uvs)
{
    std::stringstream strStream;
    std::string word;
    strStream << line;
    strStream >> word;


    if(word == "#") {
        //TODO
        return;
    }
    if(word == "") {
        //TODO
        return;
    }
    if(word == "v") {
        HandlePositionFromLine(strStream, word, positions);
        return;
    }
    if(word == "vn") {
        HandleNormalFromLine(strStream, word, normals);
        return;
    }
    if(word == "vt") {
        HandleUVFromLine(strStream, word, uvs);
        return;
    }
    if(word == "s") {
        HandleScaleFromLine(strStream, word, positions, normals, uvs);
        return;
    }
    if(word == "f") {
        HandleTriangleFromLine(strStream, temp_index, word, positions, normals, uvs);
        return;
    }
    if(word == "o") {
        HandleNameFromLine(strStream, word);
        return;
    }
}

void VisualObject::HandlePositionFromLine(std::stringstream &strStream, std::string &word, std::vector<QVector3D> &positions)
{
    QVector3D pos;

    strStream >> word;
    pos.setX(std::stof(word));
    strStream >> word;
    pos.setY(std::stof(word));
    strStream >> word;
    pos.setZ(std::stof(word));

    positions.push_back(pos);
}

void VisualObject::HandleNormalFromLine(std::stringstream &strStream, std::string &word, std::vector<QVector3D> &normals)
{
    QVector3D normal;

    strStream >> word;
    normal.setX(std::stof(word));
    strStream >> word;
    normal.setY(std::stof(word));
    strStream >> word;
    normal.setZ(std::stof(word));

    normals.push_back(normal);
}

void VisualObject::HandleUVFromLine(std::stringstream &strStream, std::string &word, std::vector<QVector2D> &uvs)
{
    QVector2D uv;

    strStream >> word;
    uv.setX(std::stof(word));
    strStream >> word;
    uv.setY(std::stof(word));

    uvs.push_back(uv);
}

void VisualObject::HandleNameFromLine(std::stringstream &strStream, std::string &word)
{
    strStream >> word;
    setName(word);
    return;
}

void VisualObject::HandleScaleFromLine(std::stringstream &strStream, std::string &word, std::vector<QVector3D> &positions, std::vector<QVector3D> &normals, std::vector<QVector2D> &uvs)
{
    strStream >> word;
    scale(std::stof(word));
}

void VisualObject::HandleTriangleFromLine(std::stringstream &strStream, unsigned int &temp_index, std::string &word, std::vector<QVector3D> &positions, std::vector<QVector3D> &normals, std::vector<QVector2D> &uvs)
{
    int index;
    int normal;
    int uv;

    for(int i = 0; i < 3; i++) {
        strStream >> word;                             //one word read
        std::stringstream tempWord(word);            //to use getline on this one word
        std::string segment;                            //the numbers in the f-line
        std::vector<std::string> segmentArray;          //temp array of the numbers
        while (std::getline(tempWord, segment, '/'))    //splitting word in segments at /
        {
            segmentArray.push_back(segment);
        }
        index = std::stoi(segmentArray[0]);             //first is vertex
        if (segmentArray[1] != "")                      //second is uv
            uv = std::stoi(segmentArray[1]);
        else
        {
            qDebug() << "No UVs in mesh!!!";            //uv not present
            uv = 0;                                     //this will become -1 in a couple of lines
        }
        normal = std::stoi(segmentArray[2]);            //third is normal

        //Fixing the indexes
        //because obj f-lines starts with 1, not 0
        --index;
        --uv;
        --normal;

        if (uv > -1)    //uv present!
        {
            Vertex tempVert{positions[index].x(), positions[index].y(), positions[index].z(), normals[normal].x(), normals[normal].y(), normals[normal].z(), uvs[uv].x(), uvs[uv].y()};
            mVertices.push_back(tempVert);
        }
        else            //no uv in mesh data, use 0, 0 as uv
        {
            Vertex tempVert{positions[index].x(), positions[index].y(), positions[index].z(), normals[normal].x(), normals[normal].y(), normals[normal].z(), 0.0f, 0.0f};
            mVertices.push_back(tempVert);
        }
        //We have now handeled one Vertex on the f-line - add it to indices
        mIndices.push_back(temp_index++);
    }
}

