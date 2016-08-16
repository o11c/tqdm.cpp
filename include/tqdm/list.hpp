#pragma once

#include <type_traits>

#include "tqdm/fwd.hpp"


namespace tqdm
{
    // CRTP
    template<class Crtp>
    class AtomicNode
    {
        using Node = AtomicNode<Crtp>;
        friend class AtomicList<Crtp>;

        std::atomic<Crtp *> intrusive_link_next;
        std::atomic<Crtp *> intrusive_link_prev;

        AtomicNode(Crtp *next, Crtp *prev);
    public:
        // Crtp is initially unattached
        AtomicNode();
        ~AtomicNode();
    };

    // A non-owning intrusive linked list,
    // using atomics to ensure thread- and signal- safety.
    template<class Crtp>
    class AtomicList
    {
        using Node = AtomicNode<Crtp>;
        AtomicNode<Crtp> meta;
    public:
        AtomicList();
        ~AtomicList();

        void append(Crtp *node);
    };
}


#include "tqdm/list.tcc"
