/**
 * @file parser.cpp
 * @author Chase Geigle
 * @date Summer 2014
 */

#include <cassert>
#include "parser.h"
#include "operation.h"
#include "number.h"
#include "terminal.h"
#include "binary_op.h"
#include "unary_op.h"

namespace cs225
{

/**
 * A "private class" for helping us parse expressions. Maintains all of the
 * state necessary to perform Dijkstra's shunting-yard algorithm.
 *
 * @see https://en.wikipedia.org/wiki/Shunting-yard_algorithm
 */
class parser
{
  public:
    /**
     * @param tokens The tokens to parse
     * @return the root of the parse tree for that expression
     */
    std::unique_ptr<node> parse(queue<std::unique_ptr<token>>& tokens);

  private:
    // add lots of other helper methods here!

    /**
     * The stack to hold the operator tokens encountered. This is the "side
     * rail" in the shunting yard algorithm.
     */
    stack<std::unique_ptr<token>> ops_;

    /**
     * What is this for? It is a mystery (and a hint)!
     */
    stack<std::unique_ptr<node>> nodes_;
};

std::unique_ptr<node> parse(queue<std::unique_ptr<token>>& tokens)
{
    parser p;
    return p.parse(std::move(tokens));
}

std::unique_ptr<node> parser::parse(queue<std::unique_ptr<token>>& tokens)
{
    while (!tokens.empty())
    {
        auto& tok = tokens.front();
        /// @todo handle the token
        tokens.pop();
    }

    /// @todo clean up remaining operators
    /// @todo return the root of your tree
}
}
