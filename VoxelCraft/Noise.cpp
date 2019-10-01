#include "stdafx.h"
#include "Noise.h"

Noise::Noise() 
	: m_seed(1001010),
	  m_mt(m_rd()),
      m_random(-1, 1) {
	  m_mt.seed(m_seed); 
}

float Noise::getOctaveNoise(int wx, int wz, int lx, int lz, int width) {
	for (int i = 0; i < 3; i++) {
		
	}
	return 0.0f;
}

float Noise::getNoiseAt(int wx, int wz, int lx, int lz, int width, int stretching)  {
	if (wx >= 0) {
		lx = lx + (wx % stretching) * width;
	}
	else {
		//lx = width - 1 - lx;
		//lx = lx + (wx % stretching) * width;
	}

	if (wz >= 0) {
		lz = lz + (wz % stretching) * width;
	}
	else {
		//lz = width - 1 - lz;
		//lz = lz + (wz % stretching) * width;
	}


	wx /= stretching;
	wz /= stretching;
	width *= stretching;

	auto edgeVec = [&](int xOff, int zOff){
		m_mt.seed((wx + xOff) * 298773213 + (wz  + zOff) * 907879988 + m_seed);
		float x, z;
		x = m_random(m_mt);
		z = m_random(m_mt);

		return vec({ x,z });
	};

	auto bLeftE  = edgeVec(0, 0);
	auto bRightE = edgeVec(1, 0);
	auto fLeftE  = edgeVec(0, 1);
	auto fRightE = edgeVec(1, 1);

	vec bLeftD  = {(float)(lx        )  / (float)width, (float)(lz        )  / (float)width};
	vec bRightD = {(float)(lx - width)  / (float)width, (float)(lz        )  / (float)width};
	vec fLeftD  = {(float)(lx        )  / (float)width, (float)(lz - width)  / (float)width};
	vec fRightD = {(float)(lx - width)  / (float)width, (float)(lz - width)  / (float)width};

	float bLeftDot = dot(bLeftE, bLeftD);
	float bRightDot = dot(bRightE, bRightD);
	float fLeftDot = dot(fLeftE, fLeftD);
	float fRightDot = dot(fRightE, fRightD);

	float u = fade((float)lx / (float)width);
	float v = fade((float)lz / (float)width);

	float xInter1 = lerp(u, bLeftDot, bRightDot);
	float xInter2 = lerp(u, fLeftDot, fRightDot);

	return (lerp(v, xInter1, xInter2) + 1) / 2;
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
