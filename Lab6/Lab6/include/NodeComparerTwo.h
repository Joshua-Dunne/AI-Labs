#pragma once
#include "GraphNode.h"

///<summary>
///
///</summary>

template<class NodeType, class ArcType>
class NodeComparerTwo
{
public:
	bool operator() (GraphNode<NodeType, ArcType>* first, GraphNode<NodeType, ArcType>* second)
	{
		return first->m_data.m_cost + first->m_data.m_distance < second->m_data.m_cost + second->m_data.m_distance;
	}

};