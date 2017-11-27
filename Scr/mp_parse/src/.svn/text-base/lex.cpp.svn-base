/**
 * @file lex.cpp
 * @author Chase Geigle
 * @date Summer 2014
 */

#include <cstdint>
#include "lex.h"
#include "number.h"
#include "operation.h"

namespace cs225
{

bool close_paren(token* prev)
{
    return prev && prev->type() == token_type::TEXT && prev->text() == ")";
}

queue<std::unique_ptr<token>> lex(const std::string& line)
{
    queue<std::unique_ptr<token>> tokens;

    token* prev = nullptr;
    std::string val;
    auto flush = [&]()
    {
        if (val.empty())
            return;
        auto tok = make_token<number>(std::move(val));
        prev = tok.get();
        tokens.push(std::move(tok));
    };

    for (uint64_t i = 0; i < line.length(); ++i)
    {
        std::unique_ptr<token> tok;
        switch (line[i])
        {
            case '*':
            case '/':
            case '^':
                flush();
                tok = make_token<operation>(std::string{line[i]});
                break;
            case '-':
                flush();
                if (prev &&
                    (prev->type() == token_type::NUMBER || close_paren(prev)))
                {
                    // binary minus
                    tok = make_token<operation>(std::string{line[i]});
                }
                else
                {
                    // unary minus
                    tok = make_token<operation>("~");
                }
                break;
            case '+':
                flush();
                if (prev &&
                    (prev->type() == token_type::NUMBER || close_paren(prev)))
                {
                    // binary plus
                    tok = make_token<operation>(std::string{line[i]});
                }
                else
                {
                    // unary plus
                    tok = make_token<operation>("#");
                }
                break;
            case '(':
            case ')':
                flush();
                tok = std::make_unique<token>(std::string{line[i]},
                                              token_type::TEXT);
                break;
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            case '.':
            case ',':
                val += line[i];
                break;
            default:
                flush();
                // ignore whitespace
                if (std::isspace(line[i]))
                    continue;
                throw std::runtime_error{std::string{"invalid token: "} +
                                         line[i]};
        }
        if (tok)
        {
            prev = tok.get();
            tokens.push(std::move(tok));
        }
    }
    flush();

    return tokens;
}
}
