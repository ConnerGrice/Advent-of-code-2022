#include <map>
#include <vector>

/*A singleton class that hold the information about what
games will result in what score and can be used as a look-up-table

|Player  |Rock|Paper|Scissors|
|--------|----|-----|--------|
|Opponent|A   |B    |C       |
|Player  |X	  |Y    |Z       |

Scores:
	Win: 6
	Draw: 3
	Loss: 0

	Rock: 1
	Paper: 2
	Scissors: 3
*/
class WinStates {
	//Private instances of the look-up-table
	static WinStates* instance;
	std::map<std::pair<char, char>, int> mStates;

	//Construct table in constructor
	WinStates() {
		std::tuple<char, char, char> opp{ 'A','B','C' };
		std::tuple<char, char, char> player{ 'X','Y','Z' };

	};
	
	//Default destructor
	~WinStates() = default;
public:
	//Does not allow copy or assignment of more than 1 instance
	WinStates(const WinStates&) = delete;
	WinStates& operator=(const WinStates&) = delete;

	//Gets the single instance of this class
	static WinStates* getInstance() {
		if (!instance) {
			instance = new WinStates();
		}
		return instance;
	};

	//Gets the score of a given game
	int getState(std::pair<char, char> play) {
		return mStates[play];
	};
};