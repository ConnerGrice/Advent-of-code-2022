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
        item.parent = self

#A class that represents a file
class File(SystemObject):
    def __init__(self,name,size):
        super().__init__(name,size)

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

#Reads all the puzzle commands
with open("input.txt","r") as f:
    puzzle = f.readlines()

test1 = [
    "$ cd /",
    "$ ls",
    "dir a",
    "dir b",
    "123 file1",
    "$ cd a",
    "$ ls",
    "1 file2",
    "1 file3",
    "$ cd ..",
    "$ cd b",
    "$ ls",
    "2 file4",
    "200 file5"
]

test = [
    "$ cd /",
    "$ ls",
    "dir a",
    "14848514 b.txt",
    "8504156 c.dat",
    "dir d",
    "$ cd a",
    "$ ls",
    "dir e",
    "29116 f",
    "2557 g",
    "62596 h.lst",
    "$ cd e",
    "$ ls",
    "584 i",
    "$ cd ..",
    "$ cd ..",
    "$ cd d",
    "$ ls",
    "4060174 j",
    "8033020 d.log",
    "5626152 d.ext",
    "7214296 k",
    ]   

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


#Once all files have been placed in their directories, update all directory sizes
for item in dir_dict.values():
    item.updateSize()

#Update any directories that do not get caught by the first sweep
for dir in dir_dict.values():
    if dir.size == 0:
        print(dir)
        dir.updateSize()
        print(dir)

total = 0
#Loop through all directories 
for item in dir_dict.values():
    #Do not count the root directory
    if item.name == "/":
        print(item)
        continue

    #Sum the size of all valid directories
    if item.size <= 100000:
        total += item.size
    
    print(item)

print("Task 1: ",total," Bytes")




    