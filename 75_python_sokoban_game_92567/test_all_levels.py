import subprocess
import re


num_levels = 100
algo_1ist=["BFS", "DFS", "AStar", "HillClimber","Genetic", "MCTS"]

for algo in algo_1ist:
    num_successes = 0
    num_failures = 0    

    for i in range(num_levels):
        process = subprocess.run(
            ["python3", "game.py", "--l", str(i), "--agent", algo], stdout=subprocess.PIPE)
        output = process.stdout.decode("utf-8")
        # print(output)
        if "GAME WON IN" in output:
            num_successes += 1
        elif "SOLUTION NOT FOUND" in output:
            num_failures += 1
    print("Running ", algo, " on all Levels..")
    print("Successes: ", num_successes)
    print("Failures: ", num_failures)