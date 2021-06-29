
#ifndef __TEST_H_
#define __TEST_H_

struct algorithm_struct
{
	char name[128];
	void (*test)(double *src, double *dst, double p0, double p1, int size);
	int cnt;
	struct timeval start, end, sum;
};

extern void __TEST1_sce_n(double *src, double *dst, double p0, double p1, int size);

#define INDEX 8
struct algorithm_struct test[INDEX] = {
	{
		.name = {'_', '_', 'T', 'E', 'S', 'T', '1', '_', '\0'},
		.test = __TEST1_sce_n,
		.cnt = 0,
		.sum = {
			.tv_sec = 0,
			.tv_usec = 0,
		},
	},
	{
		.name = {'_', '_', 'T', 'E', 'S', 'T', '2', '_', '\0'},
		.test = __TEST1_sce_n,
		.cnt = 0,
		.sum = {
			.tv_sec = 0,
			.tv_usec = 0,
		},
	},
	// {
	// 	0,
	// 	0,
	// 	0,
	// 	0,
	// 	0,
	// },

};

#define for_each_test(pt) for (pt = test; pt->test != NULL; pt++)

const double xmin = 0;
const double xmax = 1;
const double nstep = 8;
double dx;
double dt;
int size;
double v = 1;

const int COUNT = 100;

#endif /*__TEST_H_*/
