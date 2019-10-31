#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Frustum.h"

class Camera
{
public:
	enum Direction {
		FORWARD,
		UP,
		RIGHT,
		BACKWARD,
		DOWN,
		LEFT
	};
public:
	Camera();
public:
	void updateWindowSize(float width, float height);
	void updateMovement(const Direction& dir, float dt);
	void updateRotation(float xOffest, float yOffset);
	const glm::mat4& getProjMatrix() const;
	const glm::mat4 getViewMatrix() const;
	const glm::vec3& getPosition() const;
	const glm::vec3& getForward() const;
	const Frustum& getFrustum() const;
private:
	void calculateVectors();
private:
	glm::vec3 m_position;
	glm::vec3 m_worldUp;
	glm::vec3 m_up;
	glm::vec3 m_front;
	glm::vec3 m_right;

	Frustum m_viewfrustum;
	glm::mat4 m_projMatrix;

	float m_yaw;
	float m_pitch;
	float m_speed;
	float m_sensitivity;
};

