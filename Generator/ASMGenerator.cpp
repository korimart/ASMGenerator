#include "ASMGenerator.h"

AddressManager* AddressManager::Instance = nullptr;
std::string ASMBlock::NEGONE = std::string();

void ASMBlock::Init()
{
	NEGONE = AddressManager::GetInstance()->GetTemp();
	this->Assign(NEGONE, 0);
	this->SubtractAssign(NEGONE, NEGONE, 1);
}

void ASMBlock::Assign(const std::string &varName, uint16_t value)
{   
	auto statement = std::make_unique<Statement>();
    statement->type = StatementType::Assign;
    statement->value = value;
    statement->targetName = varName;
    
    mStatements.push_back(std::move(statement));
}

void ASMBlock::Assign(const std::string & varName, const std::string & op)
{
	auto statement = std::make_unique<Statement>();
	statement->type = StatementType::AssignV;
	statement->op1.str = op;
	statement->targetName = varName;

	mStatements.push_back(std::move(statement));
}

void ASMBlock::AddAssign(const std::string& varName, const std::string& op1, uint16_t op2)
{
	auto statement = std::make_unique<Statement>();
	statement->type = StatementType::AddAssignVC;
	statement->targetName = varName;
	statement->op1.str = op1;
	statement->op2.constant = op2;

	mStatements.push_back(std::move(statement));
}

void ASMBlock::AddAssign(const std::string& varName, const std::string& op1, const std::string& op2)
{
	auto statement = std::make_unique<Statement>();
	statement->type = StatementType::AddAssignVV;
	statement->targetName = varName;
	statement->op1.str = op1;
	statement->op2.str = op2;

	mStatements.push_back(std::move(statement));
}

void ASMBlock::MultiplyAssign(const std::string& varName, const std::string& op1, uint16_t op2)
{
	auto statement = std::make_unique<Statement>();
	statement->type = StatementType::MultiplyAssignVC;
	statement->targetName = varName;
	statement->op1.str = op1;
	statement->op2.constant = op2;

	mStatements.push_back(std::move(statement));
}

void ASMBlock::MultiplyAssign(const std::string& varName, const std::string& op1, const std::string& op2)
{
	auto statement = std::make_unique<Statement>();
	statement->type = StatementType::MultiplyAssignVV;
	statement->targetName = varName;
	statement->op1.str = op1;
	statement->op2.str = op2;

	mStatements.push_back(std::move(statement));
}

void ASMBlock::SubtractAssign(const std::string & varName, const std::string & op1, uint16_t op2)
{
	auto statement = std::make_unique<Statement>();
	statement->type = StatementType::SubtractAssignVC;
	statement->targetName = varName;
	statement->op1.str = op1;
	statement->op2.constant = op2;

	mStatements.push_back(std::move(statement));
}

void ASMBlock::SubtractAssign(const std::string & varName, const std::string & op1, const std::string & op2)
{
	auto statement = std::make_unique<Statement>();
	statement->type = StatementType::SubtractAssignVV;
	statement->targetName = varName;
	statement->op1.str = op1;
	statement->op2.str = op2;

	mStatements.push_back(std::move(statement));
}

void ASMBlock::BitwiseAndAssign(const std::string & varName, const std::string & op1, uint16_t op2)
{
	auto statement = std::make_unique<Statement>();
	statement->type = StatementType::BitwiseAndAssignVC;
	statement->targetName = varName;
	statement->op1.str = op1;
	statement->op2.constant = op2;

	mStatements.push_back(std::move(statement));
}

void ASMBlock::BitwiseAndAssign(const std::string & varName, const std::string & op1, const std::string & op2)
{
	auto statement = std::make_unique<Statement>();
	statement->type = StatementType::BitwiseAndAssignVV;
	statement->targetName = varName;
	statement->op1.str = op1;
	statement->op2.str = op2;

	mStatements.push_back(std::move(statement));
}

void ASMBlock::BitwiseOrAssign(const std::string & varName, const std::string & op1, uint16_t op2)
{
	auto statement = std::make_unique<Statement>();
	statement->type = StatementType::BitwiseOrAssignVC;
	statement->targetName = varName;
	statement->op1.str = op1;
	statement->op2.constant = op2;

	mStatements.push_back(std::move(statement));
}

void ASMBlock::BitwiseOrAssign(const std::string & varName, const std::string & op1, const std::string & op2)
{
	auto statement = std::make_unique<Statement>();
	statement->type = StatementType::BitwiseOrAssignVV;
	statement->targetName = varName;
	statement->op1.str = op1;
	statement->op2.str = op2;

	mStatements.push_back(std::move(statement));
}

void ASMBlock::While(const std::string& op1, uint16_t op2, BooleanOp operation, ASMBlock* block)
{
	auto statement = std::make_unique<Statement>();
	statement->type = StatementType::WhileVC;
	statement->op1.str = op1;
	statement->op2.constant = op2;
	statement->condOp = operation;
	statement->block = block;

	mStatements.push_back(std::move(statement));
}

void ASMBlock::While(const std::string& op1, const std::string& op2, BooleanOp operation, ASMBlock* block)
{
	auto statement = std::make_unique<Statement>();
	statement->type = StatementType::WhileVV;
	statement->op1.str = op1;
	statement->op2.str = op2;
	statement->condOp = operation;
	statement->block = block;

	mStatements.push_back(std::move(statement));
}

void ASMBlock::If(const std::string& op1, uint16_t op2, BooleanOp operation, ASMBlock *block)
{
	auto statement = std::make_unique<Statement>();
	statement->type = StatementType::IfVC;
	statement->op1.str = op1;
	statement->op2.constant = op2;
	statement->condOp = operation;
	statement->block = block;

	mStatements.push_back(std::move(statement));
}

void ASMBlock::If(const std::string& op1, const std::string& op2, BooleanOp operation, ASMBlock* block)
{
	auto statement = std::make_unique<Statement>();
	statement->type = StatementType::WhileVV;
	statement->op1.str = op1;
	statement->op2.str = op2;
	statement->condOp = operation;
	statement->block = block;

	mStatements.push_back(std::move(statement));
}

void ASMBlock::For(uint16_t numCycles, ASMBlock* Block)
{
	auto statement = std::make_unique<Statement>();
	statement->type = StatementType::For;
	statement->value = numCycles;
	statement->block = Block;

	mStatements.push_back(std::move(statement));
}

void ASMBlock::Break()
{
	auto statement = std::make_unique<Statement>();
	statement->type = StatementType::Break;

	mStatements.push_back(std::move(statement));
}

void ASMBlock::SetJumpPoint(unsigned point)
{
	auto statement = std::make_unique<Statement>();
	statement->type = StatementType::SetJumpPoint;
	statement->value = point;

	mStatements.push_back(std::move(statement));
}

void ASMBlock::Jump(unsigned point)
{
	auto statement = std::make_unique<Statement>();
	statement->type = StatementType::Jump;
	statement->value = point;

	mStatements.push_back(std::move(statement));
}

void ASMBlock::InvalidateRect(AREA & area, bool bIsWhite)
{
	auto statement = std::make_unique<Statement>();
	statement->type = StatementType::InvalidateRect;
	statement->area = area;
	statement->value = bIsWhite;

	mStatements.push_back(std::move(statement));
}

void ASMBlock::DrawLine(AREA& area, bool bVertical)
{
	auto statement = std::make_unique<Statement>();
	statement->type = StatementType::DrawLine;
	statement->area = area;
	statement->value = bVertical;

	mStatements.push_back(std::move(statement));
}

void ASMBlock::DrawGrid(AREA& area)
{
	auto statement = std::make_unique<Statement>();
	statement->type = StatementType::DrawGrid;
	statement->area = area;

	mStatements.push_back(std::move(statement));
}

void ASMBlock::DrawImage(const std::string& fileName, RECT rt)
{
	auto statement = std::make_unique<Statement>();
	statement->type = StatementType::DrawImage;
	statement->targetName = fileName;
	statement->rt = rt;

	mStatements.push_back(std::move(statement));
}

void ASMBlock::GetASM(std::stringstream &out)
{
    auto pInstance = AddressManager::GetInstance();
    for (auto &pStatement : mStatements)
    {
        switch (pStatement->type)
        {
			case StatementType::Assign: case StatementType::AssignV:
			{
				if (pStatement->type == StatementType::Assign)
				{
					out << "@" << pStatement->value << std::endl;
					out << "D=A" << std::endl;
				}
				else
				{
					LoadAReg(out, pStatement->op1.str);
					out << "D=M" << std::endl;
				}

				LoadAReg(out, pStatement->targetName);

				out << "M=D" << std::endl;
			}
			break;

			case StatementType::AddAssignVC: case StatementType::AddAssignVV:
			case StatementType::SubtractAssignVC: case StatementType::SubtractAssignVV:
			case StatementType::BitwiseAndAssignVC: case StatementType::BitwiseAndAssignVV:
			case StatementType::BitwiseOrAssignVC: case StatementType::BitwiseOrAssignVV:
			{
				LoadAReg(out, pStatement->op1.str);
				out << "D=M" << std::endl;
				LoadAReg(out, pStatement->targetName);
				out << "M=D" << std::endl;

				if ((pStatement->type == StatementType::AddAssignVC)
					|| (pStatement->type == StatementType::SubtractAssignVC)
					|| (pStatement->type == StatementType::BitwiseAndAssignVC)
					|| (pStatement->type == StatementType::BitwiseOrAssignVC))
				{
					out << "@" << pStatement->op2.constant << std::endl;
					out << "D=A" << std::endl;
				}
				else
				{
					LoadAReg(out, pStatement->op2.str);
					out << "D=M" << std::endl;
				}

				LoadAReg(out, pStatement->targetName);

				if ((pStatement->type == StatementType::AddAssignVC)
					|| (pStatement->type == StatementType::AddAssignVV))
					out << "M=M+D" << std::endl;
				else if ((pStatement->type == StatementType::SubtractAssignVC)
					|| (pStatement->type == StatementType::SubtractAssignVV))
					out << "M=M-D" << std::endl;
				else if ((pStatement->type == StatementType::BitwiseAndAssignVC)
					|| (pStatement->type == StatementType::BitwiseAndAssignVV))
					out << "M=M&D" << std::endl;
				else
					out << "M=M|D" << std::endl;
			}
			break;

			case StatementType::WhileVC: case StatementType::WhileVV:
			{
				int loopLabel = pInstance->GetNextUniqueID();

				// condition
				out << "(LOOP" << loopLabel << ")" << std::endl;

				if (pStatement->type == StatementType::WhileVC)
				{
					out << "@" << pStatement->op2.constant << std::endl;
					out << "D=A" << std::endl;
				}
				else
				{
					LoadAReg(out, pStatement->op2.str);
					out << "D=M" << std::endl;
				}
				LoadAReg(out, pStatement->op1.str);
				out << "D=D-M" << std::endl;
				out << "@LOOPEND" << loopLabel << std::endl;
				Jump(out, pStatement->condOp);
				// block
				pStatement->block->SetBreakPoint(loopLabel);
				pStatement->block->GetASM(out);
				out << "@LOOP" << loopLabel << std::endl;
				out << "0; JMP" << std::endl;
				out << "(LOOPEND" << loopLabel << ")" << std::endl;
			}
			break;

			case StatementType::MultiplyAssignVC: case StatementType::MultiplyAssignVV:
			{
				std::string temp = pInstance->GetTemp();
				ASMBlock initBlock, whileBlock;
				initBlock.Assign(pStatement->targetName, 0);
				initBlock.Assign(temp, 0);
				whileBlock.AddAssign(pStatement->targetName, pStatement->targetName, pStatement->op1.str);
				whileBlock.AddAssign(temp, temp, 1);
				if (pStatement->type == StatementType::MultiplyAssignVC)
					initBlock.While(temp, pStatement->op2.constant, BooleanOp::LessStrict, &whileBlock);
				else
					initBlock.While(temp, pStatement->op2.str, BooleanOp::LessStrict, &whileBlock);

				initBlock.GetASM(out);
			}
			break;

			case StatementType::IfVC: case StatementType::IfVV:
			{
				int ifLabel = pInstance->GetNextUniqueID();

				// condition
				if (pStatement->type == StatementType::IfVC)
				{
					out << "@" << pStatement->op2.constant << std::endl;
					out << "D=A" << std::endl;
				}
				else
				{
					LoadAReg(out, pStatement->op2.str);
					out << "D=M" << std::endl;
				}
				LoadAReg(out, pStatement->op1.str);
				out << "D=D-M" << std::endl;
				out << "@IFEND" << ifLabel << std::endl;
				Jump(out, pStatement->condOp);

				// block
				pStatement->block->GetASM(out);
				out << "(IFEND" << ifLabel << ")" << std::endl;
			}
			break;

			case StatementType::For:
			{
				auto temp = pInstance->GetTemp();
				auto temp2 = pInstance->GetTemp();

				ASMBlock initBlock, whileBlock;
				initBlock.Assign(temp, 0);
				initBlock.While(temp, pStatement->value, BooleanOp::LessStrict, &whileBlock);
				whileBlock.If(temp2, 0, BooleanOp::Equal, pStatement->block);
				whileBlock.AddAssign(temp, temp, 1);
				initBlock.GetASM(out);
			}
			break;

			case StatementType::Break:
			{
				out << "@" << "LOOPEND" << mBreakPoint << std::endl;
				out << "0; JMP" << std::endl;
			}
			break;

			case StatementType::InvalidateRect:
			{
				/*
					originalAddr = SCREEN + area.x + area.y * 512
					height = 0

					while (height < invalidateHeight * 16) // while1
						width = 0
						pAddr = originalAddr + height * 32
						while (width < invalidateWidth) // while2
							if (bIsWhite)
								*pAddr = 0
							else
								*pAddr = NegOne
							width++
							pAddr++
						height++
				*/
				
				const auto &area = pStatement->area;
				std::string originalAddr = pInstance->GetTemp();
				std::string height = pInstance->GetTemp();
				std::string width = pInstance->GetTemp();
				std::string pAddr = pInstance->GetTemp();

				ASMBlock block, while1, while2;

				std::string while1comp = pInstance->GetTemp();
				block.MultiplyAssign(while1comp, area.height, 16);
				
				block.MultiplyAssign(originalAddr, area.y, 512);
				block.AddAssign(originalAddr, originalAddr, SCREEN);
				block.AddAssign(originalAddr, originalAddr, area.x);
				block.Assign(height, 0);


				block.While(height, while1comp, BooleanOp::LessStrict, &while1);
				
				while1.Assign(width, 0);
				while1.MultiplyAssign(pAddr, height, 32);
				while1.AddAssign(pAddr, pAddr, originalAddr);
				while1.While(width, area.width, BooleanOp::LessStrict, &while2);
				while1.AddAssign(height, height, 1);

				if (pStatement->value)
					while2.Assign("*" + pAddr, 0);
				else
					while2.Assign("*" + pAddr, NEGONE);
				while2.AddAssign(width, width, 1);
				while2.AddAssign(pAddr, pAddr, 1);

				block.GetASM(out);
			}
			break;

			case StatementType::DrawLine:
			{
				/*
					pAddr = SCREEN + area.x + area.y * 512
					if (vertical)
						width = 0
						while (width < area.width)
							*pAddr = NEGONE
							pAddr++
							width++
					else
						height = 0
						while (height < area.height * 16)
							*pAddr |= 1
							pAddr += 32
							height++
				*/
				const auto& area = pStatement->area;
				std::string pAddr = pInstance->GetTemp();
				std::string widthOrHeight = pInstance->GetTemp();
				
				ASMBlock block, whileBlock;
				block.MultiplyAssign(pAddr, area.y, 512);
				block.AddAssign(pAddr, pAddr, area.x);
				block.AddAssign(pAddr, pAddr, SCREEN);
				block.Assign(widthOrHeight, 0);
				
				if (pStatement->value)
				{
					block.While(widthOrHeight, area.width, BooleanOp::LessStrict, &whileBlock);
					whileBlock.Assign("*" + pAddr, NEGONE);
					whileBlock.AddAssign(widthOrHeight, widthOrHeight, 1);
					whileBlock.AddAssign(pAddr, pAddr, 1);
				}
				else
				{
					std::string condTemp = pInstance->GetTemp();
					block.MultiplyAssign(condTemp, area.height, 16);
					block.While(widthOrHeight, condTemp, BooleanOp::LessStrict, &whileBlock);
					whileBlock.BitwiseOrAssign("*" + pAddr, "*" + pAddr, 1);
					whileBlock.AddAssign(pAddr, pAddr, 32);
					whileBlock.AddAssign(widthOrHeight, widthOrHeight, 1);
				}
				block.GetASM(out);
			}
			break;

			case StatementType::SetJumpPoint:
			{
				out << "(" << "JUMPPOINT" << pStatement->value << ")" << std::endl;
			}
			break;

			case StatementType::Jump:
			{
				out << "@" << "JUMPPOINT" << pStatement->value << std::endl;
				out << "0; JMP" << std::endl;
			}
			break;

			case StatementType::DrawGrid:
			{
				/*
					AREA areaArg =
					{
						x,
						y,
						width,
						height
					}
					x = area.x
					y = area.y
					width = area.width
					height area.height

					while (y < area.y + area.height)
						DrawLine(areaArg)
						y++

					y = area.y
					
					while (x < area.x + area.width)
						DrawLine(areaArg)
						x++
				*/
				AREA areaArg;
				ASMBlock block, while1, while2;
				const auto& area = pStatement->area;
				std::string x = pInstance->GetTemp();
				std::string y = pInstance->GetTemp();
				std::string width = pInstance->GetTemp();
				std::string height = pInstance->GetTemp();
				std::string whileCond1 = pInstance->GetTemp();
				std::string whileCond2 = pInstance->GetTemp();

				areaArg.x = x;
				areaArg.y = y;
				areaArg.width = width;
				areaArg.height = height;

				block.Assign(x, area.x);
				block.Assign(y, area.y);
				block.Assign(width, area.width);
				block.Assign(height, area.height);
				block.AddAssign(whileCond1, area.y, area.height);
				block.AddAssign(whileCond2, area.x, area.width);

				block.While(y, whileCond1, BooleanOp::LessStrict, &while1);
				block.Assign(y, area.y);
				block.While(x, whileCond2, BooleanOp::LessStrict, &while2);

				while1.DrawLine(areaArg);
				while1.AddAssign(y, y, 1);

				while2.DrawLine(areaArg, false);
				while2.AddAssign(x, x, 1);

				block.GetASM(out);
			}
			break;

			case StatementType::DrawImage:
			{
				DrawImage(out, pStatement.get());
			}
			break;
		}
	}
}

void ASMBlock::SetBreakPoint(uint16_t breakpoint)
{
	mBreakPoint = breakpoint;
}

void ASMBlock::Jump(std::stringstream& out, BooleanOp op)
{
	switch (op)
	{
	case BooleanOp::NotEqual:
		out << "D; JEQ" << std::endl;
		break;
	case BooleanOp::Equal:
		out << "D; JNE" << std::endl;
		break;
	case BooleanOp::LessStrict:
		out << "D; JLE" << std::endl;
		break;
	case BooleanOp::LessEqual:
		out << "D; JLT" << std::endl;
		break;
	case BooleanOp::GreaterStrict:
		out << "D; JGE" << std::endl;
		break;
	case BooleanOp::GreaterEqual:
		out << "D; JGT" << std::endl;
		break;
	}
}

inline void ASMBlock::GetPointedVal2AReg(std::stringstream& out, const std::string& varName)
{
	auto pInstance = AddressManager::GetInstance();
	out << "@" << pInstance->GetAddress(varName) << std::endl;
	out << "A=M" << std::endl;
}

inline void ASMBlock::GetVal2AReg(std::stringstream& out, const std::string& varName)
{
	auto pInstance = AddressManager::GetInstance();
	out << "@" << pInstance->GetAddress(varName) << std::endl;
}

inline void ASMBlock::LoadAReg(std::stringstream& out, const std::string& varName)
{
	if (varName[0] == '*')
		GetPointedVal2AReg(out, varName.substr(1));
	else
		GetVal2AReg(out, varName);
}

void ASMBlock::DrawImage(std::stringstream& out, const Statement* pStatement)
{
	std::ifstream file(pStatement->targetName);
	if (!file.is_open())
	{
		std::cout << "unable to open file" << std::endl;
		int a;
		std::cin >> a;
		exit(1);
	}

	const auto& rt = pStatement->rt;
	if (rt.x < 0 || rt.x > 31 || rt.y < 0 || rt.y > 15)
	{
		std::cout << "image size not acceptable" << std::endl;
		int a;
		std::cin >> a;
		exit(1);
	}

	int16_t word;
	uint16_t addr;
	for (int j = 0; j < rt.height * 16; j++) {
		addr = SCREEN + rt.x + 512 * rt.y + 32 * j;
		for (int i = 0; i < rt.width; ++i)
		{
			uint16_t temp = 0;
			for (int k = 0; k < 16; ++k)
			{
				char c;
				file >> c;
				if (c == '1')
					temp += pow(2, k);
			}
			word = (int16_t)temp;

			if (word > 0)
			{
				out << "@" << word << std::endl;
				out << "D=A" << std::endl;
			}
			else
			{
				word *= -1;
				out << "@" << word << std::endl;
				out << "D=A" << std::endl;
				out << "D=-D" << std::endl;
			}

			out << "@" << addr << std::endl;
			out << "M=D" << std::endl;
			addr++;
		}
	}
}

AddressManager* AddressManager::GetInstance()
{
	if (Instance == nullptr)
		Instance = new AddressManager;
	return Instance;
}

uint16_t AddressManager::GetAddress(const std::string &varName)
{
	if (varName[0] == '*')
		return 0x8000;

	if (mVariables.find(varName) == mVariables.end())
	{
		mVariables[varName] = mNextAddress++;
		return mVariables[varName];
	}
	return mVariables[varName];
}

std::string AddressManager::GetTemp()
{
	std::stringstream ss;
	ss << "__tempKorimart" << mNextAddress;
	this->GetAddress(ss.str());
	return ss.str();
}

int AddressManager::GetNextUniqueID(void)
{
	return mNextUniqueID++;
}
