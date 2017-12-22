#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::pair;
using std::stack;
using Pair = pair<int, int>;

class KnightConfig
{
private:
    int n, k;
    vector< vector<bool> > taken; // Marks with true positions with placed knights
    vector< vector<int> > attacked; // Marks how many knights attack every position
    vector< Pair > knights; // Linear container of knights
    stack< Pair > states; // Stack of (x, y) pairs; simulates recursion states

    const Pair delta[8] = {{-2, -1}, {-2, 1}, {2, -1}, {2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}}; // For computing knights' moves

    // Deletes the last knight
    void deleteKnight()
    {
        if(!states.empty()) // If there is a knight to delete
        {
            int last = knights.size() - 1;
            taken[knights[last].first][knights[last].second] = false;
            for(int i = 0; i < 8; i++)
            {
                if(knights[last].first + delta[i].first < 0) continue;
                if(knights[last].first + delta[i].first >= n) continue;
                if(knights[last].second + delta[i].second < 0) continue;
                if(knights[last].second + delta[i].second >= n) continue;
                attacked[knights[last].first + delta[i].first][knights[last].second + delta[i].second]--;
            }
            knights.pop_back();
        }
    }

    // Adds a knight on the position marked by the state
    void addKnight(const Pair &state)
    {
        taken[state.first][state.second] = true;
        for(int i = 0; i < 8; i++)
        {
            if(state.first + delta[i].first < 0) continue;
            if(state.first + delta[i].first >= n) continue;
            if(state.second + delta[i].second < 0) continue;
            if(state.second + delta[i].second >= n) continue;
            attacked[state.first + delta[i].first][state.second + delta[i].second]++;
        }
        knights.push_back(state);
    }

    void findConfiguration() // Finds the next k-placed-knights configuration
    {
        // !!! Invariant
        // If a knight is created for a state, then this state is responsible for deleting it by the time
        // all its child states are completed
        Pair state, newState;
        while(knights.size() != k && !states.empty()) // Completes either when a configuration is found or when there are no more
        {
            state = states.top();
            states.pop();
            if(state.first == n) deleteKnight(); // State has jumped out of the board
            else
            {
                // Computes position for the next state
                newState = {state.first, state.second + 1};
                if(newState.second == n)
                {
                    newState.first++;
                    newState.second = 0;
                }

                states.push(newState); // Do not place a knight
                if(attacked[state.first][state.second] == 0) // Place a knight
                {
                    addKnight(state);
                    states.push(newState);
                }
            }
        }
    }

    // Forfeits the current configuration (in order to find a new one)
    void dropState()
    {
        deleteKnight();
        states.pop();
    }

public:
    KnightConfig(int _n, int _k)
    {
        n = _n;
        k = _k;

        taken.resize(n);
        attacked.resize(n);
        for(int i = 0; i < n; i++)
        {
            taken[i].resize(n);
            attacked[i].resize(n);
        }

        states.push({0, 0});
        findConfiguration();
    }

    void printCurrentConfig() const
    {
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
            {
                if(taken[i][j]) cout << 'H';
                else cout << '_';
                if(j == n - 1) cout << endl;
                else cout << ' ';
            }
        cout << endl;
    }

    void findNextConfig()
    {
        dropState();
        findConfiguration();
    }

    bool noMoreConfigs() const
    {
        return states.empty();
    }

};

int main()
{
    KnightConfig it(4, 2);
    cout << "Start" << endl;
    while(!it.noMoreConfigs())
    {
        it.printCurrentConfig();
        it.findNextConfig();
    }
}
