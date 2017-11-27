/**
 * @file moveonly.h
 * @author Chase Geigle
 * @date Summer 2015
 */

#ifndef CS225_MOVEONLY_
#define CS225_MOVEONLY_

#include <cstdint>

/**
 * A simple type that is move-only, for testing.
 */
class moveonly
{
  public:
    /**
     * moveonly can be default constructed.
     */
    moveonly();

    /**
     * A basic constructor that makes a moveonly from an integer.
     */
    moveonly(uint64_t x);

    /**
     * moveonly can't be copy constructed
     */
    moveonly(const moveonly&) = delete;

    /**
     * moveonly can be moved (default implementation is fine)
     */
    moveonly(moveonly&&) = default;

    /**
     * Moveonly cannot be copy assigned.
     */
    moveonly& operator=(const moveonly&) = delete;

    /**
     * Moveonly can be move assigned (default implementation is fine)
     */
    moveonly& operator=(moveonly&&) = default;

    /**
     * @return the value in the moveonly
     */
    uint64_t get() const;

  private:
    uint64_t x_; /// A value to store
};

#endif
