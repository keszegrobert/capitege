using namespace clang;
using namespace clang::ast_matchers;
using namespace clang::driver;
using namespace clang::tooling;

static llvm::cl::OptionCategory MatcherSampleCategory("Class Matcher Sample");

#define ENDL "\n"

class ClassDefinitionHandler : public MatchFinder::MatchCallback {
public:
  ClassDefinitionHandler(Rewriter &Rewrite) : Rewrite(Rewrite) {}

  virtual void run(const MatchFinder::MatchResult &Result) {

      const CXXRecordDecl *recordDecl = Result.Nodes.getNodeAs<clang::CXXRecordDecl>("class");
      if (recordDecl){
          llvm::outs() << "Found class declaration:" << recordDecl->getName() << ENDL;
      }
  }

private:
  Rewriter &Rewrite;
};

// Implementation of the ASTConsumer interface for reading an AST produced
// by the Clang parser. It registers a couple of matchers and runs them on
// the AST.
class MyASTConsumer : public ASTConsumer {
public:
  MyASTConsumer(Rewriter &R) : /*HandlerForIf(R), HandlerForFor(R)*/
    HandleClass(R) {
    // Add a simple matcher for finding 'if' statements.
    Matcher.addMatcher(
        recordDecl(
//        isExpansionInFileMatching("src"),
            isDefinition(),
            unless(hasMethod(isPure()))
          ).bind("class"),&HandleClass
      );
  }

  void HandleTranslationUnit(ASTContext &Context) override {
    // Run the matchers when we have the whole TU parsed.
    Matcher.matchAST(Context);
  }

private:
  ClassDefinitionHandler HandleClass;
  MatchFinder Matcher;
};

// For each source file provided to the tool, a new FrontendAction is created.
class MyFrontendAction : public ASTFrontendAction {
public:
  MyFrontendAction() {}
  void EndSourceFileAction() override {
/*    TheRewriter.getEditBuffer(TheRewriter.getSourceMgr().getMainFileID())
        .write(llvm::outs());*/
  }

  std::unique_ptr<ASTConsumer> CreateASTConsumer(CompilerInstance &CI,
                                                 StringRef file) override {
    TheRewriter.setSourceMgr(CI.getSourceManager(), CI.getLangOpts());
    return llvm::make_unique<MyASTConsumer>(TheRewriter);
  }

private:
  Rewriter TheRewriter;
};
