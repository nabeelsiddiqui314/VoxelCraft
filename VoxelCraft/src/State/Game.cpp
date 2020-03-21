#include "Game.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include "../Renderer/MasterRenderer.h"
#include "../Math/Raycast.h"

Game::Game() {
	m_camera.updateWindowSize(1000, 600);
}

void Game::update(float dt) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		m_camera.updateMovement(Camera::FORWARD, dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		m_camera.updateMovement(Camera::LEFT, dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		m_camera.updateMovement(Camera::BACKWARD, dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		m_camera.updateMovement(Camera::RIGHT, dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
		m_camera.updateMovement(Camera::DOWN, dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		m_camera.updateMovement(Camera::UP, dt);
	}

	static float xLast, yLast;
	
	m_camera.updateRotation(sf::Mouse::getPosition().x - xLast, -sf::Mouse::getPosition().y + yLast);
	xLast = sf::Mouse::getPosition().x;
	yLast = sf::Mouse::getPosition().y;

	m_world.update(m_camera);
	
	editVoxels();
}

void Game::render(MasterRenderer& renderer) {
	m_world.renderSector(renderer, m_camera.getFrustum());
	renderer.renderSegments(m_camera);
}

void Game::editVoxels() {
	static bool didclickLeft;
	static bool didclickRight;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && !didclickRight) {
		auto ray = RayCast(m_camera.getPosition(), m_camera.getForward());
		ray.traverse();
		glm::vec3 lastVoxel;

		for (int i = 0; i < 10; i++) {
			if (m_world.getVoxel(ray.getDestination().x, ray.getDestination().y, ray.getDestination().z) != Voxel::Type::VOID &&
				m_world.getVoxel(ray.getDestination().x, ray.getDestination().y, ray.getDestination().z) != Voxel::Type::WATER) {
				m_world.setVoxel(lastVoxel.x, lastVoxel.y, lastVoxel.z, Voxel::Type::LANTERN);
				break;
			}
			else {
				lastVoxel = ray.getDestination();
				ray.traverse();
			}
		}
	}
	didclickRight = sf::Mouse::isButtonPressed(sf::Mouse::Right);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !didclickLeft) {
		auto ray = RayCast(m_camera.getPosition(), m_camera.getForward());
		ray.traverse();

		for (int i = 0; i < 10; i++) {
			if (m_world.getVoxel(ray.getDestination().x, ray.getDestination().y, ray.getDestination().z) != Voxel::Type::VOID &&
				m_world.getVoxel(ray.getDestination().x, ray.getDestination().y, ray.getDestination().z) != Voxel::Type::WATER) {
				m_world.setVoxel(ray.getDestination().x, ray.getDestination().y, ray.getDestination().z, Voxel::Type::VOID);
				break;
			}
			else {
				ray.traverse();
			}
		}
	}
	didclickLeft = sf::Mouse::isButtonPressed(sf::Mouse::Left);
}