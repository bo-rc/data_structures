/**
 * @file tools.tcc
 * Definition of utility functions on graphs.
 */

#include <limits>
#include <queue>
#include <iostream>

#include "dsets.h"
#include "tools.h"
#include "tools_provided.h"

namespace cs225
{
namespace tools
{

template <class Graph>
typename Graph::edge_weight_type min_weight_edge(Graph& g)
{
    using weight_t = typename Graph::edge_weight_type;
    weight_t min = std::numeric_limits<weight_t>::max();

    auto edge_vector = g.edges();
    auto it = edge_vector.begin();
    edge min_edge{it->source, it->dest};

    vertex_map<vertex_state> vtx_mark;
    for (const auto& v : g.vertices())
        vtx_mark[v] = vertex_state::UNEXPLORED;

    /// @todo your code here

    for (const auto& e : g.edges())
        g.edge_label(e, edge_state::UNEXPLORED);

    // traversal
    std::queue<vertex> q;
    auto v_start = g.start_vertex();
    q.push(v_start);
    vtx_mark[v_start] = vertex_state::VISITED;

    //snapshot snap("snap");

    while(!q.empty())
    {
        auto u = q.front();
        q.pop();

        //snap(g);

        for(const auto& v : g.adjacent(u))
        {
            auto lbl = vtx_mark[v];
            edge uv;
            uv.source = u;
            uv.dest = v;

            if(lbl == vertex_state::UNEXPLORED)
            {
                vtx_mark[v] = vertex_state::VISITED;

                g.edge_label(uv, edge_state::DISCOVERY);
                if(g.edge_weight(uv) <= g.edge_weight(min_edge))
                {
                    min_edge = uv;
                }
                q.push(v);
            }
            else if (g.edge_label(uv) == edge_state::UNEXPLORED)
            {
                g.edge_label(uv, edge_state::CROSS);
                if(g.edge_weight(uv) <= g.edge_weight(min_edge))
                {
                    min_edge = uv;
                }
            }
        }
    }

    g.edge_label(min_edge, edge_state::MIN);
    min = g.edge_weight(min_edge);

    return min;
}

void build_path(vertex_map<vertex>& vm, vertex& dest, vertex& origin, edge_set& es)
{
    if (vm[dest] == origin)
    {
        es.insert({dest, origin});
        return;
    }
    else
    {
        auto mid = vm[dest];
        es.insert({dest, mid});
        dest = mid;
        build_path(vm, dest, origin, es);
    }
}

template <class Graph>
uint64_t shortest_path_length(Graph& g, vertex start, vertex end)
{
    /// @todo your code here
    ///
    if (start == end)
        return 0;

    vertex_map<vertex> vtx_parent;
    for (const auto& v : g.vertices())
        vtx_parent[v] = v;

    vertex_map<vertex_state> vtx_mark;
    for (const auto& v : g.vertices())
        vtx_mark[v] = vertex_state::UNEXPLORED;

    for (const auto& e : g.edges())
        g.edge_label(e, edge_state::UNEXPLORED);

    auto dest = start;
    std::queue<vertex> q;
    q.push(start);
    vtx_mark[start] = vertex_state::VISITED;

    while(!q.empty())
    {
        auto u = q.front();
        q.pop();

        for(const auto& v : g.adjacent(u))
        {
            auto lbl = vtx_mark[v];
            if(lbl == vertex_state::UNEXPLORED)
            {
                vtx_mark[v] = vertex_state::VISITED;

                g.edge_label(u, v, edge_state::DISCOVERY);
                vtx_parent[v] = u; // discovered by u

                if (v == end)
                {
                    dest = end;
                    break;
                }

                q.push(v);
            }
            else if (g.edge_label(u, v) == edge_state::UNEXPLORED)
            {
                g.edge_label(u, v, edge_state::CROSS);
            }
        }
    }

    edge_set es;
    build_path(vtx_parent, dest, start, es);

    for (const auto& e : es)
        g.edge_label(e, edge_state::MINPATH);

    return es.size();
}

template <class Graph>
void mark_mst(Graph& g)
{
    for (const auto& e : minimum_spanning_tree(g))
        g.edge_label(e, edge_state::MST);
}

template <class Graph>
edge_set minimum_spanning_tree(const Graph& g)
{
    // sort all the edges
    struct weighted_edge
    {
        edge arc;
        typename Graph::edge_weight_type weight;
    };

    // initialize PQ for edge selection
    std::vector<weighted_edge> pq;
    for (const auto& e : g.edges())
        pq.push_back({e, g.edge_weight(e)});

    std::sort(pq.begin(), pq.end(),
              [&](const weighted_edge& e1, const weighted_edge& e2)
              {
                  return e1.weight < e2.weight;
              });

    /// @todo your code here
    // initialize set of edges for output
    edge_set edge_output;

    // initialize Dsets so that every vertex is in its own set
    dsets ds;
    vertex_set vs = g.vertices();

    for (auto& v : vs)
    {
        ds.add_elements(v);
    }

    auto itr_pq = pq.cbegin();

    while(edge_output.size() != vs.size()-1)
    {
        edge e = itr_pq++->arc;

        auto v0 = e.source;
        auto v1 = e.dest;

        if(ds.find(v0) != ds.find(v1))
        {
            edge_output.insert(e);
            ds.merge(v0, v1);
        }
    }

    return edge_output;
}

} // namespace tools
} // namespace cs225
