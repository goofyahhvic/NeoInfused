#include "neo_pch.hpp"
#include "NeoInfused/data_structures/neo_layer-storage.hpp"

namespace neo {
	bool LayerStorage::_Greater(Layer* left, Layer* right)
	{ return left->m_Priority > right->m_Priority; }

	LayerStorage::~LayerStorage(void)
	{
		for (Layer* layer : m_Layers)
			delete layer;
	}
	void LayerStorage::clear(void)
	{
		for (Layer* layer : m_Layers)
			delete layer;
		m_Layers.clear();
	}
	Layer* LayerStorage::_push(Layer* layer)
	{
		m_Layers.push_back(layer);
		this->_resort();
		return layer;
	}
	void LayerStorage::destroy_layer(Layer* layer)
	{
		for (auto it = m_Layers.begin(); it != m_Layers.end(); it++)
		{
			if (*it == layer)
			{
				m_Layers.erase(it);
				delete layer;
				return;
			}
		}
	}

	void LayerStorage::set_priority(Layer* layer, int32_t new_priority)
	{
		layer->m_Priority = new_priority;
		this->_resort();
	}
} // namespace neo
