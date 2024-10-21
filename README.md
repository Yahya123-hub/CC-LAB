# CC-LAB
The syntax analyzer part of a compiler made in c++


This code implements a simple lexer and parser for a basic programming language with constructs like variable declarations, assignments, conditional statements (`if-else`), and return statements.

### Components Breakdown:
1. **Token Types (`enum TokenType`)**: This defines the various token types such as `T_INT`, `T_ID`, `T_IF`, `T_ASSIGN`, etc., representing keywords, operators, and symbols used in the language.

2. **Token Structure (`struct Token`)**: A token is composed of a `type` (indicating what kind of token it is) and a `value` (the string representation of that token, like "int" or "5").

3. **Lexer**:
- The `Lexer` class is responsible for breaking the input source code into a list of tokens using the `tokenize()` method.
- It processes the input string character by character, identifying keywords, numbers, operators, and symbols.
- It has helper functions like `consumeNumber()` for extracting numeric values and `consumeWord()` for identifying identifiers and keywords.

4. **Parser**:
- The `Parser` class takes the tokens produced by the lexer and builds a syntactic structure from them, checking if the input program is grammatically correct.
- The `parseProgram()` function processes the entire program, parsing one statement at a time using functions like `parseStatement()`, `parseDeclaration()`, `parseAssignment()`, `parseIfStatement()`, and others.
- It uses recursive parsing techniques for expressions and terms, handling arithmetic operations and comparisons.

5. **Error Handling**: Both the lexer and parser detect syntax errors and report unexpected tokens or missing expected tokens.

6. **Main Function**:
- The `main()` function initializes the lexer with a sample input (a small program).
- It tokenizes the input, then parses the tokens to ensure the input conforms to the language's grammar.
- If no syntax errors are found, it outputs "Parsing completed successfully! No Syntax Error."

### Example Program Parsed:
The sample program declared in the `main()` function declares variables `a` and `b`, assigns values, performs an arithmetic operation, and evaluates a conditional `if (b > 10)` with a `return` statement inside the block.
