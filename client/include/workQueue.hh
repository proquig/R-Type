#pragma once

# include <mutex>
# include <list>
# include <vector>

template <class T>
class WorkQueue
{
	std::mutex		access;
	std::list<T>	queue;
public:
	const std::list<T> &getQueue() const {
		return queue;
	}


public:

	bool empty(void)
	{
		bool cond;
		this->access.lock();
		cond = this->queue.empty();
		this->access.unlock();
		return cond;
	}
	void	push(T obj) {
		this->access.lock();
		this->queue.push_back(obj);
		this->access.unlock();
	}

	T		pop(void) {
		T	mem = NULL;

		this->access.lock();
		if (this->queue.size()) {
			mem = this->queue.back();
			this->queue.pop_back();
		}
		this->access.unlock();
		return (mem);
	}

	T		popLast(void) {
		T	mem = NULL;

		this->access.lock();
		if (this->queue.size()) {
			mem = this->queue.front();
			this->flush();
		}
		this->access.unlock();
		return (mem);
	}

	std::vector<T>		*popAll(void) {

		std::vector<T>	*res = new std::vector<T>();

		this->access.lock();
		while (this->queue.size()) {
			res->push_back(this->queue.back());
			this->queue.pop_back();
		}
		this->access.unlock();
		return (res);
	}

	void	flush(void) {
		this->access.lock();
		//for (T* t : this->queue)
		//	delete t;
		this->queue.clear();
		this->access.unlock();
	}
};