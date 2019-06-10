#include "ASMGenerator.h"

int main(void)
{
	std::fstream file("asm.asm", std::fstream::in | std::fstream::out | std::fstream::trunc);
	std::stringstream output;

	/*
		// box
		x = 16
		y = 8
		boxWidth = 1
		boxHeight = 1

		// invalidateRect
		invX = 16
		invY = 8
		invWidth = 1
		invHeight = 1
		bInvalidateRect = true

		// general purpose area struct
		genX = 0
		genY = 0
		genWidth = 0
		genHeight = 0

		// constants
		const pKey = KEYBOARD

		// other varables
		lastKey = 0
		thisKey = 0
		bTransform = 0

		DrawGridInit(genArea)

		while (true) // gameLoop
			thisKey = *pKey
			if (thisKey != lastKey) // keyIf
				if (thisKey != 0) // keyIf2
					bInvalidateRect = true
					invX = x
					invY = y
					invWidth = boxWidth
					invHeight = boxHeight

					if (bTransform == false) // keyIfTransformFalse
						if (thisKey == arrowUp) // keyCond11
							if (y > 0) // keyCond12
								y--
							JUMP 1
						if (thisKey == arrowDown)
							if (y < 15)
								++
							JUMP 1
						if (thisKey == arrowRight)
							if (x < 31)
								x++
							JUMP 1
						if (thisKey == arrowLeft)
							if (x > 0)
								x--
							JUMP 1
					
					if (bTransform == true) // keyIfTransformTrue
						if (thisKey == arrowUp) // keyCond21
							if (boxHeight > 1) // keyCond22
								boxHeight--
							JUMP 1
						if (thisKey == arrowDown)
							if (y + boxHeight < 16)
								boxHeight++
							JUMP 1
						if (thisKey == arrowRight)
							if (x + boxWidth < 32)
								boxWidth++
							JUMP 1
						if (thisKey == arrowLeft)
							if (boxWidth > 1)
								boxWidth--

					JUMPPOINT 1

					if (thiskey == 'T') // keyIfTransformToggle
						if (bTransform == true)
							bTransform = 0
							JUMP 0
						bTransform = 1
						JUMPPOINT 0
						
						
				lastKey = thisKey

			if (bInvalidateRect) // invaldiateRectIf
				InvalidateRect(invArea)
				DrawGrid(invArea);
				InvalidateRect(boxArea); // drawbox
				bInvalidateRect = false

	*/

	/*
		DrawGridInit()
		{
			genX = 0
			genY = 0
			genWidth = 32
			genHeight = 16
			for (16) // drawGridFor1
				DrawLine(area)
				genY++

			genY = 0
			for (32) // drawGridFor2
				DrawLine(area, false)
				genX++
		}
	*/

	/*
		DrawGrid(invArea)
		{
			if (bTransform)
				if (invWidth < boxWidth)
					JUMP 2

				if (invHeight < boxHeight)
					JUMP 2	

				if (boxWidth < invWidth)
				{
					genX = x + boxWidth
					genY = y
					genWidth = 1
					genHeight = boxHeight
					JUMP 3
				}

				if (boxHeight < invHeight)
				{
					genX = x
					genY = y + boxHeight
					genWidth = boxWidth
					genHeight = 1
					JUMP 3
				}

			genX = invX
			genY = invY
			genWidth = invWidth
			genHeight = invHeight
			
			JUMPPOINT 3

			DrawGrid__rightBound = invX + invWidth
			while (genX < DrawGrid__rightBound) // DrawGridWhile1
				DrawGrid(genArea, false)
				genX++

			genX = invX
			
			DrawGrid__bottomBound = invY + invHeight
			while (genY < DrawGrid__bottomBound) // DrawGridWhile2
				DrawGrid(genArea)
				genY++

			JUMPPOINT 2
		}

	*/
	
	ASMBlock mainBlock;
	mainBlock.Init();
	mainBlock.Assign("x", 16);
	mainBlock.Assign("y", 8);
	mainBlock.Assign("boxWidth", 1);
	mainBlock.Assign("boxHeight", 1);

	mainBlock.Assign("invX", 16);
	mainBlock.Assign("invY", 8);
	mainBlock.Assign("invWidth", 1);
	mainBlock.Assign("invHeight", 1);
	mainBlock.Assign("bInvalidateRect", 1);

	mainBlock.Assign("genX", 0);
	mainBlock.Assign("genY", 0);
	mainBlock.Assign("genWidth", 32);
	mainBlock.Assign("genHeight", 16);

	mainBlock.Assign("pKey", KEYBOARD);

	mainBlock.Assign("lastKey", 0);
	mainBlock.Assign("thisKey", 0);
	mainBlock.Assign("bTransform", 0);

	ASMBlock drawGridFor1, drawGridFor2;
	mainBlock.For(16, &drawGridFor1);
	mainBlock.Assign("genY", 0);
	mainBlock.For(32, &drawGridFor2);

	AREA genArea;
	genArea.x = "genX";
	genArea.y = "genY";
	genArea.width = "genWidth";
	genArea.height = "genHeight";
	drawGridFor1.DrawLine(genArea);
	drawGridFor1.AddAssign("genY", "genY", 1);

	drawGridFor2.DrawLine(genArea, false);
	drawGridFor2.AddAssign("genX", "genX", 1);

	ASMBlock gameLoop;
	mainBlock.While("isGameOver", 0, BooleanOp::Equal, &gameLoop);

	ASMBlock keyIf, keyIf2, keyIfTransformFalse, keyIfTransformTrue, keyIfTransformToggle, invalidateRectIf;
	gameLoop.Assign("thisKey", "*pKey");
	gameLoop.If("thisKey", "lastKey", BooleanOp::NotEqual, &keyIf);
	gameLoop.If("bInvalidateRect", 1, BooleanOp::Equal, &invalidateRectIf);

	keyIf.If("thisKey", 0, BooleanOp::NotEqual, &keyIf2);
	keyIf.Assign("lastKey", "thisKey");

	keyIf2.Assign("bInvalidateRect", 1);
	keyIf2.Assign("invX", "x");
	keyIf2.Assign("invY", "y");
	keyIf2.Assign("invWidth", "boxWidth");
	keyIf2.Assign("invHeight", "boxHeight");
	keyIf2.If("bTransform", 0, BooleanOp::Equal, &keyIfTransformFalse);
	keyIf2.If("bTransform", 1, BooleanOp::Equal, &keyIfTransformTrue);
	keyIf2.If("thisKey", 'T', BooleanOp::Equal, &keyIfTransformToggle);

	ASMBlock keyCondUp11, keyCondDown11, keyCondRight11, keyCondLeft11;
	keyIfTransformFalse.If("thisKey", ARROWRIGHT, BooleanOp::Equal, &keyCondRight11);
	keyIfTransformFalse.If("thisKey", ARROWLEFT, BooleanOp::Equal, &keyCondLeft11);
	keyIfTransformFalse.If("thisKey", ARROWUP, BooleanOp::Equal, &keyCondUp11);
	keyIfTransformFalse.If("thisKey", ARROWDOWN, BooleanOp::Equal, &keyCondDown11);

	ASMBlock keyCondUp12, keyCondDown12, keyCondRight12, keyCondLeft12;

	keyCondUp11.If("y", 0, BooleanOp::GreaterStrict, &keyCondUp12);
	keyCondDown11.If("y", 15, BooleanOp::LessStrict, &keyCondDown12);
	keyCondRight11.If("x", 31, BooleanOp::LessStrict, &keyCondRight12);
	keyCondLeft11.If("x", 0, BooleanOp::GreaterStrict, &keyCondLeft12);

	keyCondUp12.SubtractAssign("y", "y", 1);
	keyCondDown12.AddAssign("y", "y", 1);
	keyCondRight12.AddAssign("x", "x", 1);
	keyCondLeft12.SubtractAssign("x", "x", 1);

	ASMBlock keyCondUp21, keyCondDown21, keyCondRight21, keyCondLeft21;
	ASMBlock keyCondUp22, keyCondDown22, keyCondRight22, keyCondLeft22;

	keyIfTransformTrue.If("thisKey", ARROWUP, BooleanOp::Equal, &keyCondUp21);
	keyIfTransformTrue.If("thisKey", ARROWDOWN, BooleanOp::Equal, &keyCondDown21);
	keyIfTransformTrue.If("thisKey", ARROWRIGHT, BooleanOp::Equal, &keyCondRight21);
	keyIfTransformTrue.If("thisKey", ARROWLEFT, BooleanOp::Equal, &keyCondLeft21);

	keyCondUp21.If("boxHeight", 1, BooleanOp::GreaterStrict, &keyCondUp22);

	std::string keyCondDown21Temp = AddressManager::GetInstance()->GetTemp();
	keyCondDown21.AddAssign(keyCondDown21Temp, "y", "boxHeight");
	keyCondDown21.If(keyCondDown21Temp, 16, BooleanOp::LessStrict, &keyCondDown22);

	std::string keyCondRight21Temp = AddressManager::GetInstance()->GetTemp();
	keyCondRight21.AddAssign(keyCondRight21Temp, "x", "boxWidth");
	keyCondRight21.If(keyCondRight21Temp, 32, BooleanOp::LessStrict, &keyCondRight22);

	keyCondLeft21.If("boxWidth", 1, BooleanOp::GreaterStrict, &keyCondLeft22);

	keyCondUp22.SubtractAssign("boxHeight", "boxHeight", 1);
	keyCondDown22.AddAssign("boxHeight", "boxHeight", 1);
	keyCondRight22.AddAssign("boxWidth", "boxWidth", 1);
	keyCondLeft22.SubtractAssign("boxWidth", "boxWidth", 1);

	ASMBlock ifTransformToggleTrue;
	keyIfTransformToggle.If("bTransform", 1, BooleanOp::Equal, &ifTransformToggleTrue);
	keyIfTransformToggle.Assign("bTransform", 1);
	keyIfTransformToggle.SetJumpPoint(0);

	ifTransformToggleTrue.Assign("bTransform", 0);
	ifTransformToggleTrue.Jump(0);


	ASMBlock whileBlock1, whileBlock2, whileBlock3, whileBlock4, drawBox;

	// InvalidateRect
	AREA invArea;
	invArea.x = "invX";
	invArea.y = "invY";
	invArea.width = "invWidth";
	invArea.height = "invHeight";
	invalidateRectIf.InvalidateRect(invArea);

	// DrawGrid
	ASMBlock DrawGridIfTransform;
	ASMBlock DrawGridWhile1, DrawGridWhile2;
	ASMBlock DrawGridIf1, DrawGridIf2, DrawGridIf3;

	invalidateRectIf.If("bTransform", 1, BooleanOp::Equal, &DrawGridIfTransform);

	DrawGridIfTransform.If("invWidth", "boxWidth", BooleanOp::LessStrict, &DrawGridIf1);
	DrawGridIf1.Jump(2);

	DrawGridIfTransform.If("invHeight", "boxHeight", BooleanOp::LessStrict, &DrawGridIf1);
	
	DrawGridIfTransform.If("boxWidth", "invWidth", BooleanOp::LessStrict, &DrawGridIf2);
	DrawGridIfTransform.If("boxHeight", "invHeight", BooleanOp::LessStrict, &DrawGridIf3);

	invalidateRectIf.Assign("genX", "invX");
	invalidateRectIf.Assign("genY", "invY");
	invalidateRectIf.Assign("genWidth", "invWidth");
	invalidateRectIf.Assign("genHeight", "invHeight");
	invalidateRectIf.SetJumpPoint(3);



	DrawGridIf2.AddAssign("genX", "x", "boxWidth");
	DrawGridIf2.Assign("genY", "y");
	DrawGridIf2.Assign("genWidth", 1);
	DrawGridIf2.Assign("genHeight", "boxHeight");
	DrawGridIf2.Jump(3);

	DrawGridIf3.Assign("genX", "x");
	DrawGridIf3.AddAssign("genY", "y", "boxHeight");
	DrawGridIf3.Assign("genWidth", "boxWidth");
	DrawGridIf3.Assign("genHeight", 1);
	DrawGridIf3.Jump(3);

	invalidateRectIf.AddAssign("DrawGrid__rightBound", "invX", "invWidth");
	invalidateRectIf.While("genX", "DrawGrid__rightBound", BooleanOp::LessStrict, &DrawGridWhile1);

	invalidateRectIf.Assign("genX", "invX");

	invalidateRectIf.AddAssign("DrawGrid__bottomBound", "invY", "invHeight");
	invalidateRectIf.While("genY", "DarwGrid__bottomBound", BooleanOp::LessStrict, &DrawGridWhile2);

	DrawGridWhile1.DrawLine(genArea, false);
	DrawGridWhile1.AddAssign("genX", "genX", 1);

	DrawGridWhile2.DrawLine(genArea);
	DrawGridWhile2.AddAssign("genY", "genY", 1);

	invalidateRectIf.SetJumpPoint(2);


	// DrawBox
	AREA boxArea;
	boxArea.x = "x";
	boxArea.y = "y";
	boxArea.width = "boxWidth";
	boxArea.height = "boxHeight";
	invalidateRectIf.InvalidateRect(boxArea, false);
	
	invalidateRectIf.Assign("bInvalidateRect", 0);

	mainBlock.GetASM(output);

	file << output.str();
	file.close();
}