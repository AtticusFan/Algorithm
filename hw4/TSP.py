import numpy as np

def TSP_branch_and_bound(matrix):
    path_length = len(matrix)
    #print(path_length)
    upper_bound = np.sum(matrix) - np.min(matrix[1])
    best_solution = (np.inf, [])
    #將stack初始化
    #         目前node,路徑,成本
    stack = [(1, [1], 0)]
    while stack:
        
        node = stack.pop()
        #print(node)
        current_node, path, cost = node
        #如果所有node都走過
        if len(path) == path_length-1:
            #cost = cost +  matrix[path[0]][path[-1]]
            #path.append(path[0])
            if current_node != 1:
                path.append(path[0])
                #print(path[-1])
                cost += matrix[current_node][path[-1]]
                #print(cost)
            if cost < best_solution[0]:
                best_solution = (cost, path)
            continue
        current_upper_bound = cost + np.min(matrix[current_node]) * (path_length - len(path))
        #如果目前upper bound沒有比較小 --> 跳過
        if current_upper_bound >= best_solution[0]:
            continue
        upper_bound = min(upper_bound, current_upper_bound)
        
        for next_node in range(1, path_length):
            if next_node in path:
                continue
            #計算新路徑與成本
            #print(next_node)
            new_path = path + [next_node]
            new_cost = cost + matrix[current_node][next_node]
            stack.append((next_node, new_path, new_cost))

    return best_solution

def get_matrix():
    file = 'test5.txt'
    adj = np.loadtxt(file, delimiter=' ', skiprows=1, dtype='int')
    with open(file) as f:
        n = int(f.readlines()[0])
    print(adj)
    matrix = np.zeros((n+1, n+1), dtype='int')
    element = 0
    print("Input matrix:")
    for i in range (1, n+1):    
        for j in range(1, n+1):
            matrix[i][j] = int(adj[element])
            element += 1
            print(matrix[i][j], end=" ")
        print()
    return matrix
if __name__ == '__main__':
    #print(get_matrix())
    result = TSP_branch_and_bound(get_matrix())
    print("Cost: ", result[0])
    path = '->'.join(str(e) for e in result[1])
    print("Path: ", path)
