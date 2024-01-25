#pip3 install opencv-python
#pip3 install -U numpy
import cv2, numpy
img_acid = cv2.imread("acid.png")
img_orig = cv2.imread("orig.png")
r = 2
g = 1
b = 0
w = len(img_acid[0])
h = len(img_acid)
diff_abs = numpy.zeros([h, w, 3])
diff_neg = numpy.zeros([h, w, 3])
diff_pos = numpy.zeros([h, w, 3])
diff_tot = numpy.zeros([h, w, 3])
diff_max = numpy.zeros([h, w, 3])
diff_min = numpy.zeros([h, w, 3])
diff_avg = numpy.zeros([h, w, 3])
for x in range(0, w):
    for y in range(0, h):
        diff_abs[y][x][r] = int(abs(float(img_acid[y][x][r]) - float(img_orig[y][x][r])))
        diff_abs[y][x][g] = int(abs(float(img_acid[y][x][g]) - float(img_orig[y][x][g])))
        diff_abs[y][x][b] = int(abs(float(img_acid[y][x][b]) - float(img_orig[y][x][b])))

        diff_neg[y][x][r] = int(max(float(img_orig[y][x][r]) - float(img_acid[y][x][r]), 0.0))
        diff_neg[y][x][g] = int(max(float(img_orig[y][x][g]) - float(img_acid[y][x][g]), 0.0))
        diff_neg[y][x][b] = int(max(float(img_orig[y][x][b]) - float(img_acid[y][x][b]), 0.0))

        diff_pos[y][x][r] = int(max(float(img_acid[y][x][r]) - float(img_orig[y][x][r]), 0.0))
        diff_pos[y][x][g] = int(max(float(img_acid[y][x][g]) - float(img_orig[y][x][g]), 0.0))
        diff_pos[y][x][b] = int(max(float(img_acid[y][x][b]) - float(img_orig[y][x][b]), 0.0))

        diff_tot[y][x][r] = int((float(diff_pos[y][x][r]) + float(diff_neg[y][x][r])) / 2.0)
        diff_tot[y][x][g] = int((float(diff_pos[y][x][g]) + float(diff_neg[y][x][g])) / 2.0)
        diff_tot[y][x][b] = int((float(diff_pos[y][x][b]) + float(diff_neg[y][x][b])) / 2.0)

        diff_max[y][x][r] = int(max(float(img_acid[y][x][r]), float(img_orig[y][x][r])))
        diff_max[y][x][g] = int(max(float(img_acid[y][x][g]), float(img_orig[y][x][g])))
        diff_max[y][x][b] = int(max(float(img_acid[y][x][b]), float(img_orig[y][x][b])))

        diff_min[y][x][r] = int(min(float(img_acid[y][x][r]), float(img_orig[y][x][r])))
        diff_min[y][x][g] = int(min(float(img_acid[y][x][g]), float(img_orig[y][x][g])))
        diff_min[y][x][b] = int(min(float(img_acid[y][x][b]), float(img_orig[y][x][b])))

        diff_avg[y][x][r] = int((float(img_acid[y][x][r]) + float(img_orig[y][x][r])) / 2.0)
        diff_avg[y][x][g] = int((float(img_acid[y][x][g]) + float(img_orig[y][x][g])) / 2.0)
        diff_avg[y][x][b] = int((float(img_acid[y][x][b]) + float(img_orig[y][x][b])) / 2.0)

cv2.imwrite("diff_abs.png", diff_abs)
cv2.imwrite("diff_neg.png", diff_neg)
cv2.imwrite("diff_pos.png", diff_pos)
cv2.imwrite("diff_tot.png", diff_tot)
cv2.imwrite("diff_max.png", diff_max)
cv2.imwrite("diff_min.png", diff_min)
cv2.imwrite("diff_avg.png", diff_avg)
print("Done!")
