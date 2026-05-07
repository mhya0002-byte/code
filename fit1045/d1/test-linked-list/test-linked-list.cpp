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

    node<T> *append_node(T data)
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

    node<T> *prepend_node(T data)
    {
        node<T> *new_node_ptr = new node<T>();

        new_node_ptr->data = data;
        new_node_ptr->next = first;

        first = new_node_ptr;

        if (last == nullptr)
        {
            last = new_node_ptr;
        }

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

    node<T> *node_at_index(int index)
    {
        node<T> *current = first;

        for (int i = 0; i < index - 1; i++)
        {
            current = current->next;
        }

        return current;
    }

    node<T> *insert_after_node(T data, node<T> *target_node)
    {
        node<T> *new_node_ptr = new node<T>();

        new_node_ptr->data = data;
        new_node_ptr->next = target_node->next;

        target_node->next = new_node_ptr;

        return new_node_ptr;
    }

    node<T> *insert_before_node(T data, node<T> *target_node)
    {
        node<T> *new_node_ptr = new node<T>();

        new_node_ptr->data = data;

        find_previous_node(target_node)->next = new_node_ptr;

        new_node_ptr->next = target_node;

        return new_node_ptr;
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
        int i = 1;

        node<T> *current = first;

        while (current != nullptr)
        {
            node<T> *next = current->next;

            write_line(to_string(i) + ": " + to_string(current->data));

            current = next;

            i++;
        }
        write_line();
    }
};

void test_list()
{
    linked_list<int> list;

    // ---- Test first node ----
    node<int> *first_node = list.append_node(2);

    write("This should be 2: ");
    write_line(list.first->data);

    write("This should also be 2: ");
    write_line(first_node->data);

    write("This should also be 2: ");
    write_line(list.last->data);

    // ---- Test adding more nodes ----

    list.append_node(4);
    list.append_node(8);
    list.append_node(16);

    write("This should be 4: ");
    write_line(list.first->next->data);

    write("This should be 8: ");
    write_line(list.first->next->next->data);

    write("This should be 16: ");
    write_line(list.last->data);
}

void test_find_previous()
{
    linked_list<int> list;

    node<int> *node_a = list.append_node(9);
    node<int> *node_b = list.append_node(18);

    if (list.find_previous_node(node_b) == node_a)
    {
        write_line("Found the correct previous node");
    }
    else
    {
        write_line("Found the wrong previous node");
    }
}

void test_deletion()
{
    linked_list<int> list;

    node<int> *first_node = list.append_node(1);
    list.append_node(2);
    node<int> *third_node = list.append_node(3);
    list.append_node(4);
    list.append_node(5);

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

void test_insert()
{
    linked_list<int> list;

    write_line("Initial list: ");

    node<int> *first_node = list.append_node(1);
    list.append_node(2);
    node<int> *third_node = list.append_node(3);

    list.print();

    list.insert_after_node(67, first_node);

    write_line("Insert 67 after 1: ");

    list.print();

    list.insert_after_node(67, third_node);

    write_line("Insert 67 after 3: ");

    list.print();
}

int main()
{
    linked_list<int> list;

    int data_input;
    int index_input;

    while (true)
    {
        {

            write_line("1: Print list");
            write_line("2: Append value");
            write_line("3: Prepend value");
            write_line("4: Insert before node");
            write_line("5: Insert after node");
            write_line("6: Delete value");

            int menu_selection = read_integer_range("Enter Option: ", 1, 6);

            write_line();

            switch (menu_selection)
            {
            case 1:
                list.print();
                break;

            case 2:
                data_input = read_integer("Value to append: ");
                list.append_node(data_input);
                break;

            case 3:
                data_input = read_integer("Value to prepend: ");
                list.prepend_node(data_input);
                break;

            case 4:
                data_input = read_integer("Which value to insert? ");
                list.print();
                index_input = read_integer("Insert before which node? ");
                list.insert_before_node(data_input, list.node_at_index(index_input));
                break;

            case 5:
                data_input = read_integer("Which value to insert? ");
                list.print();
                index_input = read_integer("Insert after which node? ");
                list.insert_after_node(data_input, list.node_at_index(index_input));
                break;

            case 6:
                list.print();
                index_input = read_integer("Delete which node? ");
                list.delete_node(list.node_at_index(index_input));
                break;
            }
        }
    }
}