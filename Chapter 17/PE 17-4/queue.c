#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "queue.c"

#define MIN_PER_HR 60.0
#define MAX_WAIT_TIME 3

bool newcustomer(double x);
Item customertime(long when, int line);
void update_advice(int cycle, int * served, int * line_wait, Queue * pq);

int main(void)
{
	Queue line1, line2;			    // 两个摊位
	Item temp;					    // 新的顾客数据
	int hours;					    // 模拟的小时数
	int perhour;				    // 每小时平均多少位顾客
	long cycle, cyclelimit;		    // 循环计数器、计数器的上限
	long turnaways = 0;			    // 因队列已满被拒的顾客数量
	long customers = 0;			    // 加入队列的顾客数量
	long served = 0;		    	// 在模拟期间完成咨询的顾客数量
	long sum_line = 0;		    	// 累计的队列总长
	long wait_time = 0;		    	// 当前顾客的等待时间
	double min_per_cust;	    	// 顾客到来的平均时间
	long line_wait = 0;		    	// 队列累计的等待时间
	int cur_line = 0;		    	// 完成处理的进程时间

	InitializeQueue(&line1);
	InitializeQueue(&line2);
	srand((unsigned int)time(0));
	puts("\n  -------------------------------------------------");
	puts("  **  Case Study: Sigmund Lander's Advice Booth  **");
	puts("  -------------------------------------------------");
	puts("Enter the number of simulation hours:");
	scanf("%d", &hours);
	cyclelimit = (long)MIN_PER_HR * hours;
	puts("Enter the average number of customers per hour:");
	scanf("%d", &perhour);
	min_per_cust = MIN_PER_HR / perhour;

	for (cycle = 0; cycle < cyclelimit; cycle++)
	{
		// 处理新增的元素
		if (newcustomer(min_per_cust))
		{
			if (QueueIsFull(&line1) && QueueIsFull(&line2))
				turnaways++;
			else
			{
				customers++;
				if (QueueItemCount(&line1) <= QueueItemCount(&line2) && !QueueIsFull(&line1))
				{
					temp = customertime(cycle, 1);
					EnQueue(temp, &line1);
				}
				else
				{
					temp = customertime(cycle, 2);
					EnQueue(temp, &line2);
				}
			}
		}

		// 处理已完成的元素
		// 分别处理两个队列首项
		update_advice(cycle, &served, &line_wait, &line1);
		update_advice(cycle, &served, &line_wait, &line2);
		sum_line += QueueItemCount(&line1) + QueueItemCount(&line2);
	}


	// 输出统计数据
	if (customers > 0)
	{
		printf("customers accepted: %ld\n", customers);
		printf("  customers served: %ld\n", served);
		printf("         turnaways: %ld\n", turnaways);
		printf("average queue size: %.2f\n", (double)sum_line / cyclelimit / 2);
		printf(" average wait time: %.2f minutes\n", (double)line_wait / served);
	}
	else
		puts("No customers!");
	EmptyTheQueue(&line1);
	EmptyTheQueue(&line2);
	puts("Bye!");

	return 0;
}

bool newcustomer(double x)
{
	// 一分钟内是否有顾客到来，(perhour / 60） 的概率为true;
	return (rand() * x / RAND_MAX < 1);
}

Item customertime(long when, int line)
{
    // 对于新加入的顾客，记录到达时间，分配咨询市场，所属线程
	Item cust;

	cust.processtime = rand() % MAX_WAIT_TIME + 1;
	cust.arrive = when;
	cust.line = line;

	return cust;
}

void update_advice(int cycle, int * served, int * line_wait, Queue * pq)
{
	// 队列不为空，且首项咨询时间完时，将首项弹出
	if (!QueueIsEmpty(pq) && pq->front->item.processtime <= 0)
	{
		(*line_wait) += cycle - pq->front->item.arrive;
		DeQueue(&pq->front->item, pq);
		(*served)++;
	}
	// 队列不为空，且首项在咨询时，递减咨询时间
	if (!QueueIsEmpty(pq) && pq->front->item.processtime > 0)
		pq->front->item.processtime--;
}
