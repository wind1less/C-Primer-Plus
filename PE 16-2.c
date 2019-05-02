// 极坐标用向量的模（即向量的长度）和向量相对x 轴逆时针旋转的角度来描述该向量。
// 直角坐标用向量的x 轴和y 轴的坐标来描述该向量。
// 编写一个程序，读取向量的模和角度（单位：度），然后显示x 轴和y 轴的坐标。
// 相关方程： x = r * cos A ; y = r * sin A
// 需要一个函数来完成转换，该函数接受一个包含极坐标的结构，并返回一个包含直角坐标的结构（或返回指向该结构的指针）。

#include <stdio.h>
#include <math.h>

struct polar {
	double dist;
	double angle;
};

struct recta{
	double x_coordinate;
	double y_coordinate;
}

struct recta invert_coor(struct polar);

int main(void)
{
	struct polar a;
	struct recta b;
	printf("Provide a polar coordinate to convert to a rectangle coordinate:\n");
	printf("Now enter distance and angle:(q to quit):");
	while (scanf("%f %f", &a.dist, &a.angle) == 2)
	{
		b = invert_coor(a);
		printf("Rectangular coordinate : X - %.2f   Y - %.2f\n", b.x_coordinate, b.y_coordinate);
		printf("Enter next pair of polar coordinate:(q to quit):\n");
	}
	printf("Bye!");

	return 0;
}

struct recta invert_coor(struct polar b)
{
	struct recta a;
	a.x_coordinate = b.dist * cos(angle);
	a.y_coordinate = b.dist * sin(angle);

	return a;
}