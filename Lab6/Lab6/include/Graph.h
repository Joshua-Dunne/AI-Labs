#ifndef GRAPH_H
#define GRAPH_H


#include <list>
#include <queue>
#include <vector>
#include <functional>
#include "NodeComparer.h"
#include "NodeComparerTwo.h"
#include <iostream>
template <class NodeType, class ArcType> class GraphArc;
template <class NodeType, class ArcType> class GraphNode;

// ---------------------------------------------------------------------
//  Name:           Graph
//  Description:    Manages the nodes and connections (arc) between them
// ---------------------------------------------------------------------
template<class NodeType, class ArcType>
class Graph
{
public:
    // typedef the classes to make our lives easier.
    typedef GraphArc<NodeType, ArcType> Arc;
    typedef GraphNode<NodeType, ArcType> Node;

    // Constructor and destructor functions
    Graph(int size);
    ~Graph();

    // Accessors
    Node* nodeIndex(int index) const
    {
        return m_nodes.at(index);
    }

    // Public member functions.
    bool addNode(NodeType data, int index);
    void removeNode(int index);
    bool addArc(int from, int to, ArcType weight);
    void removeArc(int from, int to);
    Arc* getArc(int from, int to);
    void clearMarks();
    void breadthFirst(Node* goal);
    void iteration(Node* start, Node* goal, std::vector<int>& path);
    void flowField();
    void reset();
private:


    // ----------------------------------------------------------------
    //  Description:    A container of all the nodes in the graph.
    // ----------------------------------------------------------------

    std::vector<Node*> m_nodes;

};

// ----------------------------------------------------------------
//  Name:           Graph
//  Description:    Constructor, this constructs an empty graph
//  Arguments:      The maximum number of nodes.
//  Return Value:   None.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
Graph<NodeType, ArcType>::Graph(int maxNodes) : m_nodes(maxNodes, nullptr)
{
}

// ----------------------------------------------------------------
//  Name:           ~Graph
//  Description:    destructor, This deletes every node
//  Arguments:      None.
//  Return Value:   None.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
Graph<NodeType, ArcType>::~Graph() {
    for (size_t index = 0; index < m_nodes.size(); index++)
    {
        if (m_nodes[index] != nullptr)
        {
            delete m_nodes.at(index);
        }
    }
}

// ----------------------------------------------------------------
//  Name:           addNode
//  Description:    This adds a node at a given index in the graph.
//  Arguments:      The first parameter is the data to store in the node.
//                  The second parameter is the index to store the node.
//  Return Value:   true if successful
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
bool Graph<NodeType, ArcType>::addNode(NodeType data, int index)
{
    bool nodeNotPresent = false;
    // find out if a node does not exist at that index.
    if (nullptr == m_nodes.at(index))
    {
        nodeNotPresent = true;
        // create a new node, put the data in it, and unmark it.
        m_nodes.at(index) = new Node;
        m_nodes.at(index)->m_data = data;
        m_nodes.at(index)->setMarked(false);
    }

    return nodeNotPresent;
}

// ----------------------------------------------------------------
//  Name:           removeNode
//  Description:    This removes a node from the graph
//  Arguments:      The index of the node to return.
//  Return Value:   None.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
void Graph<NodeType, ArcType>::removeNode(int index)
{
    // Only proceed if node does exist.
    if (nullptr != m_nodes.at(index))
    {
        // now find every arc that points to the node that
        // is being removed and remove it.        
        Arc* arc;

        // loop through every node
        for (int node = 0; node < m_nodes.size(); node++)
        {
            // if the node is valid...
            if (nullptr != m_nodes.at(node)) {
                // see if the node has an arc pointing to the current node.
                arc = m_nodes.at(node)->getArc(m_nodes.at(index));
            }
            // if it has an arc pointing to the current node, then
            // remove the arc.
            if (arc != 0) {
                removeArc(node, index);
            }
        }


        // now that every arc pointing to the current node has been removed,
        // the node can be deleted.
        delete m_nodes.at(index);
        m_nodes.at(index) = nullptr;
    }
}

// ----------------------------------------------------------------
//  Name:           addArd
//  Description:    Adds an arc from the first index to the 
//                  second index with the specified weight.
//  Arguments:      The first argument is the originating node index
//                  The second argument is the ending node index
//                  The third argument is the weight of the arc
//  Return Value:   true on success.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
bool Graph<NodeType, ArcType>::addArc(int from, int to, ArcType weight)
{
    bool proceed = true;
    // make sure both nodes exist.
    if ((nullptr == m_nodes.at(from) || nullptr == m_nodes.at(to)) && proceed == true)
    {
        proceed = false;
    }

    // if an arc already exists we should not proceed
    if (proceed == true)
    {
        if (m_nodes.at(from)->getArc(m_nodes.at(to)) != nullptr)
        {
            proceed = false;
        }
    }


    if (proceed == true)
    {
        // add the arc to the "from" node.
        m_nodes.at(from)->addArc(m_nodes.at(to), weight);
    }

    return proceed;
}

// ----------------------------------------------------------------
//  Name:           removeArc
//  Description:    This removes the arc from the first index to the second index
//  Arguments:      The first parameter is the originating node index.
//                  The second parameter is the ending node index.
//  Return Value:   None.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
void Graph<NodeType, ArcType>::removeArc(int from, int to)
{
    // Make sure that the node exists before trying to remove
    // an arc from it.
    bool nodeExists = true;
    if (nullptr == m_nodes.at(from) || nullptr == m_nodes.at(to))
    {
        nodeExists = false;
    }

    if (nodeExists == true)
    {
        // remove the arc.
        m_nodes.at(from)->removeArc(m_nodes.at(to));
    }
}


// ----------------------------------------------------------------
//  Name:           getArc
//  Description:    Gets a pointer to an arc from the first index
//                  to the second index.
//  Arguments:      The first parameter is the originating node index.
//                  The second parameter is the ending node index.
//  Return Value:   pointer to the arc, or 0 if it doesn't exist.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
GraphArc<NodeType, ArcType>* Graph<NodeType, ArcType>::getArc(int from, int to)
{
    Arc* arc = 0;
    // make sure the to and from nodes exist
    if (nullptr != m_nodes.at(from) && nullptr != m_nodes.at(to))
    {
        arc = m_nodes.at(from)->getArc(m_nodes.at(to));
    }

    return arc;
}


// ----------------------------------------------------------------
//  Name:           clearMarks
//  Description:    This clears every mark on every node.
//  Arguments:      None.
//  Return Value:   None.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
void Graph<NodeType, ArcType>::clearMarks()
{
    for (size_t index = 0; index < m_nodes.size(); index++)
    {
        if (nullptr != m_nodes.at(index))
        {
            m_nodes.at(index)->setMarked(false);
        }
    }
}

// ----------------------------------------------------------------
//  Name:           breadthFirst
//  Description:    Performs a depth-first traversal the starting node
//                  specified as an input parameter.
//  Arguments:      The first parameter is the starting node
//                  The second parameter is the processing function.
//  Return Value:   None.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
void Graph<NodeType, ArcType>::breadthFirst(Node* goal)
{
    reset();
    clearMarks();

    int count = 1;

    for (size_t i = 0; i < m_nodes.size(); i++)
    {
        if (m_nodes[i]->m_data.m_passable)
        {
            m_nodes[i]->m_data.m_name = -1;
            m_nodes[i]->m_data.m_distance = sqrt(pow(goal->m_data.m_x - m_nodes[i]->m_data.m_x, 2)
                + pow(goal->m_data.m_y - m_nodes[i]->m_data.m_y, 2));
            m_nodes[i]->setMarked(false);
        }
        else
        {
            m_nodes[i]->m_data.m_name = 999;
            m_nodes[i]->m_data.m_cost = 99999;
            m_nodes[i]->setMarked(true);
        }
           
    }

    if (nullptr != goal)
    {
        std::queue<Node*> nodeQueue;
        // place the first node on the queue, and mark it.
        nodeQueue.push(goal);
        goal->setMarked(true);
        goal->m_data.m_name = 0;
        goal->m_data.m_cost = 0;
        goal->m_data.m_id = 0;

        // loop through the queue while there are nodes in it.
        while (nodeQueue.size() != 0)
        {
            // add all of the child nodes that have not been 
            // marked into the queue
            auto iter = nodeQueue.front()->arcList().begin();
            auto endIter = nodeQueue.front()->arcList().end();
            
            for (; iter != endIter; iter++)
            {
                if ((*iter).node()->marked() == false)
                {  
                    (*iter).node()->m_data.m_name = nodeQueue.front()->m_data.m_name + 1;
                    (*iter).node()->m_data.m_cost = (nodeQueue.front()->m_data.m_name + 1) + nodeQueue.front()->m_data.m_distance;
                    (*iter).node()->m_data.m_id = count;
                    (*iter).node()->setMarked(true);
                    nodeQueue.push((*iter).node());

                    count++;
                }
            }
            // dequeue the current node.
            nodeQueue.pop();
        }
    }
}

// ----------------------------------------------------------------
//  Name:           iteration
//  Description:    Using existing data, get a path to the goal from the start
//  Arguments:      The first parameter is the starting node
//                  The second parameter is the goal
//                  The third parameter is the final path.
//  Return Value:   None.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
void Graph<NodeType, ArcType>::iteration(Node* start, Node* goal, std::vector<int>& path)
{
    clearMarks();

    for (size_t i = 0; i < m_nodes.size(); i++)
    {
        if (!m_nodes[i]->m_data.m_passable)
        { // don't bother processing unpassable nodes
            m_nodes[i]->setMarked(true);
        }
    }

    

    if (nullptr != start && nullptr != goal)
    {
        std::queue<Node*> nodeQueue;

        bool goalReached = false;

        // mark the goal and process the list
        goal->m_data.m_name = 0;
        goal->m_data.m_cost = 0;
        goal->m_data.m_distance = 0;
        goal->m_data.m_id = 0;
        //goal->setMarked(true);

        nodeQueue.push(start);

        // loop through the queue while there are nodes in it.
        while (nodeQueue.size() != 0 && goalReached == false)
        {
            // add all of the child nodes that have not been 
            // marked into the queue
            auto iter = nodeQueue.front()->arcList().begin();
            auto endIter = nodeQueue.front()->arcList().end();

            for (; iter != endIter; iter++)
            {
                if ((*iter).node()->marked() == false)
                { // cost is calculated cost + arc weight
                    if ((*iter).node()->m_data.m_cost < nodeQueue.front()->m_data.m_cost)
                    {
                        (*iter).node()->setPrevious(nodeQueue.front());
                        (*iter).node()->setMarked(true);
                        nodeQueue.push((*iter).node());
                    }
                }
            }
            // dequeue the current node.
            nodeQueue.pop();
        }

        Node* current = goal;

        while (current != nullptr)
        {
            path.push_back(current->m_data.m_id);

            current = current->previous();
        }
    }
}

template<class NodeType, class ArcType>
inline void Graph<NodeType, ArcType>::flowField()
{
  
    // loop through the queue while there are nodes in it.
    for(size_t i = 0; i < m_nodes.size(); i++)
    {
        // add all of the child nodes that have not been 
        // marked into the queue
        auto iter = m_nodes[i]->arcList().begin();
        auto endIter = m_nodes[i]->arcList().end();

        Node* best = (*m_nodes[i]->arcList().begin()).node();
        iter++; // take the node on top of the queue as a start
        // and increase the iterator

        for (; iter != endIter; iter++)
        {
            if (m_nodes[i]->m_data.m_name == 0)
                break;
            // we need to decide which node is the best to set a vector towards
                // this will be the node that moves us closer to the goal,
                // but it also can't be any unpassable nodes
                // so we will check for whether the node can be passed or not during
                // if an unpassable node blocks the route to the goal,
                // we'll instead take the next best node with the smallest distance
            if ((*iter).node()->m_data.m_passable)
            { // only filter passable nodes
                if ((*iter).node()->m_data.m_distance < best->m_data.m_distance)
                { // we'll have calculated the distance to the goal previously
                    best = (*iter).node();
                    // save this node for later
                }
            }
        }

        // if the node we're trying to calculate a vector for is the goal,
        // don't calculate one, as we want the vector for the goal to be nothing
        if (m_nodes[i]->m_data.m_name != 0)
        {
            // after doing this, we should have the best node to create our vector for
            // first, we need to get the distance between our current node,
            // and the best node it found
            float length = sqrt(pow(best->m_data.m_x - m_nodes[i]->m_data.m_x, 2)
                + pow(best->m_data.m_y - m_nodes[i]->m_data.m_y, 2));

            // now that we have the length, 
            // we will create a vector which is
            // a directional vector between both points
            sf::Vector2f dir = sf::Vector2f{ static_cast<float>(best->m_data.m_x), static_cast<float>(best->m_data.m_y) }
            - sf::Vector2f{ static_cast<float>(m_nodes[i]->m_data.m_x), static_cast<float>(m_nodes[i]->m_data.m_y) };

            // finally, divide the vector by the length to normalize it
            m_nodes[i]->m_data.m_dir = dir / length;
        }
        else
        {
            m_nodes[i]->m_data.m_dir = sf::Vector2f{ 0.0f, 0.0f };
        }
        
    }
}


template<class NodeType, class ArcType>
inline void Graph<NodeType, ArcType>::reset()
{
    for (size_t index = 0; index < m_nodes.size(); index++)
    {
        m_nodes[index]->setPrevious(nullptr);
    }
}


#include "GraphNode.h"
#include "GraphArc.h"


#endif
