#ifndef LOCOMOTIVE_INPUT_H
#define LOCOMOTIVE_INPUT_H

#include "locomotive/locomotive.h"

namespace Locomotive {
	class LOCOMOTIVE_API Input {
	public:
		Input();
		Input(int positive, int negative=-1);
		int update(int key)const;
		
	private:
		int positive : 16;
		int negative : 16;
	};
}
#endif