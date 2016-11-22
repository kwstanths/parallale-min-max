#include <iostream>
#include <sys/time.h>
#include <unistd.h>
#include "max.hpp"

#define MY_MAX_INT 2147483647

typedef struct my_own_struct{
	my_own_struct(int _test_var): test_var(_test_var){};
	int test_var;
	int garbage[50];
} my_struct_type;

typedef struct another_struct{
	another_struct(int _test_var): test_var(_test_var){};
	int test_var;
	int dummy[3];
} another_struct_type;


bool test_function(int left, int right){
	return left < right;
}

bool test_function2(my_struct_type * left, my_struct_type * right){
	return left->test_var > right->test_var;
}

void test(std::vector<int> test_vector, int numbers, int threads) {

	int max;
	struct timeval time_start, time_stop;

	std::cout << "Numbers: " << numbers << ", Threads: " << threads << " ... " << std::flush;
	gettimeofday(&time_start, NULL);
	max = mns::max_min(test_vector, &test_function, threads);
	gettimeofday(&time_stop, NULL);
	std::cout << "Max: " << max << ", Time: ";
	std::cout << 1000 * (time_stop.tv_sec - time_start.tv_sec) + (time_stop.tv_usec - time_start.tv_usec) / 1000 << " msec" << std::endl;
}

int * array2 = (int *)malloc(1000000000*sizeof(int));

int main(){
	//test 1
	std::cout << "--Tests" << std::endl;
	int array[] = {501,4,5,23,4,5,234,65,324,35,987};
	std::vector<int> test_vector (array, array + sizeof(array) / sizeof(array[0]));
	int max = mns::max_min(test_vector, &test_function);
	std::cout << "\tMax: " << max << std::endl;

	//test 2
	std::vector<my_struct_type *> test_vector2;
	test_vector2.push_back(new my_struct_type(5));
	test_vector2.push_back(new my_struct_type(3));
	test_vector2.push_back(new my_struct_type(15));
	test_vector2.push_back(new my_struct_type(35));
	test_vector2.push_back(new my_struct_type(35));
	test_vector2.push_back(new my_struct_type(9));
	test_vector2.push_back(new my_struct_type(45));
	my_struct_type * max2 = mns::max_min(test_vector2, &test_function2);
	std::cout << "\tMin: " << max2->test_var << std::endl;

	//test 3
	max = mns::max_min<int>(test_vector, [](int l, int r) -> bool {return l<r;});
	std::cout << "\tMax: " << max << std::endl;

	//test 4
	max = mns::max_min<int>(test_vector, [](int l, int r) -> bool {return l>r;});
	std::cout << "\tMin: " << max << std::endl;

	//test 5
	std::vector<another_struct_type *> lamvec;
	lamvec.push_back(new another_struct_type(5));
	lamvec.push_back(new another_struct_type(6));
	lamvec.push_back(new another_struct_type(33));
	lamvec.push_back(new another_struct_type(67));
	lamvec.push_back(new another_struct_type(78));
	lamvec.push_back(new another_struct_type(90));
	lamvec.push_back(new another_struct_type(54));
	another_struct_type * max4 = mns::max_min<another_struct_type *>(lamvec, [](another_struct_type * l, another_struct_type * r) -> bool {return l->test_var < r->test_var;});
	std::cout << "\tMax: " << max4->test_var << std::endl;

	//test 6
	max4 = mns::max_min<another_struct_type *>(lamvec, [](another_struct_type * l, another_struct_type * r) -> bool {return l->test_var > r->test_var;});
	std::cout << "\tMin: " << max4->test_var << std::endl;

	srand(time(NULL));
	int numbers;
	std::cout << "\n--Benchmarks" << std::endl;
	std::cout << "Creating arrays... " << std::flush;
	numbers = 500000;
	std::vector<int> test_vector3;
	for(int i=0; i<numbers; i++) test_vector3.push_back(rand()%MY_MAX_INT +1);
	numbers = 5000000;
	std::vector<int> test_vector4;
	for(int i=0; i<numbers; i++) test_vector4.push_back(rand()%MY_MAX_INT +1);
	numbers = 50000000;
	std::vector<int> test_vector5;
	for(int i=0; i<numbers; i++) test_vector5.push_back(rand()%MY_MAX_INT +1);
	numbers = 100000000;
	std::vector<int> test_vector6;
	for(int i=0; i<numbers; i++) test_vector6.push_back(rand()%MY_MAX_INT +1);
	std::cout << "Done" << std::endl;
	test(test_vector3, test_vector3.size(), 1);
	test(test_vector3, test_vector3.size(), 2);
	test(test_vector3, test_vector3.size(), 4);
	test(test_vector4, test_vector4.size(), 1);
	test(test_vector4, test_vector4.size(), 2);
	test(test_vector4, test_vector4.size(), 4);
	test(test_vector5, test_vector5.size(), 1);
	test(test_vector5, test_vector5.size(), 2);
	test(test_vector5, test_vector5.size(), 4);
	test(test_vector6, test_vector6.size(), 1);
	test(test_vector6, test_vector6.size(), 2);
	test(test_vector6, test_vector6.size(), 4);

	return 0;
}
