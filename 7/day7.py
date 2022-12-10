
#SYSTEMOBJECT CLASS====================================================================================
#Class for a basic system object that has a name and some sort of memory allocation
class SystemObject:
    def __init__(self,name,size):
        self.name = name
        self.size = size
        self.parent = 0
    
    def updateParent(self,item):
        """
        Gives the directory its parent directory
        """
        item.parent = (self)

#FILE CLASS===========================================================================================
#A class that represents a file
class File(SystemObject):
    def __init__(self,name,size):
        super().__init__(name,size)

#DIRECTORY CLASS===========================================================================================
#Directory class (contains files or directories)    
class Directory(SystemObject):
    def __init__(self,name):
        super().__init__(name,0)
        self.children = []
    
    def __str__(self):
        """
        Prints objects directly connected
        """

        #Prints name of current directory
        result = f"{self.size} {self.name}:\n"
        
        #Loops through each child and prints it
        for item in self.children:
            #Check the kind of object and tags it accordingly
            if isinstance(item,Directory):
                result += "\t Dir "
            else:
                result += "\t File"
            
            result += f"\t- {item.name:>10} {item.size} byptes\n"
        
        return result
    
    def __lt__(self,other):
        """
        Allows for directories to be sorted by size
        """
        return self.size < other.size

    def updateSize(self):
        """
        Gets the total *memory allocation* of all items inside
        """
        self.size = sum([item.size for item in self.children])

    def addChild(self,item):
        """
        Adds a directory or file into the current directory
        """
        self.children.append(item)
        self.updateParent(item)
        self.updateSize()

#FUNCTIONS===========================================================================================
def calculateSize(directories):
    """
    Updates the size for all directories
    """
    for dir in directories.values():
        #Checks if directory is at the end of a path (only contains files)
        if all(isinstance(child,File) for child in dir.children):

            #Parse down the path to the root file, updateing the size as it goes
            adult = dir
            while adult.parent != 0:
                dir_temp = adult.parent
                dir_temp.updateSize()
                adult = dir_temp

def doTask1(directories):
    """
    Finds all the directories that have a size of more than 100000
    and sums thair sizes
    """
    #Loop through all directories 
    total = 0
    for item in directories.values():

        #Sum the size of all valid directories
        if item.size <= 100000:
            total += item.size

    return total

def doTask2(directories,free):
    """
    Calculates the space needed for the update and finds the directory that is bigger but closest to that value
    """
    space_needed = 30000000 - free
    #Generates list of directories with are big enough and sorts them in acsending order
    to_remove = sorted([x for x in directories.values() if x.size >= space_needed])
    return to_remove[0]

#MAIN PROGRAMM===============================================================================================
#Reads all the puzzle commands
with open("input.txt","r") as f:
    puzzle = f.readlines()

#Initialise root directory
dir_root = Directory("//")
dir_dict = {"//": dir_root}

#Initialise starting positions
current_dir = dir_root
current_dir_string = ""
last_dir = ""
last_dir_string = ""

#Loops through the puzzle inputs
for line in puzzle:
    #Splits into components of the command, and removes newline character
    comp = line.rstrip("\n").split(" ")
    
    #Checks if the input is a command
    if comp[0] == "$":

        #If the command is for maing around the file system
        if comp[1] == "cd":
            #If command wants to go back to previous directory
            if comp[2] == "..":
                #Gets parent of current directory
                last_dir = current_dir.parent

                #Moves the current directory into the previous
                current_dir = last_dir
                current_dir_string = last_dir.name
                continue
            
            #Else the command wants to move into a directory
            #Finds the directory and moves into it
            current_dir_string += f"{comp[2]}/"
            current_dir = dir_dict[current_dir_string]

    #If not a command, then were getting the contents of a directory
    else:
        #If content is another directory
        if comp[0] == "dir":
            #Generate name of new directory and create it with that name
            dir_new_string = current_dir_string + f"{comp[1]}/"
            dir_new = Directory(dir_new_string)

            #Place new directory into storage
            dir_dict[dir_new_string] = dir_new

            #Add this directory as a child of the current directory
            current_dir.addChild(dir_new)
        
        #Else the content will be a file
        else:
            #Create file and give it the specified size
            file_new = File(comp[1],int(comp[0]))

            #Add this file as a child of the current directory
            current_dir.addChild(file_new)

#Updates the size of all directories after all have been placed in the correct places
calculateSize(dir_dict)

#Gets the sum of sizes of all the directories above 100000 bytes
task1 = doTask1(dir_dict)
print()
print("Task 1: ",task1," Bytes")

#Calculates the space free.
free_space = 70000000 - dir_dict["//"].size

#Finds the smallest directory to delete to make space for the update
dir_delete = doTask2(dir_dict,free_space)

print()
print("Local Disk (//:)")
print(f"{free_space} B free of 30000000 B")
print(f"To update, delete: ")
print(dir_delete)
print()
print("Task 2: ",dir_delete.size)
