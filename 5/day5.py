import re
import copy

class CrateStack:

    def __init__(self,crates):
        self.crates = crates[::-1]
        self.top = self.crates[-1]

    def add(self,crate):
        """
        Adds a crate to the top of the stack
        """
        if isinstance(crate,list):
            self.crates.extend(crate)
        else:
            self.crates.append(crate)

    def updateTop(self):
        """
        Updates the top crate value
        """
        if self.crates:
            self.top = self.crates[-1]
        else:
            self.top = "_"
    

    def moveTo(self,other_stack,num_moves):
        """
        Moves the top crate from current stack to a given stack
        """

        #Moves the given number of times
        for _ in range(num_moves):
            #Takes crate off the top of given stack
            crate = self.crates.pop()

            #Adds crate to the top of the other stack
            other_stack.add(crate)
        
        #Updates top of stack
        other_stack.updateTop()
        self.updateTop()


    def moveMulti(self,other_stack,num_moves):
        """
        Moves multiple crates at once, conserving order
        """
        #Length of stack
        stack_len = len(self.crates)

        #Gets a list of the top crates
        to_move = self.crates[stack_len-num_moves:]

        #Deletes top crates from list
        del self.crates[stack_len-num_moves:]

        #Add those crates to the other stack
        other_stack.add(to_move)

        #Updates top cratea
        other_stack.updateTop()
        self.updateTop()

    

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
    """
    Converts each list of crates into a stack object
    """
    for item in stacks.items():
        stacks[item[0]] = CrateStack(item[1])
    
    return stacks

def getCommands(content):
    """
    Parse puzzle input for the useable command values
    first - number of moves
    second - stack to move from
    third - stack to move to
    """
    command_list = []
    #Loops through the input that does not contain stack config
    for i in range(10,len(content)):
        #Removes all non-number characters and splits into a list
        command = re.sub(r"[a-zA-Z]","",content[i]).split()

        #Converts command values into integers
        command = [int(x) for x in command]

        command_list.append(command)
    
    return command_list

        


with open("input.txt","r") as f:
    #Read entire file
    puzzle = f.readlines()

    #Generates tuples containing each crate position
    crates = findCrates(puzzle)

    #Puts stack lists into a dict
    crates_dict = organiseCrates(crates)

    #Converts stack lists into stack objects
    crates_dict = loadCrates(crates_dict)

    #Gets a copy of the original config for task 2
    crates_copy = copy.deepcopy(crates_dict)

    #Gets a list of commands
    commands = getCommands(puzzle)

#Loops through all commands
for command in commands:
    #Carries out command
    crates_dict[command[1]].moveTo(crates_dict[command[2]],command[0]) 
    crates_copy[command[1]].moveMulti(crates_copy[command[2]],command[0])  

#Prints top crates in final config
top_crates = ""
top_copy = ""
for task1,task2 in zip(crates_dict.values(),crates_copy.values()):
    top_crates += task1.top
    top_copy += task2.top

print("Task 1: ",top_crates)
print("Task 2: ",top_copy)






