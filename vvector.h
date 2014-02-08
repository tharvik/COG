#include <math.h>

#define VEC_ZERO(v)		v[0] = 0; v[1] = 0; v[2] = 0;

#define VEC_LENGHT(v)		sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2])

#define VEC_NORMALIZE(v)	v[0] = v[0] / VEC_LENGHT(v); \
				v[1] = v[1] / VEC_LENGHT(v); \
				v[2] = v[2] / VEC_LENGHT(v);

#define VEC_COPY(r, v)		r[0] = v[0]; r[1] = v[1]; r[2] = v[2];

#define VEC_SCALE(r, m, v)	r[0] = v[0] * m; \
				r[1] = v[1] * m; \
				r[2] = v[2] * m;

#define VEC_SUM(r, v1, v2)	r[0] = v1[0] + v2[0]; \
				r[1] = v1[1] + v2[1]; \
				r[2] = v1[2] + v2[2];

#define VEC_DIFF(r, v1, v2)	r[0] = v1[0] - v2[0]; \
				r[1] = v1[1] - v2[1]; \
				r[2] = v1[2] - v2[2];
