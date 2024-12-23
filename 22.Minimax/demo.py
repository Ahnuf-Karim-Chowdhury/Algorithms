import sys
import numpy as np
import random
import pickle
from PyQt6 import QtWidgets, QtGui, QtCore

class TicTacToe:
    def __init__(self):
        self.board = np.zeros((3, 3), dtype=int)
        self.current_player = 1  # Player 1 starts

    def reset(self):
        self.board.fill(0)
        self.current_player = 1

    def available_actions(self):
        return list(zip(*np.where(self.board == 0)))

    def make_move(self, action):
        if self.board[action] == 0:
            self.board[action] = self.current_player
            self.current_player = -1 if self.current_player == 1 else 1
            return True
        return False

    def evaluate_board(self):
        for player in [1, -1]:
            for row in self.board:
                if np.all(row == player):
                    return player
            for col in self.board.T:
                if np.all(col == player):
                    return player
            if np.all(np.diag(self.board) == player) or np.all(np.diag(np.fliplr(self.board)) == player):
                return player
        if not self.available_actions():
            return 0  # Draw
        return None  # Game ongoing

class QLearningAgent:
    def __init__(self, learning_rate=0.1, discount_factor=0.9, exploration_rate=1.0, exploration_decay=0.995):
        self.q_table = {}
        self.learning_rate = learning_rate
        self.discount_factor = discount_factor
        self.exploration_rate = exploration_rate
        self.exploration_decay = exploration_decay
        self.load_q_table()

    def load_q_table(self):
        try:
            with open('q_table.pkl', 'rb') as f:
                self.q_table = pickle.load(f)
        except FileNotFoundError:
            self.q_table = {}

    def save_q_table(self):
        with open('q_table.pkl', 'wb') as f:
            pickle.dump(self.q_table, f)

    def get_q_value(self, state, action):
        return self.q_table.get((tuple(state.flatten()), action), 0.0)

    def update_q_value(self, state, action, reward, next_state):
        current_q = self.get_q_value(state, action)
        max_future_q = max(self.get_q_value(next_state, a) for a in self.available_actions) if next_state is not None else 0
        new_q = (1 - self.learning_rate) * current_q + self.learning_rate * (reward + self.discount_factor * max_future_q)
        self.q_table[(tuple(state.flatten()), action)] = new_q

    def choose_action(self, state, available_actions):
        if random.random() < self.exploration_rate:
            return random.choice(available_actions)
        q_values = [self.get_q_value(state, action) for action in available_actions]
        return available_actions[np.argmax(q_values)]

    def decay_exploration(self):
        self.exploration_rate *= self.exploration_decay

class TicTacToeGUI(QtWidgets.QWidget):
    def __init__(self):
        super().__init__()
        self.agent = QLearningAgent()
        self.game = TicTacToe()
        self.last_player_move = None  # Store the last move
        self.initUI()

    def initUI(self):
        self.setWindowTitle('Tic Tac Toe')
        self.setGeometry(100, 100, 300, 300)
        self.grid_layout = QtWidgets.QGridLayout()
        self.buttons = []

        for i in range(3):
            row = []
            for j in range(3):
                button = QtWidgets.QPushButton('')
                button.setFont(QtGui.QFont('Arial', 24))
                button.clicked.connect(lambda _, x=i, y=j: self.player_move(x, y))
                self.grid_layout.addWidget(button, i, j)
                row.append(button)
            self.buttons.append(row)

        self.setLayout(self.grid_layout)

    def player_move(self, x, y):
        if self.game.make_move((x, y)):
            self.last_player_move = (x, y)  # Save the last player move
            self.buttons[x][y].setText('X')
            self.check_game_state()
            if self.game.evaluate_board() is None:
                self.agent_move()

    def agent_move(self):
        available_actions = self.game.available_actions()
        if available_actions:
            action = self.agent.choose_action(self.game.board, available_actions)
            self.game.make_move(action)
            self.buttons[action[0]][action[1]].setText('O')
            self.check_game_state()

    def check_game_state(self):
        reward = self.game.evaluate_board()
        if reward is not None:
            if reward == 1:
                QtWidgets.QMessageBox.information(self, 'Game Over', 'You win!')
                if self.last_player_move:
                    self.agent.update_q_value(self.game.board, self.last_player_move, -1, None)
            elif reward == -1:
                QtWidgets.QMessageBox.information(self, 'Game Over', 'Agent wins!')
                if self.last_player_move:
                    self.agent.update_q_value(self.game.board, self.last_player_move, 1, None)
            elif reward == 0:
                QtWidgets.QMessageBox.information(self, 'Game Over', 'It\'s a draw!')
                if self.last_player_move:
                    self.agent.update_q_value(self.game.board, self.last_player_move, 0, None)

            self.agent.save_q_table()  # Save Q-table after each game
            self.game.reset()
            self.clear_buttons()

    def clear_buttons(self):
        for row in self.buttons:
            for button in row:
                button.setText('')

if __name__ == "__main__":
    app = QtWidgets.QApplication(sys.argv)
    window = TicTacToeGUI()
    window.show()
    sys.exit(app.exec())
