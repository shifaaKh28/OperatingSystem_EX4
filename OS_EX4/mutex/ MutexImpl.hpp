#ifndef MUTEX_IMPL_HPP
#define MUTEX_IMPL_HPP

#include "MutexBase.hpp"
#include <pthread.h>

/**
 * @class MutexImpl
 * @brief Concrete derived class implementing the MutexBase interface using POSIX pthread_mutex.
 *
 * This class ensures a single instance of the mutex is used across the application (Singleton pattern).
 */
class MutexImpl : public MutexBase {
public:
    /**
     * @brief Get the singleton instance of MutexImpl.
     * @return Reference to the singleton instance.
     */
    static MutexImpl& getInstance();

    /**
     * @brief Lock the mutex.
     */
    void lock() override;

    /**
     * @brief Unlock the mutex.
     */
    void unlock() override;

private:
    /**
     * @brief Private constructor.
     */
    MutexImpl();

    /**
     * @brief Destructor.
     */
    ~MutexImpl();

    // Delete copy constructor and assignment operator
    MutexImpl(const MutexImpl&) = delete;
    MutexImpl& operator=(const MutexImpl&) = delete;

    pthread_mutex_t mutex; ///< POSIX mutex
};

#endif // MUTEX_IMPL_HPP
