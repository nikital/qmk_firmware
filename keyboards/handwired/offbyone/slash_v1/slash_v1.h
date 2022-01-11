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
l01,  l02, l03, l04, l05,  l06,        r02, r05, r11,  r17, r23, r29, r35,   r41, r46, r52,\
\
 l07,  l08, l09, l10, l11, l12,        r03, r06, r12, r18, r24, r30, r36, r42,    r47, r53,\
l13,   l14, l15, l16, l17, l18,        r04, r07, r13, r19, r25, r31, r37, r43,    r48, r54,\
l19,   l20, l21, l22, l23, l24,        r08, r14, r20, r26, r32, r38,   r44,       r49, r55,\
l25,   l26, l27, l28, l29, l30,        r09, r15, r21, r27, r33,   r39,            r50,\
l31, l32, l33,        l34, l35,        r10, r16,   r22, r28, r34, r40,       r45, r51, r56\
) { \
    {r02, r05, r11, r17, r23, r29, r35, r41, r46, r52, r08, r14, r20, r26, r32, r38, r44,   r49, r55,   l01, l02, l03, l04, l05, l06, l31, l32, l33, KC_NO, l34, l35}, \
    {r03, r06, r12, r18, r24, r30, r36, r42, r47, r53, r09, r15, r21, r27, r33, r39, KC_NO, r50, KC_NO, l07, l08, l09, l10, l11, l12, l25, l26, l27, l28,   l29, l30}, \
    {r04, r07, r13, r19, r25, r31, r37, r43, r48, r54, r10, r16, r22, r28, r34, r40, r45,   r51, r56,   l13, l14, l15, l16, l17, l18, l19, l20, l21, l22,   l23, l24}, \
}
