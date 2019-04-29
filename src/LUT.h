#ifndef LUT_H
#define LUT_H

#include <stdint.h>
#include <stddef.h>

#include "LUT_types.h"

class LUT
{
    public:
        // Constructor
        LUT(){};

        LUT_Error_t calcData(int32_t inDataX,int32_t *outDataY);   
        LUT_Error_t setVector(LUT_Axis_t inAxis, LUT_Elements_t inElements, int32_t *inVector);     

        LUT_Locking_Error_t Lock();
        bool Locked();         

    private:
        int32_t *_VectorX = NULL;
        int32_t *_VectorY = NULL;

        LUT_Elements_t _ElementsX = 0u;
        LUT_Elements_t _ElementsY = 0u;

        bool _Locked = false;

        LUT_Error_t calcSlope(LUT_Element_t inElement, int32_t *outSlope);
        LUT_Error_t searchElement(int32_t inDataX, LUT_Element_t *outElement, LUT_Search_Return_t *outSearchReturn);              
};

#endif /* LUT_H */