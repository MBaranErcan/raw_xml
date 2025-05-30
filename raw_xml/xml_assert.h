#pragma once

#define xml_assert(condition, message)			\
	if(!(condition)) {							\
		__debugbreak();							\
		std::cout << message << std::endl;		\
	}				
