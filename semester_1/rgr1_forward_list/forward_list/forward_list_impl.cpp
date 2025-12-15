#include "forward_list_impl.h"

// default constructor
ForwardList::ForwardList() : head_(nullptr), size_(0) {}

// copy constructor
ForwardList::ForwardList(const ForwardList& rhs) : head_(nullptr), size_(0) {
    Node* current = rhs.head_;
    Node* last = nullptr;

    while (current != nullptr) {
        Node* newNode = new Node(current->value_);

        if (head_ == nullptr) {
            head_ = newNode;
        } else {
            last->next_ = newNode;
        }

        last = newNode;
        current = current->next_;
        size_++;
    }
}

// Constructs a ForwardList with `count` copies of elements with value `value`.
ForwardList::ForwardList(size_t count, int32_t value) : head_(nullptr), size_(0) {
    if (count == 0)
        return;

    head_ = new Node(value);
    Node* current = head_;
    size_ = 1;

    for (size_t i = 1; i < count; ++i) {
        current->next_ = new Node(value);
        current = current->next_;
        size_++;
    }
}

// Constructs a ForwardList with std::initializer_list<int32_t>
ForwardList::ForwardList(std::initializer_list<int32_t> init) : head_(nullptr), size_(0) {
    Node* current = nullptr;

    for (int32_t value : init) {
        Node* newNode = new Node(value);

        if (head_ == nullptr) {
            head_ = newNode;
        } else {
            current->next_ = newNode;
        }

        current = newNode;
        size_++;
    }
}

// operator= overloading (copy-and-swap idiom)
ForwardList& ForwardList::operator=(const ForwardList& rhs) {
    if (this != &rhs) {
        ForwardList temp(rhs);
        std::swap(head_, temp.head_);
        std::swap(size_, temp.size_);
    }
    return *this;
}

// destructor
ForwardList::~ForwardList() {
    Node* current = head_;
    while (current != nullptr) {
        Node* next = current->next_;
        delete current;
        current = next;
    }
    head_ = nullptr;
    size_ = 0;
}

void ForwardList::PushFront(int32_t value) {
    Node* newNode = new Node(value);
    newNode->next_ = head_;
    head_ = newNode;
    size_++;
}

void ForwardList::PopFront() {
    if (head_ == nullptr) {
        throw std::runtime_error("PopFront on empty list");
    }

    Node* toDelete = head_;
    head_ = head_->next_;
    delete toDelete;
    size_--;
}

void ForwardList::Remove(int32_t value) {
    Node* current = head_;
    Node* prev = nullptr;

    while (current != nullptr) {
        if (current->value_ == value) {
            Node* toDelete = current;

            if (prev == nullptr) {
                head_ = current->next_;
            } else {
                prev->next_ = current->next_;
            }

            current = current->next_;
            delete toDelete;
            size_--;
        } else {
            prev = current;
            current = current->next_;
        }
    }
}

void ForwardList::Clear() {
    while (head_ != nullptr) {
        Node* toDelete = head_;
        head_ = head_->next_;
        delete toDelete;
    }
    size_ = 0;
}

bool ForwardList::FindByValue(int32_t value) {
    Node* current = head_;
    while (current != nullptr) {
        if (current->value_ == value) {
            return true;
        }
        current = current->next_;
    }
    return false;
}

void ForwardList::Print(std::ostream& out) {
    Node* current = head_;
    bool first = true;

    while (current != nullptr) {
        if (!first) {
            out << " ";
        }
        out << current->value_;
        first = false;
        current = current->next_;
    }
}

int32_t ForwardList::Front() const {
    if (head_ == nullptr) {
        throw std::runtime_error("Front on empty list");
    }
    return head_->value_;
}

size_t ForwardList::Size() const {
    return size_;
}