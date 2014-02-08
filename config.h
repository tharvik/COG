#pragma once

// Window
#define WINDOW_X      MIDDLE_SCREEN_X
#define WINDOW_Y      MIDDLE_SCREEN_Y

#define WINDOW_WIDTH              800
#define WINDOW_HEIGHT             450

#define WINDOW_TITLE            "COG"

#define GAME_MODE               false
#define FULLSCREEN              false

// Perspective
#define FOV       70.00
#define NEAREST    0.10
#define FAREST  1000.00

// Simulation
#define MINIMUM_PPS 25
#define MAXIMUM_PPS 60 // Not implemented
#define REPORT_PPS  50

#define MINIMUM_FPS 25 // Not implemented
#define MAXIMUM_FPS 40 // Not implemented
#define REPORT_FPS  50

#define BACKGROUND_COLOR 0.16, 0.16, 0.16, 1

// Keyboard
#define LAYOUT            QWERTZ
#define KEY_REPEAT_PERIOD 40

// Camera
#define INITIAL_POSITION_X -5
#define INITIAL_POSITION_Y  0
#define INITIAL_POSITION_Z  1

#define INITIAL_ORIENTATION_X 1
#define INITIAL_ORIENTATION_Y 0
#define INITIAL_ORIENTATION_Z 0

#define DISTANCE_PER_MOVE     0.30
#define DISTANCE_PER_PHYSIC   DIS_M
#define DISTANCE_BOOST_FACTOR 4.00

#define ANGLE_PER_ROTATION 0.08
#define ANGLE_PER_PHYSIC   ANG_R
#define ANGLE_BOOST_FACTOR 2.00


/* ################################ PRESETS ################################ */

#define MIDDLE_SCREEN_X (glutGet(GLUT_SCREEN_WIDTH)-WIN_W)/2
#define MIDDLE_SCREEN_Y (glutGet(GLUT_SCREEN_HEIGHT)-WIN_H)/2

#define AZERTY 0
#define QWERTY 1
#define QWERTZ 2


/* ############################### SHORTCUTS ############################### */

#define WIN_X WINDOW_X
#define WIN_Y WINDOW_Y
#define WIN_W WINDOW_WIDTH
#define WIN_H WINDOW_HEIGHT
#define WIN_T WINDOW_TITLE

#define MIN_P MINIMUM_PPS
#define MAX_P MAXIMUM_PPS
#define REP_P REPORT_PPS
#define MIN_F MINIMUM_FPS
#define MAX_F MAXIMUM_FPS
#define REP_F REPORT_FPS
#define BGR_C BACKGROUND_COLOR

#define POS_X INITIAL_POSITION_X
#define POS_Y INITIAL_POSITION_Y
#define POS_Z INITIAL_POSITION_Z
#define ORI_X INITIAL_ORIENTATION_X
#define ORI_Y INITIAL_ORIENTATION_Y
#define ORI_Z INITIAL_ORIENTATION_Z
#define ANG_P ANGLE_PER_PHYSIC
#define ANG_R ANGLE_PER_ROTATION
#define ANG_B ANGLE_BOOST_FACTOR
#define DIS_P DISTANCE_PER_PHYSIC
#define DIS_M DISTANCE_PER_MOVE
#define DIS_B DISTANCE_BOOST_FACTOR

#define PHY_REF_R PHYSIQUE_AND_REFRESH_RATIO


/* ################################ LAYOUTS ################################ */

#if LAYOUT == AZERTY
#       define KEY_a 'q'
#       define KEY_b 'b'
#       define KEY_c 'c'
#       define KEY_d 'd'
#       define KEY_e 'e'
#       define KEY_f 'f'
#       define KEY_g 'g'
#       define KEY_h 'h'
#       define KEY_i 'i'
#       define KEY_j 'j'
#       define KEY_k 'k'
#       define KEY_l 'l'
#       define KEY_m ','
#       define KEY_n 'n'
#       define KEY_o 'o'
#       define KEY_p 'p'
#       define KEY_q 'a'
#       define KEY_r 'r'
#       define KEY_s 's'
#       define KEY_t 't'
#       define KEY_u 'u'
#       define KEY_v 'v'
#       define KEY_w 'z'
#       define KEY_x 'x'
#       define KEY_y 'y'
#       define KEY_z 'w'

#       define KEY_A 'Q'
#       define KEY_B 'B'
#       define KEY_C 'C'
#       define KEY_D 'D'
#       define KEY_E 'E'
#       define KEY_F 'F'
#       define KEY_G 'G'
#       define KEY_H 'H'
#       define KEY_I 'I'
#       define KEY_J 'J'
#       define KEY_K 'K'
#       define KEY_L 'L'
#       define KEY_M '?'
#       define KEY_N 'N'
#       define KEY_O 'M'
#       define KEY_P 'P'
#       define KEY_Q 'A'
#       define KEY_R 'R'
#       define KEY_S 'S'
#       define KEY_T 'T'
#       define KEY_U 'U'
#       define KEY_V 'V'
#       define KEY_W 'Z'
#       define KEY_X 'X'
#       define KEY_Y 'Y'
#       define KEY_Z 'W'
#endif

#if LAYOUT == QWERTY
#       define KEY_a 'a'
#       define KEY_b 'b'
#       define KEY_c 'c'
#       define KEY_d 'd'
#       define KEY_e 'e'
#       define KEY_f 'f'
#       define KEY_g 'g'
#       define KEY_h 'h'
#       define KEY_i 'i'
#       define KEY_j 'j'
#       define KEY_k 'k'
#       define KEY_l 'l'
#       define KEY_m 'm'
#       define KEY_n 'n'
#       define KEY_o 'o'
#       define KEY_p 'p'
#       define KEY_q 'q'
#       define KEY_r 'r'
#       define KEY_s 's'
#       define KEY_t 't'
#       define KEY_u 'u'
#       define KEY_v 'v'
#       define KEY_w 'w'
#       define KEY_x 'x'
#       define KEY_y 'y'
#       define KEY_z 'z'

#       define KEY_A 'A'
#       define KEY_B 'B'
#       define KEY_C 'C'
#       define KEY_D 'D'
#       define KEY_E 'E'
#       define KEY_F 'F'
#       define KEY_G 'G'
#       define KEY_H 'H'
#       define KEY_I 'I'
#       define KEY_J 'J'
#       define KEY_K 'K'
#       define KEY_L 'L'
#       define KEY_M 'M'
#       define KEY_N 'N'
#       define KEY_O 'O'
#       define KEY_P 'P'
#       define KEY_Q 'Q'
#       define KEY_R 'R'
#       define KEY_S 'S'
#       define KEY_T 'T'
#       define KEY_U 'U'
#       define KEY_V 'V'
#       define KEY_W 'W'
#       define KEY_X 'X'
#       define KEY_Y 'Y'
#       define KEY_Z 'Z'
#endif

#if LAYOUT == QWERTZ
#       define KEY_a 'a'
#       define KEY_b 'b'
#       define KEY_c 'c'
#       define KEY_d 'd'
#       define KEY_e 'e'
#       define KEY_f 'f'
#       define KEY_g 'g'
#       define KEY_h 'h'
#       define KEY_i 'i'
#       define KEY_j 'j'
#       define KEY_k 'k'
#       define KEY_l 'l'
#       define KEY_m 'm'
#       define KEY_n 'n'
#       define KEY_o 'o'
#       define KEY_p 'p'
#       define KEY_q 'q'
#       define KEY_r 'r'
#       define KEY_s 's'
#       define KEY_t 't'
#       define KEY_u 'u'
#       define KEY_v 'v'
#       define KEY_w 'w'
#       define KEY_x 'x'
#       define KEY_y 'z'
#       define KEY_z 'y'

#       define KEY_A 'A'
#       define KEY_B 'B'
#       define KEY_C 'C'
#       define KEY_D 'D'
#       define KEY_E 'E'
#       define KEY_F 'F'
#       define KEY_G 'G'
#       define KEY_H 'H'
#       define KEY_I 'I'
#       define KEY_J 'J'
#       define KEY_K 'K'
#       define KEY_L 'L'
#       define KEY_M 'M'
#       define KEY_N 'N'
#       define KEY_O 'O'
#       define KEY_P 'P'
#       define KEY_Q 'Q'
#       define KEY_R 'R'
#       define KEY_S 'S'
#       define KEY_T 'T'
#       define KEY_U 'U'
#       define KEY_V 'V'
#       define KEY_W 'W'
#       define KEY_X 'X'
#       define KEY_Y 'Z'
#       define KEY_Z 'Y'
#endif