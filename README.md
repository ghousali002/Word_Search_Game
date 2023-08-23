# Word_Search_Game
C++ word search game with a menu. Players find words in a grid, scoring points. It has new/resume game options, difficulty levels, high scores. Supports pausing. Uses files for saving/resuming games and high scores.

 Detailed Description: The provided code is a C++ program that implements a word search game with a menu-driven interface. Here's a brief overview of its functionality:

1. **Menu Interface (`game_menu()`):** The game starts with a menu that allows the player to choose between different options: starting a new game, resuming a saved game, selecting game levels, viewing high scores, and exiting the game.

2. **New Game (`new_game()`):** This function handles the logic for starting a new game. It initializes the game board, sets the level, and allows the player to input words to search for in the board. The player earns points for finding valid words, and the game continues until the player's lives are exhausted.

3. **Resume Game (`resume_game()`):** This function allows the player to resume a previously saved game. It reads the saved game state from a file and continues the gameplay from where it was left off.

4. **Levels of Game (`levels_of_game()`):** This function lets the player select the game difficulty level (easy, medium, or hard). It then sets up the game board and allows the player to search for words just like in the new game mode.

5. **View High Scores (`view_highscore()`):** This function displays the highest scores achieved in previous games. The scores are read from a file named "highrecord.txt."

6. **Exit Game (`exit_game()`):** This function provides a clean exit from the game, displaying a goodbye message.

7. **Word Search Logic (`row_wise()`, `col_wise()`, etc.):** These functions handle the actual word search logic. They search for the input word in various directions on the game board (row-wise, column-wise, diagonally, etc.). If the word is found, the player's score is increased.

8. **Pause and Resume (`pausegame.txt`):** The game supports pausing and resuming. When the player enters 'p' or 'P' during gameplay, the current game state (including the board, score, lives, and level) is saved to a file named "pausegame.txt." The player can then choose to resume the game later.

9. **Dictionary Check (`check_Dictionary()`, `get_length()`):** The program checks if a given word exists in its dictionary. It also includes functions to determine the length of a word.

10. **Saving High Scores (`save_high_score()`):** This function saves the player's score to the "highrecord.txt" file after the game ends.

Overall, the program provides a basic word search game experience with different levels of difficulty, the ability to pause and resume games, and tracking of high scores. It involves various C++ concepts, including dynamic memory allocation, file input/output, and functions for different aspects of the game.
