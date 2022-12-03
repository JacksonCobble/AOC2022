#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

void Day3()
{
	std::ifstream file("Input_Data/input3.txt"); //open up data file
	std::string tmp = ""; //tmp string to hold each line

	//part 1 variables
	std::string dupes = ""; //tmp string to hold all duplicates
	char* lhs; //pointer to beginning of first half of array
	char* rhs; //pointer to beginning of second half of array
	int dist; //size of each half
	int priosP1 = 0; //total priority of part 1

	//part 2 variables
	std::vector<std::string> groups; //vector to hold our set of 3 lines
	std::string intersection = ""; //intersection of first two lines
	std::string intersection2 = ""; //intersection of previous intersection and last line
	int priosP2 = 0; //total priority of part 2

	//loop over every line in file
	while (std::getline(file, tmp))
	{
		//add tmp string to our grouping of 3
		groups.push_back(tmp);

		//if we have collected 3 lines do analysis for part 2
		if (groups.size() == 3)
		{
			//for each group sort and pull uniques from them
			for (auto& l : groups)
			{
				std::sort(l.begin(), l.end());
				auto end = std::unique(l.begin(), l.end());
				l.erase(end, l.end());
			}

			//get intersection of all 3 sets
			std::set_intersection(groups.at(0).begin(), groups.at(0).end(),
				groups.at(1).begin(), groups.at(1).end(), std::back_inserter(intersection));
			std::set_intersection(groups.at(2).begin(), groups.at(2).end(),
				intersection.begin(), intersection.end(), std::back_inserter(intersection2));

			//calculate priority
			for (const auto& c : intersection2)
			{
				priosP2 += (c > 96) * (c - 96) + (c < 96) * (c - 38);
			}
			
			//clear vars used for next calculation
			intersection = "";
			intersection2 = "";
			groups.clear();

		}

		//find address of lhs and rhs addresses based on size of array
		lhs = &tmp[0];
		dist = tmp.size() / 2;
		rhs = lhs + dist;
		//sort both sides
		std::sort(lhs, rhs);
		std::sort(rhs, rhs + dist);

		//cheeky set intersection involving deleting uniques as they are passed into the function
		std::set_intersection(lhs, std::unique(lhs, rhs), rhs, std::unique(rhs, rhs + dist), 
			std::back_inserter(dupes));

		//calculate priority
		for (const auto& c : dupes)
		{
			priosP1 += (c > 96) * (c - 96) + (c < 96) * (c - 38);
		}
		//empty our dupes string for the next line
		dupes = "";
	}
	file.close();
	//print statements
	std::cout << "part 1 sum of priorities: " << priosP1 << std::endl;
	std::cout << "part 2 sum of priorities: " << priosP2 << std::endl;
	
	return;
}