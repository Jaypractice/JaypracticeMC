#include "pch.h"
#define _CRT_SECURE_NO_WARNINGS
#include<CoalaMOD.h>
#pragma comment(lib,"CoalaMOD.lib")
#include<stdio.h>

int main()
{
	// 두 점 입력 first < second 가정
	int x1, x2, y1, y2, z1, z2;
	printf("공간을 형성하는 서로 다른 두 점의 좌표 입력(예: x1 y1 z1 x2 y2 z2): \n");
	scanf("%d %d %d %d %d %d", &x1, &y1, &z1, &x2, &y2, &z2);
	printf("입력된 두 점: (%d, %d, %d), (%d, %d, %d)\n", x1, y1, z1, x2, y2, z2);

	// 건물(공간)의 중심축 (xMid, zMid) 설정
	int dx = x2 - x1, dz = z2 - z1, dy = y2 - y1;
	int xMid = x1 + (dx / 2);
	int zMid = z1 + (dz / 2);

	// 건물이 차지하는 공간의 좌표별 비율
	// dx : dz : dy = 6 : 12 : 14
	// 최소값을 이용해 주어진 공간 밖으로 나가지 않게 설정
	int px = dx / 6, pz = dz / 12, py = dy / 14;
	int min = px;
	if (min > pz)min = pz;
	if (min > py)min = py;
	int xL = min * 6, zL = min * 12, yL = min * 14;

	// 튤립 깔기
	FlowerID redtulip = createFlower(FLOWER_RED_TULIP);
	for (int x = x1 + 1, y = 4; x <= x2 - 1; x++) {
		for (int z = z1 + 1; z <= z2 - 1; z++) {
			locateBlock(redtulip, x, y, z);
		}
	}

	// 풍차 몸체 형성하기
	// 정사각형 밑면 사이즈 xL로 시작
	// 높이가 증가함에 따라 사이즈 감소(5당 1감소 = - yDelta/5)
	// 몸체 white 배정, 모서리 red 배정
	WoolID white = createWool(COLOR_WHITE);
	WoolID red = createWool(COLOR_RED);
	int halfSize1 = xL / 2;
	int height = min * 10; // 풍차 몸체 높이
	for (int y = y1; y < y1 + height; y++) {
		int yDelta = y - y1; // y의 시작점으로부터 변화량
		for (int x = xMid - (halfSize1 - yDelta / 5); x <= xMid + (halfSize1 - yDelta / 5); x++) {
			for (int z = zMid - (halfSize1 - yDelta / 5); z <= zMid + (halfSize1 - yDelta / 5); z++) {
				if ((x == xMid - (halfSize1 - yDelta / 5) || x == xMid + (halfSize1 - yDelta / 5)) && (z == zMid - (halfSize1 - yDelta / 5) || z == zMid + (halfSize1 - yDelta / 5))) {
					locateBlock(red, x, y, z);
				}
				else locateWool(white, x, y, z);
			}
		}
	}

	// 창문 형성하기
	// 사이즈 (halfSize1-2min) x 2min
	// 정면 창문: y1 + 6min <= y < y1 + 8min 
	// x좌표는 몸체 벽면에 고정
	// z범위: zMid -+ (halfSize1 - 2min)/2
	PaneID glass = createPane(PANE_GLASS); // 내부 유리 배정
	PaneID iron = createPane(PANE_IRON);   // 테두리 창틀 배정
	for (int y = y1 + 6 * min; y < y1 + 8 * min; y++) {
		int yDelta = y - y1;
		for (int x = xMid - (halfSize1 - yDelta / 5), z = zMid - (halfSize1 - 2 * min) / 2; z <= zMid + (halfSize1 - 2 * min) / 2; z++) {
			if (y == y1 + 6 * min || y == y1 + 8 * min - 1 || z == zMid - (halfSize1 - 2 * min) / 2 || z == zMid + (halfSize1 - 2 * min) / 2) {
				locatePane(iron, x, y, z);
			}
			else locatePane(glass, x, y, z);
		}
	}
	// 측면 창문: y1 + 4min <= y < y1 + 6min
	// z좌표는 몸체 벽면에 고정
	// x범위: xMid -+ (halfSize1 - 2min)/2
	for (int y = y1 + 4 * min; y < y1 + 6 * min; y++) {
		int yDelta = y - y1;
		for (int z = zMid - (halfSize1 - yDelta / 5), x = xMid - (halfSize1 - 2 * min) / 2; x <= xMid + (halfSize1 - 2 * min) / 2; x++) {
			if (y == y1 + 4 * min || y == y1 + 6 * min - 1 || x == xMid - (halfSize1 - 2 * min) / 2 || x == xMid + (halfSize1 - 2 * min) / 2) {
				locatePane(iron, x, y, z);
			}
			else locatePane(glass, x, y, z);
		}
	}
	for (int y = y1 + 4 * min; y < y1 + 6 * min; y++) {
		int yDelta = y - y1;
		for (int z = zMid + (halfSize1 - yDelta / 5), x = xMid - (halfSize1 - 2 * min) / 2; x <= xMid + (halfSize1 - 2 * min) / 2; x++) {
			if (y == y1 + 4 * min || y == y1 + 6 * min - 1 || x == xMid - (halfSize1 - 2 * min) / 2 || x == xMid + (halfSize1 - 2 * min) / 2) {
				locatePane(iron, x, y, z);
			}
			else locatePane(glass, x, y, z);
		}
	}

	// 풍차 지붕 형성하기
	// 정사각형 밑면 사이즈 xL - 2((h-1)/5) + 2 로 시작(풍차 몸체 윗둥 보다 1사이즈 더 큰 상태로 시작)
	// 높이가 증가함에 따라 사이즈 감소(1당 1감소 = -yDelta)
	// 지붕 전체 red 배정
	int halfSize2 = xL / 2 - (height - 1) / 5 + 1; // 시작 밑면 사이즈의 반
	for (int y = height + y1; y <= halfSize2 + height + y1; y++) {
		int yDelta = y - (height + y1); // y의 시작점으로부터 변화량
		for (int x = xMid - (halfSize2 - yDelta); x <= xMid + (halfSize2 - yDelta); x++) {
			for (int z = zMid - (halfSize2 - yDelta); z <= zMid + (halfSize2 - yDelta); z++) {
				locateBlock(red, x, y, z);
			}
		}
	}

	// 풍차 날개 형성하기
	// 풍차 날개 중심의 좌표 (xMid - halfSize1, zMid, y1 + 9 * min)
	int xMid2 = xMid - halfSize1, zMid2 = zMid, yMid2 = y1 + 9 * min;

	// 중심축 형성하기
	WoolID gray = createWool(COLOR_GRAY);
	for (int x = xMid2, z = zMid2, y = yMid2; x <= xMid; x++)
		locateWool(gray, x, y, z);

	// 십자 뼈대 형성하기(z축방향, y축방향)
	// 길이는 10min-2+1
	for (int x = xMid2, z = zMid2 - 5 * min + 1, y = yMid2; z <= zMid2 + 5 * min - 1; z++)
		locateWool(gray, x, y, z);
	for (int x = xMid2, z = zMid2, y = yMid2 - 5 * min + 1; y <= yMid2 + 5 * min - 1; y++)
		locateWool(gray, x, y, z);

	// 중앙 마름모 형성하기
	// 중심으로부터 z, y에 관한 거리합 = min/2
	for (int x = xMid2, z = zMid2 - min / 2; z <= zMid2 + min / 2; z++) {
		int zDelta = z - zMid2;
		int zDeltaAbsolute = zDelta > 0 ? zDelta : -zDelta; // z에 관한 중심에서 거리차(절대값)
		// 마름모 특성: zDeltaAbsolute + yDeletaAbsolute <= min / 2
		for (int y = yMid2 - (min / 2 - zDeltaAbsolute); y <= yMid2 + (min / 2 - zDeltaAbsolute); y++) {
			locateWool(gray, x, y, z);
		}
	}

	// 날개 형성하기
	// 십자 뼈대를 중심으로 한쪽에는 min두께 반대쪽은 min/3두께 fence배정
	// 날개 중심을 기준으로 사분면마다 z,y의 부호값 이용
	FenceID fence = createFence(FENCE_DARK_OAK);
	for (int x = xMid2, z = zMid2 - (5 * min - 1); z <= zMid2 + (5 * min + 1); z++) {
		for (int y = yMid2 - min; y <= yMid2 + min; y++) {
			if (z >= zMid2 - (min - 1) && z <= zMid2 + (min - 1)) {} // 중간에 빈 부분
			else {
				int quadrant = (y - yMid2) * (z - zMid2); // z,y의 부호값 곱
				if (quadrant < 0) {
					if (y - yMid2 <= min / 3 && y - yMid2 >= -min / 3) {
						locateBlock(fence, x, y, z);
					}
				}
				else if (quadrant > 0) {
					locateBlock(fence, x, y, z);
				}
			}

		}
	}
	for (int x = xMid2, y = yMid2 - 5 * min + 1; y <= yMid2 + 5 * min - 1; y++) {
		for (int z = zMid2 - min; z <= zMid2 + min; z++) {
			if (y >= yMid2 - min + 1 && y <= yMid2 + min - 1) {}
			else {
				int quadrant = (y - yMid2) * (z - zMid2);
				if (quadrant > 0) {
					if (z - zMid2 <= min / 3 && z - zMid2 >= -min / 3) {
						locateBlock(fence, x, y, z);
					}
				}
				else if (quadrant < 0) {
					locateBlock(fence, x, y, z);
				}
			}

		}
	}
}