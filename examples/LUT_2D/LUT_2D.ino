#include <LUT.h>

// Specification of your graph
// Rules for specifiyng your graph:
// - Specify only datapoints you really need
// - Specify each datapoint (on x-axis) once
// - Use max 255 datapoints
// - Limit your values between -2147483646 and 2147483647

/*
 * LUT_EXAMPLE
 * 
 *  y  ^
 *     |
 * 100 +-----------------------------------#---#
 *     |                                  /|   |
 *     +                                 / |   |
 *     |                                /  |   |
 *  80 +-------------------------------#   |   |
 *     |                             / |   |   |
 *     +                           /   |   |   |
 *     |                         /     |   |   |
 *     +                       /       |   |   |
 *     |                     /         |   |   |
 *     +                   /           |   |   |
 *     |                 /             |   |   |
 *     +               /               |   |   |
 *     |             /                 |   |   |
 *     +           /                   |   |   |
 *     |         /                     |   |   |
 *  20 +-------#                       |   |   |
 *     |      /|                       |   |   |
 *     +     / |                       |   |   |
 *     |    /  |                       |   |   |
 *   0 #---#---+---+---+---+---+---+---+---+---+-->
 *     0  10  20                      80  90 100  x
 */

#define LUT_EXAMPLE_ELEMENTS_X (LUT_Elements_t)6u
#define LUT_EXAMPLE_ELEMENTS_Y (LUT_Elements_t)6u

int32_t LUT_EXAMPLE_VECTOR_X[LUT_EXAMPLE_ELEMENTS_X] {0, 10, 20, 80,  90, 100};
int32_t LUT_EXAMPLE_VECTOR_Y[LUT_EXAMPLE_ELEMENTS_Y] {0,  0, 20, 80, 100, 100};

// Declaration and initialisation of your LUT
LUT LUT_EXAMPLE = LUT();

void setup()
{
    LUT_Error_t retLUT; // Return value of each LUT function
    int32_t outDataY; // Calculated y value

    Serial.begin(74880u);
    Serial.println();

    // Fill LUT with vectors
    while (false == LUT_EXAMPLE.Locked())
    {
        // Fill LUT with x data
        (void)LUT_EXAMPLE.setVector(LUT_AXIS_X, LUT_EXAMPLE_ELEMENTS_X, LUT_EXAMPLE_VECTOR_X);
        
        // Fill LUT with y data
        (void)LUT_EXAMPLE.setVector(LUT_AXIS_Y, LUT_EXAMPLE_ELEMENTS_Y, LUT_EXAMPLE_VECTOR_Y);
        
        // Lock LUT, to allow calculations and check if all preconditions are fulfilled.
        // The return value of of the Lock() function gives you hints why the locking fails
        (void)LUT_EXAMPLE.Lock();
    }

    // Iterate trough x axis beginning from -10 to 110
    for (int8_t i = -10; i <= 110; i++)
    {
        // Calculate each y point
        retLUT = LUT_EXAMPLE.calcData(i, &outDataY);

        // Check for any error
        if (LUT_ERROR_NO_ERROR == retLUT)
        {
            // Print x and corresponding y value
            Serial.print("X: "); Serial.print(i); Serial.print(", Y: "); Serial.println(outDataY);
        }
        else
        {
            // Print error
            Serial.println();
            Serial.print("LUT_Error: "); Serial.println(retLUT);
            break;
        }
    }
}

void loop()
{
    // Do nothing
}  
