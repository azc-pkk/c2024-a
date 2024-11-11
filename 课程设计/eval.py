
COLUMN = 15
ROW = 15

SEVEN = 7
SEVEN_SCORE = 500

SHAPE = [
    # 连五
    (1000000, (1, 1, 1, 1, 1)),
    # 活四
    (100000, (0, 1, 1, 1, 1, 0)),
    # 冲四
    (50000, (2, 1, 1, 1, 1, 0)),
    (50000, (2, 1, 1, 1, 0, 1)),
    (50000, (1, 1, 0, 1, 1)),
    # 活三
    (5000, (0, 1, 1, 1, 0)),
    (5000, (0, 1, 1, 0, 1)),
    # 眠三
    (500, (2, 0, 1, 1, 1, 0, 2)), # num 7
    (500, (1, 0, 1, 0, 1)),
    (500, (1, 1, 0, 0, 1)),
    (500, (2, 1, 1, 1, 0, 0)),
    (500, (2, 1, 1, 0, 1, 0)),
    (500, (2, 1, 0, 1, 1, 0)),
    # 活二
    (50, (0, 1, 0, 0, 1, 0)),
    (50, (0, 1, 0, 1, 0)),
    (50, (0, 0, 1, 1, 0, 0)),
    # 眠二
    (10, (1, 0, 0, 0, 1)),
    (10, (2, 1, 0, 0, 1, 0)),
    (10, (2, 1, 0, 1, 0, 0)),
    (10, (2, 1, 1, 0, 0, 0))
]
list1 = []  # AI
list2 = []  # Human
list3 = []  # All
calculated = []

# 不会出现 2 1 0 1 1 0 1 1 被判一个眠三的情况，因为后面俩没算分
def evaluate():
    my_score = 0
    en_score = 0
    calculated.clear()
    for piece in list1:
        my_score += cal(piece[0], piece[1], 1, 1, list1, list2)
        my_score += cal(piece[0], piece[1], 1, -1, list1, list2)
        my_score += cal(piece[0], piece[1], 0, 1, list1, list2)
        my_score += cal(piece[0], piece[1], 1, 0, list1, list2)

    calculated.clear()
    for piece in list2:
        en_score += cal(piece[0], piece[1], 1, 1, list2, list1)
        en_score += cal(piece[0], piece[1], 1, -1, list2, list1)
        en_score += cal(piece[0], piece[1], 0, 1, list2, list1)
        en_score += cal(piece[0], piece[1], 1, 0, list2, list1)

    return my_score - en_score


def cal(x, y, dx, dy, my_list, en_list):
    for line in calculated:
        if (x, y) in line:
            return 0

    max_score = (0, None)
    for length in range(5, 7):
        for offset in range(-length, 1):
            tmp_list = []
            for i in range(length):
                tmp_list.append(check(x + (i + offset) * dx, y + (i + offset) * dy, my_list, en_list))
            for (score, shape) in SHAPE:
                if score > max_score[0] and shape == tuple(tmp_list):
                    tmp_list = []
                    for i in range(length):
                        tmp_list.append((x + (i + offset) * dx, y + (i + offset) * dy))
                    max_score = (score, tuple(tmp_list))

    # 把唯一一个七子单独拿出来提提速
    if max_score[0] < SEVEN_SCORE:
        for offset in range(-7, 1):
            tmp_list = []
            for i in range(7):
                tmp_list.append(check(x + (i + offset) * dx, y + (i + offset) * dy, my_list, en_list))
            if SHAPE[SEVEN] == tuple(tmp_list):
                tmp_list = []
                for i in range(7):
                    tmp_list.append((x + (i + offset) * dx, y + (i + offset) * dy))
                max_score = (SEVEN_SCORE, tuple(tmp_list))
                break

    if max_score[0] != 0:
        calculated.append(max_score[1])
    return max_score[0]


def check(x, y, my_list, en_list):
    if (x, y) in my_list:
        return 1
    elif (x, y) in en_list:
        return 2
    return 0