#include <iostream>
#include <exception>

template <typename T>
struct Item
{
	T data;
	int priority;
	Item();
};

template <typename T>
class kPriorityQueue
{
	Item<T>* data;
	size_t capacity;
	size_t size;
	size_t maxPriority;

	mutable size_t get;
	size_t put;

	void resize();

	void copyFrom(const kPriorityQueue<T>& other);
	void free();
public:
	kPriorityQueue();
	kPriorityQueue(size_t maxPriority);

	kPriorityQueue(const kPriorityQueue<T>& other);
	kPriorityQueue<T>& operator=(const kPriorityQueue<T>& other);

	void push(const T& obj, size_t priority);
	void push(T&& obj, size_t priority);
	void pop();

	const T& peek() const;
	bool isEmpty() const;
	void printQueue() const;
	~kPriorityQueue();

};

template <typename T>
Item<T>::Item()
{
	priority = -1;
}


template <typename T>
kPriorityQueue<T>::kPriorityQueue() : kPriorityQueue(0) {}

template <typename T>
kPriorityQueue<T>::kPriorityQueue(size_t maxPriority)
{
	this->maxPriority = maxPriority;
	capacity = 4;
	data = new Item<T>[capacity];
	size = 0;
	get = put = 0;
}

template <typename T>
void kPriorityQueue<T>::push(const T& obj, size_t priority)
{
	if (size == capacity)
		resize();

	if (priority > maxPriority)
		throw std::logic_error("Priority is too high");

	data[put].data = obj;
	data[put].priority = priority;
	if (data[put].priority > data[get].priority)
		get = put;

	(++put) %= capacity;
	size++;
}

template <typename T>
void kPriorityQueue<T>::push(T&& obj, size_t priority)
{
	if (size == capacity)
		resize();

	if (priority > maxPriority)
		throw std::logic_error("Priority is too high");

	data[put].data = std::move(obj);
	data[put].priority = priority;
	if (data[put].priority > data[get].priority)
		get = put;

	(++put) %= capacity;
	size++;
}

template <typename T>
bool kPriorityQueue<T>::isEmpty() const
{
	return size == 0;
}


template <typename T>
const T& kPriorityQueue<T>::peek() const
{
	if (isEmpty())
		throw std::logic_error("Empty queue!");

	std::cout << data[get].data << " " << std::endl;
	return data[get].data;
}

template <typename T>
void kPriorityQueue<T>::pop()
{
	if (isEmpty())
	{
		throw std::logic_error("Empty queue!");
	}

	data[get].priority = -1;

	for (size_t i = get + 1; i != get; (++i) %= capacity)
	{
		if (data[i].priority > data[get].priority)
		{
			get = i;
		}
	}

	size--;
}

template <typename T>
void kPriorityQueue<T>::resize()
{
	Item<T>* resizedData = new Item<T>[capacity * 2];
	for (size_t i = 0; i < size; i++)
	{
		resizedData[i] = data[get];
		(++get) %= capacity;
	}

	capacity *= 2;

	delete[] data;

	data = resizedData;
	get = 0;
	put = size;
}


template <typename T>
void kPriorityQueue<T>::copyFrom(const kPriorityQueue<T>& other)
{
	data = new Item<T>[other.capacity];
	for (int i = 0; i < other.capacity; i++)
	{
		data[i] = other.data[i];
	}

	get = other.get;
	put = other.put;

	size = other.size;
	capacity = other.capacity;
	maxPriority = other.maxPriority;
}

template <typename T>
void kPriorityQueue<T>::free()
{
	delete[] data;
}

template <typename T>
kPriorityQueue<T>::kPriorityQueue(const kPriorityQueue<T>& other)
{
	copyFrom(other);
}

template <typename T>
kPriorityQueue<T>& kPriorityQueue<T>::operator=(const kPriorityQueue<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template <typename T>
kPriorityQueue<T>::~kPriorityQueue()
{
	free();
}
