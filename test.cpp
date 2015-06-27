#include "clang/AST/AST.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendActions.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "clang/Rewrite/Core/Rewriter.h"
#include "llvm/Support/raw_ostream.h"

#include "clang/AST/ASTContext.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/FrontendAction.h"

#include "src/findclasses.h"
#include "src/matchersample.h"
#include <gtest/gtest.h>

std::string sample = "class Tagger{\n\
	int m_tag;\n\
public:\n\
	Tagger():m_tag(-1){}\n\
	~Tagger(){m_tag=-1;}\n\
	void SetTag(int t){m_tag = t;}\n\
	int GetTag(){return m_tag;}\n\
};\n";

TEST(matchersample,simple)
{
    clang::tooling::runToolOnCode(new MyFrontendAction, sample.c_str());
}
