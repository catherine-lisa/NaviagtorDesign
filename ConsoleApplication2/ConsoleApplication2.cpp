#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <map>
#include <queue>
#include <vector>
using namespace std;
typedef long long ll;
const int buildingNumber = 20;
const int crossingNumber = 8;
char lesson[10][10][20];
char timetable[10][10][20];
typedef struct node {
	char name[50];
	int x, y;
}building;
typedef struct node2 {
	int x, y;
}coordinate;

building Building[25];
coordinate start, destination;
coordinate crossroads[50];

void init();//获取地图原始信息
void getLocation();//获取始末位置
coordinate askLocation();//询问所在位置
coordinate getCoordinate(char* s);//获取位置的坐标

int main() {

	init();
	getLocation();
	
	return 0;
}

void init() {
	FILE* fp1, *fp2, *fp3, *fp4;
	fp1 = fopen("lesson.txt", "r");
	fp2 = fopen("timetable.txt", "r");
	fp3 = fopen("building.txt", "r");
	for (int i = 1; i <= 8; i++) {
		for (int j = 1; j <= 5; j++) {
			fscanf(fp1, "%s", lesson[i][j]);
			fscanf(fp2, "%s", timetable[i][j]);
		}
	}
	for (int i = 1; i <= buildingNumber; i++) {
		fscanf(fp3, "%s", Building[i].name);
		fscanf(fp3, "%d,%d", &Building[i].x, &Building[i].y);
	}
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	return;
}

void getLocation() {//获取起始位置
	printf("请输入起始位置:1为逻辑位置，2为物理位置\n");
	start = askLocation();
	printf("起始位置的坐标为：(%d,%d)\n", start.x, start.y);
	printf("请输入目的位置:1为逻辑位置，2为物理位置\n");
	destination = askLocation();
	printf("终止位置的坐标为：(%d,%d)\n", destination.x, destination.y);
	return;
}

coordinate askLocation() {
	int select;
	char location[50];
	coordinate coor;
	scanf("%d", &select);
	if (select == 1) {   //选择逻辑位置
		//打印课程表
		int week, course;
		printf("\t\t");
		for (int i = 1; i <= 7; i++) printf("星期%d               ", i);
		printf("\n");
		for (int i = 1; i <= 8; i++) {
			printf("第%d节课 ", i);
			for (int j = 1; j <= 5; j++) {
				printf("   %s        ", lesson[i][j]);
			}
			printf("\n           ");
			for (int j = 1; j <= 5; j++) {
				printf("%s   ", timetable[i][j]);
			}
			printf("\n\n");
		}
		//通过课程表获得物理位置
		printf("请输入所在的星期：\n");
		scanf("%d", &week);
		printf("请输入课程节次：\n");
		scanf("%d", &course);
		strcpy(location, timetable[course][week]);
		coor = getCoordinate(location);
	}
	else if (select == 2) { //选择物理位置
		int num;
		printf("请选择你所在的位置：\n");
		for (int i = 1; i <= buildingNumber; i++) {
			printf("%d : %s\n", i, Building[i].name);
		}
		scanf("%d", &num);
		coor.x = Building[num].x;
		coor.y = Building[num].y;
	}
	return coor;
}

coordinate getCoordinate(char* s) {
	int i, j, len;
	coordinate coor;
	for (i = 1; i <= buildingNumber; i++) {
		len = strlen(Building[i].name);
		for (j = 0; j < len; j++) {
			if (s[j] != Building[i].name[j]) break;
		}
		if (j == len) break;
	}
	coor.x = Building[i].x;
	coor.y = Building[i].y;
	return coor;
}

