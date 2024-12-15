#include "proto/Person.pb.h"
#include <iostream>


int main() {
	Person person;
	person.set_name("John Doe");
	person.set_gender("M");
	person.set_email("j.doe@some.com");
	std::cout << person.ShortDebugString() << std::endl;
	return 0;
}