#include "poly2tri_wrapper.hpp"

#define POINT_PRECISION i32
#include <poly2tri/poly2tri.hpp>

#define DATA_DEF tri
#define LIST_DEF OriTriangles
#define LIST_ALIAS triangles
#include "arraylist_interface.h"

#ifdef __cplusplus
extern "C" {
#endif

    OriTriangles poly2tri_solve(OriPolygon shape) {
        std::vector<p2t::Point> cppshape(
            (p2t::Point*) shape.data[0].data, 
            (p2t::Point*)(shape.data[0].data + shape.data[0].len));

        p2t::CDT* cdt = new p2t::CDT(cppshape);

        for (int i = 1; i < shape.len; ++i) {
            std::vector<p2t::Point> cpphole(
                (p2t::Point*) shape.data[i].data, 
                (p2t::Point*)(shape.data[i].data + shape.data[i].len));

            cdt->AddHole(cpphole);
        }
        
        cdt->Triangulate();
        std::vector<p2t::Triangle*> tris(cdt->GetTriangles());

        OriTriangles ori_tris = triangles_with_capacity(tris.size());

        for (p2t::Triangle* t : tris) {
            tri i;
            i.x = 0;
            i.y = 1;
            i.z = 2;
            triangles_push(&ori_tris, i);
        }

        return ori_tris;
    }

#ifdef __cplusplus  
}
#endif
