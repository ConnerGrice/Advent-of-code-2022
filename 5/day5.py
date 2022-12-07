class CrateStack:

    def __init__(self,crates):
        self.crates = crates
        self.top = crates[-1]

def findCrates(content):
    """
    Parse through the first 8 lines of the puzzle input and extract the initial crate positions
    content: list(string) -> The lines of the input file
    """
    stacks = []

    #Loops through the first 8 lines of the puzzle file
    for line,i in zip(content,range(8)):
        level = []

        #Removes trailing new line character
        line_clean = line.rstrip("\n")

        #Loops though each character
        for j,char in enumerate(line_clean):
            #Checks for the character before setting the crate letter
            if char == "[":

                #Calculates the number of tabs + 1 (the stack number)
                #Places them into a list also including the crate letter
                stacks.append((int((j/4)+1),line_clean[j+1]))

    return stacks

def organiseCrates(stack_list):
    """
    Loads the stacking into a dict organising them into their stacks
    """
    stack_dict = {}

    #initialise dict keys and empty lists
    for i in range(1,10):
        stack_dict[i] = []

    #Loops though stack lists and puts into correct key of dict
    for crate in stack_list:
        stack_dict[crate[0]] += crate[1]
    
    return stack_dict

def loadCrates(stacks):
    for item in stacks.items():
        stacks[item[0]] = CrateStack(item[1])
    
    return stacks

with open("input.txt","r") as f:
    puzzle = f.readlines()
    thing = findCrates(puzzle)
    thing_dict = organiseCrates(thing)
    thing_dict = loadCrates(thing_dict)
    print(thing_dict[1].crates)





