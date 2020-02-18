#ifndef LOCOMOTIVE_CAMERA_H
#define LOCOMOTIVE_CAMERA_H

#include "locomotive/locomotive.h"
#include "glm/glm.hpp"

namespace Locomotive {
	class LOCOMOTIVE_API Camera {
	public:
		Camera(float fov, float aspectRatio, float near = 0.1f, float far = 1000.0f);

		float getAspectRatio() const;
		void setAspectRatio(float aspectRatio);
		float getFieldOfView() const;
		void setFieldOfView(float fov);
		float getNearClipDistance() const;
		void setNearClipDistance(float near);
		float getFarClipDistance() const;
		void setFarClipDistance(float far);

	private:
		float fov;
		float aspectRatio;
		float near;
		float far;
		glm::mat4 projectionMatrix;

		glm::mat4 getViewMatrix() const;
		void updateProjectionMatrix();
	};
}

#endif