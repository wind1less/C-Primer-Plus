// ��������������ģ���������ĳ��ȣ����������x ����ʱ����ת�ĽǶ���������������
// ֱ��������������x ���y ���������������������
// ��дһ�����򣬶�ȡ������ģ�ͽǶȣ���λ���ȣ���Ȼ����ʾx ���y ������ꡣ
// ��ط��̣� x = r * cos A ; y = r * sin A
// ��Ҫһ�����������ת�����ú�������һ������������Ľṹ��������һ������ֱ������Ľṹ���򷵻�ָ��ýṹ��ָ�룩��

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