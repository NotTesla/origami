#ifndef __POLY2TRI_WRAPPER_HPP__
#define __POLY2TRI_WRAPPER_HPP__

#include "origami.h"

#ifdef __cplusplus
extern "C" {
#endif

    OriTriangles poly2tri_solve(OriPolygon shape);

#ifdef __cplusplus
}
#endif

#endif // __CLIPPER_WRAPPER_HPP__