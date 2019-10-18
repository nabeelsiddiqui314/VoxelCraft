#include "stdafx.h"
#include "Game.h"


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
	
	editBlocks();
}

void Game::render(MasterRenderer& renderer) {
	m_world.renderChunks(renderer, m_camera.getFrustum());
	renderer.renderChunks(m_camera);
}

void Game::editBlocks() {
	static bool didclickLeft;
	static bool didclickRight;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && !didclickRight) {
		auto ray = RayCast(m_camera.getPosition(), m_camera.getForward());
		ray.traverse();
		glm::vec3 lastBlock;

		for (int i = 0; i < 10; i++) {
			if (m_world.getBlock(ray.getDestination().x, ray.getDestination().y, ray.getDestination().z) != BlockType::VOID &&
				m_world.getBlock(ray.getDestination().x, ray.getDestination().y, ray.getDestination().z) != BlockType::WATER) {
				m_world.setBlock(lastBlock.x, lastBlock.y, lastBlock.z, BlockType::WATER);
				break;
			}
			else {
				lastBlock = ray.getDestination();
				ray.traverse();
			}
		}
	}
	didclickRight = sf::Mouse::isButtonPressed(sf::Mouse::Right);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !didclickLeft) {
		auto ray = RayCast(m_camera.getPosition(), m_camera.getForward());
		ray.traverse();

		for (int i = 0; i < 10; i++) {
			if (m_world.getBlock(ray.getDestination().x, ray.getDestination().y, ray.getDestination().z) != BlockType::VOID &&
				m_world.getBlock(ray.getDestination().x, ray.getDestination().y, ray.getDestination().z) != BlockType::WATER) {
				m_world.setBlock(ray.getDestination().x, ray.getDestination().y, ray.getDestination().z, BlockType::VOID);
				break;
			}
			else {
				ray.traverse();
			}
		}
	}
	didclickLeft = sf::Mouse::isButtonPressed(sf::Mouse::Left);
}