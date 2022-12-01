"""
Day 1:
    Puzzle input    -> List of integers representing the number of calories each food contains
                    -> New line indicates that a new elf is being looked at

    Task 1  -> How many calories is the elf that is holding the most calories holding?
    Task 2  -> What is the total calorie count for the top 3 elves?
"""
#TASK 1============================================================================
#Open file containing puzzle inputs
with open("input.txt","r") as f:

    elf_list = []   #List of total calories being held by each elf
    calories = 0    #Calorie counter of each elf
    for line in f:
        #Checks if new line
        if line == "\n":
            elf_list.append(calories)
            calories = 0
        else:
            calories += int(line)

print(f"The elf carrying the most calories is carrying {max(elf_list)} calories")

#Sorts the list of elves in om ascending order
elf_list.sort()

#Gets the 1st, 2nd, and 3rd highest elf
first = elf_list[-1]
second = elf_list[-2]
third = elf_list[-3]

#Prints results
print()
print("Top 3 elves:")
print(f"1st: {first}")
print(f"2nd: {second}")
print(f"3rd: {third}")
print()
print(f"Total of top 3: {first+second+third}")


        


        