#ifndef __CLIPPER_WRAPPER_HPP__
#define __CLIPPER_WRAPPER_HPP__

#include "basic_tuples.h"
#include "rusty_ints.h"
#include "origami.h"

enum CWPolyType { ptSubject, ptClip };
enum CWClipType { ctIntersection, ctUnion, ctDifference, ctXor };

#ifdef __cplusplus
extern "C" {
#endif

    void clipper_push_shape(enum CWPolyType polyType, OriVertices shape);

    bool clipper_execute(enum CWClipType operation, OriPolygon output);

#ifdef __cplusplus
}
#endif

#endif // __CLIPPER_WRAPPER_HPP__