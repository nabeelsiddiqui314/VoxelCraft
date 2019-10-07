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
}

void Game::render(MasterRenderer& renderer) {
	m_world.renderChunks(renderer, m_camera.getFrustum());
	renderer.renderChunks(m_camera);
}
