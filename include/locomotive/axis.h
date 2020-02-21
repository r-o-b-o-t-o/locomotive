#ifndef LOCOMOTIVE_AXIS_H 
#define LOCOMOTIVE_AXIS_H

#include "locomotive/locomotive.h"
#include "locomotive/input.h"
#include <vector>

namespace Locomotive {
	class LOCOMOTIVE_API Axis {
	public:
		Axis();
		void addInput( Input&& input);
		void update(int key, int action);
		int getValue()const;
	private:
		std::vector <Input> inputs;
		int value;		
	};
}
#endif