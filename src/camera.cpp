#include "locomotive/camera.h"
#include "glm/gtc/matrix_transform.hpp"

namespace Locomotive {
	Camera::Camera(float fov, float aspectRatio, float near, float far)
		: fov(fov),
		aspectRatio(aspectRatio),
		near(near),
		far(far) {
		this->updateProjectionMatrix();
	}

	glm::mat4 Camera::getViewMatrix() const {
		//glm::vec3 pos = this->getPosition();
		glm::vec3 pos(0.0f, 0.0f, -3.5f);
		glm::vec3 target(0.0f, 0.0f, 1.0f);
		glm::vec3 up(0.0f, 1.0f, 0.0f);
		return glm::lookAt(pos, target, up);
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
		return this->fov;
	}

	void Camera::setFieldOfView(float fov) {
		this->fov = fov;
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

	void lookAt(const glm::vec3 target) {
		// TODO
	}

	void Camera::updateProjectionMatrix() {
		this->projectionMatrix = glm::perspective(fov, aspectRatio, near, far);
	}
}
