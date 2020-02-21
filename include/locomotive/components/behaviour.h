#ifndef LOCOMOTIVE_COMPONENTS_BEHAVIOUR_H
#define LOCOMOTIVE_COMPONENTS_BEHAVIOUR_H

#include "locomotive/locomotive.h"
#include "locomotive/components/component.h"

namespace Locomotive {
namespace Components {
	class LOCOMOTIVE_API Behaviour : public Component {
	public:
		Behaviour() = default;
		virtual ~Behaviour() = default;

		virtual void start() = 0;
		virtual void update(float deltaTime) = 0;
	};
}
}

#endif
