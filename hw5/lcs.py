def LCS(X, Y):
    m = len(X)
    n = len(Y)
    dp_array = [[0 for i in range(n+1)] for j in range(m+1)]
 
    for i in range(m+1):
        for j in range(n+1):
            if i == 0 or j == 0:
                dp_array[i][j] = 0
            elif X[i-1] == Y[j-1]:
                dp_array[i][j] = dp_array[i-1][j-1] + 1
            else:
                dp_array[i][j] = max(dp_array[i-1][j], dp_array[i][j-1])
 
    index = dp_array[m][n]
 
    lcs = [""] * (index+1)
    lcs[index] = ""
 
    i = m
    j = n
    while i > 0 and j > 0:
 
        if X[i-1] == Y[j-1]:
            lcs[index-1] = X[i-1]
            i-=1
            j-=1
            index-=1
 
        elif dp_array[i-1][j] > dp_array[i][j-1]:
            i-=1
        else:
            j-=1
 
    return "".join(lcs)

if __name__ == "__main__":
    s1, s2 = input().split()
    sequence = LCS(s1, s2)
    answer = ' '.join(sequence)
    print("最大共同子整數：", answer)