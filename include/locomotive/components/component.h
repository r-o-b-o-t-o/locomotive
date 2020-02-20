#ifndef LOCOMOTIVE_COMPONENTS_COMPONENT_H
#define LOCOMOTIVE_COMPONENTS_COMPONENT_H

#include "locomotive/locomotive.h"

namespace Locomotive {
class GameObject;

	namespace Components {
		class LOCOMOTIVE_API Component {
		public:
			Component();
			virtual ~Component() = default;

			bool isEnabled() const;
			void setEnabled(bool enabled);

			GameObject* getParent() const;
			void setParent(GameObject* go);

		private:
			bool enabled;
			GameObject* parent;

		};
	}	
}

#endif
