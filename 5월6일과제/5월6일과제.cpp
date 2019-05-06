#include "pch.h"
#define _CRT_SECURE_NO_WARNINGS
#include<CoalaMOD.h>
#pragma comment(lib,"CoalaMOD.lib")
#include<stdio.h>

int main()
{
	// �� �� �Է� first < second ����
	int x1, x2, y1, y2, z1, z2;
	printf("������ �����ϴ� ���� �ٸ� �� ���� ��ǥ �Է�(��: x1 y1 z1 x2 y2 z2): \n");
	scanf("%d %d %d %d %d %d", &x1, &y1, &z1, &x2, &y2, &z2);
	printf("�Էµ� �� ��: (%d, %d, %d), (%d, %d, %d)\n", x1, y1, z1, x2, y2, z2);

	// �ǹ�(����)�� �߽��� (xMid, zMid) ����
	int dx = x2 - x1, dz = z2 - z1, dy = y2 - y1;
	int xMid = x1 + (dx / 2);
	int zMid = z1 + (dz / 2);

	// �ǹ��� �����ϴ� ������ ��ǥ�� ����
	// dx : dz : dy = 6 : 12 : 14
	// �ּҰ��� �̿��� �־��� ���� ������ ������ �ʰ� ����
	int px = dx / 6, pz = dz / 12, py = dy / 14;
	int min = px;
	if (min > pz)min = pz;
	if (min > py)min = py;
	int xL = min * 6, zL = min * 12, yL = min * 14;

	// ƫ�� ���
	FlowerID redtulip = createFlower(FLOWER_RED_TULIP);
	for (int x = x1 + 1, y = 4; x <= x2 - 1; x++) {
		for (int z = z1 + 1; z <= z2 - 1; z++) {
			locateBlock(redtulip, x, y, z);
		}
	}

	// ǳ�� ��ü �����ϱ�
	// ���簢�� �ظ� ������ xL�� ����
	// ���̰� �����Կ� ���� ������ ����(5�� 1���� = - yDelta/5)
	// ��ü white ����, �𼭸� red ����
	WoolID white = createWool(COLOR_WHITE);
	WoolID red = createWool(COLOR_RED);
	int halfSize1 = xL / 2;
	int height = min * 10; // ǳ�� ��ü ����
	for (int y = y1; y < y1 + height; y++) {
		int yDelta = y - y1; // y�� ���������κ��� ��ȭ��
		for (int x = xMid - (halfSize1 - yDelta / 5); x <= xMid + (halfSize1 - yDelta / 5); x++) {
			for (int z = zMid - (halfSize1 - yDelta / 5); z <= zMid + (halfSize1 - yDelta / 5); z++) {
				if ((x == xMid - (halfSize1 - yDelta / 5) || x == xMid + (halfSize1 - yDelta / 5)) && (z == zMid - (halfSize1 - yDelta / 5) || z == zMid + (halfSize1 - yDelta / 5))) {
					locateBlock(red, x, y, z);
				}
				else locateWool(white, x, y, z);
			}
		}
	}

	// â�� �����ϱ�
	// ������ (halfSize1-2min) x 2min
	// ���� â��: y1 + 6min <= y < y1 + 8min 
	// x��ǥ�� ��ü ���鿡 ����
	// z����: zMid -+ (halfSize1 - 2min)/2
	PaneID glass = createPane(PANE_GLASS); // ���� ���� ����
	PaneID iron = createPane(PANE_IRON);   // �׵θ� âƲ ����
	for (int y = y1 + 6 * min; y < y1 + 8 * min; y++) {
		int yDelta = y - y1;
		for (int x = xMid - (halfSize1 - yDelta / 5), z = zMid - (halfSize1 - 2 * min) / 2; z <= zMid + (halfSize1 - 2 * min) / 2; z++) {
			if (y == y1 + 6 * min || y == y1 + 8 * min - 1 || z == zMid - (halfSize1 - 2 * min) / 2 || z == zMid + (halfSize1 - 2 * min) / 2) {
				locatePane(iron, x, y, z);
			}
			else locatePane(glass, x, y, z);
		}
	}
	// ���� â��: y1 + 4min <= y < y1 + 6min
	// z��ǥ�� ��ü ���鿡 ����
	// x����: xMid -+ (halfSize1 - 2min)/2
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

	// ǳ�� ���� �����ϱ�
	// ���簢�� �ظ� ������ xL - 2((h-1)/5) + 2 �� ����(ǳ�� ��ü ���� ���� 1������ �� ū ���·� ����)
	// ���̰� �����Կ� ���� ������ ����(1�� 1���� = -yDelta)
	// ���� ��ü red ����
	int halfSize2 = xL / 2 - (height - 1) / 5 + 1; // ���� �ظ� �������� ��
	for (int y = height + y1; y <= halfSize2 + height + y1; y++) {
		int yDelta = y - (height + y1); // y�� ���������κ��� ��ȭ��
		for (int x = xMid - (halfSize2 - yDelta); x <= xMid + (halfSize2 - yDelta); x++) {
			for (int z = zMid - (halfSize2 - yDelta); z <= zMid + (halfSize2 - yDelta); z++) {
				locateBlock(red, x, y, z);
			}
		}
	}

	// ǳ�� ���� �����ϱ�
	// ǳ�� ���� �߽��� ��ǥ (xMid - halfSize1, zMid, y1 + 9 * min)
	int xMid2 = xMid - halfSize1, zMid2 = zMid, yMid2 = y1 + 9 * min;

	// �߽��� �����ϱ�
	WoolID gray = createWool(COLOR_GRAY);
	for (int x = xMid2, z = zMid2, y = yMid2; x <= xMid; x++)
		locateWool(gray, x, y, z);

	// ���� ���� �����ϱ�(z�����, y�����)
	// ���̴� 10min-2+1
	for (int x = xMid2, z = zMid2 - 5 * min + 1, y = yMid2; z <= zMid2 + 5 * min - 1; z++)
		locateWool(gray, x, y, z);
	for (int x = xMid2, z = zMid2, y = yMid2 - 5 * min + 1; y <= yMid2 + 5 * min - 1; y++)
		locateWool(gray, x, y, z);

	// �߾� ������ �����ϱ�
	// �߽����κ��� z, y�� ���� �Ÿ��� = min/2
	for (int x = xMid2, z = zMid2 - min / 2; z <= zMid2 + min / 2; z++) {
		int zDelta = z - zMid2;
		int zDeltaAbsolute = zDelta > 0 ? zDelta : -zDelta; // z�� ���� �߽ɿ��� �Ÿ���(���밪)
		// ������ Ư��: zDeltaAbsolute + yDeletaAbsolute <= min / 2
		for (int y = yMid2 - (min / 2 - zDeltaAbsolute); y <= yMid2 + (min / 2 - zDeltaAbsolute); y++) {
			locateWool(gray, x, y, z);
		}
	}

	// ���� �����ϱ�
	// ���� ���븦 �߽����� ���ʿ��� min�β� �ݴ����� min/3�β� fence����
	// ���� �߽��� �������� ��и鸶�� z,y�� ��ȣ�� �̿�
	FenceID fence = createFence(FENCE_DARK_OAK);
	for (int x = xMid2, z = zMid2 - (5 * min - 1); z <= zMid2 + (5 * min + 1); z++) {
		for (int y = yMid2 - min; y <= yMid2 + min; y++) {
			if (z >= zMid2 - (min - 1) && z <= zMid2 + (min - 1)) {} // �߰��� �� �κ�
			else {
				int quadrant = (y - yMid2) * (z - zMid2); // z,y�� ��ȣ�� ��
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