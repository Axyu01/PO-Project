#include "Data.h"

Spec::Spec(std::string nm)
	:name{nm}
{

}

void Spec::addCourse(std::string nm)
{
	for (auto c : courses)
	{
		if (nm == c->name)
		{
			return;
		}
	}
	courses.push_back(new Course(nm));
}

void Spec::delCourse(std::string)
{
	for (int i = 0; i < courses.size(); i++)
	{
		if (courses[i]->name == name)
		{
			courses[i]->clearGroups();

			courses.erase(courses.begin() + i);
		}
	}
}

void Spec::clearCourses()
{
	while (courses.size())
	{
		courses.back()->clearGroups();
		courses.pop_back();
	}
}

void Spec::addStudent(User* st)
{
	students.push_back(st);
}

void Spec::delStudent(User* st)
{
	for (auto c : courses)
	{
		c->delStudent(st);
	}

	for (int i=0;i<students.size();i++)
	{
		if (students[i] = st)
		{
			students.erase(students.begin() + i);
		}
	}
}

void Spec::listCourse()
{
	for (auto c : courses)
	{
		std::cout << c->name << std::endl;
	}
}

void Spec::saveToFile()
{
	std::fstream plik;

	if (!is_path_exists("Data"))
	{
		make_directory("Data");
	}

	if (!is_path_exists("Data/RegisterData"))
	{
		make_directory("Data/RegisterData");
	}
	if (!is_path_exists("Data/RegisterData/" + name))
	{
		make_directory("Data/RegisterData/" + name);
	}

	plik.open("Data/RegisterData/" + name + "/" + name + "CourseList.txt", std::ios::out);
	if (plik.good() == false)
	{
		std::cout << "Wystapil blad z odczytywaniem pliku. Sprawdz czy " << name << "CourseList.txt istnieje" << std::endl;
		exit(0);
	}

	for (int i = 0; i < courses.size(); i++)
	{
		plik << courses[i]->name << std::endl;
	}

	plik.close();

	plik.open("Data/RegisterData/" + name + "/" + name + "StudentList.txt", std::ios::out);
	if (plik.good() == false)
	{
		std::cout << "Wystapil blad z odczytywaniem pliku. Sprawdz czy " << name << "StudentList.txt istnieje" << std::endl;
		exit(0);
	}

	for (auto s : students)
	{
		plik << s->login << std::endl;
	}



	for (auto c : courses)
	{
		c->saveToFile(name);
	}

}

void Spec::readFromFile()
{
	std::fstream plik;


	if (!is_path_exists("Data"))
	{
		make_directory("Data");
	}
	if (!is_path_exists("Data/RegisterData"))
	{
		make_directory("Data/RegisterData");
	}
	if (!is_path_exists("Data/RegisterData/" + name))
	{
		make_directory("Data/RegisterData/" + name);
	}

	plik.open("Data/RegisterData/" + name +"/"+ name+ "CourseList.txt", std::ios::in);
	if (plik.good() == false)
	{
		std::cout << "Wystapil blad z odczytywaniem pliku. Sprawdz czy "+name+"courseList.txt istnieje." << std::endl;
		exit(0);
	}



	std::string line;

	while (std::getline(plik, line))
	{

		addCourse(line);

	}

	for (auto c : courses)
	{
		c->readFromFile(name);
	}


	plik.close();

	plik.open("Data/RegisterData/" + name + "/" + name + "StudentList.txt", std::ios::in);
	
	
	while (std::getline(plik, line))

	{
		UsersData::findUser(line)->joinSpec(this);
	}


	std::cout << "Pomyslnie wczytano dane o " + name + " z pliku." << std::endl;


}