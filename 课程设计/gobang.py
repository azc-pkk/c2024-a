import time

from graphics import  *
# from test import *
from eval import *

GRID_WIDTH = 40
COLUMN = 15
ROW = 15
DEPTH = 3
INF = 999999999
"""放包里了"""
# list1 = []  # AI
# list2 = []  # Human
# list3 = []  # Al
next_step = [0, 0]

def fool():   # 好像没什么用，封装了一下 alpha_beta，看起来更方便？
    # minimax(True, DEPTH)
    alpha_beta(True, DEPTH, -INF, INF)
    return (next_step[0], next_step[1])


"""没有剪枝的版本"""
"""没有剪枝太慢了试不起QwQ"""
def minimax(is_ai, depth):
    if depth == 0 or game_win(list1) or game_win(list2):
        # return evaluation()
        return evaluate()

    val = -INF if is_ai else INF

    for i in range(COLUMN + 1):
        for j in range(ROW + 1):
            if (i, j) in list3 or (not has_neighbour((i, j))):
                continue

            list3.append((i, j))
            if is_ai:
                list1.append((i, j))
                tmp = minimax(not is_ai, depth - 1)
                if tmp > val and depth == DEPTH:
                    next_step[0] = i
                    next_step[1] = j
                val = max(tmp, val)
                list1.remove((i, j))

            else:
                list2.append((i, j))
                tmp = minimax(not is_ai, depth - 1)
                val = min(tmp, val)
                list2.remove((i, j))
            list3.remove((i, j))
            # if depth == DEPTH:
            #     print(f"piece: ({i, j})    eval: {val}")
    return val

def alpha_beta(is_ai, depth, alpha, beta):
    if depth == 0 or game_win(list1) or game_win(list2):
        return evaluate()

    for i in range(COLUMN + 1):
        for j in range(ROW + 1):
            if (i, j) in list3 or (not has_neighbour((i, j))):
                continue
            list3.append((i, j))

            if is_ai:
                list1.append((i, j))
                val = alpha_beta(not is_ai, depth - 1, alpha, beta)
                if alpha < val and depth == DEPTH:
                    next_step[0] = i
                    next_step[1] = j
                alpha = max(alpha, val)
                list1.remove((i, j))
            else:
                list2.append((i, j))
                beta = min(beta, alpha_beta(not is_ai, depth - 1, alpha, beta))
                list2.remove((i, j))
            list3.remove((i, j))
            if alpha >= beta:
                return alpha if is_ai else beta
    return alpha if is_ai else beta

def has_neighbour(piece):
    for i in range(-1, 2):
        for j in range(-1, 2):
            if i == 0 and j == 0:
                continue
            if (piece[0] + i, piece[1] + j) in list3:
                return True
    return False

def game_win(pt_list):
    for n in range(COLUMN + 1):
        for m in range(ROW + 1):
            if n <= COLUMN - 4 and (n, m) in pt_list and (n + 1, m) in pt_list and (n + 2, m) in pt_list and (n + 3, m) in pt_list and (n + 4, m) in pt_list:
                return True
            elif m <= ROW - 4 and (n, m) in pt_list and (n, m + 1) in pt_list and (n, m + 2) in pt_list and (n, m + 3) in pt_list and (n, m + 4) in pt_list:
                return True
            elif n <= COLUMN - 4 and m <= ROW - 4 and (n, m) in pt_list and (n + 1, m + 1) in pt_list and(n + 2, m + 2) in pt_list and(n + 3, m + 3) in pt_list and(n + 4, m + 4) in pt_list:
                return True
            elif n <= COLUMN and m >= 4 and (n, m) in pt_list and (n + 1, m - 1) in pt_list and (n + 2, m - 2) in pt_list and (n + 3, m - 3) in pt_list and (n + 4, m - 4) in pt_list:
                return True

    return False

def main_win():
    win = GraphWin("Gobang AI", GRID_WIDTH * COLUMN, GRID_WIDTH * ROW)
    win.setBackground('#FFC947')

    i1 = 0
    while i1 <= GRID_WIDTH * COLUMN:
        l = Line(Point(i1, 0), Point(i1, GRID_WIDTH * COLUMN))
        l.draw(win)
        i1 += GRID_WIDTH

    i2 = 0
    while i2 <= GRID_WIDTH * ROW:
        l = Line(Point(0, i2), Point(GRID_WIDTH * ROW, i2))
        l.draw(win)
        i2 += GRID_WIDTH
    return  win

def main():
    win = main_win()
    game_round = 0
    is_over = False
    while not is_over:
        if game_round % 2 == 1: # AI
            start_time = time.time()
            """人机对弈"""
            pt = fool()
            end_time = time.time()
            print(pt)

            list1.append(pt)
            list3.append(pt)

            piece = Circle(Point(GRID_WIDTH * pt[0], GRID_WIDTH * pt[1]), 16)
            """测试代码--左右互搏"""
            # pt = win.getMouse()
            # pt = (round(pt.getX()/GRID_WIDTH), round(pt.getY()/GRID_WIDTH))
            # if (pt[0], pt[1]) in list3:
            #     continue
            #
            #
            # list1.append(pt)
            # list3.append(pt)
            #
            # piece = Circle(Point(GRID_WIDTH * pt[0], GRID_WIDTH * pt[1]), 16)
            """End of test"""
            piece.setFill('White')
            piece.draw(win)
            print(f"It took {end_time - start_time} seconds for AI to think.")

            if game_win(list1):
                is_over = True

            game_round += 1

        else:
            pt = win.getMouse()
            pt = (round(pt.getX()/GRID_WIDTH), round(pt.getY()/GRID_WIDTH))
            if (pt[0], pt[1]) in list3:
                continue


            list2.append(pt)
            list3.append(pt)

            piece = Circle(Point(GRID_WIDTH * pt[0], GRID_WIDTH * pt[1]), 16)
            piece.setFill('Black')
            piece.draw(win)

            if game_win(list2):
                is_over = True

            game_round += 1

        print(f"Evaluation of round {game_round} is: " + str(evaluate()))
    print('Game Over!')
    while True:
        win.getMouse()


if __name__ == '__main__':
    main()