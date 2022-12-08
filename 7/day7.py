#Directory class (contains files or directories)    
class Directory:
    def __init__(self,name):
        self.name = name
        self.children = []
    
    def contains(item):
        self.children.append(item)
    
    


#Command class 

#File class


with open("input.txt","r") as f:
    puzzle = f.readlines()


test =[ 
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
    "7214296 k"
    ]
    
current_dir = ""
list_dir = []
for line in puzzle:
    comp = line.rstrip("\n").split(" ")
    last_dir = ""
    if comp[0] == "$":

        #MOVING AROUND
        if comp[1] == "cd":
            #Move back
            if comp[2] == "..":
                current_dir = last_dir
                continue
            elif comp[2] == "/":
                continue
            #Move in
            last_dir = current_dir
            current_dir += f"/{comp[2]}"

        #COLLECTING DIR INFO
        elif comp[1] == "ls":
            continue
    else:
        continue

    

