"""
Day 2:
    Puzzle input    -> List of rock, paper, scissors games
                    -> First (A = Rock) (B = Paper) (C = Scissors)
                    -> Second (X = Rock) (Y = Paper) (Z = Scissors)

    Scoring -> Rock = 1
            -> Paper = 2
            -> Scissors = 3
            -> Win = 6
            -> Draw = 3
            -> Loss = 0
    
    Task 1  -> What is the total score after playing all games
    Task 2  -> Second is actually the outcome
                -> X = Loss
                -> Y = Draw
                -> Z = Win
"""

def outcome1(player1,player2):
    """
    Calculates if a game is a win, draw, or loss and returns the correct score
    player1: string -> Represents hand player will play
    player2: string -> Represents hand the opponent will play
    """

    #Dict containing the game results
    result = {
        "W" : [("X","C"),("Y","A"),("Z","B")],  #Winning combos
        "D" : [("X","A"),("Y","B"),("Z","C")],  #Drawing combos
        "L" : [("X","B"),("Y","C"),("Z","A")]   #Lossing combos
    }

    #Checks how the game will result and returns the score
    if (player1,player2) in result.get("W"):
        return 6
    elif (player1,player2) in result.get("D"):
        return 3
    elif (player1,player2) in result.get("L"):
        return 0

def outcome2(player1,player2):
    """
    Calculates which hand the player should play to get the wanted outcome
    player1: string -> Represents outcome the player wants
    player2: string -> Represents hand the opponent will play   
    """
    result = {
        "Rock"      : [("X","B"),("Y","A"),("Z","C")],  #Must play rock
        "Paper"     : [("X","C"),("Y","B"),("Z","A")],  #Must play paper
        "Scissors"  : [("X","A"),("Y","C"),("Z","B")]   #Must play scissors
    }

    #Checks which hand should be played and returns the score
    if (player1,player2) in result.get("Rock"):
        return 1
    elif (player1,player2) in result.get("Paper"):
        return 2
    elif (player1,player2) in result.get("Scissors"):
        return 3


def score1(player1):
    """
    Calculates the score gained from the hand that the player plays
    """
    points = {
        "X" : 1,    #Rock
        "Y" : 2,    #Paper
        "Z" : 3     #Scissors
    }
    return points.get(player1)

def score2(player1):
    """
    Calculates the score gained from the outcome of the game
    """
    points = {
        "X" : 0,    #Loss
        "Y" : 3,    #Draw
        "Z" : 6     #Win
    }

    return points.get(player1)


#Opens the file with the puzzle input
with open("input.txt","r") as f:

    #Score counters for both tasks
    total1 = 0  #Task 1 counter
    total2 = 0  #Task 2 counter

    #Loops through all the lines in the input
    for line in f:
        
        #Splits each line into both player options
        opponent,player = line.split()

        #Sums the scores up for each game
        total1 += outcome1(player,opponent) + score1(player)
        total2 += outcome2(player,opponent) + score2(player)
    
print("Task 1 total :",total1)
print("Task 2 total :",total2)



