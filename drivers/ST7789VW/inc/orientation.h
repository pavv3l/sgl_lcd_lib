//
// Created by nte on 11/30/22.
//

#ifndef LCD_LIB_ORIENTATION_H
#define LCD_LIB_ORIENTATION_H

namespace sgl
{
namespace st8779vw
{
    enum class ScanDir
    {
        VERTICAL,
        VERTICAL_REVERSED,
        HORIZONTAL,
        HORIZONTAL_REVERSED,
        VERTICAL_MIRROR_X,
        VERTICAL_REVERSED_MIRROR_X,
        HORIZONTAL_X_MIRROR_Y,
        VERTICAL_MIRROR_X_Y,
        NONE
    };
}
}

/*
WZÓR:
		 ___
		|__
		|
		|

1:
 VERTICAL
		 ___
		|__
		|
		|

2:
 HORIZONTAL_REVERSED
		____
		  | |
		    |

3:
VERTICAL_REVERSED
		   |
         __|
		___|

4:
HORIZONTAL
		|
		|_|___

-------------------------------
 MIRRORS

5:
 VERTICAL_MIRROR_X
		___
		 __|
		   |
		   |
6:
VERTICAL_REVERSED_MIRROR_X
		|
		|__
		|___

7:
HORIZONTAL_X_MIRROR_y
		     |
		___|_|


8:
 VERTICAL_MIRROR_X_Y
		 _ ___
		| |
		|
 */

#endif //LCD_LIB_ORIENTATION_H
