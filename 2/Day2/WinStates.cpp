#include "WinStates.h"

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

WinStates* WinStates::_instance = nullptr;

WinStates::WinStates() {
	std::vector<char> opp{ 'A','B','C' };
	std::vector<char> player{ 'X','Y','Z' };
	for (char played : player) {
	}
}

WinStates* WinStates::getInstance() {
	if (!_instance) {
		_instance = new WinStates();
	}
	return _instance;
}