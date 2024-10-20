#include "coordinate.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

int id_counter = 1;

void add_coordinate(Coordinate *&list_end, float x, float y)
{
        Coordinate *new_coord = new Coordinate;
        new_coord->x = x;
        new_coord->y = y;
        new_coord->coord_id = id_counter++;
        new_coord->next = nullptr;
        new_coord->previous = list_end;

        if(list_end != nullptr)
                list_end->next = new_coord;

        list_end = new_coord;
}

void forward_display(Coordinate *list_beginning)
{
        Coordinate *current = list_beginning;
        while(current != nullptr)
        {
                std::cout << "ID: " << current->coord_id << "(x,y): (" << current->x <<", " << current->y << ")\n";
                current = current->next;
        }
}

void backward_display(Coordinate *list_end)
{
        Coordinate *current = list_end;
        while(current != nullptr)
        {
                std:: cout << "ID: " << current->coord_id << "(x,y): (" << current->x <<", " << current->y << ")\n";
                current = current->previous;
        }
}

void delete_coordinate(Coordinate *&list_beginning, int coord_id_delete)
{
        Coordinate *current = list_beginning;
        while(current != nullptr)
 {
                if(current->coord_id == coord_id_delete)
                {
                        if(current->previous != nullptr)
                                current->previous->next = current->next;

                        if(current->next != nullptr)
                                current->next->previous = current->previous;

                        if(current == list_beginning)
                                list_beginning = current->next;

                        delete current;
                        std::cout << "Coordinate with ID " << coord_id_delete << "deleted.\n";
                        return;
                }
                current = current->next;
        }
        std::cout << "Coordinate with ID " << coord_id_delete << "not found.\n";
}

int list_length(Coordinate *list_beginning)
{
        int length = 0;
        Coordinate *current = list_beginning;
        while(current != nullptr)
        {
                length++;
                current = current->next;
        }
        return length;
}

void closest_to(Coordinate *list_beginning, float x, float y)
{
        Coordinate *current = list_beginning;
        Coordinate *closest = nullptr;
        float min_distance = std::numeric_limits<float>::max();

        while(current != nullptr)
        {
                float distance = std::sqrt(std::pow(current->x -x, 2) + std::pow(current->y - y, 2));
                if(distance < min_distance)
                {
                        min_distance = distance;
                        closest = current;
                }
                current = current->next;
        }

        if(closest != nullptr)
        {
                std::cout << "Closest point to (" << x <<", " << y << ") is ID" << closest->coord_id
                          << "with coordinates (" << closest->x << ", " << closest->y << ") at a distance of " << min_distance << "\n";
        }
}

int main(int argc, char *argv[])
{

	if(argc < 2)
	{
		std::cerr << "Usage: " << argv[0] << " <number of coordinates>\n";
		return 1;
	}

	int num_coords = std::atoi(argv[1]);

	if(num_coords <= 0)
	{
		std::cerr << "Please enter a valid number of coordinates.\n";
		return 1;
	}

	srand(static_cast<unsigned>(time(0)));

	Coordinate *list_beginning = nullptr;
	Coordinate *list_end = nullptr;

	for(int i = 0; i < num_coords; ++i)
	{
		float x = static_cast<float>(rand() % 100);
		float y = static_cast<float>(rand() % 100);
		if(list_beginning == nullptr)
		{
			list_beginning = new Coordinate;
			list_beginning->x = x;
			list_beginning->y = y;
			list_beginning->coord_id = id_counter++;
			list_beginning->next = nullptr;
			list_beginning->previous = nullptr;
			list_end = list_beginning;
		}
		else
		{
			add_coordinate(list_end, x, y);
		}
	}

	std::cout << "List of coordinates (forwards): \n";
	forward_display(list_beginning);

	std::cout << "List of coordinates (backwards):\n";
	backward_display(list_end);

	delete_coordinate(list_beginning, 3);

	std::cout << "After deletion (jforwards):\n";
	forward_display(list_beginning);
	
	closest_to(list_beginning, 50.0, 50.0);

	while(list_beginning != nullptr)
	{
		Coordinate *next = list_beginning->next;
		delete list_beginning;
		list_beginning = next;
	}
	return 0;
}





















































