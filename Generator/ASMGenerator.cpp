#pragma once
#include "ASMGenerator.h"

AddressManager* AddressManager::Instance = nullptr;

void ASMBlock::Assign(const std::string &varName, uint16_t value)
{   
	auto statement = std::make_unique<Statement>();
    statement->type = StatementType::Assign;
    statement->value = value;
    statement->targetName = varName;
    
    mStatements.push_back(std::move(statement));
}

void ASMBlock::AssignAtAddress(uint16_t addr, uint16_t value)
{
	auto statement = std::make_unique<Statement>();
	statement->type = StatementType::AssignAtAddr;
	statement->value = value;
	statement->addr = addr;

	mStatements.push_back(std::move(statement));
}

void ASMBlock::AssignAtAddress(const std::string& varName, uint16_t value)
{
	auto statement = std::make_unique<Statement>();
	statement->type = StatementType::AssignAtAddrV;
	statement->value = value;
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

void ASMBlock::GetASM(std::stringstream &out)
{
    auto pInstance = AddressManager::GetInstance();
    for (auto &pStatement : mStatements)
    {
        switch (pStatement->type)
        {
			case StatementType::Assign: case StatementType::AssignAtAddr:
			{
				uint16_t addr = 
					pStatement->type == StatementType::Assign 
					? pInstance->GetAddress(pStatement->targetName) : pStatement->addr;
				out << "@" << pStatement->value << std::endl;
				out << "D=A" << std::endl;
				out << "@" << addr << std::endl;
				out << "M=D" << std::endl;
			}
			break;

			case StatementType::AssignAtAddrV:
			{
				out << "@" << pStatement->value << std::endl;
				out << "D=A" << std::endl;
				out << "@" << pInstance->GetAddress(pStatement->targetName) << std::endl;
				out << "A=M" << std::endl;
				out << "M=D" << std::endl;
			}
			break;

			case StatementType::AddAssignVC: case StatementType::AddAssignVV:
			{
				uint16_t Op1Addr = pInstance->GetAddress(pStatement->op1.str);
				uint16_t Op2Addr = pInstance->GetAddress(pStatement->op2.str);
				uint16_t targetAddr = pInstance->GetAddress(pStatement->targetName);

				out << "@" << Op1Addr << std::endl;
				out << "D=M" << std::endl;
				out << "@" << targetAddr << std::endl;
				out << "M=D" << std::endl;

				if (pStatement->type == StatementType::AddAssignVC)
				{
					out << "@" << pStatement->op2.constant << std::endl;
					out << "D=A" << std::endl;
				}
				else
				{
					out << "@" << Op2Addr << std::endl;
					out << "D=M" << std::endl;

				}
				out << "@" << targetAddr << std::endl;
				out << "M=M+D" << std::endl;
			}
			break;

			case StatementType::WhileVC: case StatementType::WhileVV:
			{
				int loopLabel = pInstance->GetNextUniqueID();
				uint16_t op1Addr = pInstance->GetAddress(pStatement->op1.str);
				uint16_t op2Addr = pInstance->GetAddress(pStatement->op2.str);

				// condition
				out << "(LOOP" << loopLabel << ")" << std::endl;

				if (pStatement->type == StatementType::WhileVC)
				{
					out << "@" << pStatement->op2.constant << std::endl;
					out << "D=A" << std::endl;
				}
				else
				{
					out << "@" << op2Addr << std::endl;
					out << "D=M" << std::endl;
				}
				out << "@" << op1Addr << std::endl;
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
				uint16_t op1Addr = pInstance->GetAddress(pStatement->op1.str);
				uint16_t op2Addr = pInstance->GetAddress(pStatement->op2.str);

				// condition
				if (pStatement->type == StatementType::IfVC)
				{
					out << "@" << pStatement->op2.constant << std::endl;
					out << "D=A" << std::endl;
				}
				else
				{
					out << "@" << op2Addr << std::endl;
					out << "D=M" << std::endl;
				}
				out << "@" << op1Addr << std::endl;
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
				ASMBlock initBlock, whileBlock;
				initBlock.Assign(temp, 0);
				whileBlock.AddAssign(temp, temp, 1);
				initBlock.While(temp, pStatement->value, BooleanOp::LessStrict, pStatement->block);
				initBlock.GetASM(out);
			}
			break;

			case StatementType::Break:
			{
				out << "@" << "LOOPEND" << mBreakPoint << std::endl;
				out << "0; JMP" << std::endl;
			}
			break;

			case StatementType::ClearRegion:
			{
				RECT rt = pStatement->rt;
				if (rt.right >= 512 || rt.bottom >= 256)
					return;
				
				// TODO
				
				ASMBlock mainBlock, whileBlock, forBlock;
				/* while chunkAddr < lastChunkAddr
						if (chunkAddr % 512 > rt.left && chunkAddr % 512 < rt.right)
							M[chunkAddr] = 0
						chunkAddr++ */
			}
			break;
        }
    }
}

uint16_t ASMBlock::LoadASMImage(const ASMImage& image)
{
	auto pInstance = AddressManager::GetInstance();
	auto id = pInstance->GetNextUniqueID();
	
	auto unique = std::make_unique<ASMImage>(image.Width(), image.Height());

	mImages[id] = std::move(unique);

	return id;
}

void ASMBlock::ClearRegion(RECT region)
{
	auto statement = std::make_unique<Statement>();
	statement->type = StatementType::ClearRegion;
	statement->rt = region;

	mStatements.push_back(std::move(statement));
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

AddressManager* AddressManager::GetInstance()
{
	if (Instance == nullptr)
		Instance = new AddressManager;
	return Instance;
}

uint16_t AddressManager::GetAddress(const std::string &varName)
{
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

ASMImage::ASMImage(unsigned width, unsigned height) : mWidth(width), mHeight(height), mImageData(width * height / 16)
{
}

void ASMImage::Dot(unsigned x, unsigned y, bool bBlack)
{
	int significance = x % 16;
	char mask = 1 << significance;
	int index = (mWidth / 16) * y + x / 16;
	if (bBlack)
	{
		mImageData[index] |= mask;
	}
	else
	{
		mask = ~mask;
		mImageData[index] &= mask;
	}
}

unsigned ASMImage::Width() const
{
	return mWidth;
}

unsigned ASMImage::Height() const
{
	return mHeight;
}

std::vector<uint16_t> ASMImage::Data() const
{
	return mImageData;
}
