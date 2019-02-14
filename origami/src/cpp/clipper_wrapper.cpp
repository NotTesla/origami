#include "clipper_wrapper.hpp"
#include "clipper.hpp"

#include <vector>

using namespace ClipperLib;

Clipper clipper;

#ifdef __cplusplus
extern "C" {
#endif
    
    void clipper_push_shape(
        enum CWPolyType polyType,
        Vertices shape) {

        Path cppshape((IntPoint*)shape.data, (IntPoint*)(shape.data + shape.len));
        clipper.AddPath(cppshape, (PolyType)polyType, true);
    }

    bool clipper_execute(
        enum CWClipType operation,
        struct arraylist_Vertices output) {
        
        auto solution = new PolyTree();
        
        bool b = clipper.Execute(
            (ClipType)operation, *solution, pftEvenOdd, pftEvenOdd);
        
        // clipper_unpack_tree(solution, output);
        return b;
    }

    // this works for now, but it will break when we implement mesh holes
    // void clipper_unpack_tree(PolyNode tree, struct arraylist_arrlist_vec output) {
    //     for (int i = 0; i < tree.ChildCount; ++i) {
    //         output.Add(tree.Childs[i].Contour);
    //         UnpackTree(tree.Childs[i], output);
    //     }
    // }

#ifdef __cplusplus  
}
#endif
