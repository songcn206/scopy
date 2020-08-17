#include "counting_semaphore.h"

#include <mutex>
#include <condition_variable>

using namespace adiscope;

struct CountingSemaphore::CountingSemaphorePrivate {
	std::mutex m_mutex;
	std::condition_variable m_cv;
	int m_count;
	int m_max;

	CountingSemaphorePrivate(int desired)
		: m_count(desired)
		, m_max(desired)
	{}
};

CountingSemaphore::CountingSemaphore(int desired):
	m_private(new CountingSemaphore::CountingSemaphorePrivate(desired))
{
}

CountingSemaphore::~CountingSemaphore() {}

/* Atomically increments the internal counter by the value of update. Any thread(s) waiting
 * for the counter to be greater than ​0​, such as due to being blocked in acquire,
 * will subsequently be unblocked.
*/
void CountingSemaphore::release(int update)
{
	std::unique_lock<std::mutex> lock(m_private->m_mutex);

	if (m_private->m_count < m_private->m_max) {
		m_private->m_count += update;

		lock.unlock(); // performance
		m_private->m_cv.notify_one();
	}
}

void CountingSemaphore::acquire()
{
	std::unique_lock<std::mutex> lock(m_private->m_mutex);

	m_private->m_cv.wait(lock, [=]{ return 0 < m_private->m_count; });

	m_private->m_count--;
}
