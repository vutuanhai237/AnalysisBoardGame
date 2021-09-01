import random
import numpy as np
import matplotlib.pyplot as plt
# ['nhà', 'kv', 'ch', 'bx', 'ct']
site = [0, 1, 2, 3, 4, 5]
# Danh sách các điểm khí vận
list_site_kv = [2, 17, 33]
# Danh sách các điểm cơ hội
list_site_ch = [7, 22, 36]
# Danh sách các điểm bến xe
list_site_bx = [5, 15, 25,35]
# Danh sách các điểm công ty
list_site_ct = [12, 28]
# Danh sách các điểm không ảnh hướng 
list_site_vodung = [0, 10, 20, 30]
# Danh sách các điểm nhà
list_site_nha = [x for x in range(0, 40) if (x not in list_site_kv) and (x not in list_site_ch) and (x not in list_site_bx) and (x not in list_site_ct) and (x not in list_site_vodung)]

def den_site_gan_nhat(x, list_site):
    kcs = []
    for site in list_site:
        kcs.append(abs(site - x))
    min_kc = min(kcs)
    min_index_kc = kcs.index(min_kc)
    return list_site[min_index_kc]

def co_hoi (x, command):
    if command == 5:
        x = 24
    if command == 13:
        x = 11
    # Đến ô bến xe gần nhất
    if command == 15 or command == 16:
        x = den_site_gan_nhat(x, list_site_bx)
    if command == 7:
        x = 30
    if command == 12:
        x = 39
    if command == 14:
        x = 5
    # Đến ô công ty gần nhất
    if command == 10:
        x = den_site_gan_nhat(x, list_site_ct)
    # Đến ô bắt đầu
    if command == 11:
        x = 0
    # Đi lùi 3 bước
    if command == 4:
        x = x - 3
        if x < 0:
            x = 40 - x
    return x

def khi_van (x, command):
    # Vào tù
    if command == 14:
        x = 30
    # Đến ô bắt đầu
    if command == 10:
        x = 0
    return x

maps = np.zeros((40))

# Khí vận
maps[2] = site[1]
maps[17] = site[1]
maps[33] = site[1]

# cơ hội
maps[7] = site[2]
maps[22] = site[2]
maps[36] = site[2]

# bến xe
maps[5] = site[3]
maps[15] = site[3]
maps[25] = site[3]
maps[35] = site[3]

# công ty
maps[12] = site[4]
maps[28] = site[4]

# trộn các thẻ khí vận và cơ hội
khivans = (list(range(1, 17)))
random.shuffle(khivans)

cohois = (list(range(1, 17)))
random.shuffle(cohois)

xs = []
x = 0
for i in range(0, 40*1000000):
    # Lắc 2 xúc xắc & đi
    x = x + random.randrange(2, 13)
    if x in list_site_kv:
        command = khivans[0]
        x = khi_van(x, command)
        # Bỏ thẻ vừa bốc vào đáy
        khivans.append(khivans.pop(khivans.index(command)))
    if x in list_site_ch:
        command = cohois[0]
        x = khi_van(x, command)
        # Bỏ thẻ vừa bốc vào đáy
        cohois.append(cohois.pop(cohois.index(command)))
    if x >= 40:
        x = abs(40 - x)
    xs.append(x)

frequency = []

# Đếm tần suất các ô đã đi vào
for i in range(0, 40):
    frequency.append(xs.count(i))


# Vẽ biểu đồ thể hiện kết quả
np.asarray(xs)
frequency_nha = []
for i in list_site_nha:
    frequency_nha.append(frequency[i])

zip_iterator = zip(list_site_nha, frequency_nha)
a = dict(zip_iterator)
print(dict(sorted(a.items(), key=lambda item: item[1])))

print(len(list_site_nha))
plt.scatter(list_site_nha, frequency_nha)
for i in range(0, len(list_site_nha)):
    plt.annotate(list_site_nha[i], (list_site_nha[i] + 0.3, frequency_nha[i] + 0.3))
plt.show()
