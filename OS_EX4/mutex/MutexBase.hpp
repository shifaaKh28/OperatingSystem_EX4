#ifndef MUTEX_BASE_HPP
#define MUTEX_BASE_HPP

/**
 * @class MutexBase
 * @brief Abstract base class defining the interface for mutex operations.
 */
class MutexBase {
public:
    /**
     * @brief Virtual destructor.
     */
    virtual ~MutexBase() = default;

    /**
     * @brief Pure virtual method for locking the mutex.
     */
    virtual void lock() = 0;

    /**
     * @brief Pure virtual method for unlocking the mutex.
     */
    virtual void unlock() = 0;
};

#endif // MUTEX_BASE_HPP
