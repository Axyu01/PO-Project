#include <iostream>
#include "Data.h"
#include <string>

int main()
{
	std::string message = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nulla et erat at nisi mattis hendrerit vel sit amet magna. Nulla facilisi. Morbi hendrerit dictum condimentum. Nulla vulputate blandit urna, a gravida ex ornare non. Nunc quis ex urna. Integer vel elementum odio. Duis egestas massa bibendum velit lacinia, sed aliquet lacus auctor.";
	//std::getline(std::cin,message);
	Mail test("Francek","Kamil",message);
	test.viewContents();
}

