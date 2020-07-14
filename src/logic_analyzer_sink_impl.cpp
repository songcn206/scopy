#include "logic_analyzer_sink_impl.h"

#include <gnuradio/io_signature.h>

#include <iostream>

using namespace gr;

logic_analyzer_sink::sptr logic_analyzer_sink::make(adiscope::logic::LogicAnalyzer *logicAnalyzer,
						    int bufferSize)
{
	return gnuradio::get_initial_sptr(
				new logic_analyzer_sink_impl(logicAnalyzer, bufferSize));
}

logic_analyzer_sink_impl::logic_analyzer_sink_impl(adiscope::logic::LogicAnalyzer *logicAnalyzer,
						   int bufferSize)
	: sync_block("logic_analyzer_sync",
		     io_signature::make(1, 1, sizeof(uint16_t)),
		     io_signature::make(0, 0, 0))
	, d_logic_analyzer(logicAnalyzer)
	, d_buffer(new uint16_t[bufferSize])
	, d_buffer_size(bufferSize)
	, d_index(0)
	, d_end(d_buffer_size)
{
	memset(d_buffer, 0, sizeof(uint16_t) * d_buffer_size);
}

int logic_analyzer_sink_impl::work(int noutput_items,
				   gr_vector_const_void_star &input_items,
				   gr_vector_void_star &output_items)
{
	// space left in buffer
	const int nfill = d_end - d_index;
	// num items we can put in the buffer
	const int nitems = std::min(noutput_items, nfill);

	const uint16_t *in = static_cast<const uint16_t *>(input_items[0]);

	memcpy(d_buffer + d_index, in, sizeof(uint16_t) * nitems);

	d_index += nitems;

	// filled a buffer let s plot it
	if (d_index == d_end) {
		d_index = 0;
		d_logic_analyzer->setData(d_buffer, d_buffer_size);
	}

	return nitems;
}
