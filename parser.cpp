#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>
#include <map>

using namespace std;

enum TokenType {
T_INT, T_FLOAT, T_DOUBLE, T_STRING, T_BOOL, T_CHAR,
T_ID, T_NUM, T_IF, T_ELSE, T_RETURN,
T_FOR, T_WHILE, T_SWITCH, T_CASE, T_DEFAULT,
T_BREAK, T_CONTINUE,
T_ASSIGN, T_PLUS, T_MINUS, T_MUL, T_DIV,
T_LPAREN, T_RPAREN, T_LBRACE, T_RBRACE,
T_SEMICOLON, T_GT, T_EOF,T_ST,T_PRCT,T_COLON,T_AGAR,T_OR,T_EQ,T_NEQ,T_AND
};


struct Token {
TokenType type;
string value;
int line; // Line number for the token
};

// Function to convert TokenType to string
string tokenTypeToString(TokenType type) {
switch (type) {
case T_INT: return "int";
case T_FLOAT: return "float";
case T_DOUBLE: return "double";
case T_STRING: return "string";
case T_BOOL: return "bool";
case T_CHAR: return "char";
case T_ID: return "identifier";
case T_NUM: return "number";
case T_IF: return "if";
case T_ELSE: return "else";
case T_RETURN: return "return";
case T_ASSIGN: return "=";
case T_PLUS: return "+";
case T_AND: return "&&";
case T_OR: return "||";
case T_EQ: return "==";
case T_NEQ: return "!=";
case T_MINUS: return "-";
case T_MUL: return "*";
case T_DIV: return "/";
case T_PRCT: return "%";
case T_LPAREN: return "(";
case T_RPAREN: return ")";
case T_LBRACE: return "{";
case T_RBRACE: return "}";
case T_SEMICOLON: return ";";
case T_COLON: return ";";
case T_GT: return ">";
case T_ST: return "<";
case T_EOF: return "EOF";
case T_FOR: return "for";
case T_WHILE: return "while";
case T_SWITCH: return "switch";
case T_CASE: return "case";
case T_DEFAULT: return "default";
case T_BREAK: return "break";
case T_CONTINUE: return "continue";
default: return "unknown";
}
}

class Lexer {
private:
string src;
size_t pos;
int line; // Track line number

public:
Lexer(const string &src) {
this->src = src;
this->pos = 0;
this->line = 1; // Initialize line number to 1
}

vector<Token> tokenize() {
vector<Token> tokens;
while (pos < src.size()) {
char current = src[pos];

if (isspace(current)) {
if (current == '\n') line++; // Increment line number on newline
pos++;
continue;
}
if (isdigit(current) || current=='.') {
tokens.push_back(Token{T_NUM, consumeNumber(), line});
continue;
}
if (current == '"') { // Handle string literals
tokens.push_back(Token{T_STRING, consumeString(), line});
continue;
}
if (current == '\'') { // Handle char
tokens.push_back(Token{T_CHAR, consumeChar(), line});
continue;
}
if (isalpha(current)) {
string word = consumeWord();
TokenType type = T_ID;
if (word == "int") type = T_INT;
else if (word == "float") type = T_FLOAT;
else if (word == "double") type = T_DOUBLE;
else if (word == "string") type = T_STRING;
else if (word == "bool") type = T_BOOL;
else if (word == "char") type = T_CHAR;
else if (word == "Agar") type = T_AGAR; // Change from "if" to "Agar"
else if (word == "else") type = T_ELSE;
else if (word == "return") type = T_RETURN;
else if (word == "for") type = T_FOR;
else if (word == "while") type = T_WHILE;
else if (word == "switch") type = T_SWITCH;
else if (word == "case") type = T_CASE;
else if (word == "default") type = T_DEFAULT;
else if (word == "break") type = T_BREAK;
else if (word == "continue") type = T_CONTINUE;
tokens.push_back(Token{type, word, line});
continue;
}


switch (current) {
case '=': tokens.push_back(Token{T_ASSIGN, "=", line}); break;
case '+': tokens.push_back(Token{T_PLUS, "+", line}); break;
case '-': tokens.push_back(Token{T_MINUS, "-", line}); break;
case '*': tokens.push_back(Token{T_MUL, "*", line}); break;
case '/': tokens.push_back(Token{T_DIV, "/", line}); break;
case '%': tokens.push_back(Token{T_PRCT, "%", line}); break;
case '(': tokens.push_back(Token{T_LPAREN, "(", line}); break;
case ')': tokens.push_back(Token{T_RPAREN, ")", line}); break;
case '{': tokens.push_back(Token{T_LBRACE, "{", line}); break;
case '}': tokens.push_back(Token{T_RBRACE, "}", line}); break;
case ';': tokens.push_back(Token{T_SEMICOLON, ";", line}); break;
case ':': tokens.push_back(Token{T_COLON, ":", line}); break;
case '>': tokens.push_back(Token{T_GT, ">", line}); break;
case '<': tokens.push_back(Token{T_ST, "<", line}); break;
case '&&': tokens.push_back(Token{T_AND, "&&", line}); break;
case '||': tokens.push_back(Token{T_OR, "||", line}); break;
case '==': tokens.push_back(Token{T_EQ, "==", line}); break;
case '!=': tokens.push_back(Token{T_NEQ, "!=", line}); break;

default: cout << "Unexpected character: " << current << " at line " << line << endl; exit(1);
}
pos++;
}
tokens.push_back(Token{T_EOF, "", line});
return tokens;
}

string consumeNumber() {
size_t start = pos;
bool hasDecimal = false; // Flag to check for decimal point
while (pos < src.size() && (isdigit(src[pos]) || (src[pos] == '.' && !hasDecimal))) {
if (src[pos] == '.') {
hasDecimal = true; // Set flag when decimal is found
}
pos++;
}
return src.substr(start, pos - start);
}

string consumeWord() {
size_t start = pos;
while (pos < src.size() && isalnum(src[pos])) pos++;
return src.substr(start, pos - start);
}

string consumeString() {
size_t start = pos++;
while (pos < src.size() && src[pos] != '"') pos++;
if (pos < src.size()) pos++; // Skip the closing quote
return src.substr(start + 1, pos - start - 2); // Return the content without quotes
}

string consumeChar() {
size_t start = pos++;
while (pos < src.size() && src[pos] != '\'') {
pos++;
}
if (pos < src.size()) pos++; // Skip the closing quote
return src.substr(start + 1, pos - start - 2); // Return the content without quotes
}


};

class Parser {
public:
    Parser(const vector<Token> &tokens) {
        this->tokens = tokens;
        this->pos = 0;
    }

    void parseProgram() {
        while (tokens[pos].type != T_EOF) {
            parseStatement();
        }
        cout << "Parsing completed successfully! No Syntax Error" << endl;
    }

private:
    vector<Token> tokens;
    size_t pos;

    void parseStatement() {
        if (tokens[pos].type == T_INT || tokens[pos].type == T_FLOAT || 
            tokens[pos].type == T_DOUBLE || tokens[pos].type == T_STRING || 
            tokens[pos].type == T_BOOL || tokens[pos].type == T_CHAR) {
            parseDeclaration(); // Call parseDeclaration to handle variable declaration
        } else if (tokens[pos].type == T_ID) {
            parseAssignment(); // Handle assignment
        } else if (tokens[pos].type == T_IF) {
            parseIfStatement(); // Handle if statements
        } else if (tokens[pos].type == T_RETURN) {
            parseReturnStatement(); // Handle return statements
        } else if (tokens[pos].type == T_LBRACE) {
            parseBlock(); // Handle blocks
        } else if (tokens[pos].type == T_FOR) {
            parseForStatement(); // Handle for loop
        } else if (tokens[pos].type == T_WHILE) {
            parseWhileStatement(); // Handle while loop
        } else if (tokens[pos].type == T_SWITCH) {
            parseSwitchStatement(); // Handle switch statements
        } else {
            cout << "Syntax error: unexpected token " << tokens[pos].value
                 << " at line " << tokens[pos].line << endl;
            exit(1);
        }
    }

    void parseBlock() {
        expect(T_LBRACE);
        while (tokens[pos].type != T_RBRACE && tokens[pos].type != T_EOF) {
            parseStatement();
        }
        expect(T_RBRACE);
    }

    void parseDeclaration() {
        if (tokens[pos].type == T_INT || tokens[pos].type == T_FLOAT ||
            tokens[pos].type == T_DOUBLE || tokens[pos].type == T_STRING ||
            tokens[pos].type == T_BOOL || tokens[pos].type == T_CHAR) {

            expect(tokens[pos].type); // Expect the type (int, float, etc.)
            expect(T_ID); // Expect an identifier (variable name)

            if (tokens[pos].type == T_ASSIGN) { // Check for assignment
                expect(T_ASSIGN); // Expect the assignment operator
                parseExpression(); // Parse the assigned expression
            }

            expect(T_SEMICOLON); // Expect a semicolon at the end of the statement
        } else {
            cout << "Syntax error: expected a type declaration but found "
                 << tokens[pos].value << " at line " << tokens[pos].line << endl;
            exit(1);
        }
    }

    void parseAssignment() {
        expect(T_ID);
        expect(T_ASSIGN);
        parseExpression();
        expect(T_SEMICOLON);
    }

    void parseIfStatement() {
        expect(T_IF);
        expect(T_LPAREN);
        parseExpression();
        expect(T_RPAREN);
        parseStatement();
        if (tokens[pos].type == T_ELSE) {
            expect(T_ELSE);
            parseStatement();
        }
    }

    void parseForStatement() {
        expect(T_FOR);
        expect(T_LPAREN);
        parseAssignment(); // or a separate parse initialization
        expect(T_SEMICOLON);
        parseExpression(); // Loop condition
        expect(T_SEMICOLON);
        parseAssignment(); // Update expression
        expect(T_RPAREN);
        parseStatement();
    }

    void parseWhileStatement() {
        expect(T_WHILE);
        expect(T_LPAREN);
        parseExpression(); // Loop condition
        expect(T_RPAREN);
        parseStatement();
    }

    void parseSwitchStatement() {
        expect(T_SWITCH); // Expecting switch keyword
        expect(T_LPAREN);
        parseExpression(); // Expression to evaluate the switch
        expect(T_RPAREN);
        expect(T_LBRACE); // Opening brace of the switch block

        while (tokens[pos].type == T_CASE || tokens[pos].type == T_DEFAULT) {
            if (tokens[pos].type == T_CASE) {
                expect(T_CASE);
                std::string caseValue = tokens[pos].value; // Get case value
                if (isValueWithinRange(caseValue)) { // Check if the case value is within range
                    parseExpression(); // Expression for case
                    expect(T_COLON); // Expecting colon after case expression
                    parseStatement(); // Parse the statement for this case
                } else {
                    std::cerr << "Warning: Case value " << caseValue << " exceeds range." << std::endl;
                    // Handle error: skip or log, based on your parser's behavior
                    pos++; // Skip to the next token to prevent infinite loop
                }
            } else if (tokens[pos].type == T_DEFAULT) {
                expect(T_DEFAULT);
                expect(T_COLON); // Expecting colon after default
                parseStatement(); // Parse the statement for default
            }
        }
    }

    bool isValueWithinRange(const std::string &value) {
        try {
            int intValue = std::stoi(value); // Convert to integer
            return (intValue >= INT_MIN && intValue <= INT_MAX); // Adjust based on your specific requirements
        } catch (const std::invalid_argument &) {
            return false; // Conversion failed
        } catch (const std::out_of_range &) {
            return false; // Value is out of range for int
        }
    }

    void parseReturnStatement() {
        expect(T_RETURN);
        parseExpression();
        expect(T_SEMICOLON);
    }

    void parseExpression() {
        parseLogicalOr(); // Start with logical OR expressions
    }

    void parseLogicalOr() {
        parseLogicalAnd(); // Handle logical AND first
        while (tokens[pos].type == T_OR) { // Handle ||
            pos++;
            parseLogicalAnd();
        }
    }

    void parseLogicalAnd() {
        parseEquality(); // Handle equality checks first
        while (tokens[pos].type == T_AND) { // Handle &&
            pos++;
            parseEquality();
        }
    }

    void parseEquality() {
        parseRelational(); // Handle relational operators first
        while (tokens[pos].type == T_EQ || tokens[pos].type == T_NEQ) { // Handle == and !=
            pos++;
            parseRelational();
        }
    }

    void parseRelational() {
        parseTerm(); // Handle arithmetic terms first
        while (tokens[pos].type == T_GT || tokens[pos].type == T_ST) { // Handle > and <
            pos++;
            parseTerm();
        }
    }

    void parseTerm() {
        parseFactor(); // Parse factors (numbers, IDs, parentheses)
        while (tokens[pos].type == T_PLUS || tokens[pos].type == T_MINUS) { // Handle + and -
            pos++;
            parseFactor();
        }
    }

    void parseFactor() {
        if (tokens[pos].type == T_NUM || tokens[pos].type == T_ID) {
            pos++; // Consume number or identifier
        } else if (tokens[pos].type == T_LPAREN) {
            expect(T_LPAREN);
            parseExpression(); // Parse the expression within parentheses
            expect(T_RPAREN);
        } else {
            reportError("unexpected token " + tokens[pos].value);
        }
    }

    void expect(TokenType type) {
        if (tokens[pos].type == type) {
            pos++;
        } else {
            reportError("expected " + tokenTypeToString(type) + " but found " + tokens[pos].value);
        }
    }

    void reportError(const string &message) {
        cout << "Syntax error: " << message << " at line " << tokens[pos].line << endl;
        exit(1);
    }
};

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " <Source_code.txt>" << endl;
        return 1;
    }

    cout << "Attempting to open file: " << argv[1] << endl; // Debugging line

    // Read the file
    ifstream file(argv[1]);
    if (!file) {
        cout << "Error: Could not open file " << argv[1] << endl;
        return 1;
    }

    string input((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();

    Lexer lexer(input);
    vector<Token> tokens = lexer.tokenize();

    Parser parser(tokens);
    parser.parseProgram();

    return 0;
}
