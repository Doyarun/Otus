template <typename T, size_t allocation_size = 10>
struct MyAllocator{
	
	using value_type = T;

	using pointer = T *;
	using const_pointer = const T *;
	using reference = T &;
	using const_reference = const T &;

	size_t _capacity = 0;
	size_t _size = 0;

	pointer _pointer;
	pointer _next;

	MyAllocator(): _pointer(nullptr), _next(nullptr)
	{
		init();
	};
	~MyAllocator(){
		std::free(_pointer);
		_pointer = nullptr;
		_capacity = 0;
		_size = 0;
	}

    template <typename U>
	struct rebind {
		using other = MyAllocator<U, allocation_size>;
	};
	void init()
	{
		auto p = std::malloc((allocation_size) * sizeof(T));
		if (!p)
			throw std::bad_alloc();

		_pointer = reinterpret_cast<T *>(p);
		_next = _pointer;
		_capacity += allocation_size;
	}

	T *allocate(std::size_t n) {
		if(!_pointer)
			init();

		if(_capacity < _size + n)
			return nullptr;

		auto p = _next++;
		return p;
	}

	void deallocate(T *p, std::size_t n) {
		if(p == _pointer && n == _capacity)
		{
			free(p);
			_pointer = nullptr;
			_next = nullptr;
			_size = 0;
			_capacity = 0;
		}
	}

	template <typename U, typename... Args>
	void construct(U *p, Args &&...args) {
		if(enable_logging)
        	std::cout <<  "construct" << std::endl;
		_size++;
		new (p) U(std::forward<Args>(args)...);
	};

	template <typename U>
	void destroy(U *p) {
		if(enable_logging)
        	std::cout << "destroy"<< std::endl;
		_size--;
		p->~U();
	};

private:
	bool enable_logging = false;
};


template<typename T>
inline bool operator==(const MyAllocator<T>&, const MyAllocator<T>&) {
  return true;
}

template<typename T>
inline bool operator!=(const MyAllocator<T>&, const MyAllocator<T>&) {
  return false;
}