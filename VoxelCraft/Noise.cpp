#include "stdafx.h"
#include "Noise.h"

Noise::Noise(const std::uint32_t seed, const NoiseProperties& properties)
	: m_seed(seed),
      m_properties(properties),
      m_random(-1,1) {

}

float Noise::getNoiseAt(float x, float z) const {
	float amplitude = 1;
	float frequency = 1;
	float maxValue = 0;
	float total = 0;
	for (int i = 0; i < m_properties.octaves; i++) {
		total += amplitude * getBasicNoise(x * frequency, z * frequency);
		maxValue += amplitude;
		frequency *= m_properties.lacunarity;
		amplitude /= m_properties.persistance;
	}
	return total / maxValue;
}

float Noise::getBasicNoise(float x, float z) const {
	x /= m_properties.smoothness;
	z /= m_properties.smoothness;
	int xi = floor(x);
	int zi = floor(z);

	float xf = x - xi;
	float zf = z - zi;

	auto edgeVec = [&](int xOff, int zOff){
		m_random.seed((xi + xOff) * 298773213 + (zi + zOff) * 907879988 + m_seed);
		float vx, vz;
		vx = m_random.random();
		vz = m_random.random();



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

float Noise::dot(const vec& v1, const vec& v2) const {
	return v1.x * v2.x + v1.z * v2.z;
}

float Noise::lerp(float x, float a, float b) const {
	return a + x * (b -a);
}

float Noise::fade(float t) const {
	return 6 * pow(t, 5) - 15 * pow(t, 4) + 10 * pow(t, 3);
}
