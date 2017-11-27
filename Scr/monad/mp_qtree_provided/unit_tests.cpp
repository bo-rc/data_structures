/**
 * mp_qtree Provided Test Cases.
 * Ported by Jack Toole
 * Ported again by Chase Geigle
 */

#include "epng.h"
#include "proxy.h"
#include "quadtree.h"

using namespace std;
using namespace util;
using namespace cs225;

#if MP_PART(1)

// test constructor, decompress
UNIT_TEST(test_outHalf, 5, 2, 1000)
{
    epng::png imgIn("in.png");

    quadtree halfTree(imgIn, 128);
    epng::png imgOut = halfTree.decompress();

    epng::png imgSoln("soln_outHalf.png");
    ASSERT(imgOut == imgSoln);
    PASS;
}

#endif

#if MP_PART(2)

UNIT_TEST(test_pruned_size, 0, 1, 1000)
{
    epng::png imgIn("in.png");
    quadtree fullTree;
    fullTree.build_tree(imgIn, 256);

    ASSERT_EQUALS(65494ul, fullTree.pruned_size(0));
    ASSERT_EQUALS(39256ul, fullTree.pruned_size(100));
    ASSERT_EQUALS(18283ul, fullTree.pruned_size(1000));
    ASSERT_EQUALS(1ul, fullTree.pruned_size(100000));

    PASS;
}

UNIT_TEST(test_ideal_prune, 0, 2, 10000)
{
    epng::png imgIn("in.png");
    quadtree fullTree;
    fullTree.build_tree(imgIn, 256);

    ASSERT_EQUALS(28594ul, fullTree.ideal_prune(1000));
    ASSERT_EQUALS(3521ul, fullTree.ideal_prune(10000));

    PASS;
}

UNIT_TEST(test_rotate_clockwise, 0, 2, 1000)
{
    epng::png imgIn("in.png");
    quadtree fullTree;
    fullTree.build_tree(imgIn, 256);

    fullTree.rotate_clockwise();
    epng::png imgOut = fullTree.decompress();

    epng::png imgSoln("soln_outRotated.png");
    ASSERT(imgOut == imgSoln);
    PASS;
}

UNIT_TEST(test_prune, 0, 1, 1000)
{
    epng::png imgIn("in.png");
    quadtree fullTree;
    fullTree.build_tree(imgIn, 256);

    fullTree.prune(1000);
    epng::png imgOut = fullTree.decompress();

    epng::png imgSoln("soln_outPruned.png");
    ASSERT(imgOut == imgSoln);
    PASS;
}

// test several functions in succession
UNIT_TEST(test_outEtc, 0, 1, 1000)
{
    epng::png imgIn("in.png");
    quadtree fullTree;
    fullTree.build_tree(imgIn, 256);

    quadtree fullTree3(fullTree);
    fullTree3.rotate_clockwise();
    fullTree3.prune(10000);
    fullTree3.rotate_clockwise();
    fullTree3.rotate_clockwise();
    fullTree3.rotate_clockwise();
    epng::png imgOut = fullTree3.decompress();

    epng::png imgSoln("soln_outEtc.png");
    ASSERT(imgOut == imgSoln);
    PASS;
}

// ensure that print still works
UNIT_TEST_OUTPUT(test_printTinyTree, 0, 1, 1000)
{
    epng::png imgIn("in.png");
    quadtree tinyTree(imgIn, 32);
    cout << "Printing tinyTree:\n";
    tinyTree.prune(100);
    tinyTree.print();
    ASSERT_OUTPUT(contains, readFile("soln_tinyTree.out"));
    PASS;
}

#endif
