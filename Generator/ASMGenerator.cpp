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

inline void ASMBlock::GetPointedVal2AReg(std::stringstream & out, const std::string & varName)
{
	auto pInstance = AddressManager::GetInstance();
	out << "@" << pInstance->GetAddress(varName) << std::endl;
	out << "A=M" << std::endl;
}

inline void ASMBlock::GetVal2AReg(std::stringstream & out, const std::string & varName)
{
	auto pInstance = AddressManager::GetInstance();
	out << "@" << pInstance->GetAddress(varName) << std::endl;
}

inline void ASMBlock::LoadAReg(std::stringstream & out, const std::string & varName)
{
	if (varName[0] == '*')
		GetPointedVal2AReg(out, varName.substr(1));
	else
		GetVal2AReg(out, varName);
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
