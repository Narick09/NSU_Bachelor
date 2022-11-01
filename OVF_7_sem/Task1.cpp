//#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

float e_float = 0.0;
float one_f = 1.0;

double e_double = 0.0;
double one_d = 1.0;

void check_double() {
	double a = 0.5;
	__int64 n = *((__int64*)&a);
	double b = *((double*)&(++n));

	printf("After %e : %e  dif  %e\n", a, b, (b - a)*2);
}

void check_float() {
	float a = 0.5;//0.5 dec is equal 0,1 bin
	__int32 n = *((__int32*)&a);
	float b = *((float*)&(++n));

	printf("After %e : %e  dif  %e\n", a, b, (b - a)*2);
}

void find_float_epsilon() {
	float num = 1;
	e_float = 0.5;
	int count = 0;
	while ((num + e_float/2) != 1.0) {
		count++;
		e_float /= 2;
	}
	printf("Epsilon %e, count_float: %d\n", e_float, count);
}

void find_double_epsilon() {
	double num = 1;
	e_double = 1.0;
	int count = 0;
	while ((num + e_double / 2) != 1.0) {
		count++;
		e_double /= 2;
	}
	printf("Epsilon %e, count_double: %d\n", e_double, count);
}

void compare_double() {
	double compare_array_d[5] = {one_d, one_d + e_double/2, one_d + e_double, one_d + e_double + e_double/2 , one_d + e_double*(double)(3/2)};
	printf("1, 1 + e/2, 1 + e, 1 + e + e/2, 1+ e*3/2 \n");
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (compare_array_d[i] > compare_array_d[j]) {
				printf(" > ");
			}
			else if (compare_array_d[i] < compare_array_d[j]) {
				printf(" < ");
			}
			else {
				printf(" = ");
			}
		}
		printf("\n");
	}
}

int main() {
	printf("float\n");
	check_float();
	find_float_epsilon();
	printf("double\n");
	check_double();
	find_double_epsilon();

	compare_double();
}
