#include <stdio.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <string.h>

#include "linalg.h"

/* MINCTEST - Minimal C Test Library - 0.2.0
*  ---------> MODIFIED FOR linalg <----------
* Copyright (c) 2014-2017 Lewis Van Winkle
*
* http://CodePlea.com
*
* This software is provided 'as-is', without any express or implied
* warranty. In no event will the authors be held liable for any damages
* arising from the use of this software.
*
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
*
* 1. The origin of this software must not be misrepresented; you must not
*    claim that you wrote the original software. If you use this software
*    in a product, an acknowledgement in the product documentation would be
*    appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
*    misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

#ifndef __MINCTEST_H__
#define __MINCTEST_H__
/*****************************TEST GLOBALS*****************************/
FILE * globalf;
/* NB all tests should be in one file. */
static int ltests = 0;
static int lfails = 0;

/* Display the test results. */
#define lresults() do {\
    if (lfails == 0) {\
        dupprintf(globalf,"ALL TESTS PASSED (%d/%d)\n", ltests, ltests);\
    } else {\
        dupprintf(globalf,"SOME TESTS FAILED (%d/%d)\n", ltests-lfails, ltests);\
    }\
} while (0)

/* Run a test. Name can be any string to print out, test is the function name to call. */
#define lrun(name, test) do {\
    const int ts = ltests;\
    const int fs = lfails;\
    const clock_t start = clock();\
    dupprintf(globalf,"\t%-14s", name);\
    test();\
    dupprintf(globalf,"pass:%2d   fail:%2d   %4dms\n",\
            (ltests-ts)-(lfails-fs), lfails-fs,\
            (int)((clock() - start) * 1000 / CLOCKS_PER_SEC));\
} while (0)

/* Assert a true statement. */
#define lok(test) do {\
    ++ltests;\
    if (!(test)) {\
        ++lfails;\
        dupprintf(globalf,"%s:%d error \n", __FILE__, __LINE__);\
    }} while (0)

#endif /*__MINCTEST_H__*/

void dupprintf(FILE * f, char const * fmt, ...) { // duplicate printf
    va_list ap;
    va_start(ap, fmt);
    vprintf(fmt, ap);
    va_end(ap);
    va_start(ap, fmt);
    vfprintf(f, fmt, ap);
    va_end(ap);
}


/*****************************TEST CONSTANTS***************************/
#define ITERATIONS 10000
#define ARRAY_LEN 100
size_t fps_iterations = 10;



/*******************************ACTUAL TESTS***************************/
void test_log2() {
    lok(log2(0.0) == -INFINITY);
    lok(log2(0.0) == -INFINITY);
    lok(log2(0) == -INFINITY);
    lok(log2(0) == -INFINITY);
    lok(log2(1.0) == 0.0);
    lok(log2(1.0) == 0);
    lok(log2(2.0) == 1.0);
    lok(log2(2.0) == 1);
}

#include "minctest.h"
#include "linalg.h"

enum {
    LINALG_ROW_LEN = 21,
    LINALG_COL_LEN = 25,
};

// void test_linalg() {
//     SDL_Log("test_linalg");
//     SDL_Log("Initting matrices");
//     int16_t * temp2D1 = calloc(LINALG_ROW_LEN * LINALG_COL_LEN, sizeof(int16_t));
//     int16_t * temp2D2 = calloc(LINALG_ROW_LEN * LINALG_COL_LEN, sizeof(int16_t));
//     int16_t * temp2D3 = calloc(LINALG_ROW_LEN * LINALG_COL_LEN, sizeof(int16_t));
//     int16_t * temp2D4 = calloc(LINALG_ROW_LEN * LINALG_COL_LEN, sizeof(int16_t));
//     for (uint8_t row = 0; row < LINALG_ROW_LEN; row++) {
//         for (uint8_t col = 0; col < LINALG_COL_LEN; col++) {
//             temp2D1[(row * LINALG_COL_LEN + col)] = 1;
//             temp2D2[(row * LINALG_COL_LEN + col)] = 2;
//             temp2D3[(row * LINALG_COL_LEN + col)] = 3;
//         }
//     }
//     int16_t * out = NULL;
//     // matrix_print_int16_t(temp2D1, LINALG_ROW_LEN, LINALG_COL_LEN);
//     // matrix_print_int16_t(temp2D2, LINALG_ROW_LEN, LINALG_COL_LEN);
//     // matrix_print_int16_t(temp2D3, LINALG_ROW_LEN, LINALG_COL_LEN);

//     SDL_Log("First tests");
//     out = matrix_plus_int16_t(temp2D3, temp2D2, LINALG_ROW_LEN, LINALG_COL_LEN, -1);

//     lok(matrix_equal_int16_t(out, temp2D1, LINALG_ROW_LEN, LINALG_COL_LEN));

//     SDL_Log("Setting up second matrix");
//     int16_t temp2D11[LINALG_COL_LEN * LINALG_ROW_LEN] = {
//         1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//         1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//         1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//         1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//         1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//         1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
//     };


//     for (uint8_t row = 0; row < LINALG_ROW_LEN; row++) {
//         for (uint8_t col = 0; col < LINALG_COL_LEN; col++) {
//             temp2D4[(row * LINALG_COL_LEN + col)] = temp2D11[(row * LINALG_COL_LEN + col)];
//         }
//     }

//     SDL_Log("More tests");
//     SDL_Log("Equal1");
//     lok(matrix_equal_int16_t(matrix_and_int16_t(temp2D1, temp2D1, LINALG_ROW_LEN, LINALG_COL_LEN), temp2D1, LINALG_ROW_LEN, LINALG_COL_LEN));
//     SDL_Log("Equal2");
//     lok(matrix_equal_int16_t(matrix_and_int16_t(temp2D1, temp2D2, LINALG_ROW_LEN, LINALG_COL_LEN), temp2D1, LINALG_ROW_LEN, LINALG_COL_LEN));
//     SDL_Log("Equal3");
//     lok(matrix_equal_int16_t(matrix_and_int16_t(temp2D2, temp2D2, LINALG_ROW_LEN, LINALG_COL_LEN), temp2D1, LINALG_ROW_LEN, LINALG_COL_LEN));
//     SDL_Log("Equal4");
//     lok(matrix_equal_int16_t(matrix_or_int16_t(temp2D2, temp2D2, LINALG_ROW_LEN, LINALG_COL_LEN), temp2D1, LINALG_ROW_LEN, LINALG_COL_LEN));
//     SDL_Log("Equal5");
//     lok(matrix_equal_int16_t(matrix_or_int16_t(temp2D11, temp2D11, LINALG_ROW_LEN, LINALG_COL_LEN), temp2D11, LINALG_ROW_LEN, LINALG_COL_LEN));
//     int16_t templist1[2 * 16] = {
//         0, 0,
//         0, 1,
//         0, 2,
//         0, 3,
//         0, 4,
//         0, 5,
//         1, 0,
//         1, 1,
//         1, 2,
//         1, 3,
//         2, 0,
//         2, 1,
//         2, 2,
//         3, 0,
//         3, 1,
//         4, 0
//     };
//     SDL_Log("list2mat");
//     int16_t * matrixed2d = list2matrix_int16_t(templist1, LINALG_ROW_LEN, LINALG_COL_LEN, 16);
//     // printf("\n");
//     // printf("\n");
//     // matrix_print_int16_t(matrixed2d, LINALG_ROW_LEN, LINALG_COL_LEN);
//     // matrix_print_int16_t(temp2D11, LINALG_ROW_LEN, LINALG_COL_LEN);
//     SDL_Log("equal6");
//     lok(matrix_equal_int16_t(matrixed2d, temp2D11, LINALG_ROW_LEN, LINALG_COL_LEN));
//     SDL_Log("mat2list");
//     int16_t * listeded2d = matrix2list_int16_t(temp2D11, LINALG_ROW_LEN, LINALG_COL_LEN);
//     SDL_Log("equal7");
//     lok(matrix_equal_int16_t(listeded2d, listeded2d, 2, 16));
//     lok(DARR_NUM(listeded2d) == 16 * 2);
// }



int main() {
    globalf = fopen("linalg_test_results.txt", "w+");
    dupprintf(globalf, "\nHello, World! I am testing linalg.\n");
    lrun("log2", test_log2);

    lresults();

    dupprintf(globalf, "linalg Test End \n \n");
    fclose(globalf);
    return (0);
}