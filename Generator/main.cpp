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

		// general purpose area struct
		genX = 0
		genY = 0
		genWidth = 32
		genHeight = 16

		// constants
		const pKey = KEYBOARD

		// other varables
		lastKey = 0
		thisKey = 0
		bTransform = 0
		bInvalidateRect = false

		DrawGrid(genArea)
		InvalidateRect(boxArea)

		while (true) // gameLoop
			thisKey = *pKey
			if (thisKey != lastKey) // keyIf
				if (thisKey != 0) // keyIf2; this prevents from drawing when you let go of key
					bInvalidateRect = true

					if (bTransform == false) // keyIfTransformFalse
						if (thisKey == arrowUp) // keyCond11
							if (y > 0) // keyCond12
								y--
						if (thisKey == arrowDown)
							if (y + boxHeight < 15)
								y++
						if (thisKey == arrowRight)
							if (x + boxWidth < 31)
								x++
						if (thisKey == arrowLeft)
							if (x > 0)
								x--
					
					if (bTransform == true) // keyIfTransformTrue
						if (thisKey == arrowUp) // keyCond21
							if (boxHeight > 1) // keyCond22
								boxHeight--
						if (thisKey == arrowDown)
							if (y + boxHeight < 16)
								boxHeight++
						if (thisKey == arrowRight)
							if (x + boxWidth < 32)
								boxWidth++
						if (thisKey == arrowLeft)
							if (boxWidth > 1)
								boxWidth--

					if (thiskey == 'T') // keyIfTransformToggle
						if (bTransform == true)
							bTransform = 0
							JUMP 0
						// else
						bTransform = 1
						JUMPPOINT 0
						
						
				lastKey = thisKey

			if (bInvalidateRect) // invaldiateRectIf
				Draw()
				bInvalidateRect = false

	*/

	/*
		Draw()
		{
			if (bTransform)
				// 가로로 커짐
				if (thisKey == ARROWRIGHT)
					genX = x + boxWidth - 1
					genY = y
					genWidth = 1
					genHeight = boxHeight
					InvalidateRect(genArea, false)
					JUMP 2 // return

				// 세로로 커짐
				if (thisKey == ARROWDOWN)
					genX = x
					genY = y + boxHeight - 1
					genWidth = boxWidth
					genHeight = 1
					InvalidateRect(genArea, false)
					JUMP 2	// return

				// 가로로 작아짐
				if (thisKey == ARROWLEFT)
				{
					genX = x + boxWidth
					genY = y
					genWidth = 1
					genHeight = boxHeight
					InvalidateRect(genArea)
					DrawGrid(genArea)
					JUMP 2 // return
				}

				// 세로로 작아짐
				if (thisKey == ARROWUP)
				{
					genX = x
					genY = y + boxHeight
					genWidth = boxWidth
					genHeight = 1
					InvalidateRect(genArea)
					DrawGrid(genArea)
					JUMP 2 // return
				}

			// if translation
			// 오른쪽으로 이동
			if (thisKey == ARROWRIGHT)
				genX = x - 1
				genY = y
				genWidth = 1
				genHeight = boxHeight
				InvalidateRect(genArea)
				DrawGrid(genArea)

				genX = genX + boxWidth
				InvalidateRect(genArea, false))
				JUMP 2 // return

			// 왼쪽으로 이동
			if (thisKey == ARROWLEFT)
				genX = x
				genY = y
				genWidth = 1
				genHeight = boxHeight
				InvalidateRect(genArea, false)

				genX = x + boxWidth
				InvalidateRect(genArea))
				DrawGrid(genArea)
				JUMP 2 // return
			
			// 아래로 이동
			if (thisKey == ARROWDOWN)
				genX = x
				genY = y - 1
				genWidth = boxWidth
				genHeight = 1
				InvalidateRect(genArea)
				DrawGrid(genARea)

				genY = genY + boxHeight
				InvalidateRect(genArea, false)
				JUMP 2 // return

			// 위로이동
			if (thisKey == ARROWUP)
				genX = x
				genY = y
				genWidth = boxWidth
				genHeight = 1
				InvalidateRect(genArea, false)

				genY = y + boxHeight
				InvalidateRect(genArea, true)
				DrawGrid(genArea)
				JUMP 2 // return

			JUMPPOINT 2
		}

	*/
	
	ASMBlock mainBlock;
	mainBlock.Init();
	mainBlock.Assign("x", 16);
	mainBlock.Assign("y", 8);
	mainBlock.Assign("boxWidth", 1);
	mainBlock.Assign("boxHeight", 1);

	mainBlock.Assign("genX", 0);
	mainBlock.Assign("genY", 0);
	mainBlock.Assign("genWidth", 32);
	mainBlock.Assign("genHeight", 16);

	mainBlock.Assign("pKey", KEYBOARD);

	mainBlock.Assign("lastKey", 0);
	mainBlock.Assign("thisKey", 0);
	mainBlock.Assign("bTransform", 0);
	mainBlock.Assign("bInvalidateRect", 0);

	AREA genArea;
	genArea.x = "genX";
	genArea.y = "genY";
	genArea.width = "genWidth";
	genArea.height = "genHeight";

	mainBlock.DrawGrid(genArea);

	AREA boxArea;
	boxArea.x = "x";
	boxArea.y = "y";
	boxArea.width = "boxWidth";
	boxArea.height = "boxHeight";
	mainBlock.InvalidateRect(boxArea, false);

	ASMBlock gameLoop;
	mainBlock.While("isGameOver", 0, BooleanOp::Equal, &gameLoop);

	ASMBlock keyIf, keyIf2, keyIfTransformFalse, keyIfTransformTrue, keyIfTransformToggle, invalidateRectIf;
	gameLoop.Assign("thisKey", "*pKey");
	gameLoop.If("thisKey", "lastKey", BooleanOp::NotEqual, &keyIf);
	gameLoop.If("bInvalidateRect", 1, BooleanOp::Equal, &invalidateRectIf);

	keyIf.If("thisKey", 0, BooleanOp::NotEqual, &keyIf2);
	keyIf.Assign("lastKey", "thisKey");

	keyIf2.Assign("bInvalidateRect", 1);
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

	std::string keyCondDown11Temp = AddressManager::GetInstance()->GetTemp();
	keyCondDown11.AddAssign(keyCondDown11Temp, "y", "boxHeight");
	keyCondDown11.If(keyCondDown11Temp, 16, BooleanOp::LessStrict, &keyCondDown12);

	std::string keyCondRight11Temp = AddressManager::GetInstance()->GetTemp();
	keyCondRight11.AddAssign(keyCondRight11Temp, "x", "boxWidth");
	keyCondRight11.If(keyCondRight11Temp, 32, BooleanOp::LessStrict, &keyCondRight12);

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

	/*------------------Draw--------------------*/
	ASMBlock drawTransform;
	invalidateRectIf.If("bTransform", 1, BooleanOp::Equal, &drawTransform);
	
	ASMBlock dtfRightIf, dtfLeftIf, dtfUpIf, dtfDownIf;
	drawTransform.If("thisKey", ARROWRIGHT, BooleanOp::Equal, &dtfRightIf);
	drawTransform.If("thisKey", ARROWDOWN, BooleanOp::Equal, &dtfDownIf);
	drawTransform.If("thisKey", ARROWLEFT, BooleanOp::Equal, &dtfLeftIf);
	drawTransform.If("thisKey", ARROWUP, BooleanOp::Equal, &dtfUpIf);

	dtfRightIf.AddAssign("genX", "x", "boxWidth");
	dtfRightIf.SubtractAssign("genX", "genX", 1);
	dtfRightIf.Assign("genY", "y");
	dtfRightIf.Assign("genWidth", 1);
	dtfRightIf.Assign("genHeight", "boxHeight");
	dtfRightIf.InvalidateRect(genArea, false);
	dtfRightIf.Jump(2);

	dtfDownIf.AddAssign("genY", "y", "boxHeight");
	dtfDownIf.SubtractAssign("genY", "genY", 1);
	dtfDownIf.Assign("genX", "x");
	dtfDownIf.Assign("genWidth", "boxWidth");
	dtfDownIf.Assign("genHeight", 1);
	dtfDownIf.InvalidateRect(genArea, false);
	dtfDownIf.Jump(2);

	dtfLeftIf.AddAssign("genX", "x", "boxWidth");
	dtfLeftIf.Assign("genY", "y");
	dtfLeftIf.Assign("genWidth", 1);
	dtfLeftIf.Assign("genHeight", "boxHeight");
	dtfLeftIf.InvalidateRect(genArea);
	dtfLeftIf.DrawGrid(genArea);
	dtfLeftIf.Jump(2);

	dtfUpIf.Assign("genX", "x");
	dtfUpIf.AddAssign("genY", "y", "boxHeight");
	dtfUpIf.Assign("genWidth", "boxWidth");
	dtfUpIf.Assign("genHeight", 1);
	dtfUpIf.InvalidateRect(genArea);
	dtfUpIf.DrawGrid(genArea);
	dtfUpIf.Jump(2);

	ASMBlock dtlRightIf, dtlLeftIf, dtlDownIf, dtlUpIf;
	invalidateRectIf.If("thisKey", ARROWRIGHT, BooleanOp::Equal, &dtlRightIf);
	invalidateRectIf.If("thisKey", ARROWDOWN, BooleanOp::Equal, &dtlDownIf);
	invalidateRectIf.If("thisKey", ARROWLEFT, BooleanOp::Equal, &dtlLeftIf);
	invalidateRectIf.If("thisKey", ARROWUP, BooleanOp::Equal, &dtlUpIf);

	dtlRightIf.SubtractAssign("genX", "x", 1);
	dtlRightIf.Assign("genY", "y");
	dtlRightIf.Assign("genWidth", 1);
	dtlRightIf.Assign("genHeight", "boxHeight");
	dtlRightIf.InvalidateRect(genArea);
	dtlRightIf.DrawGrid(genArea);
	dtlRightIf.AddAssign("genX", "genX", "boxWidth");
	dtlRightIf.InvalidateRect(genArea, false);
	dtlRightIf.Jump(2);
	
	dtlLeftIf.Assign("genX", "x");
	dtlLeftIf.Assign("genY", "y");
	dtlLeftIf.Assign("genWidth", 1);
	dtlLeftIf.Assign("genHeight", "boxHeight");
	dtlLeftIf.InvalidateRect(genArea, false);
	dtlLeftIf.AddAssign("genX", "x", "boxWidth");
	dtlLeftIf.InvalidateRect(genArea);
	dtlLeftIf.DrawGrid(genArea);
	dtlLeftIf.Jump(2);

	dtlDownIf.Assign("genX", "x");
	dtlDownIf.SubtractAssign("genY", "y", 1);
	dtlDownIf.Assign("genWidth", "boxWidth");
	dtlDownIf.Assign("genHeight", 1);
	dtlDownIf.InvalidateRect(genArea);
	dtlDownIf.DrawGrid(genArea);
	dtlDownIf.AddAssign("genY", "genY", "boxHeight");
	dtlDownIf.InvalidateRect(genArea, false);
	dtlDownIf.Jump(2);

	dtlUpIf.Assign("genX", "x");
	dtlUpIf.Assign("genY", "y");
	dtlUpIf.Assign("genWidth", "boxWidth");
	dtlUpIf.Assign("genHeight", 1);
	dtlUpIf.InvalidateRect(genArea, false);
	dtlUpIf.AddAssign("genY", "y", "boxHeight");
	dtlUpIf.InvalidateRect(genArea, true);
	dtlUpIf.DrawGrid(genArea);
	dtlUpIf.Jump(2);

	invalidateRectIf.SetJumpPoint(2);
	invalidateRectIf.Assign("bInvalidateRect", 0);
	/*------------------DrawEnd-----------------*/

	mainBlock.GetASM(output);

	file << output.str();
	file.close();
}