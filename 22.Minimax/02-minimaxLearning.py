import numpy as np
import random

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
        # Simple evaluation function (win/loss/draw)
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

    def get_q_value(self, state, action):
        return self.q_table.get((tuple(state.flatten()), action), 0.0)

    def update_q_value(self, state, action, reward, next_state):
        current_q = self.get_q_value(state, action)
        max_future_q = max(self.get_q_value(next_state, a) for a in available_actions) if next_state is not None else 0
        new_q = (1 - self.learning_rate) * current_q + self.learning_rate * (reward + self.discount_factor * max_future_q)
        self.q_table[(tuple(state.flatten()), action)] = new_q

    def choose_action(self, state, available_actions):
        if random.random() < self.exploration_rate:
            return random.choice(available_actions)
        q_values = [self.get_q_value(state, action) for action in available_actions]
        return available_actions[np.argmax(q_values)]

    def decay_exploration(self):
        self.exploration_rate *= self.exploration_decay

def main():
    agent = QLearningAgent()
    game = TicTacToe()
    episodes = 10000

    for episode in range(episodes):
        game.reset()
        state = game.board.copy()
        done = False
        while not done:
            available_actions = game.available_actions()
            action = agent.choose_action(state, available_actions)
            game.make_move(action)
            reward = game.evaluate_board()

            next_state = game.board.copy()
            if reward is not None:
                if reward == 1:  # Player 1 wins
                    agent.update_q_value(state, action, 1, None)
                    done = True
                elif reward == -1:  # Player -1 wins
                    agent.update_q_value(state, action, -1, None)
                    done = True
                elif reward == 0:  # Draw
                    agent.update_q_value(state, action, 0, None)
                    done = True
                else:  # Game ongoing
                    agent.update_q_value(state, action, 0, next_state)
            state = next_state
        agent.decay_exploration()

    print("Training complete.")

if __name__ == "__main__":
    main()
