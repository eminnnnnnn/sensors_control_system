#ifndef FONT_H
#define FONT_H

/*
** В этом модуле объявлены константные массивы байтов для отображения символов
** на LCD дисплее
*/

#include <stdint.h>

// Каждый символ - это массив байтов длиной 8 (8x8 бит или 8 колонок страницы LCD)

/*
** Пример: uint8_t sym[8]
**
**    0 1 2 3 4 5 6 7
** 0 +-+-+-+-+-+-+-+-+ LSB
** 1 +-+-+-+-+-+-+-+-+
** 2 +-+-+-+-+-+-+-+-+
** 3 +-+-+-+-+-+-+-+-+
** 4 +-+-+-+-+-+-+-+-+
** 5 +-+-+-+-+-+-+-+-+
** 6 +-+-+-+-+-+-+-+-+
** 7 +-+-+-+-+-+-+-+-+ MSB
**   +-+-+-+-+-+-+-+-+
**
**  Каждая колонка - это один байт (число массива), всего чисел - 8 (8 колонок)
*/
extern uint8_t dig_0[8];
extern uint8_t dig_1[8];
extern uint8_t dig_2[8];
extern uint8_t dig_3[8];
extern uint8_t dig_4[8];
extern uint8_t dig_5[8];
extern uint8_t dig_6[8];
extern uint8_t dig_7[8];
extern uint8_t dig_8[8];
extern uint8_t dig_9[8];

extern uint8_t lat_A[8];
extern uint8_t lat_B[8];
extern uint8_t lat_C[8];
extern uint8_t lat_D[8];
extern uint8_t lat_E[8];
extern uint8_t lat_F[8];
extern uint8_t lat_G[8];
extern uint8_t lat_H[8];
extern uint8_t lat_I[8];
extern uint8_t lat_J[8];
extern uint8_t lat_K[8];
extern uint8_t lat_L[8];
extern uint8_t lat_M[8];
extern uint8_t lat_N[8];
extern uint8_t lat_O[8];
extern uint8_t lat_P[8];
extern uint8_t lat_Q[8];
extern uint8_t lat_R[8];
extern uint8_t lat_S[8];
extern uint8_t lat_T[8];
extern uint8_t lat_U[8];
extern uint8_t lat_V[8];
extern uint8_t lat_W[8];
extern uint8_t lat_X[8];
extern uint8_t lat_Y[8];
extern uint8_t lat_Z[8];

extern uint8_t lat_a[8];
extern uint8_t lat_b[8];
extern uint8_t lat_c[8];
extern uint8_t lat_d[8];
extern uint8_t lat_e[8];
extern uint8_t lat_f[8];
extern uint8_t lat_g[8];
extern uint8_t lat_h[8];
extern uint8_t lat_i[8];
extern uint8_t lat_j[8];
extern uint8_t lat_k[8];
extern uint8_t lat_l[8];
extern uint8_t lat_m[8];
extern uint8_t lat_n[8];
extern uint8_t lat_o[8];
extern uint8_t lat_p[8];
extern uint8_t lat_q[8];
extern uint8_t lat_r[8];
extern uint8_t lat_s[8];
extern uint8_t lat_t[8];
extern uint8_t lat_u[8];
extern uint8_t lat_v[8];
extern uint8_t lat_w[8];
extern uint8_t lat_x[8];
extern uint8_t lat_y[8];
extern uint8_t lat_z[8];

/*
uint8_t cyr_A[8];
uint8_t cyr_B[8];
uint8_t cyr_V[8];
uint8_t cyr_G[8];
uint8_t cyr_D[8];
uint8_t cyr_E[8];
uint8_t cyr_JO[8];
uint8_t cyr_ZH[8];
uint8_t cyr_Z[8];
uint8_t cyr_I[8];
uint8_t cyr_JJ[8];
uint8_t cyr_K[8];
uint8_t cyr_L[8];
uint8_t cyr_M[8];
uint8_t cyr_N[8];
uint8_t cyr_O[8];
uint8_t cyr_P[8];
uint8_t cyr_R[8];
uint8_t cyr_S[8];
uint8_t cyr_T[8];
uint8_t cyr_U[8];
uint8_t cyr_F[8];
uint8_t cyr_KH[8];
uint8_t cyr_C[8];
uint8_t cyr_CH[8];
uint8_t cyr_SH[8];
uint8_t cyr_SHH[8];
uint8_t cyr_TZ[8];
uint8_t cyr_Y[8];
uint8_t cyr_MZ[8];
uint8_t cyr_EH[8];
uint8_t cyr_YU[8];
uint8_t cyr_YA[8];

uint8_t cyr_a[8];
uint8_t cyr_b[8];
uint8_t cyr_v[8];
uint8_t cyr_g[8];
uint8_t cyr_d[8];
uint8_t cyr_e[8];
uint8_t cyr_jo[8];
uint8_t cyr_zh[8];
uint8_t cyr_z[8];
uint8_t cyr_i[8];
uint8_t cyr_jj[8];
uint8_t cyr_k[8];
uint8_t cyr_l[8];
uint8_t cyr_m[8];
uint8_t cyr_n[8];
uint8_t cyr_o[8];
uint8_t cyr_p[8];
uint8_t cyr_r[8];
uint8_t cyr_s[8];
uint8_t cyr_t[8];
uint8_t cyr_u[8];
uint8_t cyr_f[8];
uint8_t cyr_kh[8];
uint8_t cyr_c[8];
uint8_t cyr_ch[8];
uint8_t cyr_sh[8];
uint8_t cyr_shh[8];
uint8_t cyr_tz[8];
uint8_t cyr_y[8];
uint8_t cyr_mz[8];
uint8_t cyr_eh[8];
uint8_t cyr_yu[8];
uint8_t cyr_ya[8];
*/

extern uint8_t sym_sp[8];          // пробел
extern uint8_t sym_pt[8];          // точка
extern uint8_t sym_degree_cels[8]; // oC
extern uint8_t sym_percent[8];     // %
extern uint8_t sym_arrow_right[8];
extern uint8_t sym_arrow_up[8];
extern uint8_t sym_arrow_down[8];
extern uint8_t sym_arrow_left[8];
extern uint8_t sym_exlam[8];
extern uint8_t sym_minus[8];
extern uint8_t sym_colon[8];

/*
uint8_t sym_lcm[8];
uint8_t sym_rcm[8];
*/

// extern uint8_t sym_cursor[8]; // "<-"
// uint8_t icon_mil[32];

#endif
