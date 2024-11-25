#include "neo_pch.hpp"
#include "NeoInfused/data_structures/neo_layer-storage.hpp"

namespace neo {
	namespace layer {
		bool storage_t::_Greater(layer_t* left, layer_t* right)
		{ return left->priority > right->priority; }

		storage_t::~storage_t(void)
		{
			for (layer_t* layer : m_Layers)
				delete layer;
		}
		void storage_t::clear(void)
		{
			for (layer_t* layer : m_Layers)
				delete layer;
			m_Layers.clear();
		}
		layer_t* storage_t::_push(layer_t* layer)
		{
			m_Layers.emplace_back(layer);
			this->_resort();
			return layer;
		}
		void storage_t::destroy_layer(layer_t* layer)
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

		void storage_t::set_priority(layer_t* layer, int32_t new_priority)
		{
			layer->priority = new_priority;
			this->_resort();
		}
	} // namespace layer
} // namespace neo
