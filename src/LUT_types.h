#ifndef LUT_TYPES_H
#define LUT_TYPES_H

typedef enum LUT_Error_e
{
    LUT_ERROR_NO_ERROR,
    LUT_ERROR_NULLPOINTER_EXCEPTION,
    LUT_ERROR_AXIS_NOT_SPECIFIED,
    LUT_ERROR_DEVISION_BY_ZERO,
    LUT_ERROR_NOT_LOCKED,
}LUT_Error_t;

typedef enum LUT_Locking_Error_e
{
    LUT_LOCKING_ERROR_NO_ERROR,
    LUT_LOCKING_ERROR_DIMENSION_MISMATCH,
    LUT_LOCKING_ERROR_VECTOR_X_MISSING,
    LUT_LOCKING_ERROR_VECTOR_Y_MISSING,
}LUT_Locking_Error_t;

typedef enum LUT_Search_Return_e
{
    LUT_SEARCH_RETURN_MIN,
    LUT_SEARCH_RETURN_MAX,
    LUT_SEARCH_RETURN_HIT,
    LUT_SEARCH_RETURN_NO_HIT,
}LUT_Search_Return_t;

typedef enum LUT_Axis_e
{
    LUT_AXIS_X,
    LUT_AXIS_Y,
}LUT_Axis_t;

typedef uint8_t LUT_Element_t;
typedef LUT_Element_t LUT_Elements_t;

#endif /* LUT_TYPES_H */