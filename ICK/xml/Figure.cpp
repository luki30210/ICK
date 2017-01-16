#include"Figure.h"

void Figure::setColor(int r, int g, int b, int alfa){
 double rNorm, gNorm, bNorm, alfaNorm;
 rNorm = r / 255.f;
 gNorm = g / 255.f;
 bNorm = b / 255.f;
 alfaNorm = alfa / 255.f;
 color[0] = rNorm;
 color[1] = gNorm;
 color[2] = bNorm;
 color[3] = alfaNorm;
	}
