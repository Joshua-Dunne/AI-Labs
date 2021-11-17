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
    void depthFirst(Node* node, std::function<void(Node*)> f_visit);
    void ucs(Node* start, Node* dest, std::vector<Node*>& path);
    void breadthFirst(Node* node);
    void iteration(Node* start, Node* goal, std::vector<int>& path);
    void adaptedBreadthFirst(Node* current, Node* goal);
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
//  Name:           depthFirst
//  Description:    Performs a depth-first traversal on the specified 
//                  node.
//  Arguments:      The first argument is the starting node
//                  The second argument is the processing function.
//  Return Value:   None.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
void Graph<NodeType, ArcType>::depthFirst(Node* node, std::function<void(Node*)> f_visit)
{
    if (nullptr != node) {
        // process the current node and mark it
        f_visit(node);
        node->setMarked(true);

        // go through each connecting node
        auto iter = node->arcList().begin();
        auto endIter = node->arcList().end();

        for (; iter != endIter; ++iter)
        {
            // process the linked node if it isn't already marked.
            if ((*iter).node()->marked() == false)
            {
                depthFirst((*iter).node(), f_visit);
            }
        }
    }
}
// ----------------------------------------------------------------
//  Name:           ucs
//  Description:   finding the cheapest path between the two nodes
//  Arguments:      start node,end node, function to print and vector to store path.
//  Return Value:   None.
// ----------------------------------------------------------------

template<class NodeType, class ArcType>
inline void Graph<NodeType, ArcType>::ucs(Node* start, Node* dest, std::vector<Node*>& path)
{
    if (start != nullptr && dest != nullptr)
    {

        //jack showed me how to do this part
        std::priority_queue<Node*, std::vector<Node*>, NodeComparer<NodeType, ArcType>> pq;
        for (Node* node : m_nodes)
        {
            node->m_data.m_id = std::numeric_limits<int>::max();
            std::cout << "crash 1.25" << std::endl;
        }
        start->m_data.m_id = 0;
        bool goalReached = false;
        pq.push(start);
        start->setMarked(true);
        while (!pq.empty() && pq.top() != dest)
        {
            for (auto arc : pq.top()->arcList())
            {
                if (arc.node() != pq.top()->previous())
                {
                    int distC = (pq.top()->m_data.m_id + arc.weight());//jack showed me how to do this part
                    if (arc.node()->m_data.m_id > distC)
                    {
                        arc.node()->m_data.m_id = distC;

                        arc.node()->setPrevious(pq.top());
                    }
                    if (!arc.node()->marked())
                    {
                        pq.push(arc.node());
                        arc.node()->setMarked(true);
                    }


                }
            }
            pq.pop();
        }

        Node* current = pq.top();
        while (current != nullptr)
        {
            path.push_back(current);

            current = current->previous();

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
void Graph<NodeType, ArcType>::breadthFirst(Node* node)
{
    reset();
    clearMarks();

    for (size_t i = 0; i < m_nodes.size(); i++)
    {
        if (m_nodes[i]->m_data.m_passable)
        {
            m_nodes[i]->m_data.m_id = -1;
            m_nodes[i]->setMarked(false);
        }
        else
        {
            m_nodes[i]->m_data.m_id = 999;
            m_nodes[i]->setMarked(true);
        }
           
    }

    if (nullptr != node)
    {
        std::queue<Node*> nodeQueue;
        // place the first node on the queue, and mark it.
        nodeQueue.push(node);
        node->setMarked(true);
        node->m_data.m_id = 0;

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
                    (*iter).node()->m_data.m_id = nodeQueue.front()->m_data.m_id + 1;
                    (*iter).node()->setMarked(true);
                    nodeQueue.push((*iter).node());
                }
            }
            // dequeue the current node.
            nodeQueue.pop();
        }
    }
}

// ----------------------------------------------------------------
//  Name:           iteration
//  Description:    Using existing id data, get a path to the goal from the start
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
        {
            m_nodes[i]->m_data.m_id = 999;
            m_nodes[i]->setMarked(true);
        }

    }


    for (Node* node : m_nodes)
    {
        // calculate distance to goal node from every node
        if(node->m_data.m_passable)
            node->m_data.m_distance = sqrt(pow(goal->m_data.m_x - node->m_data.m_x, 2) + pow(goal->m_data.m_y - node->m_data.m_y, 2));

    }

    if (nullptr != start && nullptr != goal)
    {
        std::queue<Node*> nodeQueue;
        // place the first node on the queue, and mark it.
        nodeQueue.push(start);
        path.push_back(start->m_data.m_id);

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
                    if ((*iter).node()->m_data.m_id + (*iter).node()->m_data.m_distance
                        < nodeQueue.front()->m_data.m_id + nodeQueue.front()->m_data.m_distance)
                    { // always move towards the next smallest
                        path.push_back((*iter).node()->m_data.m_id);
                        nodeQueue.push((*iter).node());
                        (*iter).node()->setMarked(true);
                    }
                }

                
            }
            // dequeue the current node.
            nodeQueue.pop();

            if (nodeQueue.front() == goal) // if the goal is the front of the queue, don't need to go further
            {
                break;
            }
                
        }
    }
}


// ----------------------------------------------------------------
//  Name:           adaptedBreadthFirst
//  Description:    Performs a breadth-first traversal the starting node
//                  specified as an input parameter, terminating at the goal.
//  Arguments:      The first parameter is the starting node.
//                  The second parameter is the goal node.
//  Return Value:   None.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
void Graph<NodeType, ArcType>::adaptedBreadthFirst(Node* current, Node* goal)
{
    bool goalReached = false;
    std::queue<Node*> nodeQueue;
    nodeQueue.push(current);
    current->setMarked(true);
    if (current != nullptr || goal != nullptr)
    {
        if (current == goal)
        {
            goalReached = true;
            goal->setPrevious(nodeQueue.front());
        }
        else
        {
            while (nodeQueue.size() != 0 && goalReached == false)
            {
                auto iter = nodeQueue.front()->arcList().begin();
                auto endIter = nodeQueue.front()->arcList().end();
                for (; iter != endIter; iter++)
                {
                    if ((*iter).node()->marked() == false)
                    {
                        (*iter).node()->setPrevious(nodeQueue.front());
                        (*iter).node()->setMarked(true);
                        nodeQueue.push((*iter).node());

                        if ((*iter).node() == goal)
                        {
                            goalReached = true;
                            break;


                        }
                    }


                }
                nodeQueue.pop();
            }
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
