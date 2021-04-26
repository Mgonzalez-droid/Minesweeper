#ifndef MineCounter_h
#define MineCounter_h

struct MineCounter{
    int mines;
    int counterNumber;
    std::vector<sf::Sprite> counter;
    
    MineCounter();
    void ModifyMines(int difference);
    std::vector<sf::Sprite> GetCounter();
    void SetCounter();
    void SetMines(int mines);
    void SetCounterNumber(int counterNumber);
    void PrintCounter(sf::RenderWindow &window);
    void DecrementCounter(bool aMine = false);
    void IncrementCounter(bool aMine = false);
};

#endif /* MineCounter_h */
