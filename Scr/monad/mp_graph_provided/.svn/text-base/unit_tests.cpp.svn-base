/**
 * MP7 Test Cases.
 * Ported by Jack Toole
 * Provided test cases created by Sean Massung.
 * Ported again by Chase Geigle.
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "png.h"
#include "dsets.h"

#include "mp_part.h"
#if MP_PART(2)
#include "graph.h"
#include "tools.h"
#include "tools_provided.h"
#include "features/edge_weights.h"
#include "features/edge_labels.h"
#include "features/vertex_labels.h"
#endif
#if MP_PART(3)
#include "maze.h"
#include "mazereader.h"
#endif

#include "proxy.h"

using namespace std;
using namespace util;
namespace cs225
{
namespace tools
{
}
}
using namespace cs225;

#define GENERATE_SOLUTIONS 0

#if MP_PART(1)

#if MONAD_SPLIT

UNIT_TEST(addElements1, 25, 1, 5000)
{
    dsets disjSets;
    disjSets.add_elements(4);
    ASSERT_EQUALS(2ul, disjSets.find(2));
}

#endif
#if MONAD_SPLIT

UNIT_TEST(addElements2, 25, 1, 5000)
{
    dsets disjSets;
    disjSets.add_elements(7);
    ASSERT_EQUALS(0ul, disjSets.find(0));
    disjSets.add_elements(3);
    ASSERT_EQUALS(9ul, disjSets.find(9));
}

#endif
#if MONAD_SPLIT

UNIT_TEST(testFindAndSetUnion1, 25, 2, 5000)
{
    dsets disjSets;
    disjSets.add_elements(3);
    disjSets.merge(1, 2);
    ASSERT_EQUALS(disjSets.find(2), disjSets.find(1));
}

#endif
#if MONAD_SPLIT

UNIT_TEST(testFindAndSetUnion2, 25, 2, 5000)
{
    dsets disjSets;
    disjSets.add_elements(7);

    disjSets.merge(4, 1);
    disjSets.merge(2, 3);
    disjSets.merge(6, 5);
    disjSets.merge(1, 3);

    ASSERT_EQUALS(0ul, disjSets.find(0));
    ASSERT_EQUALS(4ul, disjSets.find(1));
    ASSERT_EQUALS(4ul, disjSets.find(2));
    ASSERT_EQUALS(4ul, disjSets.find(3));
    ASSERT_EQUALS(4ul, disjSets.find(4));
    ASSERT_EQUALS(6ul, disjSets.find(5));
    ASSERT_EQUALS(6ul, disjSets.find(6));
}

#endif
#endif // MP_PART(1)

#if MP_PART(2)

using labeled_graph =
    graph<vertex_labels<std::string>, edge_labels<tools::edge_state>>;
using weighted_graph = graph<vertex_labels<std::string>,
                             edge_labels<tools::edge_state>, edge_weights<int>>;

void add_edge(weighted_graph& g, uint64_t v1, uint64_t v2, int weight);

#if MONAD_SPLIT
void add_edge(weighted_graph& g, uint64_t v1, uint64_t v2, int weight)
{
    g.add_edge(vertex{v1}, vertex{v2});
    g.edge_weight(vertex{v1}, vertex{v2}, weight);
}
#endif

//  minWeight - one edge - return value
#if MONAD_SPLIT
UNIT_TEST(minWeight_OneEdge_ReturnValue, 11, 2, 1000)
{
    weighted_graph g;
    auto v1 = g.add_vertex();
    auto v2 = g.add_vertex();
    g.add_edge(v1, v2);
    g.edge_weight(v1, v2, 145);

    tools::print(g);

    ASSERT(tools::min_weight_edge(g) == 145);
}
#endif

//  minWeight - one edge - edge label
#if MONAD_SPLIT
UNIT_TEST(minWeight_OneEdge_EdgeLabel, 11, 2, 1000)
{
    weighted_graph g;
    auto v1 = g.add_vertex();
    auto v2 = g.add_vertex();
    g.add_edge(v1, v2);
    g.edge_weight(v1, v2, 145);

    tools::print(g);

    tools::min_weight_edge(g); // ignore return value
    ASSERT(g.edge_label(v1, v2) == tools::edge_state::MIN);
}
#endif

//  minWeight - multiple edges - return value
#if MONAD_SPLIT

weighted_graph make_graph()
{
    weighted_graph g;
    for (uint8_t i = 0; i < 12; ++i)
        g.add_vertex();

    add_edge(g, 11, 4, 258);
    add_edge(g, 11, 7, 554);
    add_edge(g, 11, 8, 293);
    add_edge(g, 11, 10, 288);

    add_edge(g, 10, 7, 288);

    add_edge(g, 0, 3, 162);
    add_edge(g, 0, 2, 548);

    add_edge(g, 1, 9, 660);
    add_edge(g, 1, 8, 292);

    add_edge(g, 3, 7, 661);

    add_edge(g, 4, 11, 258);
    add_edge(g, 4, 5, 298);
    add_edge(g, 4, 6, 554);

    add_edge(g, 6, 9, 66); // minimum edge

    return g;
}

UNIT_TEST(minWeight_MultiEdge_ReturnValue, 11, 2, 1000)
{
    auto g = make_graph();

    auto es = g.edges();
    for (const auto& e : es)
        g.edge_label(e, tools::edge_state::UNEXPLORED);
    tools::print(g);

    ASSERT(tools::min_weight_edge(g) == 66);
}
#endif

//  minWeight - multiple edges - edge labels
#if MONAD_SPLIT
UNIT_TEST(minWeight_MultiEdge_EdgeLabels, 11, 2, 1000)
{
    auto g = make_graph();

    auto es = g.edges();
    for (const auto& e : es)
        g.edge_label(e, tools::edge_state::UNEXPLORED);
    tools::print(g);

    std::vector<edge> edges{es.begin(), es.end()};
    std::sort(edges.begin(), edges.end(), [&](edge e1, edge e2)
    { return g.edge_weight(e1) < g.edge_weight(e2); });

    tools::min_weight_edge(g); // ignore return value

    std::for_each(edges.begin() + 1, edges.end(), [&](edge e)
    { ASSERT(g.edge_label(e) != tools::edge_state::MIN); });
}
#endif

//  minPath - one edge - return value
#if MONAD_SPLIT
UNIT_TEST(minPath_OneEdge_ReturnValue, 11, 2, 1000)
{
    labeled_graph g;
    auto v1 = g.add_vertex();
    auto v2 = g.add_vertex();
    g.add_edge(v1, v2);
    tools::print(g);

    ASSERT(tools::shortest_path_length(g, v1, v2) == 1);
}
#endif

//  minPath - one edge - edge label
#if MONAD_SPLIT
UNIT_TEST(minPath_OneEdge_EdgeLabel, 11, 2, 1000)
{
    labeled_graph g;
    auto v1 = g.add_vertex();
    auto v2 = g.add_vertex();
    g.add_edge(v1, v2);
    tools::print(g);

    tools::shortest_path_length(g, v1, v2); // ignore return value

    ASSERT(g.edge_label(v1, v2) == tools::edge_state::MINPATH);
}
#endif

//  minPath - multiple edges - return value
#if MONAD_SPLIT
UNIT_TEST(minPath_MultiEdge_ReturnValue, 11, 2, 1000)
{
    labeled_graph g;
    for (uint8_t i = 0; i <= 9; ++i)
        g.add_vertex();

    g.add_edge(vertex{8}, vertex{4});
    g.add_edge(vertex{8}, vertex{6});

    g.add_edge(vertex{7}, vertex{4});
    g.add_edge(vertex{7}, vertex{6});
    g.add_edge(vertex{7}, vertex{0});

    g.add_edge(vertex{5}, vertex{3});

    g.add_edge(vertex{4}, vertex{2});

    g.add_edge(vertex{3}, vertex{0});

    g.add_edge(vertex{2}, vertex{1});

    tools::print(g);

    ASSERT(tools::shortest_path_length(g, vertex{2}, vertex{8}) == 2);
}
#endif

//  minPath - multiple edges - edge labels
#if MONAD_SPLIT
UNIT_TEST(minPath_MultiEdge_EdgeLabels, 11, 2, 1000)
{
    labeled_graph g;
    for (uint8_t i = 0; i <= 9; ++i)
        g.add_vertex();

    g.add_edge(vertex{8}, vertex{4});
    g.add_edge(vertex{8}, vertex{6});

    g.add_edge(vertex{7}, vertex{4});
    g.add_edge(vertex{7}, vertex{6});
    g.add_edge(vertex{7}, vertex{0});

    g.add_edge(vertex{5}, vertex{3});

    g.add_edge(vertex{4}, vertex{2});

    g.add_edge(vertex{3}, vertex{0});

    g.add_edge(vertex{2}, vertex{1});

    for (const auto& e : g.edges())
        g.edge_label(e, tools::edge_state::UNEXPLORED);

    tools::print(g);

    tools::shortest_path_length(g, vertex{2}, vertex{8}); // ignore return value

    edge_set minpath = {{vertex{2}, vertex{4}}, {vertex{4}, vertex{8}}};

    for (const auto& e : g.edges())
    {
        if (minpath.find(e) != minpath.end() ||
            minpath.find(e.reverse()) != minpath.end())
        {
            ASSERT(g.edge_label(e) == tools::edge_state::MINPATH);
        }
        else
        {
            ASSERT(g.edge_label(e) != tools::edge_state::MINPATH);
        }
    }
}
#endif

//  Test Kruskal's
#if MONAD_SPLIT

weighted_graph make_kruskal_graph()
{
    weighted_graph g;
    for (uint8_t i = 0; i < 9; ++i)
        g.add_vertex();

    add_edge(g, 8, 5, 129);
    add_edge(g, 8, 7, 68);
    add_edge(g, 8, 6, 330);
    add_edge(g, 8, 2, 681);

    add_edge(g, 7, 0, 69);
    add_edge(g, 7, 4, 162);
    add_edge(g, 7, 6, 657);

    add_edge(g, 6, 0, 298);
    add_edge(g, 6, 3, 593);
    add_edge(g, 6, 1, 340);

    add_edge(g, 5, 2, 133);
    add_edge(g, 5, 4, 296);
    add_edge(g, 5, 3, 145);
    add_edge(g, 5, 1, 329);

    add_edge(g, 4, 1, 649);
    add_edge(g, 4, 0, 548);

    add_edge(g, 3, 2, 322);

    add_edge(g, 2, 1, 170);

    add_edge(g, 1, 0, 41);

    return g;
}

bool edge_is(edge e1, uint64_t v1, uint64_t v2)
{
    edge test{vertex{v1}, vertex{v2}};
    return e1 == test || e1.reverse() == test;
}

UNIT_TEST(kruskal_all, 12, 3, 1000)
{
    // there are no duplicate weights in this graph
    //  (i.e., there is only one solution)
    auto g = make_kruskal_graph();
    for (const auto& e : g.edges())
        g.edge_label(e, tools::edge_state::UNEXPLORED);

    tools::print(g);

    tools::mark_mst(g);

    // edges in the MST are:
    // (8, 5), (8, 7), (7, 0), (7, 4), (6, 0), (5, 2), (5, 3), (1, 0)
    for (const auto& edge : g.edges())
    {
        if (edge_is(edge, 8, 5) || edge_is(edge, 8, 7) || edge_is(edge, 7, 0) ||
            edge_is(edge, 7, 4) || edge_is(edge, 6, 0) || edge_is(edge, 5, 2) ||
            edge_is(edge, 5, 3) || edge_is(edge, 1, 0))
        {
            ASSERT(g.edge_label(edge) == tools::edge_state::MST);
        }
        else
        {
            ASSERT(g.edge_label(edge) != tools::edge_state::MST);
        }
    }
}
#endif

#endif // MP_PART(2)

#if MP_PART(3)

// m is not const to avoid compilation failures
void assert_maze_acyclic(maze& m, uint64_t width, uint64_t height);
void assert_maze_connected(maze& m, uint64_t width, uint64_t height);
void assert_maze_tree(maze& m, uint64_t width, uint64_t height);
void copyMaze(const MazeReader& source, maze* dest);
void advancePosition(int* x, int* y, direction dir);
epng::png read_solution(const string& filename, uint64_t width,
                        uint64_t height);
epng::png read_unsolved(const string& filename, uint64_t width,
                        uint64_t height);
#define READ_SOLUTION_PNG(width, height)                                       \
    read_solution(string("soln_") + __func__ + string(".png"), width, height)
#define READ_UNSOLVED_PNG(width, height)                                       \
    read_unsolved(string("soln_") + __func__ + string(".png"), width, height)
#define READ_SOLUTION_MAZE(width, height)                                      \
    MazeReader(READ_SOLUTION_PNG(width, height))
#define READ_UNSOLVED_MAZE(widht, height)                                      \
    MazeReader(READ_UNSOLVED_PNG(width, height))

#if MONAD_SPLIT // assert maze helpers
                /**
* Traverse the maze with a DFS, counting the number of recursive calls.
*/
void recDFS(maze& m, vector<vector<uint8_t>>* visited, uint64_t x, uint64_t y,
            uint64_t width, uint64_t height, uint64_t* calls)
{
    (*calls)++;
    if ((*visited)[x][y] != 0)
        return;
    (*visited)[x][y] = 1;

    if (x < width - 1 && m.can_travel(x, y, direction::RIGHT))
        recDFS(m, visited, x + 1, y, width, height, calls);
    if (y < height - 1 && m.can_travel(x, y, direction::DOWN))
        recDFS(m, visited, x, y + 1, width, height, calls);
    if (x > 0 && m.can_travel(x, y, direction::LEFT))
        recDFS(m, visited, x - 1, y, width, height, calls);
    if (y > 0 && m.can_travel(x, y, direction::UP))
        recDFS(m, visited, x, y - 1, width, height, calls);
}

/**
 * Explores the whole maze whether connected or not.
 * @return pair containing (num components, num recursive calls from DFS)
 */
pair<int, int> assert_maze_helper(maze& m, uint64_t width, uint64_t height)
{
    vector<vector<uint8_t>> visited;
    for (uint64_t i = 0; i < width; i++)
        visited.push_back(vector<uint8_t>(height));

    uint64_t components = 0;
    uint64_t calls = 0;

    for (uint64_t i = 0; i < width; i++)
    {
        for (uint64_t j = 0; j < height; j++)
        {
            if (visited[i][j] == 0)
            {
                recDFS(m, &visited, i, j, width, height, &calls);
                components++;
            }
        }
    }

    return make_pair(components, calls);
}

void assert_maze_acyclic(maze& m, uint64_t width, uint64_t height)
{
    pair<int, int> checks = assert_maze_helper(m, width, height);
    uint64_t components = checks.first;
    uint64_t calls = checks.second;
    if (calls + components != width * height * 2)
        FAIL("Maze has a cycle");
}

void assert_maze_connected(maze& m, uint64_t width, uint64_t height)
{
    pair<int, int> checks = assert_maze_helper(m, width, height);
    uint64_t components = checks.first;
    // TODO: This was unused... why?
    // uint64_t calls = checks.second;
    if (components != 1)
        FAIL("Maze is not connected");
}

void assert_maze_tree(maze& m, uint64_t width, uint64_t height)
{
    pair<int, int> checks = assert_maze_helper(m, width, height);
    uint64_t components = checks.first;
    uint64_t calls = checks.second;
    if (calls + components != width * height * 2)
        FAIL("Maze has a cycle");
    if (components != 1)
        FAIL("Maze is not connected");
}

epng::png read_solution(const string& filename, uint64_t width, uint64_t height)
{
    (void)width;
    (void)height;
#if GENERATE_SOLUTIONS
    maze solnMaze{width, height};
    auto out = solnMaze.draw_with_solution();
    out.save(filename);
    return result;
#else
    return {filename};
#endif
}

epng::png read_unsolved(const string& filename, uint64_t width, uint64_t height)
{
    (void)width;
    (void)height;
#if GENERATE_SOLUTIONS
    maze solnMaze{width, height};
    auto out = solnMaze.draw();
    out.save(filename);
    return result;
#else
    return {filename};
#endif
}

void copyMaze(const MazeReader& source, maze* dest)
{
    for (uint64_t x = 0; x < source.getWidth(); x++)
    {
        for (uint64_t y = 0; y < source.getHeight(); y++)
        {
            if (x < source.getWidth() - 1)
            {
                try
                {
                    dest->set_wall(x, y, direction::RIGHT,
                                   source.isWall(x, y, MazeReader::RIGHTWALL));
                }
                catch (...)
                {
                    // nothing
                }
            }
            if (y < source.getHeight() - 1)
            {
                try
                {
                    dest->set_wall(x, y, direction::DOWN,
                                   source.isWall(x, y, MazeReader::DOWNWALL));
                }
                catch (...)
                {
                    // nothing
                }
            }
        }
    }
}

void advancePosition(uint64_t* x, uint64_t* y, direction dir)
{
    if (dir == direction::RIGHT)
        (*x)++;
    else if (dir == direction::DOWN)
        (*y)++;
    else if (dir == direction::LEFT)
        (*x)--;
    else if (dir == direction::UP)
        (*y)--;
}
#endif // end assert maze helpers

#if MONAD_SPLIT
UNIT_TEST(testMakeSmallMaze, 0, 5, 5000)
{
    maze m{2, 2};
    assert_maze_tree(m, 2, 2);
}
#endif

#if MONAD_SPLIT
UNIT_TEST(testMakeMazeConnected, 0, 5, 5000)
{
    maze m{15, 15};
    assert_maze_connected(m, 15, 15);
}
#endif

#if MONAD_SPLIT
UNIT_TEST(testMakeMazeAcyclic, 0, 5, 5000)
{
    maze m{12, 14};
    assert_maze_acyclic(m, 12, 14);
}
#endif

#if MONAD_SPLIT
UNIT_TEST(testMakeMazeTree400, 0, 5, 15000)
{
    maze m{400, 400};
    assert_maze_tree(m, 400, 400);
}
#endif

#if MONAD_SPLIT
UNIT_TEST(testMakeMazeRandom, 0, 5, 10000)
{
    maze m1{42, 47};
    sleep(2);
    maze m2{42, 47};

    for (uint64_t y = 0; y < 47; y++)
    {
        for (uint64_t x = 0; x < 42; x++)
        {
            if (m1.can_travel(x, y, direction::RIGHT) !=
                m2.can_travel(x, y, direction::RIGHT))
                PASS;
            if (m1.can_travel(x, y, direction::DOWN) !=
                m2.can_travel(x, y, direction::DOWN))
                PASS;
        }
    }
    FAIL("Generated the same 42x47 maze twice");
}
#endif

#if MONAD_SPLIT
UNIT_TEST(testSolveMazeValidPath, 0, 10, 5000)
{
    MazeReader soln = READ_SOLUTION_MAZE(25, 25);
    maze m{25, 25};

    copyMaze(soln, &m);
    auto solution = m.solve();

    if (solution.empty())
        FAIL("No solution was generated");

    uint64_t x = 0;
    uint64_t y = 0;
    for (size_t i = 0; i < solution.size(); i++)
    {
        if (soln.isWallInDir(x, y, solution[i]))
            FAIL("Solution passes through walls");
        advancePosition(&x, &y, solution[i]);
    }
}
#endif

#if MONAD_SPLIT
UNIT_TEST(testSolutionBottomRow, 0, 5, 5000)
{
    maze m{15, 15};
    MazeReader soln = READ_SOLUTION_MAZE(15, 15);
    copyMaze(soln, &m);
    auto solution = m.solve();

    uint64_t x = 0;
    uint64_t y = 0;
    for (size_t i = 0; i < solution.size(); i++)
        advancePosition(&x, &y, solution[i]);

    if (y != soln.getDestinationY())
        FAIL("Didn't end up at the bottom row");
}
#endif

#if MONAD_SPLIT
// The MazeReader object must be passed in because READ_SOLUTION uses
// the function name to name the file
void helpSolveMaze(const MazeReader& soln)
{
    maze m{soln.getWidth(), soln.getHeight()};
    copyMaze(soln, &m);
    auto solution = m.solve();

    cout << "first 10 steps in solution:" << endl;
    for (size_t i = 0;
         i < solution.size() && i < soln.getSolutionSize() && i < 10; i++)
    {
        cout << "step " << i << ": actual=" << solution[i]
             << ", expected=" << soln.getSolutionAt(i) << endl;
    }

    ASSERT_EQUALS(soln.getSolutionSize(), solution.size());

    for (size_t i = 0; i < solution.size(); i++)
        if (solution[i] != soln.getSolutionAt(i))
            FAIL("Solution is incorrect");
}
UNIT_TEST(testSolveMazeSmall, 0, 5, 5000)
{
    helpSolveMaze(READ_SOLUTION_MAZE(2, 2));
}
UNIT_TEST(testSolveMazeLarge, 0, 5, 45000)
{
    helpSolveMaze(READ_SOLUTION_MAZE(700, 700));
}
#endif // MONAD_SPLIT

#if MONAD_SPLIT
UNIT_TEST(testDrawMazeSmall, 0, 5, 5000)
{
    auto solnImage = READ_UNSOLVED_PNG(2, 2);
    MazeReader soln(solnImage);
    maze m{2, 2};
    copyMaze(soln, &m);
    auto actualOutput = m.draw();
    actualOutput.save(__func__ + string{".png"});
    ASSERT(actualOutput == solnImage);
}
#endif // MONAD_SPLIT

#if MONAD_SPLIT
UNIT_TEST(testDrawMazeMed, 0, 5, 10000)
{
    auto solnImage = READ_UNSOLVED_PNG(50, 50);
    MazeReader soln(solnImage);
    maze m{50, 50};
    copyMaze(soln, &m);
    auto actualOutput = m.draw();
    actualOutput.save(__func__ + string{".png"});
    ASSERT(actualOutput == solnImage);
}
#endif // MONAD_SPLIT

#if MONAD_SPLIT
UNIT_TEST(testDrawMazeLarge, 0, 5, 25000)
{
    auto solnImage = READ_UNSOLVED_PNG(500, 500);
    MazeReader soln(solnImage);
    maze m{500, 500};
    copyMaze(soln, &m);
    auto actualOutput = m.draw();
    actualOutput.save(__func__ + string{".png"});
    ASSERT(actualOutput == solnImage);
}
#endif // MONAD_SPLIT

#if MONAD_SPLIT
UNIT_TEST(testDrawSolutionMed, 0, 5, 10000)
{
    auto solnImage = READ_SOLUTION_PNG(50, 50);
    MazeReader soln(solnImage);
    maze m{50, 50};
    copyMaze(soln, &m);
    m.solve();
    auto actualOutput = m.draw_with_solution();
    actualOutput.save(__func__ + string{".png"});
    ASSERT(actualOutput == solnImage);
}
#endif

#if MONAD_SPLIT
UNIT_TEST(testDrawSolutionLarge, 0, 5, 30000)
{
    auto solnImage = READ_SOLUTION_PNG(500, 500);
    MazeReader soln(solnImage);
    maze m{500, 500};
    copyMaze(soln, &m);
    m.solve();
    auto actualOutput = m.draw_with_solution();
    actualOutput.save(__func__ + string{".png"});
    ASSERT(actualOutput == solnImage);
}
#endif

#endif // MP_PART(3)
