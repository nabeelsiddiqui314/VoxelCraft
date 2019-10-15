#include "stdafx.h"
#include "Camera.h"

Camera::Camera() 
: m_position(0.0f, 150.0f, 0.0f),
  m_worldUp(0.0f, 1.0f, 0.0f),
  m_up(0.0f, 1.0f, 0.0f),
  m_front(0.0f, 0.0f, 1.0f),
  m_right(1.0f, 0.0f, 0.0f),
  m_yaw(-90.0f),
  m_pitch(0.0f),
  m_speed(20.5f),
  m_sensitivity(0.2f) {
	m_worldUp = m_up;
	calculateVectors();
	m_projMatrix = glm::perspective(glm::radians(70.0f), (float)1000 / (float)600, 0.1f, 1000.0f);
}

void Camera::updateWindowSize(int width, int height) {
	m_projMatrix = glm::perspective(glm::radians(70.0f), (float)width / (float)height, 0.1f, 1000.0f);
}

void Camera::updateMovement(const Direction& dir, float dt) {
	float speed = m_speed * dt;
	if (dir == FORWARD)
		m_position += m_front * speed;
	if (dir == BACKWARD)
		m_position -= m_front * speed;
	if (dir == LEFT)
		m_position -= m_right * speed;
	if (dir == RIGHT)
		m_position += m_right * speed;
	if (dir == UP)
		m_position += m_worldUp * speed;
	if (dir == DOWN)
		m_position -= m_worldUp * speed;
}

void Camera::updateRotation(float xOffset, float yOffset) {
	xOffset *= m_sensitivity;
	yOffset *= m_sensitivity;

	m_yaw += xOffset;
	m_pitch += yOffset;

	if (m_pitch > 89.0f)
		m_pitch = 89.0f;
	if (m_pitch < -89.0f)
		m_pitch = -89.0f;

	calculateVectors();
	m_viewfrustum.updateFrustum(m_projMatrix * getViewMatrix());
}

const glm::mat4& Camera::getProjMatrix() const {
	return m_projMatrix;
}

const glm::mat4 Camera::getViewMatrix() const {
	return glm::lookAt(m_position, m_position + m_front, m_worldUp);
}

const glm::vec3& Camera::getPosition() const {
	return m_position;
}

const glm::vec3 & Camera::getForward() const {
	return m_front;
}

const Frustum & Camera::getFrustum() const {
	return m_viewfrustum;
}

void Camera::calculateVectors() {
	glm::vec3 front;
	front.x = cosf(glm::radians(m_yaw)) * cosf(glm::radians(m_pitch));
	front.y = sinf(glm::radians(m_pitch));
	front.z = sinf(glm::radians(m_yaw)) * cosf(glm::radians(m_pitch));
	m_front = glm::normalize(front);

	m_right = glm::normalize(glm::cross(m_front, m_worldUp));
	m_up = glm::normalize(glm::cross(m_right, m_front));
}
