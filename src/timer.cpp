#include "timer.h"
#include <iostream>

Timer::Timer(const std::string& label, uint32_t shapeCount) : 
	m_label(label),
	m_shapeCount(shapeCount),
	m_start(std::chrono::high_resolution_clock::now())
{
}

Timer::~Timer() {
	m_end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(m_end - m_start);
	auto durationPerShape = ((double)duration.count()) / (double)m_shapeCount;
	std::cout << "Timer " << m_label << " duration:\t" << duration.count() << "ns  -  Per instance: " << std::setprecision(15) << durationPerShape << "ns " << std::endl;
}