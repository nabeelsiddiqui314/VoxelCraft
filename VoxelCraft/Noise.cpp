#include "stdafx.h"
#include "Noise.h"

Noise::Noise()
	: m_seed(1001010),
	  m_mt(m_rd()),
      m_random(-1, 1) {
	  m_mt.seed(m_seed); 
}

void Noise::setProperties(const NoiseProperties& properties) {
	m_properties = properties;
}

float Noise::getOctaveNoise(float x, float z) {
	float amplitude = 1;
	float frequency = 1;
	float maxValue = 0;
	float total = 0;
	for (int i = 0; i < m_properties.octaves; i++) {
		total += amplitude * getNoiseAt(x * frequency, z * frequency);
		maxValue += amplitude;
		frequency *= m_properties.lacunarity;
		amplitude /= m_properties.persistance;
	}
	return total / maxValue;
}

float Noise::getNoiseAt(float x, float z)  {
	x /= m_properties.smoothness;
	z /= m_properties.smoothness;
	int xi = floor(x);
	int zi = floor(z);

	float xf = x - xi;
	float zf = z - zi;

	auto edgeVec = [&](int xOff, int zOff){
		m_mt.seed((xi + xOff) * 298773213 + (zi + zOff) * 907879988 + m_seed);
		float vx, vz;
		vx = m_random(m_mt);
		vz = m_random(m_mt);

		return vec({ vx, vz });
	};

	auto bLeftE  = edgeVec(0, 0);
	auto bRightE = edgeVec(1, 0);
	auto fLeftE  = edgeVec(0, 1);
	auto fRightE = edgeVec(1, 1);

	vec bLeftD  = {xf    , zf};
	vec bRightD = {xf - 1, zf};
	vec fLeftD  = {xf    , zf - 1};
	vec fRightD = {xf - 1, zf - 1};

	float bLeftDot = dot(bLeftE, bLeftD);
	float bRightDot = dot(bRightE, bRightD);
	float fLeftDot = dot(fLeftE, fLeftD);
	float fRightDot = dot(fRightE, fRightD);

	float u = fade(xf);
	float v = fade(zf);

	float xInter1 = lerp(u, bLeftDot, bRightDot);
	float xInter2 = lerp(u, fLeftDot, fRightDot);

	return m_properties.amplitude * ((lerp(v, xInter1, xInter2) + 1) / 2);
}

float Noise::dot(const vec& v1, const vec& v2) {
	return v1.x * v2.x + v1.z * v2.z;
}

float Noise::lerp(float x, float a, float b) {
	return a + x * (b -a);
}

float Noise::fade(float t) {
	return 6 * pow(t, 5) - 15 * pow(t, 4) + 10 * pow(t, 3);
}
