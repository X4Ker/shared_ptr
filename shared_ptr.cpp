private:
	size_t * counter_ ; 
	T * ptr_ ;
public:
	explicit shared_ptr(T * ptr = nullptr)
	{
		ptr_ = ptr;
		if (ptr_) counter_ = new size_t(1);
		else counter_ = nullptr;
	}

	~shared_ptr()
	{
		if (counter_ && --*counter_ == 0) {
			delete ptr_;
			delete counter_;
		}
	}

	shared_ptr(shared_ptr<T> const & other)
	{
		ptr_ = other.ptr_;
		counter_ = other.counter_;
		if (other.counter_) {
			(*counter_)++;
		}
	}

	shared_ptr & operator =(shared_ptr<T> const & other)
	{
		if (&other != this) {
			shared_ptr(other).swap(*this);
		}

		return *this;
	}

	void swap(shared_ptr & shared) 
	{
		std::swap(shared.ptr_, ptr_);
		std::swap(shared.counter_, counter_);
	}

	void reset(T * ptr = nullptr)
	{
		shared_ptr(ptr).swap(*this);
	}

	T & operator*() const
	{
		return *ptr_;
	}
	T * operator->() const
	{
		return ptr_;
	}
	T * get() const
	{
		return ptr_;
	}

};
