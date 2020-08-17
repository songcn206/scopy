#ifndef COUNTING_SEMAPHORE_H
#define COUNTING_SEMAPHORE_H

#include <memory>

namespace adiscope {

class CountingSemaphore {
public:
	explicit CountingSemaphore(int desired);

	CountingSemaphore(const CountingSemaphore&) = delete;
	CountingSemaphore& operator=(const CountingSemaphore&) = delete;

	~CountingSemaphore();

	void release(int update = 1);
	void acquire();

private:
	struct CountingSemaphorePrivate;
	std::unique_ptr<CountingSemaphorePrivate> m_private;
};


} // namespace adiscope

#endif // COUNTING_SEMAPHORE_H
