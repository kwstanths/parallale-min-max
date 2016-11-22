#ifndef __MAX_HPP__
#define __MAX_HPP__

#include <iostream>
#include <vector>
#include <thread>


namespace mns{
	template<typename T>
	void search(T * array, int start, int stop, bool (*function)(T,T), T &dest){
		T max = array[start];
		for(int i=start; i<stop; i++){
			if (function(max,array[i])){
				max = array[i];
			}
		}
		dest = max;
	}

	template<typename T>
	T max_min(std::vector<T> array, bool (*func)(T,T), int threads = 1){
		std::vector<T> elems_vec(threads);
		std::vector<std::thread> threads_vec;
		int step = array.size() / threads;
		for (int i=0; i<threads; i++){
			threads_vec.push_back(std::thread(search<T>, &array[0], i * step, (i==threads-1)?(array.size()):(i*step + step), func, std::ref(elems_vec[i])));
		}

		for(std::vector<std::thread>::iterator itr = threads_vec.begin(); itr!=threads_vec.end(); ++itr){
			(*itr).join();
		}

		T max;
		search<T>(&elems_vec[0], 0, elems_vec.size(), func, std::ref(max));
		return max;
	}

}
#endif
