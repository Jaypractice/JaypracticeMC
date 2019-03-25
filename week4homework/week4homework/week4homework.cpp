#include "pch.h"
#include <iostream>
#include <CoalaMOD.h>
#pragma comment(lib, "CoalaMOD.lib")

#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

int main()
{
	int px, py, pz;
	getPlayerLocation(&px, &py, &pz);

	double dir = getPlayerDirection();

	double radian = dir * M_PI / 180.;

	int dx = -25 * sin(radian);
	int dz = 25 * cos(radian);

	BlockID dirt = createBlock(BLOCK_DIRT);

	for (int i = 0; i < 11; i++) {
		int y = 14 - i;
		for (int x = px + dx - i; x < px + dx + 1 + i; x++) {
			for (int z = pz + dz - i; z < pz + dz + 1 + i; z++) {
				locateBlock(dirt, x, y, z);
			}
		}
	}

	return 0;
}