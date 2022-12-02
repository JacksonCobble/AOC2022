#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>

/*
--- Day 1: Calorie Counting ---
Santa's reindeer typically eat regular reindeer food, but they need a lot of magical energy to deliver presents on Christmas.
For that, their favorite snack is a special type of star fruit that only grows deep in the jungle. The Elves have brought you
on their annual expedition to the grove where the fruit grows.

The Elves take turns writing down the number of Calories contained by the various meals, snacks, rations, etc. that they've brought
with them, one item per line. Each Elf separates their own inventory from the previous Elf's inventory (if any) by a blank line.

For example, suppose the Elves finish writing their items' Calories and end up with the following list:

1000
2000
3000

4000

5000
6000

7000
8000
9000

10000

This list represents the Calories of the food carried by five Elves:

The first Elf is carrying food with 1000, 2000, and 3000 Calories, a total of 6000 Calories.
The second Elf is carrying one food item with 4000 Calories.
The third Elf is carrying food with 5000 and 6000 Calories, a total of 11000 Calories.
The fourth Elf is carrying food with 7000, 8000, and 9000 Calories, a total of 24000 Calories.
The fifth Elf is carrying one food item with 10000 Calories.

In case the Elves get hungry and need extra snacks, they need to know which Elf to ask: they'd like to know how many Calories
are being carried by the Elf carrying the most Calories. In the example above, this is 24000 (carried by the fourth Elf).

Find the Elf carrying the most Calories. How many total Calories is that Elf carrying?

--- Part Two ---
By the time you calculate the answer to the Elves' question, they've already realized that the Elf carrying the most Calories
of food might eventually run out of snacks.

To avoid this unacceptable situation, the Elves would instead like to know the total Calories carried by the top three Elves
carrying the most Calories. That way, even if one of those Elves runs out of snacks, they still have two backups.

In the example above, the top three Elves are the fourth Elf (with 24000 Calories), then the third Elf (with 11000 Calories),
then the fifth Elf (with 10000 Calories). The sum of the Calories carried by these three elves is 45000.

Find the top three Elves carrying the most Calories. How many Calories are those Elves carrying in total?

*/

void Day1()
{
    //open file, init list of calories held
    std::ifstream file("Input_Data/input1.txt");

    //pair functions as first = which # elf, second = # of calories
    std::vector<std::pair<int, int>> values = {};

    //tmp string for getline and number for which elf we are on
    std::string tmp;
    int elfNum = 0;

    //loop over entirety of file
    while (!file.eof())
    {
        std::getline(file, tmp);
        //skip to next iter if empty string
        if (tmp == "")
        {
            elfNum++;
            continue;
        }
        //try to add to current elf #
        try
        {
            values.at(elfNum).second += stoi(tmp);
        }
        //if not, resize vector and set value
        catch (const std::out_of_range& oor)
        {
            values.resize(elfNum + 1);
            values.at(elfNum) = std::pair<int, int>(elfNum + 1, stoi(tmp));
        }
    }

    //sort using lambda, sorting comparison is checking the number of calories 
    std::sort(values.begin(), values.end(),
        [](const std::pair<int, int>& x, const std::pair<int, int>& y)
        {
            return x.second < y.second;
        });

    //print statements
    std::cout << "Day 1" << std::endl;
    std::cout << "Elf #" << values.at(values.size() - 1).first << " has the most calories with: " <<
        values.at(values.size() - 1).second << std::endl;
    std::cout << "Elf #" << values.at(values.size() - 2).first << " has the second most calories with: " <<
        values.at(values.size() - 2).second << std::endl;
    std::cout << "Elf #" << values.at(values.size() - 3).first << " has the third most calories with: " <<
        values.at(values.size() - 3).second << std::endl;
    std::cout << "Their combined total number of calories is: " << values.at(values.size() - 1).second +
        values.at(values.size() - 2).second + values.at(values.size() - 3).second << std::endl;
    std::cout << std::endl;
    return;
}

