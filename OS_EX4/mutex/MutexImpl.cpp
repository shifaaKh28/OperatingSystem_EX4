#include " MutexImpl.hpp"

/**
 * @brief Get the singleton instance of MutexImpl.
 * @return Reference to the singleton instance.
 */
MutexImpl& MutexImpl::getInstance() {
    static MutexImpl instance;
    return instance;
}

/**
 * @brief Private constructor. Initializes the POSIX mutex.
 */
MutexImpl::MutexImpl() {
    pthread_mutex_init(&mutex, nullptr);
}

/**
 * @brief Destructor. Destroys the POSIX mutex.
 */
MutexImpl::~MutexImpl() {
    pthread_mutex_destroy(&mutex);
}

/**
 * @brief Lock the mutex.
 */
void MutexImpl::lock() {
    pthread_mutex_lock(&mutex);
}

/**
 * @brief Unlock the mutex.
 */
void MutexImpl::unlock() {
    pthread_mutex_unlock(&mutex);
}
