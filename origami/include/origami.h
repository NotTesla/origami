#ifndef __ORIGAMI_H__
#define __ORIGAMI_H__

#include "rusty_ints.h"
#include "basic_tuples.h"

// Define Vertex type
typedef struct i32_2t vert;
#define TYPE vert
#include "arraylist_schema.h"
typedef struct arraylist_vert OriVertices;

// Define Polygon type
#define TYPE OriVertices
#include "arraylist_schema.h"
typedef struct arraylist_OriVertices OriPolygon;

// Define Triangle List
typedef struct u32_3t tri;
#define TYPE tri
#include "arraylist_schema.h"
typedef struct arraylist_tri OriTriangles;

#endif // __ORIGAMI_H__