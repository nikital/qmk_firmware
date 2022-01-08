// Copyright 2022 Nikita Leshenko (@nikital)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT( \
r02, r05, r11,  r17, r23, r29, r35,   r41, r46, r52,\
\
r03, r06, r12, r18, r24, r30, r36, r42,    r47, r53,\
r04, r07, r13, r19, r25, r31, r37, r43,    r48, r54,\
r08, r14, r20, r26, r32, r38,   r44,       r49, r55,\
r09, r15, r21, r27, r33,   r39,            r50,\
r10, r16,   r22, r28, r34, r40,       r45, r51, r56\
) { \
    {r02, r05, r11, r17, r23, r29, r35, r41, r46, r52, r08, r14, r20, r26, r32, r38, r44,   r49, r55}, \
    {r03, r06, r12, r18, r24, r30, r36, r42, r47, r53, r09, r15, r21, r27, r33, r39, KC_NO, r50, KC_NO}, \
    {r04, r07, r13, r19, r25, r31, r37, r43, r48, r54, r10, r16, r22, r28, r34, r40, r45,   r51, r56}, \
}
