/**
 * MP5 Provided Test Cases.
 * Ported by Jack Toole
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "png.h"
#include "proxy.h"
#include "kdtree.h"

#if MP_PART(2)
#include "maptiles.h"
#endif

using namespace std;
using namespace util;

#define GENERATE_SOLUTIONS 0

template <int K>
string printTree(const kd_tree<K>& tree)
{
    stringstream output;
    output << tree;
    return output.str();
}

#if GENERATE_SOLUTIONS
#define ASSERT_TREE_EQUALS(tree, filename)                                     \
    do                                                                         \
    {                                                                          \
        string output = printTree(tree);                                       \
        ofstream fout(string(filename).c_str());                               \
        fout << output;                                                        \
        fout.close();                                                          \
    } while (0)
#else
#define ASSERT_TREE_EQUALS(tree, filename)                                     \
    do                                                                         \
    {                                                                          \
        string output = printTree(tree);                                       \
        cout << output;                                                        \
        ASSERT(output == readFile(filename));                                  \
    } while (0)
#endif

#if MP_PART(1)

UNIT_TEST(test_smaller_in_dimension, 4, 3, 5000)
{
    vector<point<3>> pts;
    kd_tree<3> tree(pts);
    point<3> a(1, 2, 3);
    point<3> b(3, 2, 1);

    ASSERT_EQUALS(true, tree.smaller_in_dimension(a, b, 0));
    ASSERT_EQUALS(false, tree.smaller_in_dimension(a, b, 2));
    ASSERT_EQUALS(true, tree.smaller_in_dimension(a, b, 1));
}

UNIT_TEST(test_should_replace, 4, 3, 5000)
{
    vector<point<3>> pts;
    kd_tree<3> tree(pts);

    point<3> target(1, 3, 5);
    point<3> currentBest1(1, 3, 2);
    point<3> possibleBest1(2, 4, 4);
    point<3> currentBest2(1, 3, 6);
    point<3> possibleBest2(2, 4, 4);
    point<3> currentBest3(0, 2, 4);
    point<3> possibleBest3(2, 4, 6);

    ASSERT_EQUALS(true,
                  tree.should_replace(target, currentBest1, possibleBest1));
    ASSERT_EQUALS(false,
                  tree.should_replace(target, currentBest2, possibleBest2));
    ASSERT_EQUALS(false,
                  tree.should_replace(target, currentBest3, possibleBest3));
}

template <int K>
void test_linear_ctor(int size)
{
    vector<point<K>> points;
    points.reserve(size);
    for (int i = 0; i < size; i++)
    {
        point<K> p;
        for (int j = 0; j < K; j++)
            p[j] = i;
        points.push_back(p);
    }

    kd_tree<K> tree(points);

    ASSERT_TREE_EQUALS(tree, "soln_test_linear_ctor_" + to_string(K) + "_" +
                                 to_string(size) + ".out");
}

UNIT_TEST(test_linear_ctor_1_10, 9, 7, 5000)
{
    test_linear_ctor<1>(10);
}
UNIT_TEST(test_linear_ctor_3_31, 9, 7, 5000)
{
    test_linear_ctor<3>(31);
}

template <int K>
void test_linear_nns(int size)
{
    vector<point<K>> points;
    points.reserve(size);
    for (int i = 0; i < size; i++)
    {
        point<K> p;
        for (int j = 0; j < K; j++)
            p[j] = i;
        points.push_back(p);
    }

    kd_tree<K> tree(points);

    for (size_t i = 0; i < points.size(); i++)
        ASSERT_EQUALS(points[i], tree.find_nearest_neighbor(points[i]));
}

UNIT_TEST(test_linear_nns_1_10, 9, 7, 5000)
{
    test_linear_nns<1>(10);
}
UNIT_TEST(test_linear_nns_3_31, 9, 7, 5000)
{
    test_linear_nns<3>(31);
}

UNIT_TEST(test_deceptive_nn_one_level_ctor, 4, 4, 5000)
{
    double coords[6][2] = {
        {-15, 7}, {6, 7}, {-13, -1}, {-5, 0}, {14, -3}, {14, 2}};

    vector<point<2>> points;
    for (int i = 0; i < 6; ++i)
        points.push_back(point<2>(coords[i]));

    kd_tree<2> tree(points);
    ASSERT_TREE_EQUALS(tree, "soln_test_deceptive_nn_one_level_ctor.out");
}

UNIT_TEST(test_deceptive_nn_one_level_nns, 4, 3, 5000)
{
    double coords[6][2] = {
        {-15, 7}, {6, 7}, {-13, -1}, {-5, 0}, {14, -3}, {14, 2}};
    double targetCoords[2] = {-13, 1};
    double expectedCoords[2] = {-13, -1};

    vector<point<2>> points;
    for (int i = 0; i < 6; ++i)
        points.push_back(point<2>(coords[i]));
    point<2> target(targetCoords);
    point<2> expected(expectedCoords);

    kd_tree<2> tree(points);

    ASSERT_EQUALS(expected, tree.find_nearest_neighbor(target));
}

UNIT_TEST(test_mines_ctor, 6, 4, 5000)
{
    //                              NN
    double coords[10][2] = {{-8, 7},
                            {-6, 4},
                            {-5, 6},
                            {-3, 5},
                            {0, 7},
                            {2, -7},
                            {3, 0},
                            {5, -4},
                            {6, -3},
                            {7, -6}};
    //                     M        M       M        M        M
    bool isMine[10] = {false, false, false, false, false,
                       true,  true,  true,  true,  true};

    vector<point<2>> points;
    for (int i = 0; i < 10; ++i)
        points.push_back(point<2>(coords[i], isMine[i]));

    kd_tree<2> tree(points);
    ASSERT_TREE_EQUALS(tree, "soln_test_mines_ctor.out");
}

UNIT_TEST(test_mines_nns, 6, 5, 5000)
{
    //                              NN
    double coords[10][2] = {{-8, 7},
                            {-6, 4},
                            {-5, 6},
                            {-3, 5},
                            {0, 7},
                            {2, -7},
                            {3, 0},
                            {5, -4},
                            {6, -3},
                            {7, -6}};
    //                     M        M       M        M        M
    bool isMine[10] = {false, false, false, false, false,
                       true,  true,  true,  true,  true};
    double targetCoords[2] = {-7, 5};
    double expectedCoords[2] = {-6, 4};

    vector<point<2>> points;
    for (int i = 0; i < 10; ++i)
        points.push_back(point<2>(coords[i], isMine[i]));
    point<2> target(targetCoords);
    point<2> expected(expectedCoords);

    kd_tree<2> tree(points);
    // Turn on land mines to make sure we don't step on them
    point<2>::enable_mines = true;
    ASSERT_EQUALS(expected, tree.find_nearest_neighbor(target));
    point<2>::enable_mines = false;
}

double deceptiveMinesCoords[20][2] = {{84, 44}, // mine
                                      {74, 0},  // mine
                                      {54, 62}, // mine
                                      {59, 0},  // mine
                                      {34, 15}, // mine
                                      {42, 63},
                                      {96, 56}, // mine
                                      {44, 79},
                                      {44, 43},
                                      {28, 10}, // mine
                                      {60, 30}, // mine
                                      {88, 72}, // mine
                                      {75, 68}, // mine
                                      {43, 65},
                                      {48, 0},  // mine
                                      {14, 15}, // mine
                                      {49, 83},
                                      {51, 35},
                                      {95, 50},  // mine
                                      {82, 20}}; // mine
bool deceptiveMinesIsMine[20] = {1, 1, 1, 1, 1, 0, 1, 0, 0, 1,
                                 1, 1, 1, 0, 1, 1, 0, 0, 1, 1};

UNIT_TEST(test_deceptive_mines_ctor, 6, 4, 5000)
{
    double targetCoords[2] = {45, 59};
    double expectedCoords[2] = {42, 63};

    vector<point<2>> points;
    for (int i = 0; i < 20; ++i)
        points.push_back(
            point<2>(deceptiveMinesCoords[i], deceptiveMinesIsMine[i]));
    point<2> target(targetCoords);
    point<2> expected(expectedCoords);

    kd_tree<2> tree(points);
    ASSERT_TREE_EQUALS(tree, "soln_test_deceptive_mines_ctor.out");
}

UNIT_TEST(test_deceptive_mines_nns, 6, 6, 5000)
{
    double targetCoords[2] = {45, 59};
    double expectedCoords[2] = {42, 63};

    vector<point<2>> points;
    for (int i = 0; i < 20; ++i)
        points.push_back(
            point<2>(deceptiveMinesCoords[i], deceptiveMinesIsMine[i]));
    point<2> target(targetCoords);
    point<2> expected(expectedCoords);

    kd_tree<2> tree(points);

    // Turn on land mines to make sure we don't step on them
    point<2>::enable_mines = true;
    ASSERT_EQUALS(expected, tree.find_nearest_neighbor(target));
    point<2>::enable_mines = false;
}

double tieBreakingCoords[14][3] = {{0, 0, 100},   // mine
                                   {0, 100, 100}, // mine
                                   {0, 50, 50},   // mine
                                   {0, 0, 50},    // mine
                                   {100, 0, 100}, // mine
                                   {100, 100, 0},
                                   {0, 0, 0},
                                   {0, 50, 0},  // mine
                                   {50, 0, 0},  // mine
                                   {50, 0, 50}, // mine
                                   {100, 0, 0}, // mine
                                   {50, 50, 0},
                                   {0, 100, 0}, // mine
                                   {50, 50, 50}};

UNIT_TEST(test_tie_breaking_ctor, 6, 4, 5000)
{
    vector<point<3>> points;
    for (int i = 0; i < 14; ++i)
        points.push_back(point<3>(tieBreakingCoords[i]));

    kd_tree<3> tree(points);
    ASSERT_TREE_EQUALS(tree, "soln_test_tie_breaking_ctor.out");
}

UNIT_TEST(test_tie_breaking_nns, 6, 4, 5000)
{
    double targetCoords[3] = {50, 100, 0};
    double expectedCoords[3] = {0, 100, 0};
    double targetCoords2[3] = {14, 17, 20};
    double expectedCoords2[3] = {0, 0, 0};

    vector<point<3>> points;
    for (int i = 0; i < 14; ++i)
        points.push_back(point<3>(tieBreakingCoords[i]));
    point<3> target(targetCoords);
    point<3> expected(expectedCoords);
    point<3> target2(targetCoords2);
    point<3> expected2(expectedCoords2);

    kd_tree<3> tree(points);

    // Turn on land mines to make sure we don't step on them
    point<3>::enable_mines = true;
    ASSERT_EQUALS(expected, tree.find_nearest_neighbor(target));
    ASSERT_EQUALS(expected2, tree.find_nearest_neighbor(target2));
    point<3>::enable_mines = false;
}

double leftRecurseCoords[10][3] = {{5, 3, 1},
                                   {3, 1, 10},
                                   {2, 0, 8},
                                   {4, 3, 0},
                                   {0, 2, 9},
                                   {10, 10, 10},
                                   {11, 11, 11},
                                   {12, 12, 12},
                                   {13, 13, 13},
                                   {14, 14, 14}};

UNIT_TEST(test_left_recurse_ctor, 6, 4, 5000)
{
    double targetCoords[3] = {1, 1, 9};
    double expectedCoords[3] = {0, 2, 9};

    vector<point<3>> points;
    for (int i = 0; i < 10; ++i)
        points.push_back(point<3>(leftRecurseCoords[i]));
    point<3> target(targetCoords);
    point<3> expected(expectedCoords);

    kd_tree<3> tree(points);
    ASSERT_TREE_EQUALS(tree, "soln_test_left_recurse_ctor.out");
}

UNIT_TEST(test_left_recurse_nns, 6, 4, 5000)
{
    double targetCoords[3] = {1, 1, 9};
    double expectedCoords[3] = {0, 2, 9};

    vector<point<3>> points;
    for (int i = 0; i < 10; ++i)
        points.push_back(point<3>(leftRecurseCoords[i]));
    point<3> target(targetCoords);
    point<3> expected(expectedCoords);

    kd_tree<3> tree(points);

    // Turn on land mines to make sure we don't step on them
    point<3>::enable_mines = true;
    ASSERT_EQUALS(expected, tree.find_nearest_neighbor(target));
    point<3>::enable_mines = false;
}

#endif

#if MP_PART(2)
#include "src/maptiles.cpp"

UNIT_TEST(test_checkered_mosaic, 1, 24, 5000)
{
    epng::png source_png("testsource.png");
    source_image source(source_png, 8);

    vector<tile_image> tileList;
    epng::png a(1, 1);
    epng::png b(1, 1);
    epng::png c(1, 1);
    *a(0, 0) = {255, 0, 0};
    *b(0, 0) = {0, 255, 0};
    *c(0, 0) = {0, 0, 255};
    tileList.emplace_back(a);
    tileList.emplace_back(b);
    tileList.emplace_back(c);

    auto canvas = map_tiles(source, tileList);

    epng::png soln_testmaptiles("soln_testmaptiles.png");
    ASSERT(canvas.draw(10) == soln_testmaptiles);
}

#endif
