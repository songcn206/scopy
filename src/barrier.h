#ifndef BARRIER_H
#define BARRIER_H

#include <memory>

namespace adiscope {

class Barrier {
public:
	explicit Barrier(int expected);

	Barrier(const Barrier&) = delete;
	Barrier& operator=(const Barrier&) = delete;

	~Barrier();

	void arriveAndWait();

private:
	struct BarrierPrivate;
	std::unique_ptr<BarrierPrivate> m_private;
};

} // namespace adiscope

#endif // BARRIER_H
