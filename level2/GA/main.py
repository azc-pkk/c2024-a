import random

maze = [
    "### ################",
    "#   #   #   # #   ##",
    "# #   #   # #   #  #",
    "##  ## # #  # ## # #",
    "#  #   #  # #    # #",
    "# #  #  # # # # ## #",
    "# ##### # # #  #   #",
    "#    #  # #  # # # #",
    "####   #   # ### # #",
    "#  ###  # ##     # #",
    "##   # #  # # ##  ##",
    "#  #   # #   #  #  #",
    "##  ## # # #   ### #",
    "# #   ## # # ## ## #",
    "#  # #   #  #      #",
    "##   # #### # # ####",
    "#  ###   #    ##   #",
    "# #   ## ## #   # ##",
    "#   #  #   #  #    #",
    "########## #########"
]

LEN = 20
start_x = 19
start_y = 10
end_x = 0
end_y = 3

class Population:
    def __init__(self):
        self.generation = 0
        self.genomes = []
        self.mutation_rate = 0.05
        self.fitness = {}
        self.tot_fitness = 0
        return

    def roulette(self):
        aim_score = self.tot_fitness * random.random()
        tot = 0
        for i in range(len(self.genomes)):
            tot += self.fitness[i]
            if tot >= aim_score:
                return self.genomes[i]

    def evaluate(self):
        idx = 0
        for individual in self.genomes:
            x = start_x
            y = start_y
            flag = False
            steps = 0
            times = 0
            for op in individual:
                steps += 1
                if op == 1:
                    if x == 0 or maze[x-1][y] == ' ':
                        times += 1
                    else:
                        x -= 1
                elif op == 2:
                    if x == LEN - 1 or maze[x+1][y] == ' ':
                        times += 1
                    else:
                        x += 1
                elif op == 3:
                    if y == 0 or maze[x][y-1] == ' ':
                        times += 1
                    else:
                        y -= 1
                else:
                    if y == LEN - 1 or maze[x][y+1] == ' ':
                        times += 1
                    else:
                        y += 1
            if x == end_x and y == end_y:
                flag = True
            self.fitness[idx] = 10000 * (10000 if flag else 1) / ((steps + 1) * (times + 1))
            self.tot_fitness += 10000 * (10000 if flag else 1) / ((steps + 1) * (times + 1))
            idx += 1


# 步数s，撞墙次数t，能否到达终点f 10000 * (f ? 10 : 1)/ (s * t)
def mutation(gene):
    if len(gene) == 0:
        return
    spot = int(random.random() * (len(gene) - 1))
    num = int(4 * random.random())
    gene[spot] = num
    return

def cross_over(original_generation, next_generation):
    dad = original_generation.roulette()
    mum = original_generation.roulette()
    if dad == mum:
        return
    spot_1 = int(len(dad) * random.random())
    if spot_1 == 0:
        spot_1 += 1
    spot_2 = int(len(mum) * random.random())
    if spot_2 == 0:
        spot_2 += 1
    child_1 = dad[:spot_1] + mum[spot_2 + 1:]
    child_2 = mum[:spot_2] + dad[spot_1 + 1:]
    next_generation.genomes.append(child_1)
    next_generation.genomes.append(child_1)
    return
def main():
    origin = Population()
    for i in range(500):
        new_gene = []
        gen_len = int(random.random() * 80)
        for j in range(gen_len):
            op = int(random.random() * 4)
            new_gene.append(op)
        origin.genomes.append(new_gene)
    for i in range(100):
        print(f"Generation {i} is reproducing...")
        next_g = Population()
        origin.evaluate()
        for j in range(20 + int(5 * random.random())):
            cross_over(origin, next_g)
        origin = next_g
        for individual in origin.genomes:
            if random.random() <= origin.mutation_rate:
                mutation(individual)
    origin.evaluate()
    max_score = 0
    best = []
    idx = 0
    for individual in origin.genomes:
        if origin.fitness[idx] > max_score:
            best = individual
            max_score = origin.fitness[idx]
            idx += 1
    print(best)
    return



if __name__ == "__main__":
    main()