#pragma once
#include <chrono>
#include <string>

class Timer {

	public:
		Timer(const std::string& label, uint32_t shapeCount);
		~Timer();
	private:
		std::chrono::high_resolution_clock::time_point m_start;
		std::chrono::high_resolution_clock::time_point m_end;
		std::string m_label;
		uint32_t m_shapeCount;
};