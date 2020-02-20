#include "locomotive/components/camera.h"
#include "glm/gtc/matrix_transform.hpp"

namespace Locomotive {
namespace Components {
	Camera::Camera(float fov, float aspectRatio, float near, float far)
		  : fov(glm::radians(fov)),
			aspectRatio(aspectRatio),
			near(near),
			far(far) {
		this->updateProjectionMatrix();
	}

	glm::mat4 Camera::getViewMatrix() {
		return glm::inverse(this->getParent()->getTransform().getTransformMatrix());
	}

	const glm::mat4 &Camera::getProjectionMatrix() const {
		return this->projectionMatrix;
	}

	float Camera::getAspectRatio() const {
		return this->aspectRatio;
	}

	void Camera::setAspectRatio(float aspectRatio) {
		this->aspectRatio = aspectRatio;
		this->updateProjectionMatrix();
	}

	float Camera::getFieldOfView() const {
		return glm::degrees(this->fov);
	}

	void Camera::setFieldOfView(float fov) {
		this->fov = glm::radians(fov);
		this->updateProjectionMatrix();
	}

	float Camera::getNearClipDistance() const {
		return this->near;
	}

	void Camera::setNearClipDistance(float near) {
		this->near = near;
		this->updateProjectionMatrix();
	}

	float Camera::getFarClipDistance() const {
		return this->far;
	}

	void Camera::setFarClipDistance(float far) {
		this->far = far;
		this->updateProjectionMatrix();
	}

	void Camera::updateProjectionMatrix() {
		this->projectionMatrix = glm::perspective(fov, aspectRatio, near, far);
	}
}
}
