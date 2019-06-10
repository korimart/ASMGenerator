#include "..//Generator/ASMGenerator.h"

int main(void)
{
	std::fstream file("asm.asm", std::fstream::in | std::fstream::out | std::fstream::trunc);
	std::stringstream output;

	ASMBlock mainBlock;

	mainBlock.Init();
	mainBlock.Assign("x", 10);
	mainBlock.Assign("y", 10);
	mainBlock.Assign("width", 5);
	AREA area;
	area.x = "x";
	area.y = "y";
	area.width = "width";
	area.height = "width";

	mainBlock.DrawLine(area, false);

	mainBlock.GetASM(output);

	file << output.str();
	file.close();
}