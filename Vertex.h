// Dag Nylund, Universitetet i Innlandet
// Matematikk III 2025

#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>

struct  Vertex {
    float x;    //Position
    float y;
    float z;
	float r;	//Color
    float g;
    float b;
	float u;	//Texture coordinates (UV)
    float v;
    //! Overloaded ostream operator which writes all vertex data on an open textfile stream
    friend std::ostream& operator<< (std::ostream&, const Vertex&);

    //! Overloaded ostream operator which reads all vertex data from an open textfile stream
    friend std::istream& operator>> (std::istream&, Vertex&);
};

#endif // VERTEX_H
