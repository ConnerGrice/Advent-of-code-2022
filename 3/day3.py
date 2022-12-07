import string

#Class for each backpack
class Backpack:

    def __init__(self,contents):
        """
        Constructor
        contents: List  -> Items in the entire backpack
        comp1: List     -> First half of the backpack
        comp2: list     -> Second half of backpack
        """
        self.contents = contents
        self.comp1 = contents[:int(len(contents)/2)]
        self.comp2 = contents[int(len(contents)/2):]

    def compare(self):
        """
        Finds the item that is in both halves of the backpack
        """

        #Loops through items in the first half
        for item1 in self.comp1:
            #Loops through items in the second half
            for item2 in self.comp2:
                #Finds the letter that is in both halves
                if item1 == item2:
                    return item1
    
    def findDup(self):
        """
        Finds the duplicate character and calculates the score
        """
        item = self.compare()
        return score(item)

def score(letter):
    """
    Calculates the score based on the letter
    """

    #List of all characters, upper and lower
    alph = list(string.ascii_letters)
    
    #Calculates socre based on position in list
    for i, char in enumerate(alph):
        if letter == char:
            return i+1

def makeSet(team):
    elf1 = set(team[0].contents)
    elf2 = set(team[1].contents)
    elf3 = set(team[2].contents)

    return elf1,elf2,elf3
    
#Opens the file
with open("input.txt","r") as f:

    #Score counter
    result1 = 0

    #Loops through all lines in input file
    platoon = []

    for line in f:
        #Converts the line in the list to a list of characters
        things = list(line)

        #Removes the "\n" character from the end of the list
        things.pop()

        #Declares backpack object
        pack = Backpack(things)

        #Sums the score for each backpack
        result1 += pack.findDup()

        #Add backpack into a list of all backpacks for task 2
        platoon.append(pack)


print("Task 1: ",result1)

#Convert the list of backpacks into a 2D array
#Each element contains 3 backpack objects
platoon = [platoon[i:i+3] for i in range(0,len(platoon),3)]

#Task 2 counter
result2 = 0

#Loops through each team of 3
for group in platoon:

    #Converts each list of objects into sets for easier logic
    member1,member2,member3 = makeSet(group)
    
    #Finds which element of the set is shared between all 3 backpacks
    badge = member1 & member2 & member3

    #Add the score to the result
    result2 += score(badge.pop())

print("Task 2: ",result2)
