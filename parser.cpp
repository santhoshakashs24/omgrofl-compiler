#include "parser.hpp"

static int CurTok;
int getNextToken() {
  return CurTok = gettok();
}

static int GetTokPrecedence() {
  return -1;
}

ExprAST *Error(const char *Str) { fprintf(stderr, "Error: %s\n", Str); return 0;}

static ExprAST *ParseExpression();

/// identifierexpr
///   ::= identifier
///   ::= identifier '(' expression* ')'
static ExprAST *ParseIdentifierExpr() {
  std::string IdName = lastIdentifier();
  fprintf(stderr, "Identifier: %s\n", IdName.c_str());
  return 0;
}

/// expression
///   ::= identifierexpr
static ExprAST *ParseExpression() {
  switch (CurTok) {
    case tok_identifier: return ParseIdentifierExpr();
    default: return Error("unknown token when expecting an expression");
  }
}

static void HandleTopLevelExpression() {
  if (ParseExpression()) {
    fprintf(stderr, "Parsed a top-level expr\n");
  } else {
    getNextToken();
  }
}

/// top ::= definition | external | expression | ';'
void MainLoop() {
  while (1) {
    fprintf(stdout, ">> ");

    switch (CurTok) {
      case tok_eof: fprintf(stdout, "Omgendoffile!\n"); return;
      default:      HandleTopLevelExpression(); break;
    }
  }
}
