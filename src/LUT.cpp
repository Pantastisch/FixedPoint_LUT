#include "LUT.h"

LUT_Error_t LUT::calcData(int32_t inDataX, int32_t *outDataY)
{
    LUT_Error_t ret;
    LUT_Element_t searchedElement;
    LUT_Search_Return_t searchReturn = LUT_SEARCH_RETURN_NO_HIT;
    int32_t calculatedSlope = 0;

    if (NULL == outDataY)
    {
        ret = LUT_ERROR_NULLPOINTER_EXCEPTION;
    }
    else if (false == Locked())
    {
        ret = LUT_ERROR_NOT_LOCKED;
    }
    else
    {
        ret = searchElement(inDataX, &searchedElement, &searchReturn);

        if (LUT_ERROR_NO_ERROR == ret)
        {
            switch(searchReturn)
            {
                case LUT_SEARCH_RETURN_MIN:
                case LUT_SEARCH_RETURN_MAX:
                case LUT_SEARCH_RETURN_HIT:
                {
                    *outDataY = _VectorY[searchedElement];
                    break;
                }
                default:
                case LUT_SEARCH_RETURN_NO_HIT:
                {
                    ret = calcSlope(searchedElement, &calculatedSlope);

                    if (LUT_ERROR_NO_ERROR == ret)
                    {
                        *outDataY = _VectorY[searchedElement] + calculatedSlope * (inDataX - _VectorX[searchedElement]);
                    }

                    break;
                }
            }
        }
    }

    return ret;
}

LUT_Error_t LUT::calcSlope(LUT_Element_t inElement, int32_t *outSlope)
{
    LUT_Error_t ret = LUT_ERROR_NULLPOINTER_EXCEPTION;
    int32_t dx;
    int32_t dy;

    if (NULL != outSlope)    
    {
        dx = _VectorX[inElement+1u] - _VectorX[inElement];
        dy = _VectorY[inElement+1u] - _VectorY[inElement];

        if (0 == dx)
        {
            ret = LUT_ERROR_DEVISION_BY_ZERO;
        }
        else
        {
            *outSlope = dy / dx;

            ret = LUT_ERROR_NO_ERROR;
        }
    }

    return ret;
}

LUT_Error_t LUT::searchElement(int32_t inDataX, LUT_Element_t *outElement, LUT_Search_Return_t *outSearchReturn)
{
    LUT_Error_t ret = LUT_ERROR_NULLPOINTER_EXCEPTION;
    LUT_Element_t lastElement = _ElementsX-1u;

    if ((NULL != outElement) && (NULL != outSearchReturn))
    {
        if (inDataX <= _VectorX[0])
        {
            *outElement = 0u;
            *outSearchReturn = LUT_SEARCH_RETURN_MIN;
        }
        else if (inDataX >= _VectorX[lastElement])
        {
            *outElement = lastElement;
            *outSearchReturn = LUT_SEARCH_RETURN_MAX;
        }
        else
        {
            for(LUT_Element_t i = 0u; i <= lastElement; i++)
            {
                *outElement = i;

                if (inDataX == _VectorX[i])
                {
                    *outSearchReturn = LUT_SEARCH_RETURN_HIT;  
                    break;
                }
                else if ((inDataX > _VectorX[i]) && (inDataX < _VectorX[i+1u]))
                {
                    *outSearchReturn = LUT_SEARCH_RETURN_NO_HIT;  
                    break;
                }
            }
        }

        ret = LUT_ERROR_NO_ERROR;
    }
    
    return ret;
}

LUT_Locking_Error_t LUT::Lock()
{
    LUT_Locking_Error_t ret;

    if (NULL == _VectorX)
    {
        ret =  LUT_LOCKING_ERROR_VECTOR_X_MISSING;
    }
    else if (NULL == _VectorY)
    {
        ret =  LUT_LOCKING_ERROR_VECTOR_Y_MISSING;
    }
    else if (_ElementsX != _ElementsY)
    {
        ret =  LUT_LOCKING_ERROR_DIMENSION_MISMATCH;
    }
    else
    {
        _Locked = true;
        ret =  LUT_LOCKING_ERROR_NO_ERROR;
    }
    
    return ret;
}

bool LUT::Locked()
{
    return _Locked;
}


LUT_Error_t LUT::setVector(LUT_Axis_t inAxis, uint8_t inElements, int32_t *inVector)
{
    LUT_Error_t ret = LUT_ERROR_NULLPOINTER_EXCEPTION;

    if (NULL != inVector)
    {
        switch(inAxis)
        {
            case LUT_AXIS_X:
            {
                _VectorX = inVector;
                _ElementsX = inElements;
                ret = LUT_ERROR_NO_ERROR;
                break;
            }
            case LUT_AXIS_Y:
            {
                _VectorY = inVector;
                _ElementsY = inElements;
                ret = LUT_ERROR_NO_ERROR;
                break;
            }
            default:
            {
                ret = LUT_ERROR_AXIS_NOT_SPECIFIED;
                break;
            }
        }
    }

    return ret;
}
