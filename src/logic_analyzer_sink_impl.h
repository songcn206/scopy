#ifndef LOGIC_ANALYZER_SINK_IMPL_H
#define LOGIC_ANALYZER_SINK_IMPL_H

#include "logic_analyzer_sink.h"

class logic_analyzer_sink_impl : public logic_analyzer_sink
{
public:
	logic_analyzer_sink_impl(adiscope::logic::LogicAnalyzer *logicAnalyzer, int bufferSize);

	int work(int noutput_items,
	         gr_vector_const_void_star &input_items,
	         gr_vector_void_star &output_items);

private:
	adiscope::logic::LogicAnalyzer *d_logic_analyzer;
	uint16_t *d_buffer;
	int d_buffer_size;
	int d_index;
	int d_end;
};

#endif // LOGIC_ANALYZER_SINK_IMPL_H
