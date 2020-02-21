#include "Composition.h"

Composition::Composition(const std::vector<Layer>& layers) 
	: m_layers(layers) {}

Voxel::Type Composition::getVoxelAt(int depth) const {
	int layerDepth = 0;
	for (int i = 0; i < m_layers.size(); i++) {
		if (i == m_layers.size() - 1) {
			return m_layers.back().first;
		}

		else if (depth >= layerDepth && depth < layerDepth + m_layers[i].second) { // if the voxel is in bounds
			return m_layers[i].first;
		}
		layerDepth += m_layers[i].second;
	}
	return m_layers.back().first; // never happens
}
