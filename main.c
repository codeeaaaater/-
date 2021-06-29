#include <stdio.h>
static void PartDiffEquOfFstOrd_one(double *dst, double *src, double p0, double p1, int size)
{
	double first = src[0]*(1-p0)/p1;
//汇编内联
	asm volatile(
	"dup v0.2d, %[p0]\n"
	"dup v1.2d, %[p1]\n"
	"lsr %[cnt], %[cnt], #3\n"
	"mov x9, %[first]\n"

 	"1:"		
	"ld1 {v4.2d-v7.2d}, [%[src]], #64\n" 
	
	"mov v23.d[0], x9\n"
	"mov v23.d[1], v4.d[0]\n"
	"mov v24.d[0], v4.d[1]\n"
	"mov v24.d[1], v5.d[0]\n"
	"mov v25.d[0], v5.d[1]\n"
	"mov v25.d[1], v6.d[0]\n"
	"mov v26.d[0], v6.d[1]\n"
	"mov v26.d[1], v7.d[0]\n"
	"mov x9,v7.d[1]\n"	

	"fmul v4.2d, v4.2d, v0.2d\n"
	"fmul v5.2d, v5.2d, v0.2d\n"
	"fmul v6.2d, v6.2d, v0.2d\n"
	"fmul v7.2d, v7.2d, v0.2d\n"

	"fmul v23.2d, v23.2d, v1.2d\n"
	"fmul v24.2d, v24.2d, v1.2d\n"
	"fmul v25.2d, v25.2d, v1.2d\n"
	"fmul v26.2d, v26.2d, v1.2d\n"

	"fadd v4.2d, v4.2d, v23.2d\n"
	"fadd v5.2d, v5.2d, v24.2d\n"
	"fadd v6.2d, v6.2d, v25.2d\n"
	"fadd v7.2d, v7.2d, v26.2d\n"
	
	
	"st1 {v4.2d-v7.2d}, [%[dst]], #64\n"

	"sub %[cnt], %[cnt], #1\n"

	"cbnz %[cnt], 1b\n"

	:
	:[dst]"r"(dst), [src]"r"(src), [p0]"r"(p0), [p1]"r"(p1), [cnt]"r"(size), [first]"r"(first)
	:"memory"
	);
}
static void PartDiffEquOfFstOrd_two(double *dst, double *src, double p0, double p1, int size)
{
	double first = src[0]*(1-p0)/p1;
	asm volatile(
	"dup v0.2d, %[p0]\n"
	"dup v1.2d, %[p1]\n"
	"lsr %[cnt], %[cnt], #3\n"
	"mov x9, %[first]\n"
	"mov x10, x9\n"

 	"1:"		
	"ld1 {v4.2d-v7.2d}, [%[src]]\n" 
	
	
	"mov v23.d[0], x9\n"			//
	"mov v23.d[1], v4.d[0]\n"
	"mov v24.d[0], v4.d[1]\n"
	"mov v24.d[1], v5.d[0]\n"
	"mov v25.d[0], v5.d[1]\n"
	"mov v25.d[1], v6.d[0]\n"
	"mov v26.d[0], v6.d[1]\n"
	"mov v26.d[1], v7.d[0]\n"
	"mov x9,v7.d[1]\n"
	"fmul v4.2d, v4.2d, v0.2d\n"
	"fmul v5.2d, v5.2d, v0.2d\n"
	"fmul v6.2d, v6.2d, v0.2d\n"
	"fmul v7.2d, v7.2d, v0.2d\n"

	"fmul v23.2d, v23.2d, v1.2d\n"
	"fmul v24.2d, v24.2d, v1.2d\n"
	"fmul v25.2d, v25.2d, v1.2d\n"
	"fmul v26.2d, v26.2d, v1.2d\n"

	"fadd v4.2d, v4.2d, v23.2d\n"
	"fadd v5.2d, v5.2d, v24.2d\n"
	"fadd v6.2d, v6.2d, v25.2d\n"
	"fadd v7.2d, v7.2d, v26.2d\n"
						


/////////////////////
	"mov v23.d[0], x10\n"				//
	"mov v23.d[1], v4.d[0]\n"
	"mov v24.d[0], v4.d[1]\n"
	"mov v24.d[1], v5.d[0]\n"
	"mov v25.d[0], v5.d[1]\n"
	"mov v25.d[1], v6.d[0]\n"
	"mov v26.d[0], v6.d[1]\n"
	"mov v26.d[1], v7.d[0]\n"
	"mov x10,v7.d[1]\n"				//
	"fmul v4.2d, v4.2d, v0.2d\n"
	"fmul v5.2d, v5.2d, v0.2d\n"
	"fmul v6.2d, v6.2d, v0.2d\n"
	"fmul v7.2d, v7.2d, v0.2d\n"

	"fmul v23.2d, v23.2d, v1.2d\n"
	"fmul v24.2d, v24.2d, v1.2d\n"
	"fmul v25.2d, v25.2d, v1.2d\n"
	"fmul v26.2d, v26.2d, v1.2d\n"

	"fadd v4.2d, v4.2d, v23.2d\n"
	"fadd v5.2d, v5.2d, v24.2d\n"
	"fadd v6.2d, v6.2d, v25.2d\n"
	"fadd v7.2d, v7.2d, v26.2d\n"
	

	"st1 {v4.2d-v7.2d}, [%[dst]]\n"
//////////////////////

	"add %[src], %[src], #64\n"
	"add %[dst], %[dst], #64\n"
	"sub %[cnt], %[cnt], #1\n"

	"cbnz %[cnt], 1b\n"

	:
	:[dst]"r"(dst), [src]"r"(src), [p0]"r"(p0), [p1]"r"(p1), [cnt]"r"(size), [first]"r"(first)
	:"memory"
	);	
}
static void PartDiffEquOfFstOrd_oct(double *dst, double *src, double p0, double p1, int size)
{
	double temp[8];

	for(int i=0;i<8;i++) {
		temp[i] = src[0]*(1-p0)/p1;
	}

	asm volatile(
	"dup v0.2d, %[p0]\n"
	"dup v1.2d, %[p1]\n"
	"lsr %[cnt], %[cnt], #3\n"
"1:\t"
	"mov x10, %[temp]\n"
	"mov x11, #8\n"	 				//
	"ld1 {v4.2d-v7.2d}, [%[src]]\n" 
	
"2:\t"
	"ldr x9, [x10]\n"
	"mov v23.d[0], x9\n"			//
	"mov v23.d[1], v4.d[0]\n"
	"mov v24.d[0], v4.d[1]\n"
	"mov v24.d[1], v5.d[0]\n"
	"mov v25.d[0], v5.d[1]\n"
	"mov v25.d[1], v6.d[0]\n"
	"mov v26.d[0], v6.d[1]\n"
	"mov v26.d[1], v7.d[0]\n"
	"mov x9,v7.d[1]\n"

	"fmul v4.2d, v4.2d, v0.2d\n"
	"fmul v5.2d, v5.2d, v0.2d\n"
	"fmul v6.2d, v6.2d, v0.2d\n"
	"fmul v7.2d, v7.2d, v0.2d\n"

	"fmul v23.2d, v23.2d, v1.2d\n"
	"fmul v24.2d, v24.2d, v1.2d\n"
	"fmul v25.2d, v25.2d, v1.2d\n"
	"fmul v26.2d, v26.2d, v1.2d\n"

	"fadd v4.2d, v4.2d, v23.2d\n"
	"fadd v5.2d, v5.2d, v24.2d\n"
	"fadd v6.2d, v6.2d, v25.2d\n"
	"fadd v7.2d, v7.2d, v26.2d\n"
	//是否存在temp中
	"str x9, [x10], #8\n"	
	"sub x11, x11, #1\n"

	"cbnz x11, 2b\n"				

	"st1 {v4.2d-v7.2d}, [%[dst]]\n"

	"add %[src], %[src], #64\n"
	"add %[dst], %[dst], #64\n"
	"sub %[cnt], %[cnt], #1\n"

	"cbnz %[cnt], 1b\n"

	:
	:[dst]"r"(dst), [src]"r"(src), [p0]"r"(p0), [p1]"r"(p1), [cnt]"r"(size), [temp]"r"(temp)
	:"memory"
	);	
}


#define CNT 3
int main(int argc, char *argv[])
{
	double src[8*CNT],dst1[8*CNT],dst2[8*CNT],dst8[8*CNT];
	printf("src\n");
	for(int i=0;i<8*CNT;i++) {
		src[i]=0.2*(i%2+1);
		if(i%8==7)
			printf("%f\n", src[i]);
		else
			printf("%f\t", src[i]);
	}
	printf("\n");
	PartDiffEquOfFstOrd_one(dst1, src, 0.5, 3, 8*CNT);
	PartDiffEquOfFstOrd_two(dst2, src, 0.5, 3, 8*CNT);
	PartDiffEquOfFstOrd_oct(dst8, src, 0.5, 3, 8*CNT);
	printf("dst1\n");
	for(int i=0;i<8*CNT;i++)
		if(i%8==7)
			printf("%f\n", dst1[i]);
		else
			printf("%f\t", dst1[i]);
	printf("\n");
	printf("dst2\n");
	for(int i=0;i<8*CNT;i++)
		if(i%8==7)
			printf("%f\n", dst2[i]);
		else
			printf("%f\t", dst2[i]);
	printf("\n");
	printf("dst8\n");
	for(int i=0;i<8*CNT;i++)
		if(i%8==7)
			printf("%f\n", dst8[i]);
		else
			printf("%f\t", dst8[i]);
}
