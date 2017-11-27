#include <iostream>

#include "util.h"

int partial_link(std::string linker, std::vector<std::string> args)
{
    // Linking failed, so we need to determine which of the unit_tests.o.#
    // caused the link failure. We'll do this in linear time by attempting
    // to link an executable against each one individually: if the linker
    // returns success, then we know that particular unit_tests.o.# is
    // valid, so we keep it around for our final link. If it fails, we toss
    // it out.
    //
    // In the end, we'll have a list of all of the unit_tests.o.# files
    // that can successfully link into an executable file, and so we link
    // against all of these at once to create a unit test harness that
    // links against the maximum number of tests possible.

    std::string test_object_name;
    std::vector<std::string> non_unit_args;
    for (const auto& arg : args)
    {
        // skip over unit_tests.o
        auto dot_pos = arg.find_last_of(".");
        auto filename = arg.substr(0, dot_pos);
        if (filename.substr(0, 10) == "unit_tests")
        {
            test_object_name = std::move(filename);
            std::cerr << "skipping unit test object object '" << arg << "'..."
                      << std::endl;
        }
        else
        {
            non_unit_args.push_back(arg);
        }
    }

    if (test_object_name.empty())
    {
        std::cerr << "failed to find unit test object" << std::endl;
        return 1;
    }

    // force partial compilation
    // This is really ugly: we have a special rule in Makefile.proxy for
    // forcing partial compilation to occur, but we need to invoke the
    // right one (for regular unit_tests or for unit_tests-asan).
    std::cerr << "running partial compilation..." << std::endl;
    auto make_ret
        = util::exec("/usr/bin/make", {test_object_name + ".o.partial"});
    if (make_ret != 0)
    {
        std::cerr << "partial compilation failed, cannot partial link"
                  << std::endl;
        return make_ret;
    }

    // find the number of splits, and what type each split is. Each split
    // could either be a regular MONAD_SPLIT, which is used for defining
    // test cases in their own splits, or it could be a MONAD_HELPER_SPLIT,
    // which is used to define helper functions in their own splits. By
    // convention, every MONAD_HELPER_SPLIT will be linked when attempting
    // to partially link.
    //
    // TODO: any way to not hardcode the filename here?
    std::ifstream input{"unit_tests.cpp"};
    std::string line;

    std::vector<std::size_t> helper_splits = {0}; // 0th split is always helper
    std::vector<std::size_t> test_splits;
    std::size_t num_splits = 1;
    while (std::getline(input, line))
    {
        auto tokens = util::tokenize(line, " \t");
        if (tokens.size() >= 2 && tokens[0] == "#if"
            && (tokens[1] == "MONAD_SPLIT"
                || tokens[1] == "MONAD_HELPER_SPLIT"))
        {
            if (tokens[1] == "MONAD_SPLIT")
                test_splits.push_back(num_splits);
            else
                helper_splits.push_back(num_splits);
            ++num_splits;
        }
    }
    std::cout << num_splits << " splits found: " << test_splits.size()
              << " regular, " << helper_splits.size() << " helper..."
              << std::endl;

    for (const auto& hsplit : helper_splits)
        non_unit_args.push_back(test_object_name + ".o."
                                + std::to_string(hsplit));

    // determine whether we can successfully link with each individual
    // test split
    std::vector<std::size_t> successful_splits;
    for (const auto& split_i : test_splits)
    {
        auto link_args = non_unit_args;
        link_args.push_back(test_object_name + ".o." + std::to_string(split_i));

#if 0
        std::cerr << "calling linker: " << linker;
        for (const auto& arg : link_args)
            std::cerr << " " << arg;
        std::cerr << "\n";
#endif

        auto ld_ret = util::exec(linker, link_args);
        if (ld_ret != 0)
            std::cerr << "failed to link split " << split_i << std::endl;
        else
            successful_splits.push_back(split_i);
    }

    // finally link everything back together
    auto ld_args = non_unit_args;
    for (const auto& split : successful_splits)
        ld_args.push_back(test_object_name + ".o." + std::to_string(split));

    auto ld_ret = util::exec(linker, ld_args);
    if (ld_ret != 0)
    {
        std::cerr << "partial linking failed, aborting" << std::endl;
        return ld_ret;
    }

    std::cerr << "partial linking of "
              << successful_splits.size() + helper_splits.size() << " out of "
              << helper_splits.size() + test_splits.size() << " complete"
              << std::endl;
    return 0;
}

int main(int argc, char** argv)
{
    if (argc < 3)
    {
        std::cerr << "ld-monad: missing linker and input file\n"
                  << "Usage:\n\tld-monad linker-exe linker-arg1 "
                     "linker-arg2...\n";
        return 1;
    }

    // First, try just a straight-up, normal link.
    std::vector<std::string> args{argv + 2, argv + argc};
    auto result = util::exec(argv[1], args);
    if (result == 0)
        return 0;

    std::cerr << "ld-monad: initial link failed, attempting "
                 "partial-link...\n";

    return partial_link(argv[1], std::move(args));
}
