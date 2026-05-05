#include "splashkit.h"
#include "utilities.h"

template <typename T>
class node
{
public:
    node *next;
    T data;
};

template <typename T>
class linked_list
{
public:
    node<T> *first;
    node<T> *last;

    linked_list()
    {
        first = nullptr;
        last = nullptr;
    }

    node<T> *add_node(T data)
    {
        node<T> *new_node_ptr = new node<T>();

        new_node_ptr->data = data;
        new_node_ptr->next = nullptr;

        if (first == nullptr)
        {
            first = new_node_ptr;
        }
        else
        {
            last->next = new_node_ptr;
        }

        last = new_node_ptr;

        return new_node_ptr;
    }

    node<T> *find_previous_node(node<T> *target_node)
    {
        if (target_node == first)
        {
            return nullptr;
        }

        node<T> *current = first;

        while (current != nullptr)
        {

            if (current->next == target_node)
            {
                return current;
            }

            current = current->next;
        }

        throw string("find_previous_node search failed: node not in list.");
    }

    void clear()
    {
        node<T> *current = first;

        while (current != nullptr)
        {
            node<T> *next = current->next;

            delete current;
            current = next;
        }
        first = nullptr;
        last = nullptr;
    }

    ~linked_list()
    {
        clear();
    }

    void delete_node(node<T> *target_node)
    {
        if (first == target_node)
        {
            first = target_node->next;
        }
        else
        {
            node<T> *previous_node = find_previous_node(target_node);
            previous_node->next = target_node->next;

            if (last == target_node)
            {
                last = previous_node;
            }
            
        }

        delete target_node;
    }

    void print()
    {
        node<T> *current = first;

        while (current != nullptr)
        {
            node<T> *next = current->next;

            write_line(to_string(current->data));

            current = next;
        }
    }
};

void test_list()
{
    linked_list<int> list;

    // ---- Test first node ----
    node<int> *first_node = list.add_node(2);

    write("This should be 2: ");
    write_line(list.first->data);

    write("This should also be 2: ");
    write_line(first_node->data);

    write("This should also be 2: ");
    write_line(list.last->data);

    // ---- Test adding more nodes ----

    list.add_node(4);
    list.add_node(8);
    list.add_node(16);

    write("This should be 4: ");
    write_line(list.first->next->data);

    write("This should be 8: ");
    write_line(list.first->next->next->data);

    write("This should be 16: ");
    write_line(list.last->data);

    // ---- Test find_previous_node ----

    node<int> *node_a = list.add_node(9);
    node<int> *node_b = list.add_node(18);

    if (list.find_previous_node(node_b) == node_a)
    {
        write_line("Found the correct previous node");
    }
    else
    {
        write_line("Found the wrong previous node");
    }
    
    list.clear();

    node<int> *first_node = list.add_node(1);
    list.add_node(2);
    node<int> *third_node = list.add_node(3);
    list.add_node(4);
    list.add_node(5);

    write_line("Testing deletion:");
    write_line("List contents: (Should be 1 2 3 4 5)");
    list.print();

    list.delete_node(third_node);

    write_line("List contents after deleting third node: (Should be 1 2 4 5)");
    list.print();

    list.delete_node(first_node);

    write_line("List contents after deleting first node: (Should be 2 4 5)");
    list.print();

    list.delete_node(list.last);

    write_line("List contents after deleting last node: (Should be 2 4)");
    list.print();
}

int main()
{
    // test_list();


}