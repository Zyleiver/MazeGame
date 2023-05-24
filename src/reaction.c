#include"MyHeader.h"

void myMouseEvent (int x, int y, int button, int event)
{
	double mx = ScaleXInches(x);
	double my = ScaleYInches(y);
	switch (event)
	{
	case BUTTON_DOWN:
		if (button == LEFT_BUTTON)
		{
			MovePen(mx,my);
			DrawArc(1,0,360);
		}
			
		display();
		break;
	}
	display();
}
