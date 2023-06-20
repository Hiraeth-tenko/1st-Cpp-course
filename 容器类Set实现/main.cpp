#include <iostream>
#include <fstream>

template <typename T>
class Set
{
private:
    struct Node
    {
        T data;
        Node *next;
    };

    Node *head;

public:
    Set() : head(nullptr) {}

    ~Set()
    {
        clear();
    }

    void add(const T &element)
    {
        if (contains(element))
        {
            std::cout << "Element already exists in the set.\n";
            return;
        }

        Node *newNode = new Node;
        newNode->data = element;
        newNode->next = nullptr;

        if (head == nullptr || element < head->data)
        {
            newNode->next = head;
            head = newNode;
        }
        else
        {
            Node *curr = head;
            while (curr->next && element > curr->next->data)
            {
                curr = curr->next;
            }
            newNode->next = curr->next;
            curr->next = newNode;
        }

        std::cout << "Element added to the set.\n";
    }

    void remove(const T &element)
    {
        if (head == nullptr)
        {
            std::cout << "Set is empty. Cannot remove element.\n";
            return;
        }

        Node *curr = head;
        Node *prev = nullptr;
        bool found = false;

        while (curr != nullptr)
        {
            if (curr->data == element)
            {
                if (prev == nullptr)
                {
                    head = curr->next;
                }
                else
                {
                    prev->next = curr->next;
                }
                delete curr;
                found = true;
                break;
            }
            prev = curr;
            curr = curr->next;
        }

        if (found)
        {
            std::cout << "Element removed from the set.\n";
        }
        else
        {
            std::cout << "Element not found in the set.\n";
        }
    }

    Set<T> intersection(const Set<T> &other) const
    {
        Set<T> result;
        Node *curr1 = head;
        Node *curr2 = other.head;

        while (curr1 && curr2)
        {
            if (curr1->data < curr2->data)
            {
                curr1 = curr1->next;
            }
            else if (curr1->data > curr2->data)
            {
                curr2 = curr2->next;
            }
            else
            {
                result.add(curr1->data);
                curr1 = curr1->next;
                curr2 = curr2->next;
            }
        }

        return result;
    }

    Set<T> unionSet(const Set<T> &other) const
    {
        Set<T> result;
        Node *curr1 = head;
        Node *curr2 = other.head;

        while (curr1 && curr2)
        {
            if (curr1->data < curr2->data)
            {
                result.add(curr1->data);
                curr1 = curr1->next;
            }
            else if (curr1->data > curr2->data)
            {
                result.add(curr2->data);
                curr2 = curr2->next;
            }
            else
            {
                result.add(curr1->data);
                curr1 = curr1->next;
                curr2 = curr2->next;
            }
        }

        while (curr1)
        {
            result.add(curr1->data);
            curr1 = curr1->next;
        }

        while (curr2)
        {
            result.add(curr2->data);
            curr2 = curr2->next;
        }

        return result;
    }

    Set<T> difference(const Set<T> &other) const
    {
        Set<T> result;
        Node *curr1 = head;
        Node *curr2 = other.head;

        while (curr1 && curr2)
        {
            if (curr1->data < curr2->data)
            {
                result.add(curr1->data);
                curr1 = curr1->next;
            }
            else if (curr1->data > curr2->data)
            {
                curr2 = curr2->next;
            }
            else
            {
                curr1 = curr1->next;
                curr2 = curr2->next;
            }
        }

        while (curr1)
        {
            result.add(curr1->data);
            curr1 = curr1->next;
        }

        return result;
    }

    bool contains(const T &element) const
    {
        Node *curr = head;
        while (curr != nullptr)
        {
            if (curr->data == element)
            {
                return true;
            }
            curr = curr->next;
        }
        return false;
    }

    void clear()
    {
        Node *curr = head;
        while (curr != nullptr)
        {
            Node *temp = curr;
            curr = curr->next;
            delete temp;
        }
        head = nullptr;
    }

    void print() const
    {
        Node *curr = head;
        while (curr != nullptr)
        {
            std::cout << curr->data << " ";
            curr = curr->next;
        }
        std::cout << std::endl;
    }

    void saveToFile(const std::string &filename) const
    {
        std::ofstream file(filename);
        if (!file)
        {
            std::cout << "Error opening file for writing.\n";
            return;
        }

        Node *curr = head;
        while (curr != nullptr)
        {
            file << curr->data << "\n";
            curr = curr->next;
        }

        file.close();
        std::cout << "Set saved to file.\n";
    }

    void loadFromFile(const std::string &filename)
    {
        clear();

        std::ifstream file(filename);
        if (!file)
        {
            std::cout << "Error opening file for reading.\n";
            return;
        }

        T element;
        while (file >> element)
        {
            add(element);
        }

        file.close();
        std::cout << "Set loaded from file.\n";
    }
};

int main()
{
    Set<int> set;

    int choice;
    int element;
    std::string filename;

    while (true)
    {
        std::cout << "********* Set Management System *********\n";
        std::cout << "1. Add Element\n";
        std::cout << "2. Remove Element\n";
        std::cout << "3. Intersection\n";
        std::cout << "4. Union\n";
        std::cout << "5. Difference\n";
        std::cout << "6. Save to File\n";
        std::cout << "7. Load from File\n";
        std::cout << "8. Show Nodes\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            std::cout << "Enter element to add: ";
            std::cin >> element;
            set.add(element);
            break;
        case 2:
            std::cout << "Enter element to remove: ";
            std::cin >> element;
            set.remove(element);
            break;
        case 3:
        {
            Set<int> otherSet;
            std::cout << "Enter elements of other set (0 to stop):\n";
            while (true)
            {
                std::cin >> element;
                if (element == 0)
                {
                    break;
                }
                otherSet.add(element);
            }
            Set<int> intersectionSet = set.intersection(otherSet);
            std::cout << "Intersection: ";
            intersectionSet.print();
            break;
        }
        case 4:
        {
            Set<int> otherSet;
            std::cout << "Enter elements of other set (0 to stop):\n";
            while (true)
            {
                std::cin >> element;
                if (element == 0)
                {
                    break;
                }
                otherSet.add(element);
            }
            Set<int> unionSet = set.unionSet(otherSet);
            std::cout << "Union: ";
            unionSet.print();
            break;
        }
        case 5:
        {
            Set<int> otherSet;
            std::cout << "Enter elements of other set (0 to stop):\n";
            while (true)
            {
                std::cin >> element;
                if (element == 0)
                {
                    break;
                }
                otherSet.add(element);
            }
            Set<int> differenceSet = set.difference(otherSet);
            std::cout << "Difference: ";
            differenceSet.print();
            break;
        }
        case 6:
            std::cout << "Enter filename to save: ";
            std::cin >> filename;
            set.saveToFile(filename);
            break;
        case 7:
            std::cout << "Enter filename to load: ";
            std::cin >> filename;
            set.loadFromFile(filename);
            break;
        case 8:
            set.print();
            break;
        case 0:
            std::cout << "Exiting the program.\n";
            exit(0);
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }

        std::cout << std::endl;
    }

    return 0;
}
