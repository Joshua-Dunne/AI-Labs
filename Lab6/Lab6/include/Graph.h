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
    Graph( int size );
    ~Graph();

    // Accessors
    Node * nodeIndex(int index) const 
	{
		return m_nodes.at(index);
    }

    // Public member functions.
    bool addNode( NodeType data, int index );
    void removeNode( int index );
    bool addArc( int from, int to, ArcType weight );
    void removeArc( int from, int to );
    Arc* getArc( int from, int to );        
    void clearMarks();
    void depthFirst( Node* node, std::function<void(Node *)> f_visit);
    void ucs(Node* start, Node* dest, std::function<void(Node*)> f_visit, std::vector<Node*>& path);
    void breadthFirst( Node* node, std::function<void(Node *)> f_visit);
	void adaptedBreadthFirst( Node* current, Node* goal );	
    void aStar(Node* start, Node* dest, std::function<void(Node*)> f_visit, std::vector<Node*>& path);
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
Graph<NodeType, ArcType>::Graph( int maxNodes ) : m_nodes( maxNodes, nullptr) 
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
   for( int index = 0; index < m_nodes.size(); index++ ) 
   {
        if( m_nodes[index] != nullptr ) 
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
bool Graph<NodeType, ArcType>::addNode( NodeType data, int index ) 
{
   bool nodeNotPresent = false;
   // find out if a node does not exist at that index.
   if ( nullptr == m_nodes.at(index) ) 
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
void Graph<NodeType, ArcType>::removeNode( int index ) 
{
     // Only proceed if node does exist.
     if( nullptr != m_nodes.at(index) ) 
	 {
         // now find every arc that points to the node that
         // is being removed and remove it.        
         Arc* arc;

         // loop through every node
         for( int node = 0; node < m_nodes.size(); node++ ) 
		 {
              // if the node is valid...
              if( nullptr != m_nodes.at(node) ) {
                  // see if the node has an arc pointing to the current node.
                  arc = m_nodes.at(node)->getArc(m_nodes.at(index) );
              }
              // if it has an arc pointing to the current node, then
              // remove the arc.
              if( arc != 0 ) {
                  removeArc( node, index );
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
bool Graph<NodeType, ArcType>::addArc( int from, int to, ArcType weight ) 
{
     bool proceed = true; 
     // make sure both nodes exist.
     if( nullptr == m_nodes.at(from) || nullptr == m_nodes.at(to) ) 
	 {
         proceed = false;
     }
        
     // if an arc already exists we should not proceed
     if( m_nodes.at(from)->getArc( m_nodes.at(to) ) != nullptr ) 
	 {
         proceed = false;
     }

     if (proceed == true) 
	 {
        // add the arc to the "from" node.
		 m_nodes.at(from)->addArc(m_nodes.at(to), weight );
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
void Graph<NodeType, ArcType>::removeArc( int from, int to ) 
{
     // Make sure that the node exists before trying to remove
     // an arc from it.
     bool nodeExists = true;
     if( nullptr == m_nodes.at(from) || nullptr == m_nodes.at(to) ) 
	 {
         nodeExists = false;
     }

     if (nodeExists == true) 
	 {
        // remove the arc.
		 m_nodes.at(from)->removeArc(m_nodes.at(to) );
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
GraphArc<NodeType, ArcType>* Graph<NodeType, ArcType>::getArc( int from, int to ) 
{
     Arc* arc = 0;
     // make sure the to and from nodes exist
     if( nullptr != m_nodes.at(from) && nullptr != m_nodes.at(to) ) 
	 {
         arc = m_nodes.at(from)->getArc(m_nodes.at(to) );
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
     for( int index = 0; index < m_nodes.size(); index++ ) 
	 {
          if( nullptr != m_nodes.at(index) ) 
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
void Graph<NodeType, ArcType>::depthFirst( Node* node, std::function<void(Node *)> f_visit ) 
{
     if( nullptr != node ) {
           // process the current node and mark it
           f_visit( node );
           node->setMarked(true);

           // go through each connecting node
           auto iter = node->arcList().begin(); 
           auto endIter = node->arcList().end();
        
		   for( ; iter != endIter; ++iter) 
		   {
			    // process the linked node if it isn't already marked.
                if ( (*iter).node()->marked() == false ) 
				{
                   depthFirst( (*iter).node(), f_visit);
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
inline void Graph<NodeType, ArcType>::ucs(Node* start, Node* dest, std::function<void(Node*)> f_visit, std::vector<Node*>& path)
{
    if (start != nullptr && dest != nullptr)
    {

    //jack showed me how to do this part
    std::priority_queue<Node*, std::vector<Node*>, NodeComparer<NodeType, ArcType>> pq;
    for (Node* node : m_nodes)
    {
        node->m_data.m_cost = std::numeric_limits<int>::max();
        std::cout << "crash 1.25" << std::endl;
    }
    start->m_data.m_cost = 0;
    bool goalReached = false;
    pq.push(start);
    start->setMarked(true);
    while (!pq.empty() && pq.top() != dest)
    {
        for (auto arc : pq.top()->arcList())
        {
            if (arc.node() != pq.top()->previous())
            {
                int distC = (pq.top()->m_data.m_cost + arc.weight());//jack showed me how to do this part
                if (arc.node()->m_data.m_cost > distC)
                {
                    arc.node()->m_data.m_cost = distC;

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
        for (auto begin = path.rbegin(); begin != path.rend(); begin++)
        {

            f_visit(*begin);
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
void Graph<NodeType, ArcType>::breadthFirst( Node* node, std::function<void(Node *)> f_visit) 
{
   if( nullptr != node ) 
   {
	  std::queue<Node*> nodeQueue;        
	  // place the first node on the queue, and mark it.
      nodeQueue.push( node );
      node->setMarked(true);

      // loop through the queue while there are nodes in it.
      while( nodeQueue.size() != 0 ) 
	  {
         // process the node at the front of the queue.
		 f_visit( nodeQueue.front() );

         // add all of the child nodes that have not been 
         // marked into the queue
         auto iter = nodeQueue.front()->arcList().begin();
         auto endIter = nodeQueue.front()->arcList().end();
         
		 for( ; iter != endIter; iter++ ) 
		 {
              if ( (*iter).node()->marked() == false) 
			  {
				 // mark the node and add it to the queue.
                 (*iter).node()->setMarked(true);
                 nodeQueue.push( (*iter).node() );
              }
         }

         // dequeue the current node.
         nodeQueue.pop();
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
void Graph<NodeType, ArcType>::adaptedBreadthFirst( Node* current, Node *goal ) 
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
void Graph<NodeType, ArcType>::aStar(Node* start, Node* dest, std::function<void(Node*)> f_visit, std::vector<Node*>& path)
{
   
    
      //  Initialise g[start] to 0  For each node v in graph 
      //  GCalculate h[v] // Compute estimated distance to goal for each node.Initialise g[v] to infinity 
                        // Don’t yet know the distances to these nodesAdd start to the pq 
                        // N.B. The pq must sort nodes by their f(n) valuesMark(start)
     //   While the queue is not empty AND pq.top() != goal
     //   For each child node of pq.top()
        //If (child != previous(pq.top())
       //     Let distantChild = h(child) + g(child) // g(child) is actual path cost to child
        //    If ( distantChild < f(child) )
        //    let f[child] = distantChild
          //  Set previous pointer of child to pq.top()
          //  End if
         //   If (notMarked(child))
        //    Add child to the pq Mark(child)
         //   End if
        //    End if
        //    End for
           // Remove pq.top()
       //     End while
    reset();
              clearMarks();

            if (start != nullptr && dest != nullptr)
            {

               
                std::priority_queue<Node*, std::vector<Node*>, NodeComparerTwo<NodeType, ArcType>> pq;

                for (Node* node : m_nodes)
                {
                    node->m_data.m_cost = std::numeric_limits<int>::max()-100000;

                    node->m_data.m_distance = sqrt(pow(dest->m_data.m_x - node->m_data.m_x,2) + pow(dest->m_data.m_y - node->m_data.m_y, 2));

                }
                start->m_data.m_cost = 0;
                bool goalReached = false;
                pq.push(start);

                start->setMarked(true);

                Node* closestNode = dest;
                closestNode->m_data.m_distance = 10000;
                Node* lastNode = nullptr;

                while (!pq.empty() && pq.top() != dest)
                {

                    for (auto arc : pq.top()->arcList())
                    {
                      

                        if (arc.node() != pq.top()->previous())
                        {
                            int distantChild = pq.top()->m_data.m_cost + arc.weight() + arc.node()->m_data.m_distance;

                            if (arc.node()->m_data.m_passable)
                            {
                                if (distantChild < arc.node()->m_data.m_distance + arc.node()->m_data.m_cost)
                                {
                                    arc.node()->m_data.m_cost = pq.top()->m_data.m_cost + arc.weight();

                                    arc.node()->setPrevious(pq.top());

                                }
                            }
                            if (!arc.node()->marked())
                            {

                                pq.push(arc.node());

                                arc.node()->setMarked(true);
                            }


                        }
                    }
                    lastNode = pq.top();
                    if ((lastNode->m_data.m_distance) < (closestNode->m_data.m_distance))
                    {

                        closestNode = lastNode;
                    }
                    pq.pop();

                }

                Node* current = pq.top();
                while (current != nullptr)
                {
                    path.push_back(current);

                    current = current->previous();
                   
                }
                for (auto begin = path.rbegin(); begin != path.rend(); begin++)
                {

                    f_visit(*begin);

                }
            }
}

template<class NodeType, class ArcType>
inline void Graph<NodeType, ArcType>::reset()
{
    for (int index = 0; index < m_nodes.size(); index++)
    {
        
        m_nodes[index]->setPrevious(nullptr);
        
    }
}


#include "GraphNode.h"
#include "GraphArc.h"


#endif
