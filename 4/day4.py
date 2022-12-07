
class CleaningJob:

    def __init__(self,limits):
        self.limits = limits

    def numLine(self):
        """
        Converts bounds into a set of numbers
        """
        lower = self.limits[0]
        upper = self.limits[1]

        return set([i for i in range(lower,upper+1)])
    
    def inside(self,job):
        """
        Checks if jobs are a subset/superset of eachother
        job: CleaningJob -> The other job to compare
        """

        #Gets range of given job
        job_set = job.numLine()

        #Gets range of current job
        current_set = self.numLine()

        #Checks if jobs are subsets of eachother
        if current_set.issubset(job_set) | job_set.issubset(current_set):
            return True
        
        #If not subset/superset
        return False

    def overlap(self,job):
        """
        Checks if jobs overlaps with current job at all
        """

        #Gets range of given job
        job_set = job.numLine()

        #Gets range of current job
        current_set = self.numLine()

        #Checks if any of the numbers in the sets match
        if current_set & job_set:
            return True
        
        return False

        
def getBounds(string):
    """
    Gets upper and lower bound from string in the format "upper-lower"
    """
    
    #Splits string to 2 integers
    lower,upper = string.split("-")

    return int(lower),int(upper)

#Opens puzzle input file
with open("input.txt","r") as f:

    #Counter for pairs with full overlap
    full_overlap = 0

    #Counter for pairs with any overlap
    partial_overlap = 0

    #Loops through every line of the file
    for line in f:
        #Removes newline and seperates elf pair
        pair = line.strip("\n").split(",")

        #Converts each elf into the correct formet
        elf1,elf2 = getBounds(pair[0]),getBounds(pair[1])
        elf1Job,elf2Job = CleaningJob(elf1),CleaningJob(elf2)

        #Checks if pair fully overlap
        if elf1Job.inside(elf2Job): 
            full_overlap += 1
        
        #Checks if pair overlap at all 
        if elf1Job.overlap(elf2Job):
            partial_overlap += 1
    
    print(full_overlap)
    print(partial_overlap)       

