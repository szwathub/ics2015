#include "FLOAT.h"

FLOAT F_mul_F(FLOAT a, FLOAT b) {
    //nemu_assert(0);
    int sign1 = a >> 31;
    int sign2 = b >> 31;
    FLOAT result = (Fabs(a) * Fabs(b)) >> 16;
    if(sign1 != sign2) {
        result = -result;
    }
    return result;
}

FLOAT F_div_F(FLOAT a, FLOAT b) {
    int sign1 = a >> 31;
    int sign2 = b >> 31;
    int count = 16;
    FLOAT remain = Fabs(a) << 16;
    FLOAT divisor = Fabs(b) << 16;
    FLOAT result;

    while(remain != 0) {
        if (remain >= divisor && remain > 0) {
            remain = remain - divisor;
            result = result | (1 << count);
        }
        if (count == 0) {
            break;
        }
        divisor >>= 1;
        count --;
    }

    if(sign1 != sign2) {
        result = -result;
    }
    return result;
}

FLOAT f2F(float a) {
    int i, fa, sign, m, e, result;

    fa = *(int *)(&a);
    sign = fa >> 31;
    m = fa & ((1 << 23) - 1);                   //
    e = ((fa >> 23) & ((1 << 8) - 1)) - 127;   // 指数部分
    result = 1;

    for(i = 1; i < e + 16; i++) {
        result = (result << 1) + ((m & (1 << 22)) >> 22);
        if(result < 0) {
            return 0x80000000u;
        }
        m <<= 1;
    }
    if(sign == 1) {
        result = (~result) + 1;
    }

    return result;
}

FLOAT Fabs(FLOAT a) {
    //nemu_assert(0);
    return (a < 0) ? -a : a;;
}

FLOAT sqrt(FLOAT x) {
	FLOAT dt, t = int2F(2);

	do {
		dt = F_div_int((F_div_F(x, t) - t), 2);
		t += dt;
	} while(Fabs(dt) > f2F(1e-4));

	return t;
}

FLOAT pow(FLOAT x, FLOAT y) {
	/* we only compute x^0.333 */
	FLOAT t2, dt, t = int2F(2);

	do {
		t2 = F_mul_F(t, t);
		dt = (F_div_F(x, t2) - t) / 3;
		t += dt;
	} while(Fabs(dt) > f2F(1e-4));

	return t;
}
