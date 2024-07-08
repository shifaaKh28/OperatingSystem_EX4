#ifndef GUARD_HPP
#define GUARD_HPP

#include "MutexBase.hpp"

/**
 * @class Guard
 * @brief Scope-based guard class for locking and unlocking a mutex.
 *
 * This class locks the mutex in the constructor and unlocks it in the destructor,
 * ensuring proper resource management.
 */
class Guard {
public:
    /**
     * @brief Constructor. Locks the provided mutex.
     * @param mutex Reference to the mutex to be locked.
     */
    explicit Guard(MutexBase& mutex) : mutex(mutex) {
        mutex.lock();
    }

    /**
     * @brief Destructor. Unlocks the mutex.
     */
    ~Guard() {
        mutex.unlock();
    }

private:
    MutexBase& mutex; ///< Reference to the mutex
};

#endif // GUARD_HPP
