#include "barrier.h"

#include <mutex>
#include <condition_variable>

using namespace adiscope;

struct Barrier::BarrierPrivate {
	std::mutex m_mutex;
	std::condition_variable m_cv;
	int m_count;
	int m_threshold;
	int m_generation;

	BarrierPrivate(int expected)
		: m_count(expected)
		, m_threshold(expected)
		, m_generation(0)
	{}
};

Barrier::Barrier(int expected)
	: m_private(new Barrier::BarrierPrivate(expected))
{}

Barrier::~Barrier() = default;

void Barrier::arriveAndWait()
{
	std::unique_lock<std::mutex> lock(m_private->m_mutex);

	const int gen = m_private->m_generation;
	if (!--m_private->m_count) {
		m_private->m_generation++;
		m_private->m_count = m_private->m_threshold;

		lock.unlock(); // performance
		m_private->m_cv.notify_all();
	} else {
		m_private->m_cv.wait(lock, [this, gen] { return gen != m_private->m_generation; });
	}
}
