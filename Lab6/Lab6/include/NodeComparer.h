#pragma once
#include "GraphNode.h"

///<summary>
///got help from jack to write this part of the code.
///</summary>

template<class NodeType, class ArcType>
class NodeComparer
{
public:
	bool operator() (GraphNode<NodeType, ArcType>* first, GraphNode<NodeType, ArcType>* second)
	{
		return first->m_data.m_id > second->m_data.m_id;
	}
	
};