#pragma once
#include <type_traits>

namespace cppjni
{
namespace concepts
{
    template<typename base_element_type_t, typename tag_t = void>
    class StaticList
    {
        struct Node
        {
            Node(base_element_type_t& element, Node*& head)
                :element(element)
            {
                //TODO: compare and swap for thread safety
                next = head;
                head = this;
            }
            Node* next;
            base_element_type_t& element;
        };
        
        friend struct Node;
        
    public:
        class iterator
        {
        public:
            iterator()
                :node(StaticList::getHead())
            {}
            iterator(Node* node)
                :node(node)
            {}
            auto& operator++()
            {
                increment();
                return *this;
            }
            bool operator == (const iterator& i)
            {
                return equal(i);
            }
            bool operator != (const iterator& i)
            {
                return !equal(i);
            }
            base_element_type_t& operator*()
            {
                return dereference();
            }
            const base_element_type_t& operator*() const
            {
                return dereference();
            }
            
        private:
            void increment() { node = node->next; }
            bool equal(const iterator& other) const
            {
                return this->node == other.node;
            }
            
            base_element_type_t& dereference() const { return node->element; }
            
            Node* node;
        };
        
        template<typename element_type_t>
        typename element_type_t::type& get()
        {
            using element_t = typename element_type_t::type;
            static_assert(
                std::is_base_of<base_element_type_t, element_t>::value || std::is_same<base_element_type_t, element_t>::value,
                "Can't add/access element that is not derived from list base element!"
            );
            static element_t element = element_type_t{}();
            static Node node{element, getHead()};
            
            return element;
        }
        
        iterator begin() {return iterator(getHead());}
        
        iterator end() {return iterator(nullptr);}
        
    private:
        static Node*& getHead()
        {
            static Node* head = nullptr;
            return head;
        }
    };
}
}