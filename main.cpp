#include <getopt.h>
#include <malloc.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include "test.h"

static void usage(void)
{
    printf("使用参数说明:./main -x 0.1 -t 0.1 -s 16\n"
           "-x\t空间步长\n"
           "-t\t时间步长\n"
           "-s\t空间点数\n"
           "-h\t帮助信息\n");
}
static const char short_options[] = "x:t:s:h";
static const struct option long_options[] = {
    {"dx", required_argument, NULL, 'x'},
    {"dt", required_argument, NULL, 't'},
    {"size", required_argument, NULL, 's'},
    {"help", no_argument, NULL, 'h'},
    {0, 0, 0, 0},
};

//循环读取参数
static void parameters_parser(int argc, char *argv[])
{

    if (argc < 2)
    {
        printf("[Error]: too few input parameters\n");
        usage();
        exit(-1);
    }

    for (;;)
    {
        int index, c;
        c = getopt_long(argc, argv, short_options, long_options, &index);
        if (-1 == c)
            break;

        switch (c)
        {
        case 'x':
            dx = atof(optarg);
            break;
        case 't':
            dt = atof(optarg);
            break;
        case 's':
            size = atoi(optarg);
            break;
        case 'h':
        default:
            usage();
            exit(-1);
        }
    }
}
//输入指定的算法并运行
static void run(struct algorithm_struct *pt, double *src)
{
    // destination
    double *dst = (double *)malloc((size + 3) * sizeof(double));
    double p0 = 1 - v * dt / dx;
    double p1 = p0 - 1;
    
    if (dst == NULL)
    {
        printf("[ERROR]: dst malloc error\n");
        exit(-1);
    }
//初始化0时刻的空间分布
    const double a = xmin - dx;
    const double interval = (xmax - xmin) / size;
    for (int i = 0; i < size; i++)
    {
        src[i] = interval * i + a;
    }

    // initialize
    for (int i = 0; i < size; i++)
    {
        // u0[i] = 0.2*(i%2+1);
        src[i] = exp(-200 * pow(src[i] - 0.25, 2));
    }


    gettimeofday(&(pt->start), NULL);
///////////内联汇编模板///////
    __asm__ __volatile__("" ::
                             : "memory");
    pt->test(src, dst, p0, p1, size);
    __asm__ __volatile__("" ::
                             : "memory");
    gettimeofday(&(pt->end), NULL);

    pt->sum.tv_usec += (pt->end.tv_sec - pt->start.tv_sec) * 1000000 + pt->end.tv_usec - pt->start.tv_usec;
    pt->cnt++;

    printf("output:\n");
    for (int i = 0; i < size; i++)
    {
        printf("%f\t", dst[i]);
    }
    printf("\n");

    for_each_test(pt)
        printf("%s:\t%ld(us)\n", pt->name, pt->sum.tv_usec);

    free(dst);
}

extern void __TEST1_sce_n(double *src, double *dst, double p0, double p1, int size);

int main(int argc, char *argv[])
{
    struct algorithm_struct *pt;
    double *src;
    parameters_parser(argc, argv);

    // source
    src = (double *)malloc(size * sizeof(double));
    if (src == NULL)
    {
        printf("[ERROR]: src malloc error\n");
        exit(-1);
    }
    srand((unsigned)time(NULL));

    for (int i = 0; i < COUNT; i++)
    {
        for_each_test(pt)
        {
            run(pt, src);
        }
    }

    for_each_test(pt)
        printf("%s:\t%ld(us)\n", pt->name, pt->sum.tv_usec);

    free(src);
    return 0;
}
//此算法对应test->.test
extern void __TEST1_sce_n(double *src, double *dst,
                   double p0, double p1,
                   int size)
{
    const int N = size;
    double t = 0;

    // 仅在src上操作
    for (int n = 1; n < nstep + 1; n++)
    {
        for (int i = N - 1; i >= 1; i--)
        {
            // FTCS1 – Forward time and Central space
            src[i] = p0 * src[i] - p1 * src[i - 1];
        }

        t += dt;
    }

    for (int i = 0; i < N; i++)
    {
        dst[i] = src[i];
    }
}